/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2015-2016                                                **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  Copyright (c) 2009-2014                                                **
**  German Research School for Simulation Sciences GmbH,                   **
**  Laboratory for Parallel Programming                                    **
**                                                                         **
**  Copyright (c) 2014                                                     **
**  RWTH Aachen University, JARA-HPC                                       **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


#ifndef cube_Singleton_H
#define cube_Singleton_H

/*-------------------------------------------------------------------------*/
/**
 *  @file    CubeSingleton.h
 *  @ingroup CUBE_lib.service
 *  @brief   Definition of the class CubeSingleton
 **/
/*-------------------------------------------------------------------------*/

namespace cube
{
/*-------------------------------------------------------------------------*/
/**
 *  @class   cube::Singleton
 *  @ingroup CUBE_lib.service
 *  @brief   A class template for singlton objects;
 *
 *  A singleton class template in Alexandrescu-style, described in "Modern
 *  C++ Design, Chaper 6". This is not a full-fledged implementation as
 *  described in the book, but provides the basic singleton feature. More
 *  features, such as threading policies, may be added in the future.
 **/
/*-------------------------------------------------------------------------*/

class NoLocking
{
public:
    NoLocking()
    {
    };
    ~NoLocking()
    {
    }
};

template < class T,
           class LockingPolicy >
class Singleton : public T
{
public:
    /// @brief
    ///     Get a reference to the singleton object;
    /// @return
    ///     Object reference.
    ///
    static T&
    getInstance()
    {
        static T* mInstance;
        if ( mInstance == NULL )
        {
            LockingPolicy mutex;

            if ( mInstance == NULL )
            {
                mInstance = new T();
            }
        }
        return *mInstance;
    }
private:
    Singleton()
    {
    }

    /// @brief
    ///     Private destructor
    ///
    ~Singleton()
    {
    }
};
} /* namespace cube */

#endif /* cube_Singleton_H */
