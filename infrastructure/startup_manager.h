/* startup_manager.h: handle Fuse's startup routines
   Copyright (c) 2016 Philip Kendall

   $Id$

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

#ifndef FUSE_STARTUP_MANAGER_H
#define FUSE_STARTUP_MANAGER_H

/* The modules the startup manager knows about */
typedef enum startup_manager_module {

  STARTUP_MANAGER_MODULE_AY,
  STARTUP_MANAGER_MODULE_BETA,
  STARTUP_MANAGER_MODULE_DEBUGGER,
  STARTUP_MANAGER_MODULE_DIDAKTIK,
  STARTUP_MANAGER_MODULE_DISCIPLE,
  STARTUP_MANAGER_MODULE_FDD,
  STARTUP_MANAGER_MODULE_FULLER,
  STARTUP_MANAGER_MODULE_IF1,
  STARTUP_MANAGER_MODULE_IF2,
  STARTUP_MANAGER_MODULE_KEMPMOUSE,
  STARTUP_MANAGER_MODULE_MACHINES_PERIPH,
  STARTUP_MANAGER_MODULE_MELODIK,
  STARTUP_MANAGER_MODULE_MEMORY,
  STARTUP_MANAGER_MODULE_MEMPOOL,
  STARTUP_MANAGER_MODULE_OPUS,
  STARTUP_MANAGER_MODULE_PLUSD,
  STARTUP_MANAGER_MODULE_PRINTER,
  STARTUP_MANAGER_MODULE_PROFILE,
  STARTUP_MANAGER_MODULE_PSG,
  STARTUP_MANAGER_MODULE_RZX,
  STARTUP_MANAGER_MODULE_SCLD,
  STARTUP_MANAGER_MODULE_SLT,
  STARTUP_MANAGER_MODULE_SPECCYBOOT,
  STARTUP_MANAGER_MODULE_SPECDRUM,
  STARTUP_MANAGER_MODULE_SPECTRANET,
  STARTUP_MANAGER_MODULE_SPECTRUM,
  STARTUP_MANAGER_MODULE_ULA,
  STARTUP_MANAGER_MODULE_USOURCE,
 
} startup_manager_module;

/* Callback for each module's init function */
typedef void (*startup_manager_fn)( void );

/* Initialise the startup manager itself */
void startup_manager_init( void );

/* Register an init function with the startup manager */
void startup_manager_register(
  startup_manager_module module, startup_manager_module *dependencies,
  size_t dependency_count, startup_manager_fn init_fn );

/* Register an init function with no dependencies with the startup manager */
void startup_manager_register_no_dependencies(
  startup_manager_module module, startup_manager_fn init_fn );

/* Run all the registered init functions in the right order */
int startup_manager_run( void );

#endif				/* #ifndef FUSE_STARTUP_MANAGER_H */
