/* event.h: Routines needed for dealing with the event list
   Copyright (c) 2000-2004 Philip Kendall

   $Id: event.h 3217 2007-10-21 21:22:07Z zubzero $

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

#ifndef FUSE_EVENT_H
#define FUSE_EVENT_H

#ifdef HAVE_LIB_GLIB
#include <glib.h>
#endif				/* #ifdef HAVE_LIB_GLIB */

#include <libspectrum.h>

/* Information about an event */
typedef struct event_t {
  libspectrum_dword tstates;
  int type;
  void *user_data;
} event_t;

/* The various types of event which can occur */
typedef enum event_type {

  EVENT_TYPE_BREAKPOINT,
  EVENT_TYPE_EDGE,
  EVENT_TYPE_FRAME,
  EVENT_TYPE_INTERRUPT,
  EVENT_TYPE_NMI,
  EVENT_TYPE_NULL,
  EVENT_TYPE_RZX_SENTINEL,
  EVENT_TYPE_BETA_INDEX,
  EVENT_TYPE_TIMER,
  EVENT_TYPE_TAPE_RECORD,
  EVENT_TYPE_PLUSD_INDEX,
  EVENT_TYPE_WD_FDC,
  EVENT_TYPE_WD_FDC_MOTOR_OFF,
  EVENT_TYPE_WD_FDC_TIMEOUT,

} event_type;

/* A large value to mean `no events due' */
extern const libspectrum_dword event_no_events;

/* When will the next event happen? */
extern libspectrum_dword event_next_event;

/* Set up the event list */
int event_init(void);

/* Add an event at the correct place in the event list */
int event_add_with_data( libspectrum_dword event_time, event_type type,
			 void *user_data );

static inline int
event_add( libspectrum_dword event_time, event_type type )
{
  return event_add_with_data( event_time, type, NULL );
}

/* Do all events which have passed */
int event_do_events(void);

/* Called at end of frame to reduce T-state count of all entries */
int event_frame( libspectrum_dword tstates_per_frame );

/* Remove all events of a specific type from the stack */
int event_remove_type( event_type type );

/* Clear the event stack */
int event_reset(void);

/* Call a user-supplied function for every event in the current list */
int event_foreach( void (*function)( gpointer data, gpointer user_data ),
		   gpointer user_data );

/* A textual representation of each event type */
const char *event_name( event_type type );

/* Called on exit to clean up */
int event_end(void);

#endif				/* #ifndef FUSE_EVENT_H */