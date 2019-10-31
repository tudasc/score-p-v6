/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2019                                                **
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


#ifndef CUBELIB_CONFIG_CUSTOM_H
#define CUBELIB_CONFIG_CUSTOM_H


/**
 * @file       cubelib-config-custom.h
 *
 * @brief This file gets included by config.h (resp. config-frontend.h and
 * config-backend.h) and contains supplementary macros to be used with the
 * macros in config.h.
 *
 */

#define UTILS_DEBUG_MODULES \
    UTILS_DEFINE_DEBUG_MODULE( CORE,                0 ), \
    UTILS_DEFINE_DEBUG_MODULE( CUBEPL_EXECUTION,    1 ), \
    UTILS_DEFINE_DEBUG_MODULE( CUBEPL_VARIABLES,    2 ), \
    UTILS_DEFINE_DEBUG_MODULE( CUBELIB_TOOLS,       10 )
#endif /* CONFIG_CUSTOM_H */
