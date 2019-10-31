/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2017                                                **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  Copyright (c) 2009-2015                                                **
**  German Research School for Simulation Sciences GmbH,                   **
**  Laboratory for Parallel Programming                                    **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/



#ifndef __CUBE_RANK_CALLS_H
#define __CUBE_RANK_CALLS_H

typedef pair<size_t, size_t>        CnodeThreadId; ///< Pair (cnode, thread) makes an ID.

typedef pair<double, CnodeThreadId> RankingItem;   ///< Pair (rank, ID) is a ranking item.
typedef vector<RankingItem>         Ranking;       ///<  A set of ranking items makes a ranking.



/* TODO TODO TODO
 *
 * operate on a thread/cnode level
 *
 * */
/// @cond PROTOTYPES
Ranking
find_ranking( Cube*         input,
              const string& metricname );

/// @endcond
/**
 * A "human version" of operator ">" for a ranking item. It compares a "rank" value.
 */
bool
greater_than( const RankingItem& x,
              const RankingItem& y )
{
    if ( x.first == y.first )
    {
        return x.first; // ????? (returns value? not boolean?)
    }
    else
    {
        return x.first > y.first;
    }
}
/**
 * Prints out the help how to use this tool.
 *
 */
void
usage( const char* str )
{
    cout << "usage: " << str << " [-p] [-m M] [-n N] cubefile" << endl;
    cout << "  -p  heuristically decide whether a region should be blacklisted or not\n"
         << "  -m  choose a metric\n";
    exit( EXIT_FAILURE );
};
/**
 * Calculates a average value of ranking.
 *
 * \f$ \langle rank \rangle = \frac{\sum_i rank_i}{N}  \f$
 *
 * (ranking shouldn't be empty -> devision by zero number of ranks)
 */
double
expected_value( Ranking ranking )
{
    double evalue( 0.0 );
    for ( size_t i = 0; i < ranking.size(); i++ )
    {
        evalue += ranking[ i ].first;
    }
    evalue /= ( double )ranking.size();
    return evalue;
}
/**
 * Calculates a standart deviation value of ranking. .
 *
 *********************\f$  \sigma_{rank}  = \frac{\sum_i (rank_i - \langle rank \rangle)^2}{N-1}  \f$
 *
 * (ranking shouldn't be empty -> devision by zero number of ranks)
 */
double
standard_deviation( Ranking ranking, double evalue )
{
    double stddev( 0.0 );
    for ( size_t i = 0; i < ranking.size(); i++ )
    {
        double diff = ranking[ i ].first - evalue;
        stddev += diff * diff;
    }
    stddev /= ( double )( ranking.size() - 1 );
    return stddev;
}

/**
 * Calculates a value of a normal distribution's distribution function aka gaussian function
 *
 * \f$ f(x) = \frac{1}{\sigma \sqrt{2 \pi }} \exp^{(-\frac{(x-\mu)^2}{2 \sigma^2})} \f$
 */
double
nddf( const double evalue, const double stddev, double x )
{
    x  = ( x - evalue ) / stddev;
    x *= x;
    x *= -0.5;
    x  = exp( x );
    const double s = 1.0 / ( stddev * sqrt( 2.0 * M_PI ) );
    return s * x;
}

/**
 * Calculates a value of a standard Normal distribution
 *
 ** \f$ f(x) = \frac{1}{\sqrt{2 \pi }} \exp^{(-\frac{(x)^2}{2})} \f$
 */
double
nddf( double x )
{
    x *= x;
    x *= -0.5;
    x  = exp( x );
    const double s = 1.0 / sqrt( 2.0 * M_PI );
    return s * x;
}

/** now determine the error of the approximation
 * With another words, error of integration.
 *********************Given by formula (Cavalieri-Simpson-Formula for the integration)
 *
 * \f$  E_{2,m}(f) = -\frac{b-a}{180} \bigl( \frac{H}{2}\bigr)^4 f^{(4)}(\xi) \f$
 */
double
cgfnd_error( double evalue, double stddev, double a, double b, double H )
{
    double d4_max = -1.0;
    double H4     = 0.5 * H;
    double x      = a;
    H4 *= H4;
    H4 *= H4;

    /* 1. find maximum of guassian function's 4th derivative */
    double s0 = nddf( evalue, stddev, x );
    double s1 = stddev * stddev;    // \mu^2
    double s2 = 1.0 / s1 * s1;
    double s3 = 1.0 / s1 * s2;
    double s4 = 1.0 / s2 * s2;
    double s5 = x - stddev;
    double s6 = s5 * s5;
    double s7 = s5 * s6;
    double s8 = s6 * s6;
    d4_max  = -2.0 * s4 * s7;
    d4_max += s3 * ( s8 - 4.0 * ( s6 - s5 ) );
    d4_max += 1.0 / s1;
    d4_max *= s0;
    x      += H4;

    while ( x < b )
    {
        s0 = nddf( evalue, stddev, x );
        s5 = x - stddev;
        s6 = s5 * s5;
        s7 = s5 * s6;
        s8 = s6 * s6;

        double d4 = -2.0 * s4 * s7;
        d4 += s3 * ( s8 - 4.0 * ( s6 - s5 ) );
        d4 += 1.0 / s1;
        d4 *= s0;

        if ( d4 > d4_max )
        {
            d4_max = d4;
        }
        x += H4;
    }

    /* max of gf's 4th derivative should now reside in f_max */
    /* error term found in "Numerical Mathematics" by Alfio Quarteori et al   */
    /* see page 377 */

    double error = ( a - b ) / 180.0;
    error *= H4;
    error *= d4_max;
    return error;
}


/**
 *   cummulative generating function of the normal distribution
 *   approximated by simpsons rule
 *
 *       for \f$ x_k = a + k \frac{H}{2} \f$, \f$ k=0, \dots, 2m\f$ and
   \f$ H=\frac{(b-a)}{m}\f$
 *
 *     \f$ I_{2,m}=\frac{H}{6}\left[ f(x_0) + 2 \sum_{r=1}^{m-1} f(x_{2 r}) +
   4 \sum_{s=0}^{m-1} f(x_{2 s +1}) + f(x_{2m})\right]\f$
 */
double
cgfnd( const double evalue, const double stddev,
       const double a, const double b,
       const double H = 1e-3 )
{
    unsigned int m        = ( unsigned int )floor( ( b - a ) / H );
    double       x        = a;
    const double H2       = 0.5 * H;
    double       integral = nddf( evalue, stddev, x );
    for ( size_t i = 1; i < m; i++ )
    {
        integral += 4.0 * nddf( evalue, stddev, x + H2 );
        x        += H;
        integral += 2.0 * nddf( evalue, stddev, x );
    }
    integral += 4.0 * nddf( evalue, stddev, x + H2 );
    x        += H;
    integral += nddf( evalue, stddev, x );
    integral *= ( H / 6.0 );
    return integral;
}
/**
 *   cummulative generating function of the standart normal distribution
 *   approximated by simpsons rule.
 *
 *       for \f$ x_k = a + k \frac{H}{2} \f$, \f$ k=0, \dots, 2m\f$ and
   \f$ H=\frac{(b-a)}{m} \f$
 *
 *     \f$ I_{2,m}=\frac{H}{6}\left[ f(x_0) + 2 \sum_{r=1}^{m-1} f(x_{2 r}) +
   4 \sum_{s=0}^{m-1} f(x_{2 s +1}) + f(x_{2m})\right] \f$
 */
double
cgfnd( const double a, const double b,
       const double H = 1e-3 )
{
    unsigned int m        = ( unsigned int )floor( ( b - a ) / H );
    double       x        = a;
    const double H2       = 0.5 * H;
    double       integral = nddf( x );
    for ( size_t i = 1; i < m; i++ )
    {
        integral += 4.0 * nddf( x + H2 );
        x        += H;
        integral += 2.0 * nddf( x );
    }
    integral += 4.0 * nddf( x + H2 );
    x        += H;
    integral += nddf( x );
    integral *= ( H / 6.0 );
    return integral;
}





/**
 *   Calculate a ranking. Transforms absolut rank, given by severity value into
   "gradient rank", given by the integral of standart gaussian function over
   "absolute rank +/- halfstepsize". The gradiant rank is related to the probability
   to get an absolute value of a rank. This is a probability that given region
   of code will be run.
 */
Ranking
gradient_ranking( Ranking met_ranking )
{
    /* assumes that met_ranking is sorted... */
    const size_t sz( met_ranking.size() - 1 );
    Ranking      ranking;

    cout << " sz " << sz << endl;

    ranking.reserve( sz ); /* lowest ranked item is not considered/has no gradient */
    for ( size_t i = 0; i < sz; i++ )
    {
        const double diff = met_ranking[ i ].first - met_ranking[ i + 1 ].first;
        ranking.push_back( std::make_pair( diff, met_ranking[ i ].second ) );
    }

    double evalue = expected_value( ranking );
    double stddev = standard_deviation( ranking, evalue );

    for ( size_t i = 0; i < sz; i++ )
    {
        double& val = ranking[ i ].first;
        val = ( val - evalue ) / stddev;
    }

    const double interval_length = met_ranking[ 0 ].first - met_ranking[ sz ].first;
    std::cout << "Ranking extends over " << interval_length << " units." << std::endl;
    std::cout << "...from: "
              << fixed << setprecision( 4 )
              << met_ranking[ sz ].first << std::endl;
    std::cout << ".....to: "
              << fixed << setprecision( 4 )
              << met_ranking[ 0 ].first << std::endl;

    const double stepsize = interval_length / ( double )sz;

    std::cout << "Going through interval with stepsize of "
              << fixed << setprecision( 4 )
              << stepsize << std::endl;

    std::cout << "Expected value    : "
              << fixed << setprecision( 4 )
              << evalue << std::endl;

    std::cout << "Standard deviation: "
              << fixed << setprecision( 4 )
              << stddev << std::endl;

    const double half_stepsize = stepsize * 0.5;
    for ( size_t i = 0; i < sz; i++ )
    {
        const double x = ranking[ i ].first - half_stepsize;
        const double y = x + half_stepsize;
        ranking[ i ].first = cgfnd( x, y );
    }

    std::stable_sort( ranking.begin(), ranking.end() );

    return ranking;
}





/**
   Increment of ranks. Acts only on value. No check, whether same ID.
 */
RankingItem&
operator+=( RankingItem& x, double v )
{
    x.first += v;
    return x;
}



/**
 * Creates a sorted vector of rankings. As value is the severity for some metric
   ("metricname"). Ranking contains all combinations of "cnode: thread"
 */
Ranking
find_ranking( Cube* input, const string& metricname )
{
//     const vector<Region*>&  regions = input->get_regv(); // unused
    const vector<Cnode*>&  cnodes  = input->get_cnodev();
    const vector<Thread*>& threads = input->get_thrdv();

//     const size_t rcnt = regions.size(); // unused
    const size_t tcnt = threads.size();
    const size_t ccnt = cnodes.size();

    Ranking ranking;
    ranking.reserve( tcnt * ccnt );

    Metric* metric = input->get_met( metricname );

    if ( metric != 0 )
    {
        for ( size_t cnodeId = 0; cnodeId < ccnt; cnodeId++ )
        {
            Cnode* const cnode = cnodes[ cnodeId ];
            for ( size_t threadId = 0; threadId < tcnt; threadId++ )
            {
                Thread* const thread = threads[ threadId ];
                // const Region* caller = cnodes[cnodeId]->get_caller();
                // int callerId=0;

                // if (caller !=0)
                //     callerId = caller->get_id();
                double val = input->get_sev( metric, cnode, thread );
                ranking.push_back( make_pair( val, make_pair( cnodeId, threadId ) ) );
            }
        }

        /* 2nd sort the vector */
        std::stable_sort( ranking.begin(), ranking.end(), greater_than );

        /* 3rd remove entries with zero value */
        Ranking::iterator it = ranking.begin();

        while ( ( it != ranking.end() ) && ( it->first != 0 ) )
        {
            it++;
        }

        ranking.erase( it, ranking.end() );
    }

    return ranking;
}


#endif
