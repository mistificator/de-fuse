/* didaktik.h: Routines for handling the Didaktik 40/80 disk interface
   Copyright (c) 2015 Gergely Szasz

   $Id: didaktik.h 5677 2016-07-09 13:58:02Z fredm $

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

   szaszg@hu.inter.net

*/

#ifndef FUSE_DIDAKTIK80_H
#define FUSE_DIDAKTIK80_H

#include <config.h>

#include <libspectrum.h>

#include "fdd.h"

typedef enum didaktik80_drive_number {
  DIDAKTIK80_DRIVE_A = 0,
  DIDAKTIK80_DRIVE_B,
  DIDAKTIK80_NUM_DRIVES,
} didaktik80_drive_number;

extern int didaktik80_available;  /* Is the D80/40 available for use? */
extern int didaktik80_active;     /* D80/D40 enabled? */
extern int didaktik80_snap;       /* SNAPshot pressed */

void didaktik80_register_startup( void );

void didaktik80_page( void );
void didaktik80_unpage( void );

int didaktik80_disk_insert( didaktik80_drive_number which, const char *filename,
		       int autoload );
fdd_t *didaktik80_get_fdd( didaktik80_drive_number which );

int didaktik80_unittest( void );

#endif                  /* #ifndef FUSE_DIDAKTIK80_H */
