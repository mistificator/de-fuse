/* divmmc.c: DivMMC interface routines
   Copyright (c) 2005-2017 Matthew Westcott, Philip Kendall
   Copyright (c) 2015 Stuart Brady

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

   E-mail: Philip Kendall <philip-fuse@shadowmagic.org.uk>

*/

#include <config.h>

#include <libspectrum.h>

#include <string.h>

#include "debugger/debugger.h"
#include "ide.h"
#include "infrastructure/startup_manager.h"
#include "machine.h"
#include "module.h"
#include "periph.h"
#include "settings.h"
#include "ui/ui.h"
#include "unittests/unittests.h"
#include "divmmc.h"
#include "divxxx.h"

/* Private function prototypes */

static void divmmc_control_write( libspectrum_word port, libspectrum_byte data );
static void divmmc_card_select( libspectrum_word port, libspectrum_byte data );
static libspectrum_byte divmmc_mmc_read( libspectrum_word port, libspectrum_byte *attached );
static void divmmc_mmc_write( libspectrum_word port, libspectrum_byte data );
static void divmmc_activate( void );

/* Data */

static const periph_port_t divmmc_ports[] = {
  { 0x00ff, 0x00e3, NULL, divmmc_control_write },
  { 0x00ff, 0x00e7, NULL, divmmc_card_select },
  { 0x00ff, 0x00eb, divmmc_mmc_read, divmmc_mmc_write },
  { 0, 0, NULL, NULL }
};

static const periph_t divmmc_periph = {
  /* .option = */ &settings_current.divmmc_enabled,
  /* .ports = */ divmmc_ports,
  /* .hard_reset = */ 1,
  /* .activate = */ divmmc_activate,
};

int divmmc_automapping_enabled = 0;
static divxxx_t *divmmc_state;

/* The card inserted into the DivMMC. For now, we emulate only one card. */
static libspectrum_mmc_card *card;

/* The card currently selected via the "card select" call */
static libspectrum_mmc_card *current_card;

/* *Our* DivMMC has 128 Kb of RAM - this is all that ESXDOS needs */
#define DIVMMC_PAGES 16
#define DIVMMC_PAGE_LENGTH 0x2000
static libspectrum_byte *divmmc_ram[ DIVMMC_PAGES ];
static libspectrum_byte *divmmc_eprom;
static memory_page divmmc_memory_map_eprom[ MEMORY_PAGES_IN_8K ];
static memory_page divmmc_memory_map_ram[ DIVMMC_PAGES ][ MEMORY_PAGES_IN_8K ];
static int memory_allocated = 0;
static int divmmc_memory_source_eprom;
static int divmmc_memory_source_ram;

static void divmmc_reset( int hard_reset );
static void divmmc_memory_map( void );
static void divmmc_enabled_snapshot( libspectrum_snap *snap );
static void divmmc_from_snapshot( libspectrum_snap *snap );
static void divmmc_to_snapshot( libspectrum_snap *snap );

static module_info_t divmmc_module_info = {

  /* .reset = */ divmmc_reset,
  /* .romcs = */ divmmc_memory_map,
  /* .snapshot_enabled = */ divmmc_enabled_snapshot,
  /* .snapshot_from = */ divmmc_from_snapshot,
  /* .snapshot_to = */ divmmc_to_snapshot,

};

/* Debugger events */
static const char * const event_type_string = "divmmc";

/* Housekeeping functions */

static int
divmmc_init( void *context )
{
  int i, j;

  card = libspectrum_mmc_alloc();

  /*
   TODO
  error = ide_init( divmmc_idechn0,
		    settings_current.divmmc_master_file,
		    UI_MENU_ITEM_MEDIA_IDE_DIVMMC_MASTER_EJECT,
		    settings_current.divmmc_slave_file,
		    UI_MENU_ITEM_MEDIA_IDE_DIVMMC_SLAVE_EJECT );
  if( error ) return error;
  */

  module_register( &divmmc_module_info );

  divmmc_memory_source_eprom = memory_source_register( "DivMMC EPROM" );
  divmmc_memory_source_ram = memory_source_register( "DivMMC RAM" );

  for( i = 0; i < MEMORY_PAGES_IN_8K; i++ ) {
    memory_page *page = &divmmc_memory_map_eprom[i];
    page->source = divmmc_memory_source_eprom;
    page->page_num = 0;
  }

  for( i = 0; i < DIVMMC_PAGES; i++ ) {
    for( j = 0; j < MEMORY_PAGES_IN_8K; j++ ) {
      memory_page *page = &divmmc_memory_map_ram[i][j];
      page->source = divmmc_memory_source_ram;
      page->page_num = i;
    }
  }

  periph_register( PERIPH_TYPE_DIVMMC, &divmmc_periph );

  divmmc_state = divxxx_alloc( event_type_string );

  return 0;
}

static void
divmmc_end( void )
{
  divxxx_free( divmmc_state );
  libspectrum_mmc_free( card );
}

void
divmmc_register_startup( void )
{
  startup_manager_module dependencies[] = {
    STARTUP_MANAGER_MODULE_DEBUGGER,
    STARTUP_MANAGER_MODULE_DISPLAY,
    STARTUP_MANAGER_MODULE_MEMORY,
    STARTUP_MANAGER_MODULE_SETUID,
  };
  startup_manager_register( STARTUP_MANAGER_MODULE_DIVMMC, dependencies,
                            ARRAY_SIZE( dependencies ), divmmc_init, NULL,
                            divmmc_end );
}

/* DivMMC does not page in immediately on a reset condition (we do that by
   trapping PC instead); however, it needs to perform housekeeping tasks upon
   reset */
static void
divmmc_reset( int hard_reset )
{
  divxxx_reset( divmmc_state, settings_current.divmmc_enabled, settings_current.divmmc_wp, hard_reset );

  /*
   TODO
  libspectrum_ide_reset( divmmc_idechn0 );
  libspectrum_ide_reset( divmmc_idechn1 );
  */
}

/* TODO: merge this with ide_eject() */
static int
mmc_eject( libspectrum_mmc_card *card )
{
  int error;

  if( libspectrum_mmc_dirty( card ) ) {
    
    ui_confirm_save_t confirm = ui_confirm_save(
      "Card has been modified.\nDo you want to save it?"
    );
  
    switch( confirm ) {

    case UI_CONFIRM_SAVE_SAVE: libspectrum_mmc_commit( card ); break;
    case UI_CONFIRM_SAVE_DONTSAVE: break;
    case UI_CONFIRM_SAVE_CANCEL: return 1;

    }
  }

  libspectrum_free( settings_current.divmmc_master_file );
  settings_current.divmmc_master_file = NULL;
  
  libspectrum_mmc_eject( card );

  error = ui_menu_activate( UI_MENU_ITEM_MEDIA_IDE_DIVMMC_MASTER_EJECT, 0 );
  if( error ) return error;

  return 0;
}

int
divmmc_insert( const char *filename )
{
  int error;

  /* Remove any currently inserted card; abort if we want to keep the current
     card */
  if( settings_current.divmmc_master_file )
    if( mmc_eject( card ) )
      return 0;

  settings_set_string( &settings_current.divmmc_master_file, filename );

  error = libspectrum_mmc_insert( card, filename );
  if( error ) return error;
  return ui_menu_activate( UI_MENU_ITEM_MEDIA_IDE_DIVMMC_MASTER_EJECT, 1 );
}
  
void
divmmc_commit( void )
{
  libspectrum_mmc_commit( card );
}

int
divmmc_eject( void )
{
  return mmc_eject( card );
}

/* Port read/writes */

static void
divmmc_control_write( libspectrum_word port GCC_UNUSED, libspectrum_byte data )
{
  divxxx_control_write( divmmc_state, data, settings_current.divmmc_wp );
}

static void
divmmc_card_select( libspectrum_word port GCC_UNUSED, libspectrum_byte data )
{
  printf("divmmc_card_select( 0x%02x )\n", data );

  switch( data ) {
    case 0xf6:
      current_card = card;
      break;
    default:
      current_card = NULL;
      break;
  }
}

static libspectrum_byte
divmmc_mmc_read( libspectrum_word port GCC_UNUSED, libspectrum_byte *attached )
{
  *attached = 0xff;

  return current_card ? libspectrum_mmc_read( card ) : 0xff;
}

static void
divmmc_mmc_write( libspectrum_word port GCC_UNUSED, libspectrum_byte data )
{
  if( current_card ) libspectrum_mmc_write( card, data );
}

void
divmmc_set_automap( int state )
{
  divxxx_set_automap( divmmc_state, state, settings_current.divmmc_wp );
}

void
divmmc_refresh_page_state( void )
{
  divxxx_refresh_page_state( divmmc_state, settings_current.divmmc_wp );
}

void
divmmc_memory_map( void )
{
  divxxx_memory_map( divmmc_state, settings_current.divmmc_wp, DIVMMC_PAGES, divmmc_memory_map_eprom, divmmc_memory_map_ram );
}

static void
divmmc_enabled_snapshot( libspectrum_snap *snap )
{
  /* TODO: not going to work yet!

  if( libspectrum_snap_divmmc_active( snap ) )
    settings_current.divmmc_enabled = 1;

  */
}

static void
divmmc_from_snapshot( libspectrum_snap *snap )
{
  /* TODO: not going to work yet!

  size_t i;

  if( !libspectrum_snap_divmmc_active( snap ) ) return;

  settings_current.divmmc_wp =
    libspectrum_snap_divmmc_eprom_writeprotect( snap );
  divmmc_control_write_internal( libspectrum_snap_divmmc_control( snap ) );

  if( libspectrum_snap_divmmc_eprom( snap, 0 ) ) {
    memcpy( divmmc_eprom,
	    libspectrum_snap_divmmc_eprom( snap, 0 ), DIVMMC_PAGE_LENGTH );
  }

  for( i = 0; i < libspectrum_snap_divmmc_pages( snap ); i++ )
    if( libspectrum_snap_divmmc_ram( snap, i ) )
      memcpy( divmmc_ram[ i ], libspectrum_snap_divmmc_ram( snap, i ),
	      DIVMMC_PAGE_LENGTH );

  if( libspectrum_snap_divmmc_paged( snap ) ) {
    divmmc_page();
  } else {
    divmmc_unpage();
  }

  */
}

static void
divmmc_to_snapshot( libspectrum_snap *snap )
{
  /* TODO: not going to work yet!

  size_t i;
  libspectrum_byte *buffer;

  if( !settings_current.divmmc_enabled ) return;

  libspectrum_snap_set_divmmc_active( snap, 1 );
  libspectrum_snap_set_divmmc_eprom_writeprotect( snap,
                                                  settings_current.divmmc_wp );
  libspectrum_snap_set_divmmc_paged( snap, divmmc_active );
  libspectrum_snap_set_divmmc_control( snap, divmmc_control );

  buffer = libspectrum_new( libspectrum_byte, DIVMMC_PAGE_LENGTH );

  memcpy( buffer, divmmc_eprom, DIVMMC_PAGE_LENGTH );
  libspectrum_snap_set_divmmc_eprom( snap, 0, buffer );

  libspectrum_snap_set_divmmc_pages( snap, DIVMMC_PAGES );

  for( i = 0; i < DIVMMC_PAGES; i++ ) {

    buffer = libspectrum_new( libspectrum_byte, DIVMMC_PAGE_LENGTH );

    memcpy( buffer, divmmc_ram[ i ], DIVMMC_PAGE_LENGTH );
    libspectrum_snap_set_divmmc_ram( snap, i, buffer );
  }

  */
}

static void
divmmc_activate( void )
{
  if( !memory_allocated ) {
    int i, j;
    libspectrum_byte *memory =
      memory_pool_allocate_persistent( DIVMMC_PAGES * DIVMMC_PAGE_LENGTH, 1 );

    for( i = 0; i < DIVMMC_PAGES; i++ ) {
      divmmc_ram[i] = memory + i * DIVMMC_PAGE_LENGTH;
      for( j = 0; j < MEMORY_PAGES_IN_8K; j++ ) {
        memory_page *page = &divmmc_memory_map_ram[i][j];
        page->page = divmmc_ram[i] + j * MEMORY_PAGE_SIZE;
        page->offset = j * MEMORY_PAGE_SIZE;
      }
    }

    divmmc_eprom = memory_pool_allocate_persistent( DIVMMC_PAGE_LENGTH, 1 );
    for( i = 0; i < MEMORY_PAGES_IN_8K; i++ ) {
      memory_page *page = &divmmc_memory_map_eprom[i];
      page->page = divmmc_eprom + i * MEMORY_PAGE_SIZE;
      page->offset = i * MEMORY_PAGE_SIZE;
    }

    memory_allocated = 1;
  }
}

int
divmmc_unittest( void )
{
  int r = 0;

  divmmc_set_automap( 1 );

  divmmc_control_write( 0x00e3, 0x80 );
  r += unittests_assert_8k_page( 0x0000, divmmc_memory_source_eprom, 0 );
  r += unittests_assert_8k_page( 0x2000, divmmc_memory_source_ram, 0 );
  r += unittests_assert_16k_ram_page( 0x4000, 5 );
  r += unittests_assert_16k_ram_page( 0x8000, 2 );
  r += unittests_assert_16k_ram_page( 0xc000, 0 );

  divmmc_control_write( 0x00e3, 0x83 );
  r += unittests_assert_8k_page( 0x0000, divmmc_memory_source_eprom, 0 );
  r += unittests_assert_8k_page( 0x2000, divmmc_memory_source_ram, 3 );
  r += unittests_assert_16k_ram_page( 0x4000, 5 );
  r += unittests_assert_16k_ram_page( 0x8000, 2 );
  r += unittests_assert_16k_ram_page( 0xc000, 0 );

  divmmc_control_write( 0x00e3, 0x40 );
  r += unittests_assert_8k_page( 0x0000, divmmc_memory_source_ram, 3 );
  r += unittests_assert_8k_page( 0x2000, divmmc_memory_source_ram, 0 );
  r += unittests_assert_16k_ram_page( 0x4000, 5 );
  r += unittests_assert_16k_ram_page( 0x8000, 2 );
  r += unittests_assert_16k_ram_page( 0xc000, 0 );

  divmmc_control_write( 0x00e3, 0x02 );
  r += unittests_assert_8k_page( 0x0000, divmmc_memory_source_ram, 3 );
  r += unittests_assert_8k_page( 0x2000, divmmc_memory_source_ram, 2 );
  r += unittests_assert_16k_ram_page( 0x4000, 5 );
  r += unittests_assert_16k_ram_page( 0x8000, 2 );
  r += unittests_assert_16k_ram_page( 0xc000, 0 );

  /* We have only 128 Kb of RAM (16 x 8 Kb pages), so setting all of bits 0-5
     results in page 15 being selected */
  divmmc_control_write( 0x00e3, 0x3f );
  r += unittests_assert_8k_page( 0x0000, divmmc_memory_source_ram, 3 );
  r += unittests_assert_8k_page( 0x2000, divmmc_memory_source_ram, 15 );
  r += unittests_assert_16k_ram_page( 0x4000, 5 );
  r += unittests_assert_16k_ram_page( 0x8000, 2 );
  r += unittests_assert_16k_ram_page( 0xc000, 0 );

  divmmc_set_automap( 0 );

  r += unittests_paging_test_48( 2 );

  return r;
}
