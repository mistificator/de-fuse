/* printer.h: Printer support
   Copyright (c) 2001-2004 Ian Collier, Russell Marks, Philip Kendall

   $Id: printer.h 2993 2007-06-17 13:54:49Z pak21 $

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

   Author contact information:

   E-mail: philip-fuse@shadowmagic.org.uk

*/

#ifndef FUSE_PRINTER_H
#define FUSE_PRINTER_H

#include <libspectrum.h>

libspectrum_byte printer_zxp_read( libspectrum_word port, int *attached );
void printer_zxp_write( libspectrum_word port, libspectrum_byte b );
void printer_frame( void );
void printer_serial_write( libspectrum_byte b );
void printer_parallel_strobe_write( int on );
libspectrum_byte printer_parallel_read( libspectrum_word port, int *attached );
void printer_parallel_write( libspectrum_word port, libspectrum_byte b );
int printer_init( void );
void printer_end( void );

#endif				/* #ifndef FUSE_PRINTER_H */
