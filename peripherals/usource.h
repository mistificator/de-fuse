/* usource.h: Routines for handling the Currah uSource interface
   Copyright (c) 2007-2016 Stuart Brady, Philip Kendall

   $Id: usource.h 5677 2016-07-09 13:58:02Z fredm $

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

   Stuart: stuart.brady@gmail.com

*/

#ifndef FUSE_USOURCE_H
#define FUSE_USOURCE_H

extern int usource_active;
extern int usource_available;

void usource_register_startup( void );

void usource_toggle( void );

int usource_unittest( void );

#endif				/* #ifndef FUSE_USOURCE_H */
