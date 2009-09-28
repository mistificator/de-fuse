/* fdd.h: Header for handling raw disk images
   Copyright (c) 2007 Gergely Szasz

   $Id: fdd.h 3312 2007-11-19 22:02:14Z zubzero $

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

   Philip: philip-fuse@shadowmagic.org.uk

*/

#ifndef FUSE_FDD_H
#define FUSE_FDD_H

#include <config.h>

#include "disk.h"

typedef enum fdd_error_t {
  FDD_OK = 0,
  FDD_GEOM,
  FDD_DATA,
  FDD_RDONLY,
  
  FDD_LAST_ERROR,
} fdd_error_t;

typedef enum fdd_type_t {
  FDD_SHUGART = 0,
  FDD_IBMPC = 1,
} fdd_type_t;

typedef enum fdd_write_t {
  FDD_READ = 0,
  FDD_WRITE,
} fdd_write_t;

typedef enum fdd_dir_t {
  FDD_STEP_OUT = 0,
  FDD_STEP_IN = 1,
} fdd_dir_t;

typedef struct fdd_t {
  fdd_type_t type;	/* fdd interface Shugart or IBMPC */
  int fdd_heads;	/* 1 or 2 */
  int fdd_cylinders;	/* 40/40+/80/80+ */

  int tr00;		/* track 0 mark */
  int index;		/* index hole */
  int wrprot;		/* write protect 0 -> write protect */
  int data;		/* read/write to data byte 0x00nn or 0xffnn */
  
  disk_t *disk;		/* pointer to inserted disk */
  int loaded;		/* disk loaded */
  int upsidedown;	/* flipped disk */
  int ready;		/* some disk drive offer a ready signal */
  
  fdd_error_t status;

/*--private section, fdc may never use it */
  int unreadable;	/* disk unreadable in this drive */
  int c_head;		/* current head (side) */
  int c_cylinder;	/* current cylinder number (0 -> TR00) */
  int motoron;		/* motor on */
  int loadhead;		/* head loaded */

} fdd_t;

const char *fdd_strerror( int error );
/* initialize the fdd_t struct, and set fdd_heads and cylinders (e.g. 2/83 ) */
int fdd_init( fdd_t *d, int heads, int cyls );
/* load the given disk into the fdd. if upsidedown = 1, floppy upsidedown in drive :) */
int fdd_load( fdd_t *d, disk_t *disk, int upsidedown );
/* unload the disk from fdd */
void fdd_unload( fdd_t *d );
/* set fdd head */
void fdd_set_head( fdd_t *d, int head );
/* step one track according to d->direction direction. set d->tr00 if reach track 0 */
void fdd_step( fdd_t *d, fdd_dir_t direction );
/* set floppy position ( upsidedown or not )*/
void fdd_motoron( fdd_t *d, int on );
/* start (1) or stop (0) spindle motor */
void fdd_head_load( fdd_t *d, int load );
/* load (1) or unload (0) head */
void fdd_flip( fdd_t *d, int upsidedown );
/* read or write next 1 byte from disk. if read, the read byte go into
   d->data, if write d->data written to disk. if d->data = 0xffnn then this
   byte recorded with different clock 'mark'. set d->idx if reach 'index hole'
   read 0x0100 if disk unreadable or not motor on and/or head not loaded.
*/
int fdd_read_write_data( fdd_t *d, fdd_write_t write );
/* set write protect status on loaded disk */
void fdd_wrprot( fdd_t *d, int wrprot );
/* to reach index hole */
void fdd_wait_index_hole( fdd_t *d );

#endif 	/* FUSE_FDD_H */
