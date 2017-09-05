/* menu_data.c: menu structure for Fuse
   Copyright (c) 2004-2007 Philip Kendall, Stuart Brady, Marek Januszewski

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

/* This file is autogenerated from menu_data.dat by ./menu_data.pl.
   Any changes made here will not be preserved. */

#include <config.h>

#include "menu.h"

#include "ui/win32/menu_data.h"

int handle_menu( DWORD cmd, HWND window )
{
  switch( cmd )
  {
    case IDM_MENU_FILE_OPEN:
      menu_file_open( 0 ); return 0;
    case IDM_MENU_FILE_SAVESNAPSHOT:
      menu_file_savesnapshot( 0 ); return 0;
    case IDM_MENU_FILE_RECORDING_RECORD:
      menu_file_recording_record( 0 ); return 0;
    case IDM_MENU_FILE_RECORDING_RECORDFROMSNAPSHOT:
      menu_file_recording_recordfromsnapshot( 0 ); return 0;
    case IDM_MENU_FILE_RECORDING_CONTINUERECORDING:
      menu_file_recording_continuerecording( 0 ); return 0;
    case IDM_MENU_FILE_RECORDING_INSERTSNAPSHOT:
      menu_file_recording_insertsnapshot( 0 ); return 0;
    case IDM_MENU_FILE_RECORDING_ROLLBACK:
      menu_file_recording_rollback( 0 ); return 0;
    case IDM_MENU_FILE_RECORDING_ROLLBACKTO:
      menu_file_recording_rollbackto( 0 ); return 0;
    case IDM_MENU_FILE_RECORDING_PLAY:
      menu_file_recording_play( 0 ); return 0;
    case IDM_MENU_FILE_RECORDING_STOP:
      menu_file_recording_stop( 0 ); return 0;
    case IDM_MENU_FILE_RECORDING_FINALISE:
      menu_file_recording_finalise( 0 ); return 0;
    case IDM_MENU_FILE_AYLOGGING_RECORD:
      menu_file_aylogging_record( 0 ); return 0;
    case IDM_MENU_FILE_AYLOGGING_STOP:
      menu_file_aylogging_stop( 0 ); return 0;
    case IDM_MENU_FILE_SCREENSHOT_OPENSCRSCREENSHOT:
      menu_file_screenshot_openscrscreenshot( 0 ); return 0;
    case IDM_MENU_FILE_SCREENSHOT_SAVESCREENASSCR:
      menu_file_screenshot_savescreenasscr( 0 ); return 0;
    case IDM_MENU_FILE_SCREENSHOT_OPENMLTSCREENSHOT:
      menu_file_screenshot_openmltscreenshot( 0 ); return 0;
    case IDM_MENU_FILE_SCREENSHOT_SAVESCREENASMLT:
      menu_file_screenshot_savescreenasmlt( 0 ); return 0;
    case IDM_MENU_FILE_SCREENSHOT_SAVESCREENASPNG:
      menu_file_screenshot_savescreenaspng( 0 ); return 0;
    case IDM_MENU_FILE_MOVIE_RECORD:
      menu_file_movie_record( 0 ); return 0;
    case IDM_MENU_FILE_MOVIE_RECORDFROMRZX:
      menu_file_movie_record_recordfromrzx( 0 ); return 0;
    case IDM_MENU_FILE_MOVIE_PAUSE:
      menu_file_movie_pause( 0 ); return 0;
    case IDM_MENU_FILE_MOVIE_CONTINUE:
      menu_file_movie_pause( 0 ); return 0;
    case IDM_MENU_FILE_MOVIE_STOP:
      menu_file_movie_stop( 0 ); return 0;
    case IDM_MENU_FILE_LOADBINARYDATA:
      menu_file_loadbinarydata( 0 ); return 0;
    case IDM_MENU_FILE_SAVEBINARYDATA:
      menu_file_savebinarydata( 0 ); return 0;
    case IDM_MENU_FILE_EXIT:
      menu_file_exit( 0 ); return 0;
    case IDM_MENU_OPTIONS_GENERAL:
      menu_options_general( 0 ); return 0;
    case IDM_MENU_OPTIONS_MEDIA:
      menu_options_media( 0 ); return 0;
    case IDM_MENU_OPTIONS_SOUND:
      menu_options_sound( 0 ); return 0;
    case IDM_MENU_OPTIONS_PERIPHERALS_GENERAL:
      menu_options_peripherals_general( 0 ); return 0;
    case IDM_MENU_OPTIONS_PERIPHERALS_DISK:
      menu_options_peripherals_disk( 0 ); return 0;
    case IDM_MENU_OPTIONS_RZX:
      menu_options_rzx( 0 ); return 0;
    case IDM_MENU_OPTIONS_MOVIE:
      menu_options_movie( 0 ); return 0;
    case IDM_MENU_OPTIONS_JOYSTICKS_KEYBOARD:
      menu_options_joysticks_select( 3 ); return 0;
    case IDM_MENU_OPTIONS_SELECTROMS_MACHINEROMS_SPECTRUM16K:
      menu_options_selectroms_machine_select( 1 ); return 0;
    case IDM_MENU_OPTIONS_SELECTROMS_MACHINEROMS_SPECTRUM48K:
      menu_options_selectroms_machine_select( 2 ); return 0;
    case IDM_MENU_OPTIONS_SELECTROMS_MACHINEROMS_SPECTRUM128K:
      menu_options_selectroms_machine_select( 3 ); return 0;
    case IDM_MENU_OPTIONS_SELECTROMS_MACHINEROMS_SPECTRUM2:
      menu_options_selectroms_machine_select( 4 ); return 0;
    case IDM_MENU_OPTIONS_SELECTROMS_MACHINEROMS_SPECTRUM2A:
      menu_options_selectroms_machine_select( 5 ); return 0;
    case IDM_MENU_OPTIONS_SELECTROMS_MACHINEROMS_SPECTRUM3:
      menu_options_selectroms_machine_select( 6 ); return 0;
    case IDM_MENU_OPTIONS_SELECTROMS_MACHINEROMS_SPECTRUM3E:
      menu_options_selectroms_machine_select( 7 ); return 0;
    case IDM_MENU_OPTIONS_SELECTROMS_MACHINEROMS_TIMEXTC2048:
      menu_options_selectroms_machine_select( 8 ); return 0;
    case IDM_MENU_OPTIONS_SELECTROMS_MACHINEROMS_TIMEXTC2068:
      menu_options_selectroms_machine_select( 9 ); return 0;
    case IDM_MENU_OPTIONS_SELECTROMS_MACHINEROMS_TIMEXTS2068:
      menu_options_selectroms_machine_select( 10 ); return 0;
    case IDM_MENU_OPTIONS_SELECTROMS_MACHINEROMS_PENTAGON128K:
      menu_options_selectroms_machine_select( 11 ); return 0;
    case IDM_MENU_OPTIONS_SELECTROMS_MACHINEROMS_PENTAGON512K:
      menu_options_selectroms_machine_select( 12 ); return 0;
    case IDM_MENU_OPTIONS_SELECTROMS_MACHINEROMS_PENTAGON1024K:
      menu_options_selectroms_machine_select( 13 ); return 0;
    case IDM_MENU_OPTIONS_SELECTROMS_MACHINEROMS_SCORPIONZS256:
      menu_options_selectroms_machine_select( 14 ); return 0;
    case IDM_MENU_OPTIONS_SELECTROMS_MACHINEROMS_SPECTRUMSE:
      menu_options_selectroms_machine_select( 15 ); return 0;
    case IDM_MENU_OPTIONS_SELECTROMS_PERIPHERALROMS_INTERFACE1:
      menu_options_selectroms_peripheral_select( 1 ); return 0;
    case IDM_MENU_OPTIONS_SELECTROMS_PERIPHERALROMS_BETA128:
      menu_options_selectroms_peripheral_select( 2 ); return 0;
    case IDM_MENU_OPTIONS_SELECTROMS_PERIPHERALROMS_D:
      menu_options_selectroms_peripheral_select( 3 ); return 0;
    case IDM_MENU_OPTIONS_SELECTROMS_PERIPHERALROMS_DIDAKTIK80:
      menu_options_selectroms_peripheral_select( 4 ); return 0;
    case IDM_MENU_OPTIONS_SELECTROMS_PERIPHERALROMS_DISCIPLE:
      menu_options_selectroms_peripheral_select( 5 ); return 0;
    case IDM_MENU_OPTIONS_SELECTROMS_PERIPHERALROMS_MULTIFACEONE:
      menu_options_selectroms_peripheral_select( 6 ); return 0;
    case IDM_MENU_OPTIONS_SELECTROMS_PERIPHERALROMS_MULTIFACE128:
      menu_options_selectroms_peripheral_select( 7 ); return 0;
    case IDM_MENU_OPTIONS_SELECTROMS_PERIPHERALROMS_MULTIFACE3:
      menu_options_selectroms_peripheral_select( 8 ); return 0;
    case IDM_MENU_OPTIONS_SELECTROMS_PERIPHERALROMS_OPUSDISCOVERY:
      menu_options_selectroms_peripheral_select( 9 ); return 0;
    case IDM_MENU_OPTIONS_SELECTROMS_PERIPHERALROMS_SPECCYBOOT:
      menu_options_selectroms_peripheral_select( 10 ); return 0;
    case IDM_MENU_OPTIONS_SELECTROMS_PERIPHERALROMS_USOURCE:
      menu_options_selectroms_peripheral_select( 11 ); return 0;
    case IDM_MENU_OPTIONS_FILTER:
      menu_options_filter( 0 ); return 0;
    case IDM_MENU_OPTIONS_DISKOPTIONS:
      menu_options_diskoptions( 0 ); return 0;
    case IDM_MENU_OPTIONS_SAVE:
      menu_options_save( 0 ); return 0;
    case IDM_MENU_MACHINE_PAUSE:
      menu_machine_pause( 0 ); return 0;
    case IDM_MENU_MACHINE_RESET:
      menu_machine_reset( 0 ); return 0;
    case IDM_MENU_MACHINE_HARDRESET:
      menu_machine_reset( 1 ); return 0;
    case IDM_MENU_MACHINE_SELECT:
      menu_machine_select( 0 ); return 0;
    case IDM_MENU_MACHINE_DEBUGGER:
      menu_machine_debugger( 0 ); return 0;
    case IDM_MENU_MACHINE_POKEFINDER:
      menu_machine_pokefinder( 0 ); return 0;
    case IDM_MENU_MACHINE_POKEMEMORY:
      menu_machine_pokememory( 0 ); return 0;
    case IDM_MENU_MACHINE_MEMORYBROWSER:
      menu_machine_memorybrowser( 0 ); return 0;
    case IDM_MENU_MACHINE_PROFILER_START:
      menu_machine_profiler_start( 0 ); return 0;
    case IDM_MENU_MACHINE_PROFILER_STOP:
      menu_machine_profiler_stop( 0 ); return 0;
    case IDM_MENU_MACHINE_NMI:
      menu_machine_nmi( 0 ); return 0;
    case IDM_MENU_MACHINE_MULTIFACEREDBUTTON:
      menu_machine_multifaceredbutton( 0 ); return 0;
    case IDM_MENU_MACHINE_DIDAKTIKSNAP:
      menu_machine_didaktiksnap( 0 ); return 0;
    case IDM_MENU_MEDIA_TAPE_OPEN:
      menu_media_tape_open( 0 ); return 0;
    case IDM_MENU_MEDIA_TAPE_PLAY:
      menu_media_tape_play( 0 ); return 0;
    case IDM_MENU_MEDIA_TAPE_BROWSE:
      menu_media_tape_browse( 0 ); return 0;
    case IDM_MENU_MEDIA_TAPE_REWIND:
      menu_media_tape_rewind( 0 ); return 0;
    case IDM_MENU_MEDIA_TAPE_CLEAR:
      menu_media_tape_clear( 0 ); return 0;
    case IDM_MENU_MEDIA_TAPE_WRITE:
      menu_media_tape_write( 0 ); return 0;
    case IDM_MENU_MEDIA_TAPE_RECORDSTART:
      menu_media_tape_recordstart( 0 ); return 0;
    case IDM_MENU_MEDIA_TAPE_RECORDSTOP:
      menu_media_tape_recordstop( 0 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE1_INSERTNEW:
      menu_media_insert_new( 0x31 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE1_INSERT:
      menu_media_insert( 0x31 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE1_EJECT:
      menu_media_eject( 0x31 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE1_SAVE:
      menu_media_save( 0x031 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE1_SAVEAS:
      menu_media_save( 0x131 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE1_WRITEPROTECT_ENABLE:
      menu_media_writeprotect( 0x131 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE1_WRITEPROTECT_DISABLE:
      menu_media_writeprotect( 0x031 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE2_INSERTNEW:
      menu_media_insert_new( 0x32 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE2_INSERT:
      menu_media_insert( 0x32 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE2_EJECT:
      menu_media_eject( 0x32 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE2_SAVE:
      menu_media_save( 0x032 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE2_SAVEAS:
      menu_media_save( 0x132 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE2_WRITEPROTECT_ENABLE:
      menu_media_writeprotect( 0x132 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE2_WRITEPROTECT_DISABLE:
      menu_media_writeprotect( 0x032 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE3_INSERTNEW:
      menu_media_insert_new( 0x33 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE3_INSERT:
      menu_media_insert( 0x33 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE3_EJECT:
      menu_media_eject( 0x33 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE3_SAVE:
      menu_media_save( 0x033 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE3_SAVEAS:
      menu_media_save( 0x133 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE3_WRITEPROTECT_ENABLE:
      menu_media_writeprotect( 0x133 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE3_WRITEPROTECT_DISABLE:
      menu_media_writeprotect( 0x033 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE4_INSERTNEW:
      menu_media_insert_new( 0x34 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE4_INSERT:
      menu_media_insert( 0x34 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE4_EJECT:
      menu_media_eject( 0x34 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE4_SAVE:
      menu_media_save( 0x034 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE4_SAVEAS:
      menu_media_save( 0x134 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE4_WRITEPROTECT_ENABLE:
      menu_media_writeprotect( 0x134 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE4_WRITEPROTECT_DISABLE:
      menu_media_writeprotect( 0x034 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE5_INSERTNEW:
      menu_media_insert_new( 0x35 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE5_INSERT:
      menu_media_insert( 0x35 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE5_EJECT:
      menu_media_eject( 0x35 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE5_SAVE:
      menu_media_save( 0x035 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE5_SAVEAS:
      menu_media_save( 0x135 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE5_WRITEPROTECT_ENABLE:
      menu_media_writeprotect( 0x135 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE5_WRITEPROTECT_DISABLE:
      menu_media_writeprotect( 0x035 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE6_INSERTNEW:
      menu_media_insert_new( 0x36 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE6_INSERT:
      menu_media_insert( 0x36 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE6_EJECT:
      menu_media_eject( 0x36 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE6_SAVE:
      menu_media_save( 0x036 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE6_SAVEAS:
      menu_media_save( 0x136 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE6_WRITEPROTECT_ENABLE:
      menu_media_writeprotect( 0x136 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE6_WRITEPROTECT_DISABLE:
      menu_media_writeprotect( 0x036 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE7_INSERTNEW:
      menu_media_insert_new( 0x37 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE7_INSERT:
      menu_media_insert( 0x37 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE7_EJECT:
      menu_media_eject( 0x37 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE7_SAVE:
      menu_media_save( 0x037 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE7_SAVEAS:
      menu_media_save( 0x137 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE7_WRITEPROTECT_ENABLE:
      menu_media_writeprotect( 0x137 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE7_WRITEPROTECT_DISABLE:
      menu_media_writeprotect( 0x037 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE8_INSERTNEW:
      menu_media_insert_new( 0x38 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE8_INSERT:
      menu_media_insert( 0x38 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE8_EJECT:
      menu_media_eject( 0x38 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE8_SAVE:
      menu_media_save( 0x038 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE8_SAVEAS:
      menu_media_save( 0x138 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE8_WRITEPROTECT_ENABLE:
      menu_media_writeprotect( 0x138 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_MICRODRIVE8_WRITEPROTECT_DISABLE:
      menu_media_writeprotect( 0x038 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_RS232_PLUGRXD:
      menu_media_if1_rs232( 0x01 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_RS232_UNPLUGRXD:
      menu_media_if1_rs232( 0x11 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_RS232_PLUGTXD:
      menu_media_if1_rs232( 0x02 ); return 0;
    case IDM_MENU_MEDIA_INTERFACE1_RS232_UNPLUGTXD:
      menu_media_if1_rs232( 0x12 ); return 0;
    case IDM_MENU_MEDIA_DISK_3_DRIVEA_INSERTNEW:
      menu_media_insert_new( 0x01 ); return 0;
    case IDM_MENU_MEDIA_DISK_3_DRIVEA_INSERT:
      menu_media_insert( 0x01 ); return 0;
    case IDM_MENU_MEDIA_DISK_3_DRIVEA_EJECT:
      menu_media_eject( 0x01 ); return 0;
    case IDM_MENU_MEDIA_DISK_3_DRIVEA_SAVE:
      menu_media_save( 0x001 ); return 0;
    case IDM_MENU_MEDIA_DISK_3_DRIVEA_SAVEAS:
      menu_media_save( 0x101 ); return 0;
    case IDM_MENU_MEDIA_DISK_3_DRIVEA_FLIPDISK_TURNUPSIDEDOWN:
      menu_media_flip( 0x101 ); return 0;
    case IDM_MENU_MEDIA_DISK_3_DRIVEA_FLIPDISK_TURNBACK:
      menu_media_flip( 0x001 ); return 0;
    case IDM_MENU_MEDIA_DISK_3_DRIVEA_WRITEPROTECT_ENABLE:
      menu_media_writeprotect( 0x101 ); return 0;
    case IDM_MENU_MEDIA_DISK_3_DRIVEA_WRITEPROTECT_DISABLE:
      menu_media_writeprotect( 0x001 ); return 0;
    case IDM_MENU_MEDIA_DISK_3_DRIVEB_INSERTNEW:
      menu_media_insert_new( 0x02 ); return 0;
    case IDM_MENU_MEDIA_DISK_3_DRIVEB_INSERT:
      menu_media_insert( 0x02 ); return 0;
    case IDM_MENU_MEDIA_DISK_3_DRIVEB_EJECT:
      menu_media_eject( 0x02 ); return 0;
    case IDM_MENU_MEDIA_DISK_3_DRIVEB_SAVE:
      menu_media_save( 0x002 ); return 0;
    case IDM_MENU_MEDIA_DISK_3_DRIVEB_SAVEAS:
      menu_media_save( 0x102 ); return 0;
    case IDM_MENU_MEDIA_DISK_3_DRIVEB_FLIPDISK_TURNUPSIDEDOWN:
      menu_media_flip( 0x102 ); return 0;
    case IDM_MENU_MEDIA_DISK_3_DRIVEB_FLIPDISK_TURNBACK:
      menu_media_flip( 0x002 ); return 0;
    case IDM_MENU_MEDIA_DISK_3_DRIVEB_WRITEPROTECT_ENABLE:
      menu_media_writeprotect( 0x102 ); return 0;
    case IDM_MENU_MEDIA_DISK_3_DRIVEB_WRITEPROTECT_DISABLE:
      menu_media_writeprotect( 0x002 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVEA_INSERTNEW:
      menu_media_insert_new( 0x11 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVEA_INSERT:
      menu_media_insert( 0x11 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVEA_EJECT:
      menu_media_eject( 0x11 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVEA_SAVE:
      menu_media_save( 0x011 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVEA_SAVEAS:
      menu_media_save( 0x111 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVEA_FLIPDISK_TURNUPSIDEDOWN:
      menu_media_flip( 0x111 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVEA_FLIPDISK_TURNBACK:
      menu_media_flip( 0x011 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVEA_WRITEPROTECT_ENABLE:
      menu_media_writeprotect( 0x111 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVEA_WRITEPROTECT_DISABLE:
      menu_media_writeprotect( 0x011 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVEB_INSERTNEW:
      menu_media_insert_new( 0x12 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVEB_INSERT:
      menu_media_insert( 0x12 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVEB_EJECT:
      menu_media_eject( 0x12 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVEB_SAVE:
      menu_media_save( 0x012 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVEB_SAVEAS:
      menu_media_save( 0x112 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVEB_FLIPDISK_TURNUPSIDEDOWN:
      menu_media_flip( 0x112 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVEB_FLIPDISK_TURNBACK:
      menu_media_flip( 0x012 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVEB_WRITEPROTECT_ENABLE:
      menu_media_writeprotect( 0x112 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVEB_WRITEPROTECT_DISABLE:
      menu_media_writeprotect( 0x012 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVEC_INSERTNEW:
      menu_media_insert_new( 0x13 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVEC_INSERT:
      menu_media_insert( 0x13 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVEC_EJECT:
      menu_media_eject( 0x13 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVEC_SAVE:
      menu_media_save( 0x013 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVEC_SAVEAS:
      menu_media_save( 0x113 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVEC_FLIPDISK_TURNUPSIDEDOWN:
      menu_media_flip( 0x113 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVEC_FLIPDISK_TURNBACK:
      menu_media_flip( 0x013 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVEC_WRITEPROTECT_ENABLE:
      menu_media_writeprotect( 0x113 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVEC_WRITEPROTECT_DISABLE:
      menu_media_writeprotect( 0x013 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVED_INSERTNEW:
      menu_media_insert_new( 0x14 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVED_INSERT:
      menu_media_insert( 0x14 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVED_EJECT:
      menu_media_eject( 0x14 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVED_SAVE:
      menu_media_save( 0x014 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVED_SAVEAS:
      menu_media_save( 0x114 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVED_FLIPDISK_TURNUPSIDEDOWN:
      menu_media_flip( 0x114 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVED_FLIPDISK_TURNBACK:
      menu_media_flip( 0x014 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVED_WRITEPROTECT_ENABLE:
      menu_media_writeprotect( 0x114 ); return 0;
    case IDM_MENU_MEDIA_DISK_BETA_DRIVED_WRITEPROTECT_DISABLE:
      menu_media_writeprotect( 0x014 ); return 0;
    case IDM_MENU_MEDIA_DISK_D_DRIVE1_INSERTNEW:
      menu_media_insert_new( 0x21 ); return 0;
    case IDM_MENU_MEDIA_DISK_D_DRIVE1_INSERT:
      menu_media_insert( 0x21 ); return 0;
    case IDM_MENU_MEDIA_DISK_D_DRIVE1_EJECT:
      menu_media_eject( 0x21 ); return 0;
    case IDM_MENU_MEDIA_DISK_D_DRIVE1_SAVE:
      menu_media_save( 0x021 ); return 0;
    case IDM_MENU_MEDIA_DISK_D_DRIVE1_SAVEAS:
      menu_media_save( 0x121 ); return 0;
    case IDM_MENU_MEDIA_DISK_D_DRIVE1_FLIPDISK_TURNUPSIDEDOWN:
      menu_media_flip( 0x121 ); return 0;
    case IDM_MENU_MEDIA_DISK_D_DRIVE1_FLIPDISK_TURNBACK:
      menu_media_flip( 0x021 ); return 0;
    case IDM_MENU_MEDIA_DISK_D_DRIVE1_WRITEPROTECT_ENABLE:
      menu_media_writeprotect( 0x121 ); return 0;
    case IDM_MENU_MEDIA_DISK_D_DRIVE1_WRITEPROTECT_DISABLE:
      menu_media_writeprotect( 0x021 ); return 0;
    case IDM_MENU_MEDIA_DISK_D_DRIVE2_INSERTNEW:
      menu_media_insert_new( 0x22 ); return 0;
    case IDM_MENU_MEDIA_DISK_D_DRIVE2_INSERT:
      menu_media_insert( 0x22 ); return 0;
    case IDM_MENU_MEDIA_DISK_D_DRIVE2_EJECT:
      menu_media_eject( 0x22 ); return 0;
    case IDM_MENU_MEDIA_DISK_D_DRIVE2_SAVE:
      menu_media_save( 0x022 ); return 0;
    case IDM_MENU_MEDIA_DISK_D_DRIVE2_SAVEAS:
      menu_media_save( 0x122 ); return 0;
    case IDM_MENU_MEDIA_DISK_D_DRIVE2_FLIPDISK_TURNUPSIDEDOWN:
      menu_media_flip( 0x122 ); return 0;
    case IDM_MENU_MEDIA_DISK_D_DRIVE2_FLIPDISK_TURNBACK:
      menu_media_flip( 0x022 ); return 0;
    case IDM_MENU_MEDIA_DISK_D_DRIVE2_WRITEPROTECT_ENABLE:
      menu_media_writeprotect( 0x122 ); return 0;
    case IDM_MENU_MEDIA_DISK_D_DRIVE2_WRITEPROTECT_DISABLE:
      menu_media_writeprotect( 0x022 ); return 0;
    case IDM_MENU_MEDIA_DISK_DISCIPLE_DRIVE1_INSERTNEW:
      menu_media_insert_new( 0x51 ); return 0;
    case IDM_MENU_MEDIA_DISK_DISCIPLE_DRIVE1_INSERT:
      menu_media_insert( 0x51 ); return 0;
    case IDM_MENU_MEDIA_DISK_DISCIPLE_DRIVE1_EJECT:
      menu_media_eject( 0x51 ); return 0;
    case IDM_MENU_MEDIA_DISK_DISCIPLE_DRIVE1_SAVE:
      menu_media_save( 0x051 ); return 0;
    case IDM_MENU_MEDIA_DISK_DISCIPLE_DRIVE1_SAVEAS:
      menu_media_save( 0x151 ); return 0;
    case IDM_MENU_MEDIA_DISK_DISCIPLE_DRIVE1_FLIPDISK_TURNUPSIDEDOWN:
      menu_media_flip( 0x151 ); return 0;
    case IDM_MENU_MEDIA_DISK_DISCIPLE_DRIVE1_FLIPDISK_TURNBACK:
      menu_media_flip( 0x051 ); return 0;
    case IDM_MENU_MEDIA_DISK_DISCIPLE_DRIVE1_WRITEPROTECT_ENABLE:
      menu_media_writeprotect( 0x151 ); return 0;
    case IDM_MENU_MEDIA_DISK_DISCIPLE_DRIVE1_WRITEPROTECT_DISABLE:
      menu_media_writeprotect( 0x051 ); return 0;
    case IDM_MENU_MEDIA_DISK_DISCIPLE_DRIVE2_INSERTNEW:
      menu_media_insert_new( 0x52 ); return 0;
    case IDM_MENU_MEDIA_DISK_DISCIPLE_DRIVE2_INSERT:
      menu_media_insert( 0x52 ); return 0;
    case IDM_MENU_MEDIA_DISK_DISCIPLE_DRIVE2_EJECT:
      menu_media_eject( 0x52 ); return 0;
    case IDM_MENU_MEDIA_DISK_DISCIPLE_DRIVE2_SAVE:
      menu_media_save( 0x052 ); return 0;
    case IDM_MENU_MEDIA_DISK_DISCIPLE_DRIVE2_SAVEAS:
      menu_media_save( 0x152 ); return 0;
    case IDM_MENU_MEDIA_DISK_DISCIPLE_DRIVE2_FLIPDISK_TURNUPSIDEDOWN:
      menu_media_flip( 0x152 ); return 0;
    case IDM_MENU_MEDIA_DISK_DISCIPLE_DRIVE2_FLIPDISK_TURNBACK:
      menu_media_flip( 0x052 ); return 0;
    case IDM_MENU_MEDIA_DISK_DISCIPLE_DRIVE2_WRITEPROTECT_ENABLE:
      menu_media_writeprotect( 0x152 ); return 0;
    case IDM_MENU_MEDIA_DISK_DISCIPLE_DRIVE2_WRITEPROTECT_DISABLE:
      menu_media_writeprotect( 0x052 ); return 0;
    case IDM_MENU_MEDIA_DISK_OPUS_DRIVE1_INSERTNEW:
      menu_media_insert_new( 0x41 ); return 0;
    case IDM_MENU_MEDIA_DISK_OPUS_DRIVE1_INSERT:
      menu_media_insert( 0x41 ); return 0;
    case IDM_MENU_MEDIA_DISK_OPUS_DRIVE1_EJECT:
      menu_media_eject( 0x41 ); return 0;
    case IDM_MENU_MEDIA_DISK_OPUS_DRIVE1_SAVE:
      menu_media_save( 0x041 ); return 0;
    case IDM_MENU_MEDIA_DISK_OPUS_DRIVE1_SAVEAS:
      menu_media_save( 0x141 ); return 0;
    case IDM_MENU_MEDIA_DISK_OPUS_DRIVE1_FLIPDISK_TURNUPSIDEDOWN:
      menu_media_flip( 0x141 ); return 0;
    case IDM_MENU_MEDIA_DISK_OPUS_DRIVE1_FLIPDISK_TURNBACK:
      menu_media_flip( 0x041 ); return 0;
    case IDM_MENU_MEDIA_DISK_OPUS_DRIVE1_WRITEPROTECT_ENABLE:
      menu_media_writeprotect( 0x141 ); return 0;
    case IDM_MENU_MEDIA_DISK_OPUS_DRIVE1_WRITEPROTECT_DISABLE:
      menu_media_writeprotect( 0x041 ); return 0;
    case IDM_MENU_MEDIA_DISK_OPUS_DRIVE2_INSERTNEW:
      menu_media_insert_new( 0x42 ); return 0;
    case IDM_MENU_MEDIA_DISK_OPUS_DRIVE2_INSERT:
      menu_media_insert( 0x42 ); return 0;
    case IDM_MENU_MEDIA_DISK_OPUS_DRIVE2_EJECT:
      menu_media_eject( 0x42 ); return 0;
    case IDM_MENU_MEDIA_DISK_OPUS_DRIVE2_SAVE:
      menu_media_save( 0x042 ); return 0;
    case IDM_MENU_MEDIA_DISK_OPUS_DRIVE2_SAVEAS:
      menu_media_save( 0x142 ); return 0;
    case IDM_MENU_MEDIA_DISK_OPUS_DRIVE2_FLIPDISK_TURNUPSIDEDOWN:
      menu_media_flip( 0x142 ); return 0;
    case IDM_MENU_MEDIA_DISK_OPUS_DRIVE2_FLIPDISK_TURNBACK:
      menu_media_flip( 0x042 ); return 0;
    case IDM_MENU_MEDIA_DISK_OPUS_DRIVE2_WRITEPROTECT_ENABLE:
      menu_media_writeprotect( 0x142 ); return 0;
    case IDM_MENU_MEDIA_DISK_OPUS_DRIVE2_WRITEPROTECT_DISABLE:
      menu_media_writeprotect( 0x042 ); return 0;
    case IDM_MENU_MEDIA_DISK_DIDAKTIK80_DRIVEA_INSERTNEW:
      menu_media_insert_new( 0x61 ); return 0;
    case IDM_MENU_MEDIA_DISK_DIDAKTIK80_DRIVEA_INSERT:
      menu_media_insert( 0x61 ); return 0;
    case IDM_MENU_MEDIA_DISK_DIDAKTIK80_DRIVEA_EJECT:
      menu_media_eject( 0x61 ); return 0;
    case IDM_MENU_MEDIA_DISK_DIDAKTIK80_DRIVEA_SAVE:
      menu_media_save( 0x061 ); return 0;
    case IDM_MENU_MEDIA_DISK_DIDAKTIK80_DRIVEA_SAVEAS:
      menu_media_save( 0x161 ); return 0;
    case IDM_MENU_MEDIA_DISK_DIDAKTIK80_DRIVEA_FLIPDISK_TURNUPSIDEDOWN:
      menu_media_flip( 0x161 ); return 0;
    case IDM_MENU_MEDIA_DISK_DIDAKTIK80_DRIVEA_FLIPDISK_TURNBACK:
      menu_media_flip( 0x061 ); return 0;
    case IDM_MENU_MEDIA_DISK_DIDAKTIK80_DRIVEA_WRITEPROTECT_ENABLE:
      menu_media_writeprotect( 0x161 ); return 0;
    case IDM_MENU_MEDIA_DISK_DIDAKTIK80_DRIVEA_WRITEPROTECT_DISABLE:
      menu_media_writeprotect( 0x061 ); return 0;
    case IDM_MENU_MEDIA_DISK_DIDAKTIK80_DRIVEB_INSERTNEW:
      menu_media_insert_new( 0x62 ); return 0;
    case IDM_MENU_MEDIA_DISK_DIDAKTIK80_DRIVEB_INSERT:
      menu_media_insert( 0x62 ); return 0;
    case IDM_MENU_MEDIA_DISK_DIDAKTIK80_DRIVEB_EJECT:
      menu_media_eject( 0x62 ); return 0;
    case IDM_MENU_MEDIA_DISK_DIDAKTIK80_DRIVEB_SAVE:
      menu_media_save( 0x062 ); return 0;
    case IDM_MENU_MEDIA_DISK_DIDAKTIK80_DRIVEB_SAVEAS:
      menu_media_save( 0x162 ); return 0;
    case IDM_MENU_MEDIA_DISK_DIDAKTIK80_DRIVEB_FLIPDISK_TURNUPSIDEDOWN:
      menu_media_flip( 0x162 ); return 0;
    case IDM_MENU_MEDIA_DISK_DIDAKTIK80_DRIVEB_FLIPDISK_TURNBACK:
      menu_media_flip( 0x062 ); return 0;
    case IDM_MENU_MEDIA_DISK_DIDAKTIK80_DRIVEB_WRITEPROTECT_ENABLE:
      menu_media_writeprotect( 0x162 ); return 0;
    case IDM_MENU_MEDIA_DISK_DIDAKTIK80_DRIVEB_WRITEPROTECT_DISABLE:
      menu_media_writeprotect( 0x062 ); return 0;
    case IDM_MENU_MEDIA_CARTRIDGE_TIMEXDOCK_INSERT:
      menu_media_cartridge_timexdock_insert( 0 ); return 0;
    case IDM_MENU_MEDIA_CARTRIDGE_TIMEXDOCK_EJECT:
      menu_media_cartridge_timexdock_eject( 0 ); return 0;
    case IDM_MENU_MEDIA_CARTRIDGE_INTERFACE2_INSERT:
      menu_media_cartridge_interface2_insert( 0 ); return 0;
    case IDM_MENU_MEDIA_CARTRIDGE_INTERFACE2_EJECT:
      menu_media_cartridge_interface2_eject( 0 ); return 0;
    case IDM_MENU_MEDIA_IDE_SIMPLE8BIT_MASTER_INSERT:
      menu_media_ide_insert( 1 ); return 0;
    case IDM_MENU_MEDIA_IDE_SIMPLE8BIT_MASTER_COMMIT:
      menu_media_ide_commit( 1 ); return 0;
    case IDM_MENU_MEDIA_IDE_SIMPLE8BIT_MASTER_EJECT:
      menu_media_ide_eject( 1 ); return 0;
    case IDM_MENU_MEDIA_IDE_SIMPLE8BIT_SLAVE_INSERT:
      menu_media_ide_insert( 2 ); return 0;
    case IDM_MENU_MEDIA_IDE_SIMPLE8BIT_SLAVE_COMMIT:
      menu_media_ide_commit( 2 ); return 0;
    case IDM_MENU_MEDIA_IDE_SIMPLE8BIT_SLAVE_EJECT:
      menu_media_ide_eject( 2 ); return 0;
    case IDM_MENU_MEDIA_IDE_ZXATASP_MASTER_INSERT:
      menu_media_ide_insert( 3 ); return 0;
    case IDM_MENU_MEDIA_IDE_ZXATASP_MASTER_COMMIT:
      menu_media_ide_commit( 3 ); return 0;
    case IDM_MENU_MEDIA_IDE_ZXATASP_MASTER_EJECT:
      menu_media_ide_eject( 3 ); return 0;
    case IDM_MENU_MEDIA_IDE_ZXATASP_SLAVE_INSERT:
      menu_media_ide_insert( 4 ); return 0;
    case IDM_MENU_MEDIA_IDE_ZXATASP_SLAVE_COMMIT:
      menu_media_ide_commit( 4 ); return 0;
    case IDM_MENU_MEDIA_IDE_ZXATASP_SLAVE_EJECT:
      menu_media_ide_eject( 4 ); return 0;
    case IDM_MENU_MEDIA_IDE_ZXCFCOMPACTFLASH_INSERT:
      menu_media_ide_insert( 5 ); return 0;
    case IDM_MENU_MEDIA_IDE_ZXCFCOMPACTFLASH_COMMIT:
      menu_media_ide_commit( 5 ); return 0;
    case IDM_MENU_MEDIA_IDE_ZXCFCOMPACTFLASH_EJECT:
      menu_media_ide_eject( 5 ); return 0;
    case IDM_MENU_MEDIA_IDE_DIVIDE_MASTER_INSERT:
      menu_media_ide_insert( 6 ); return 0;
    case IDM_MENU_MEDIA_IDE_DIVIDE_MASTER_COMMIT:
      menu_media_ide_commit( 6 ); return 0;
    case IDM_MENU_MEDIA_IDE_DIVIDE_MASTER_EJECT:
      menu_media_ide_eject( 6 ); return 0;
    case IDM_MENU_MEDIA_IDE_DIVIDE_SLAVE_INSERT:
      menu_media_ide_insert( 7 ); return 0;
    case IDM_MENU_MEDIA_IDE_DIVIDE_SLAVE_COMMIT:
      menu_media_ide_commit( 7 ); return 0;
    case IDM_MENU_MEDIA_IDE_DIVIDE_SLAVE_EJECT:
      menu_media_ide_eject( 7 ); return 0;
    case IDM_MENU_MEDIA_IDE_DIVMMC_INSERT:
      menu_media_ide_insert( 8 ); return 0;
    case IDM_MENU_MEDIA_IDE_DIVMMC_COMMIT:
      menu_media_ide_commit( 8 ); return 0;
    case IDM_MENU_MEDIA_IDE_DIVMMC_EJECT:
      menu_media_ide_eject( 8 ); return 0;
    case IDM_MENU_MEDIA_IDE_ZXMMC_INSERT:
      menu_media_ide_insert( 9 ); return 0;
    case IDM_MENU_MEDIA_IDE_ZXMMC_COMMIT:
      menu_media_ide_commit( 9 ); return 0;
    case IDM_MENU_MEDIA_IDE_ZXMMC_EJECT:
      menu_media_ide_eject( 9 ); return 0;
    case IDM_MENU_HELP_KEYBOARD:
      menu_help_keyboard( 0 ); return 0;
    case IDM_MENU_HELP_ABOUT:
      menu_help_about( 0 ); return 0;
  }
  return 1;
}
