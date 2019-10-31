/*
 * This file is part of the Score-P software (http://www.score-p.org)
 *
 * Copyright (c) 2009-2013,
 * RWTH Aachen University, Germany
 *
 * Copyright (c) 2009-2013,
 * Gesellschaft fuer numerische Simulation mbH Braunschweig, Germany
 *
 * Copyright (c) 2009-2014, 2016,
 * Technische Universitaet Dresden, Germany
 *
 * Copyright (c) 2009-2013,
 * University of Oregon, Eugene, USA
 *
 * Copyright (c) 2009-2013,
 * Forschungszentrum Juelich GmbH, Germany
 *
 * Copyright (c) 2009-2013,
 * German Research School for Simulation Sciences GmbH, Juelich/Aachen, Germany
 *
 * Copyright (c) 2009-2013,
 * Technische Universitaet Muenchen, Germany
 *
 * This software may be modified and distributed under the terms of
 * a BSD-style license.  See the COPYING file in the package base
 * directory for details.
 *
 */

@otf2 with max_name_length = 0
@otf2  for def in defs:
@otf2   if def.upper|length > max_name_length:
@otf2    set max_name_length = def.upper|length
@otf2   endif
@otf2   if loop.last:
/** @internal
 *  @brief width of the column with the definition names. */
static int otf2_DEF_COLUMN_WIDTH = @@max_name_length@@;
@otf2   endif
@otf2  endfor
@otf2 endwith

@otf2 with max_name_length = 0
@otf2  for event in events + snaps:
@otf2   if event.upper|length > max_name_length:
@otf2    set max_name_length = event.upper|length
@otf2   endif
@otf2   if loop.last:
/** @internal
 *  @brief width of the column with the event names. */
static int otf2_EVENT_COLUMN_WIDTH = @@max_name_length@@;
@otf2   endif
@otf2  endfor
@otf2 endwith

@otf2 with max_known_paradigm = 0
@otf2  for paradigm in Paradigm.entries:
@otf2   if paradigm.value > max_known_paradigm:
@otf2    set max_known_paradigm = paradigm.value
@otf2   endif
@otf2   if loop.last:
/** @internal
 *  @brief max value of an OTF2_Paradigm entry + 1. */
static int otf2_max_known_paradigm = @@max_known_paradigm@@ + 1;
@otf2   endif
@otf2  endfor
@otf2 endwith
@otf2 for enum in enums:

static inline const char*
otf2_print_get_@@enum.lower@@( @@enum.type@@ @@enum.lname@@ )
{
    @otf2 if enum is bitset_enum:
    size_t buffer_size =
        2 + ( 2 * @@enum.entries|length@@ )
        @otf2 for entry in enum.entries:
        + sizeof( "@@entry.suffix@@" )
        @otf2 endfor
        + 1 + sizeof( "INVALID <0x00000000>" );
    char* buffer = otf2_print_get_buffer( buffer_size );

    buffer[ 0 ] = '\0';
    @otf2 with skip_none_entry = 0
    @otf2 if enum.entries[0].suffix == 'NONE':
    @otf2 set skip_none_entry = 1
    if ( @@enum.lname@@ == @@enum.prefix@@NONE )
    {
        strcat( buffer, "NONE" );
        return buffer;
    }

    @otf2 endif
    const char* sep    = "";
    strcat( buffer, "{" );
    @otf2 for entry in enum.entries[skip_none_entry:]:
    if ( @@enum.lname@@ & @@entry.name@@ )
    {
        strcat( buffer, sep );
        strcat( buffer, "@@entry.suffix@@" );
        sep = ", ";
        @@enum.lname@@ &= ~@@entry.name@@;
    }
    @otf2 endfor
    @otf2 endwith
    if ( @@enum.lname@@ )
    {
        snprintf( buffer + strlen( buffer ),
                  2 + sizeof( "INVALID <0x00000000>" ),
                  "%sINVALID <0x%" PRIx32 ">",
                  sep, @@enum.lname@@ );
    }
    strcat( buffer, "}" );

    return buffer;
    @otf2 else:
    switch ( @@enum.lname@@ )
    {
        @otf2 for entry in enum.entries:
        case @@entry.name@@:
            return "@@entry.suffix@@";
        @otf2 endfor

        default:
            return otf2_print_get_invalid( @@enum.lname@@ );
    }
    @otf2 endif
}

@otf2 endfor
