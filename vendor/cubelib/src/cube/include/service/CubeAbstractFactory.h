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


#ifndef CUBE_ABSTRACTFACTORY_H
#define CUBE_ABSTRACTFACTORY_H

#include <map>

/**
 * @file CubeAbstractFactory.h
 * @ingroup CUBE_lib.service
 * @brief Declaration of the class cube::AbstractFactory.
 */

namespace cube
{

/** @class cube::AbstractFactory
 *  @brief An abstract factory class to create generic objects.
 */
template < class ProductType,
        typename KeyType,
        typename FactoryCallback = ProductType* (*)() >
class AbstractFactory
{
    public:
        /// Registry container
        typedef std::map< KeyType, FactoryCallback > registry_t;

        /// Explicitly virtual constructor
        virtual ~AbstractFactory() = default;

        /// Create a concrete object based on key
        ProductType*
        create( const KeyType& key ) const
                {
            registry_t::const_iterator func = mRegistry.find( key );
            if (func == mRegistry.end())
            {
                throw NetworkError( "Use of unregistered key." );
            }

            return ( *func() );
        }

        /**
         * Register a factory callback for a given key
         * @param key Identifier for factory callback.
         * @param callback Callback function that creates a
         * @return
         */
        bool
        registerCallback( const KeyType&  key,
                          FactoryCallback callback )
        {
            return mRegistry.insert( make_pair( key, callback ) );
        }

        /**
         * Unregister a factory callback for certain key
         * @param key Identifier of callback to be unregistered.
         * @return True if callback was registered and successfully unsubscribed.
         */
        bool
        unregisterCallback( const KeyType& key )
        {
            return ( mRegistry.erase( key ) == 1 );
        }

    private:
        /// Registry of factory callbacks
        registry_t mRegistry;
};

} /* namespace cube */

#endif /* CUBE_ABSTRACTFACTORY_H */
