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

/* This file is autogenerated from menu_data.dat by ../../../ui/gtk/../../menu_data.pl.
   Any changes made here will not be preserved. */

#include <config.h>

#include "menu.h"

#include <gtk/gtk.h>

GtkItemFactoryEntry gtkui_menu_data[] = {

  { "/File", NULL, NULL, 0, "<Branch>", NULL },
  { "/File/_Open...", "F3", menu_file_open, 0, "<Item>", NULL },
  { "/File/_Save Snapshot...", "F2", menu_file_savesnapshot, 0, "<Item>", NULL },
  { "/File/_Recording", NULL, NULL, 0, "<Branch>", NULL },
  { "/File/Recording/_Record...", NULL, menu_file_recording_record, 0, "<Item>", NULL },
  { "/File/Recording/Record _from snapshot...", NULL, menu_file_recording_recordfromsnapshot, 0, "<Item>", NULL },
  { "/File/Recording/_Insert snapshot", "Insert", menu_file_recording_insertsnapshot, 0, "<Item>", NULL },
  { "/File/Recording/Roll_back", "Delete", menu_file_recording_rollback, 0, "<Item>", NULL },
  { "/File/Recording/Rollback _to...", NULL, menu_file_recording_rollbackto, 0, "<Item>", NULL },
  { "/File/Recording/_Play...", NULL, menu_file_recording_play, 0, "<Item>", NULL },
  { "/File/Recording/_Stop", NULL, menu_file_recording_stop, 0, "<Item>", NULL },
  { "/File/A_Y Logging", NULL, NULL, 0, "<Branch>", NULL },
  { "/File/AY Logging/_Record...", NULL, menu_file_aylogging_record, 0, "<Item>", NULL },
  { "/File/AY Logging/_Stop", NULL, menu_file_aylogging_stop, 0, "<Item>", NULL },
  { "/File/separator", NULL, NULL, 0, "<Separator>", NULL },
  { "/File/O_pen SCR Screenshot...", NULL, menu_file_openscrscreenshot, 0, "<Item>", NULL },
  { "/File/S_ave Screen as SCR...", NULL, menu_file_savescreenasscr, 0, "<Item>", NULL },
  { "/File/Save S_creen as PNG...", NULL, menu_file_savescreenaspng, 0, "<Item>", NULL },
  { "/File/_Movies", NULL, NULL, 0, "<Branch>", NULL },
  { "/File/Movies/Record Movie as _SCR...", NULL, menu_file_movies_recordmovieasscr, 0, "<Item>", NULL },
  { "/File/Movies/Record Movie as _PNG...", NULL, menu_file_movies_recordmovieaspng, 0, "<Item>", NULL },
  { "/File/Movies/S_top Movie Recording", NULL, menu_file_movies_stopmovierecording, 0, "<Item>", NULL },
  { "/File/separator", NULL, NULL, 0, "<Separator>", NULL },
  { "/File/Loa_d binary data...", NULL, menu_file_loadbinarydata, 0, "<Item>", NULL },
  { "/File/Save _binary data...", NULL, menu_file_savebinarydata, 0, "<Item>", NULL },
  { "/File/separator", NULL, NULL, 0, "<Separator>", NULL },
  { "/File/E_xit...", "F10", menu_file_exit, 0, "<Item>", NULL },
  { "/Options", NULL, NULL, 0, "<Branch>", NULL },
  { "/Options/_General...", "F4", menu_options_general, 0, "<Item>", NULL },
  { "/Options/_Sound...", NULL, menu_options_sound, 0, "<Item>", NULL },
  { "/Options/_Peripherals...", NULL, menu_options_peripherals, 0, "<Item>", NULL },
  { "/Options/_RZX...", NULL, menu_options_rzx, 0, "<Item>", NULL },
  { "/Options/_Joysticks", NULL, NULL, 0, "<Branch>", NULL },
  { "/Options/Joysticks/_Keyboard...", NULL, menu_options_joysticks_select, 3, "<Item>", NULL },
  { "/Options/S_elect ROMs", NULL, NULL, 0, "<Branch>", NULL },
  { "/Options/Select ROMs/Spectrum 1_6K...", NULL, menu_options_selectroms_select, 1, "<Item>", NULL },
  { "/Options/Select ROMs/Spectrum _48K...", NULL, menu_options_selectroms_select, 2, "<Item>", NULL },
  { "/Options/Select ROMs/Spectrum _128K...", NULL, menu_options_selectroms_select, 3, "<Item>", NULL },
  { "/Options/Select ROMs/Spectrum +_2...", NULL, menu_options_selectroms_select, 4, "<Item>", NULL },
  { "/Options/Select ROMs/Spectrum +2_A...", NULL, menu_options_selectroms_select, 5, "<Item>", NULL },
  { "/Options/Select ROMs/Spectrum +_3...", NULL, menu_options_selectroms_select, 6, "<Item>", NULL },
  { "/Options/Select ROMs/Spectrum +3_e...", NULL, menu_options_selectroms_select, 7, "<Item>", NULL },
  { "/Options/Select ROMs/Timex _TC2048...", NULL, menu_options_selectroms_select, 8, "<Item>", NULL },
  { "/Options/Select ROMs/Timex TC206_8...", NULL, menu_options_selectroms_select, 9, "<Item>", NULL },
  { "/Options/Select ROMs/Ti_mex TS2068...", NULL, menu_options_selectroms_select, 10, "<Item>", NULL },
  { "/Options/Select ROMs/_Pentagon 128K...", NULL, menu_options_selectroms_select, 11, "<Item>", NULL },
  { "/Options/Select ROMs/Pe_ntagon 512K...", NULL, menu_options_selectroms_select, 12, "<Item>", NULL },
  { "/Options/Select ROMs/Penta_gon 1024K...", NULL, menu_options_selectroms_select, 13, "<Item>", NULL },
  { "/Options/Select ROMs/S_corpion ZS 256...", NULL, menu_options_selectroms_select, 14, "<Item>", NULL },
  { "/Options/Select ROMs/Spectrum _SE...", NULL, menu_options_selectroms_select, 15, "<Item>", NULL },
  { "/Options/Select ROMs/Interface _I...", NULL, menu_options_selectroms_select, 16, "<Item>", NULL },
  { "/Options/Select ROMs/_Beta 128...", NULL, menu_options_selectroms_select, 17, "<Item>", NULL },
  { "/Options/Select ROMs/+_D...", NULL, menu_options_selectroms_select, 18, "<Item>", NULL },
  { "/Options/_Filter...", NULL, menu_options_filter, 0, "<Item>", NULL },
  { "/Options/_Disk options...", NULL, menu_options_diskoptions, 0, "<Item>", NULL },
  { "/Options/separator", NULL, NULL, 0, "<Separator>", NULL },
  { "/Options/S_ave", NULL, menu_options_save, 0, "<Item>", NULL },
  { "/Machine", NULL, NULL, 0, "<Branch>", NULL },
  { "/Machine/_Pause...", "Pause", menu_machine_pause, 0, "<Item>", NULL },
  { "/Machine/_Reset...", "F5", menu_machine_reset, 0, "<Item>", NULL },
  { "/Machine/_Hard reset...", NULL, menu_machine_reset, 1, "<Item>", NULL },
  { "/Machine/_Select...", "F9", menu_machine_select, 0, "<Item>", NULL },
  { "/Machine/_Debugger...", NULL, menu_machine_debugger, 0, "<Item>", NULL },
  { "/Machine/P_oke Finder...", NULL, menu_machine_pokefinder, 0, "<Item>", NULL },
  { "/Machine/_Memory Browser...", NULL, menu_machine_memorybrowser, 0, "<Item>", NULL },
  { "/Machine/Pro_filer", NULL, NULL, 0, "<Branch>", NULL },
  { "/Machine/Profiler/_Start", NULL, menu_machine_profiler_start, 0, "<Item>", NULL },
  { "/Machine/Profiler/_Stop", NULL, menu_machine_profiler_stop, 0, "<Item>", NULL },
  { "/Machine/_NMI", NULL, menu_machine_nmi, 0, "<Item>", NULL },
  { "/Media", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/_Tape", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Tape/_Open...", "F7", menu_media_tape_open, 0, "<Item>", NULL },
  { "/Media/Tape/_Play", "F8", menu_media_tape_play, 0, "<Item>", NULL },
  { "/Media/Tape/_Browse...", NULL, menu_media_tape_browse, 0, "<Item>", NULL },
  { "/Media/Tape/_Rewind", NULL, menu_media_tape_rewind, 0, "<Item>", NULL },
  { "/Media/Tape/_Clear", NULL, menu_media_tape_clear, 0, "<Item>", NULL },
  { "/Media/Tape/_Write...", "F6", menu_media_tape_write, 0, "<Item>", NULL },
  { "/Media/Tape/R_ecord Start", NULL, menu_media_tape_recordstart, 0, "<Item>", NULL },
  { "/Media/Tape/Recor_d Stop", NULL, menu_media_tape_recordstop, 0, "<Item>", NULL },
  { "/Media/_Interface I", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Interface I/Microdrive _1", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Interface I/Microdrive 1/Insert _New", NULL, menu_media_insert_new, 0x31, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 1/_Insert...", NULL, menu_media_insert, 0x31, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 1/_Eject", NULL, menu_media_eject, 0x031, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 1/_Save", NULL, menu_media_eject, 0x231, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 1/Save _As...", NULL, menu_media_eject, 0x131, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 1/Write _protect", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Interface I/Microdrive 1/Write protect/_Enable", NULL, menu_media_writeprotect, 0x131, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 1/Write protect/_Disable", NULL, menu_media_writeprotect, 0x031, "<Item>", NULL },
  { "/Media/Interface I/Microdrive _2", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Interface I/Microdrive 2/Insert _New", NULL, menu_media_insert_new, 0x32, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 2/_Insert...", NULL, menu_media_insert, 0x32, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 2/_Eject", NULL, menu_media_eject, 0x032, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 2/_Save", NULL, menu_media_eject, 0x232, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 2/Save _As...", NULL, menu_media_eject, 0x132, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 2/Write _protect", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Interface I/Microdrive 2/Write protect/_Enable", NULL, menu_media_writeprotect, 0x132, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 2/Write protect/_Disable", NULL, menu_media_writeprotect, 0x032, "<Item>", NULL },
  { "/Media/Interface I/Microdrive _3", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Interface I/Microdrive 3/Insert _New", NULL, menu_media_insert_new, 0x33, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 3/_Insert...", NULL, menu_media_insert, 0x33, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 3/_Eject", NULL, menu_media_eject, 0x033, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 3/_Save", NULL, menu_media_eject, 0x233, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 3/Save _As...", NULL, menu_media_eject, 0x133, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 3/Write _protect", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Interface I/Microdrive 3/Write protect/_Enable", NULL, menu_media_writeprotect, 0x133, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 3/Write protect/_Disable", NULL, menu_media_writeprotect, 0x033, "<Item>", NULL },
  { "/Media/Interface I/Microdrive _4", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Interface I/Microdrive 4/Insert _New", NULL, menu_media_insert_new, 0x34, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 4/_Insert...", NULL, menu_media_insert, 0x34, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 4/_Eject", NULL, menu_media_eject, 0x034, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 4/_Save", NULL, menu_media_eject, 0x234, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 4/Save _As...", NULL, menu_media_eject, 0x134, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 4/Write _protect", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Interface I/Microdrive 4/Write protect/_Enable", NULL, menu_media_writeprotect, 0x134, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 4/Write protect/_Disable", NULL, menu_media_writeprotect, 0x034, "<Item>", NULL },
  { "/Media/Interface I/Microdrive _5", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Interface I/Microdrive 5/Insert _New", NULL, menu_media_insert_new, 0x35, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 5/_Insert...", NULL, menu_media_insert, 0x35, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 5/_Eject", NULL, menu_media_eject, 0x035, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 5/_Save", NULL, menu_media_eject, 0x235, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 5/Save _As...", NULL, menu_media_eject, 0x135, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 5/Write _protect", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Interface I/Microdrive 5/Write protect/_Enable", NULL, menu_media_writeprotect, 0x135, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 5/Write protect/_Disable", NULL, menu_media_writeprotect, 0x035, "<Item>", NULL },
  { "/Media/Interface I/Microdrive _6", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Interface I/Microdrive 6/Insert _New", NULL, menu_media_insert_new, 0x36, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 6/_Insert...", NULL, menu_media_insert, 0x36, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 6/_Eject", NULL, menu_media_eject, 0x036, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 6/_Save", NULL, menu_media_eject, 0x236, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 6/Save _As...", NULL, menu_media_eject, 0x136, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 6/Write _protect", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Interface I/Microdrive 6/Write protect/_Enable", NULL, menu_media_writeprotect, 0x136, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 6/Write protect/_Disable", NULL, menu_media_writeprotect, 0x036, "<Item>", NULL },
  { "/Media/Interface I/Microdrive _7", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Interface I/Microdrive 7/Insert _New", NULL, menu_media_insert_new, 0x37, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 7/_Insert...", NULL, menu_media_insert, 0x37, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 7/_Eject", NULL, menu_media_eject, 0x037, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 7/_Save", NULL, menu_media_eject, 0x237, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 7/Save _As...", NULL, menu_media_eject, 0x137, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 7/Write _protect", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Interface I/Microdrive 7/Write protect/_Enable", NULL, menu_media_writeprotect, 0x137, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 7/Write protect/_Disable", NULL, menu_media_writeprotect, 0x037, "<Item>", NULL },
  { "/Media/Interface I/Microdrive _8", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Interface I/Microdrive 8/Insert _New", NULL, menu_media_insert_new, 0x38, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 8/_Insert...", NULL, menu_media_insert, 0x38, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 8/_Eject", NULL, menu_media_eject, 0x038, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 8/_Save", NULL, menu_media_eject, 0x238, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 8/Save _As...", NULL, menu_media_eject, 0x138, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 8/Write _protect", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Interface I/Microdrive 8/Write protect/_Enable", NULL, menu_media_writeprotect, 0x138, "<Item>", NULL },
  { "/Media/Interface I/Microdrive 8/Write protect/_Disable", NULL, menu_media_writeprotect, 0x038, "<Item>", NULL },
  { "/Media/Interface I/_RS232", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Interface I/RS232/Plug _RxD", NULL, menu_media_if1_rs232, 0x01, "<Item>", NULL },
  { "/Media/Interface I/RS232/_Unplug RxD", NULL, menu_media_if1_rs232, 0x11, "<Item>", NULL },
  { "/Media/Interface I/RS232/Plug _TxD", NULL, menu_media_if1_rs232, 0x02, "<Item>", NULL },
  { "/Media/Interface I/RS232/Un_plug TxD", NULL, menu_media_if1_rs232, 0x12, "<Item>", NULL },
  { "/Media/_Disk", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Disk/+_3", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Disk/+3/Drive _A:", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Disk/+3/Drive A:/Insert _New", NULL, menu_media_insert_new, 0x01, "<Item>", NULL },
  { "/Media/Disk/+3/Drive A:/_Insert...", NULL, menu_media_insert, 0x01, "<Item>", NULL },
  { "/Media/Disk/+3/Drive A:/_Eject", NULL, menu_media_eject, 0x01, "<Item>", NULL },
  { "/Media/Disk/+3/Drive A:/_Save", NULL, menu_media_eject, 0x201, "<Item>", NULL },
  { "/Media/Disk/+3/Drive A:/Save _As...", NULL, menu_media_eject, 0x101, "<Item>", NULL },
  { "/Media/Disk/+3/Drive A:/_Flip disk", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Disk/+3/Drive A:/Flip disk/Turn _upside down", NULL, menu_media_flip, 0x101, "<Item>", NULL },
  { "/Media/Disk/+3/Drive A:/Flip disk/Turn _back", NULL, menu_media_flip, 0x001, "<Item>", NULL },
  { "/Media/Disk/+3/Drive A:/Write _protect", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Disk/+3/Drive A:/Write protect/_Enable", NULL, menu_media_writeprotect, 0x101, "<Item>", NULL },
  { "/Media/Disk/+3/Drive A:/Write protect/_Disable", NULL, menu_media_writeprotect, 0x001, "<Item>", NULL },
  { "/Media/Disk/+3/Drive _B:", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Disk/+3/Drive B:/Insert _New", NULL, menu_media_insert_new, 0x02, "<Item>", NULL },
  { "/Media/Disk/+3/Drive B:/_Insert...", NULL, menu_media_insert, 0x02, "<Item>", NULL },
  { "/Media/Disk/+3/Drive B:/_Eject", NULL, menu_media_eject, 0x02, "<Item>", NULL },
  { "/Media/Disk/+3/Drive B:/_Save", NULL, menu_media_eject, 0x202, "<Item>", NULL },
  { "/Media/Disk/+3/Drive B:/Save _As...", NULL, menu_media_eject, 0x102, "<Item>", NULL },
  { "/Media/Disk/+3/Drive B:/_Flip disk", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Disk/+3/Drive B:/Flip disk/Turn _upside down", NULL, menu_media_flip, 0x102, "<Item>", NULL },
  { "/Media/Disk/+3/Drive B:/Flip disk/Turn _back", NULL, menu_media_flip, 0x002, "<Item>", NULL },
  { "/Media/Disk/+3/Drive B:/Write _protect", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Disk/+3/Drive B:/Write protect/_Enable", NULL, menu_media_writeprotect, 0x102, "<Item>", NULL },
  { "/Media/Disk/+3/Drive B:/Write protect/_Disable", NULL, menu_media_writeprotect, 0x002, "<Item>", NULL },
  { "/Media/Disk/_Beta", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Disk/Beta/Drive _A:", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Disk/Beta/Drive A:/Insert _New", NULL, menu_media_insert_new, 0x11, "<Item>", NULL },
  { "/Media/Disk/Beta/Drive A:/_Insert...", NULL, menu_media_insert, 0x11, "<Item>", NULL },
  { "/Media/Disk/Beta/Drive A:/_Eject", NULL, menu_media_eject, 0x11, "<Item>", NULL },
  { "/Media/Disk/Beta/Drive A:/_Save", NULL, menu_media_eject, 0x211, "<Item>", NULL },
  { "/Media/Disk/Beta/Drive A:/Save _As...", NULL, menu_media_eject, 0x111, "<Item>", NULL },
  { "/Media/Disk/Beta/Drive A:/_Flip disk", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Disk/Beta/Drive A:/Flip disk/Turn _upside down", NULL, menu_media_flip, 0x111, "<Item>", NULL },
  { "/Media/Disk/Beta/Drive A:/Flip disk/Turn _back", NULL, menu_media_flip, 0x011, "<Item>", NULL },
  { "/Media/Disk/Beta/Drive A:/Write _protect", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Disk/Beta/Drive A:/Write protect/_Enable", NULL, menu_media_writeprotect, 0x111, "<Item>", NULL },
  { "/Media/Disk/Beta/Drive A:/Write protect/_Disable", NULL, menu_media_writeprotect, 0x011, "<Item>", NULL },
  { "/Media/Disk/Beta/Drive _B:", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Disk/Beta/Drive B:/Insert _New", NULL, menu_media_insert_new, 0x12, "<Item>", NULL },
  { "/Media/Disk/Beta/Drive B:/_Insert...", NULL, menu_media_insert, 0x12, "<Item>", NULL },
  { "/Media/Disk/Beta/Drive B:/_Eject", NULL, menu_media_eject, 0x012, "<Item>", NULL },
  { "/Media/Disk/Beta/Drive B:/_Save", NULL, menu_media_eject, 0x212, "<Item>", NULL },
  { "/Media/Disk/Beta/Drive B:/Save _As...", NULL, menu_media_eject, 0x112, "<Item>", NULL },
  { "/Media/Disk/Beta/Drive B:/_Flip disk", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Disk/Beta/Drive B:/Flip disk/Turn _upside down", NULL, menu_media_flip, 0x112, "<Item>", NULL },
  { "/Media/Disk/Beta/Drive B:/Flip disk/Turn _back", NULL, menu_media_flip, 0x012, "<Item>", NULL },
  { "/Media/Disk/Beta/Drive B:/Write _protect", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Disk/Beta/Drive B:/Write protect/_Enable", NULL, menu_media_writeprotect, 0x112, "<Item>", NULL },
  { "/Media/Disk/Beta/Drive B:/Write protect/_Disable", NULL, menu_media_writeprotect, 0x012, "<Item>", NULL },
  { "/Media/Disk/Beta/Drive _C:", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Disk/Beta/Drive C:/Insert _New", NULL, menu_media_insert_new, 0x13, "<Item>", NULL },
  { "/Media/Disk/Beta/Drive C:/_Insert...", NULL, menu_media_insert, 0x13, "<Item>", NULL },
  { "/Media/Disk/Beta/Drive C:/_Eject", NULL, menu_media_eject, 0x013, "<Item>", NULL },
  { "/Media/Disk/Beta/Drive C:/_Save", NULL, menu_media_eject, 0x213, "<Item>", NULL },
  { "/Media/Disk/Beta/Drive C:/Save _As...", NULL, menu_media_eject, 0x113, "<Item>", NULL },
  { "/Media/Disk/Beta/Drive C:/_Flip disk", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Disk/Beta/Drive C:/Flip disk/Turn _upside down", NULL, menu_media_flip, 0x113, "<Item>", NULL },
  { "/Media/Disk/Beta/Drive C:/Flip disk/Turn _back", NULL, menu_media_flip, 0x013, "<Item>", NULL },
  { "/Media/Disk/Beta/Drive C:/Write _protect", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Disk/Beta/Drive C:/Write protect/_Enable", NULL, menu_media_writeprotect, 0x113, "<Item>", NULL },
  { "/Media/Disk/Beta/Drive C:/Write protect/_Disable", NULL, menu_media_writeprotect, 0x013, "<Item>", NULL },
  { "/Media/Disk/Beta/Drive _D:", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Disk/Beta/Drive D:/Insert _New", NULL, menu_media_insert_new, 0x14, "<Item>", NULL },
  { "/Media/Disk/Beta/Drive D:/_Insert...", NULL, menu_media_insert, 0x14, "<Item>", NULL },
  { "/Media/Disk/Beta/Drive D:/_Eject", NULL, menu_media_eject, 0x014, "<Item>", NULL },
  { "/Media/Disk/Beta/Drive D:/_Save", NULL, menu_media_eject, 0x214, "<Item>", NULL },
  { "/Media/Disk/Beta/Drive D:/Save _As...", NULL, menu_media_eject, 0x114, "<Item>", NULL },
  { "/Media/Disk/Beta/Drive D:/_Flip disk", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Disk/Beta/Drive D:/Flip disk/Turn _upside down", NULL, menu_media_flip, 0x114, "<Item>", NULL },
  { "/Media/Disk/Beta/Drive D:/Flip disk/Turn _back", NULL, menu_media_flip, 0x014, "<Item>", NULL },
  { "/Media/Disk/Beta/Drive D:/Write _protect", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Disk/Beta/Drive D:/Write protect/_Enable", NULL, menu_media_writeprotect, 0x114, "<Item>", NULL },
  { "/Media/Disk/Beta/Drive D:/Write protect/_Disable", NULL, menu_media_writeprotect, 0x014, "<Item>", NULL },
  { "/Media/Disk/+_D", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Disk/+D/Drive _1", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Disk/+D/Drive 1/Insert _New", NULL, menu_media_insert_new, 0x21, "<Item>", NULL },
  { "/Media/Disk/+D/Drive 1/_Insert...", NULL, menu_media_insert, 0x21, "<Item>", NULL },
  { "/Media/Disk/+D/Drive 1/_Eject", NULL, menu_media_eject, 0x021, "<Item>", NULL },
  { "/Media/Disk/+D/Drive 1/_Save", NULL, menu_media_eject, 0x221, "<Item>", NULL },
  { "/Media/Disk/+D/Drive 1/Save _As...", NULL, menu_media_eject, 0x121, "<Item>", NULL },
  { "/Media/Disk/+D/Drive 1/_Flip disk", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Disk/+D/Drive 1/Flip disk/Turn _upside down", NULL, menu_media_flip, 0x121, "<Item>", NULL },
  { "/Media/Disk/+D/Drive 1/Flip disk/Turn _back", NULL, menu_media_flip, 0x021, "<Item>", NULL },
  { "/Media/Disk/+D/Drive 1/Write _protect", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Disk/+D/Drive 1/Write protect/_Enable", NULL, menu_media_writeprotect, 0x121, "<Item>", NULL },
  { "/Media/Disk/+D/Drive 1/Write protect/_Disable", NULL, menu_media_writeprotect, 0x021, "<Item>", NULL },
  { "/Media/Disk/+D/Drive _2", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Disk/+D/Drive 2/Insert _New", NULL, menu_media_insert_new, 0x22, "<Item>", NULL },
  { "/Media/Disk/+D/Drive 2/_Insert...", NULL, menu_media_insert, 0x22, "<Item>", NULL },
  { "/Media/Disk/+D/Drive 2/_Eject", NULL, menu_media_eject, 0x022, "<Item>", NULL },
  { "/Media/Disk/+D/Drive 2/_Save", NULL, menu_media_eject, 0x222, "<Item>", NULL },
  { "/Media/Disk/+D/Drive 2/Save _As...", NULL, menu_media_eject, 0x122, "<Item>", NULL },
  { "/Media/Disk/+D/Drive 2/_Flip disk", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Disk/+D/Drive 2/Flip disk/Turn _upside down", NULL, menu_media_flip, 0x122, "<Item>", NULL },
  { "/Media/Disk/+D/Drive 2/Flip disk/Turn _back", NULL, menu_media_flip, 0x022, "<Item>", NULL },
  { "/Media/Disk/+D/Drive 2/Write _protect", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Disk/+D/Drive 2/Write protect/_Enable", NULL, menu_media_writeprotect, 0x122, "<Item>", NULL },
  { "/Media/Disk/+D/Drive 2/Write protect/_Disable", NULL, menu_media_writeprotect, 0x022, "<Item>", NULL },
  { "/Media/Disk/_Opus", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Disk/Opus/Drive _1", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Disk/Opus/Drive 1/Insert _New", NULL, menu_media_insert_new, 0x41, "<Item>", NULL },
  { "/Media/Disk/Opus/Drive 1/_Insert...", NULL, menu_media_insert, 0x41, "<Item>", NULL },
  { "/Media/Disk/Opus/Drive 1/_Eject", NULL, menu_media_eject, 0x041, "<Item>", NULL },
  { "/Media/Disk/Opus/Drive 1/_Save", NULL, menu_media_eject, 0x241, "<Item>", NULL },
  { "/Media/Disk/Opus/Drive 1/Save _As...", NULL, menu_media_eject, 0x141, "<Item>", NULL },
  { "/Media/Disk/Opus/Drive 1/_Flip disk", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Disk/Opus/Drive 1/Flip disk/Turn _upside down", NULL, menu_media_flip, 0x141, "<Item>", NULL },
  { "/Media/Disk/Opus/Drive 1/Flip disk/Turn _back", NULL, menu_media_flip, 0x041, "<Item>", NULL },
  { "/Media/Disk/Opus/Drive 1/Write _protect", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Disk/Opus/Drive 1/Write protect/_Enable", NULL, menu_media_writeprotect, 0x141, "<Item>", NULL },
  { "/Media/Disk/Opus/Drive 1/Write protect/_Disable", NULL, menu_media_writeprotect, 0x041, "<Item>", NULL },
  { "/Media/Disk/Opus/Drive _2", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Disk/Opus/Drive 2/Insert _New", NULL, menu_media_insert_new, 0x42, "<Item>", NULL },
  { "/Media/Disk/Opus/Drive 2/_Insert...", NULL, menu_media_insert, 0x42, "<Item>", NULL },
  { "/Media/Disk/Opus/Drive 2/_Eject", NULL, menu_media_eject, 0x042, "<Item>", NULL },
  { "/Media/Disk/Opus/Drive 2/_Save", NULL, menu_media_eject, 0x242, "<Item>", NULL },
  { "/Media/Disk/Opus/Drive 2/Save _As...", NULL, menu_media_eject, 0x142, "<Item>", NULL },
  { "/Media/Disk/Opus/Drive 2/_Flip disk", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Disk/Opus/Drive 2/Flip disk/Turn _upside down", NULL, menu_media_flip, 0x142, "<Item>", NULL },
  { "/Media/Disk/Opus/Drive 2/Flip disk/Turn _back", NULL, menu_media_flip, 0x042, "<Item>", NULL },
  { "/Media/Disk/Opus/Drive 2/Write _protect", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Disk/Opus/Drive 2/Write protect/_Enable", NULL, menu_media_writeprotect, 0x142, "<Item>", NULL },
  { "/Media/Disk/Opus/Drive 2/Write protect/_Disable", NULL, menu_media_writeprotect, 0x042, "<Item>", NULL },
  { "/Media/_Cartridge", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Cartridge/_Timex Dock", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Cartridge/Timex Dock/_Insert...", NULL, menu_media_cartridge_timexdock_insert, 0, "<Item>", NULL },
  { "/Media/Cartridge/Timex Dock/_Eject", NULL, menu_media_cartridge_timexdock_eject, 0, "<Item>", NULL },
  { "/Media/Cartridge/_Interface II", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/Cartridge/Interface II/_Insert...", NULL, menu_media_cartridge_interfaceii_insert, 0, "<Item>", NULL },
  { "/Media/Cartridge/Interface II/_Eject", NULL, menu_media_cartridge_interfaceii_eject, 0, "<Item>", NULL },
  { "/Media/ID_E", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/IDE/Simple _8-bit", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/IDE/Simple 8-bit/_Master", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/IDE/Simple 8-bit/Master/_Insert...", NULL, menu_media_ide_insert, 1, "<Item>", NULL },
  { "/Media/IDE/Simple 8-bit/Master/_Commit", NULL, menu_media_ide_commit, 1, "<Item>", NULL },
  { "/Media/IDE/Simple 8-bit/Master/_Eject", NULL, menu_media_ide_eject, 1, "<Item>", NULL },
  { "/Media/IDE/Simple 8-bit/_Slave", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/IDE/Simple 8-bit/Slave/_Insert...", NULL, menu_media_ide_insert, 2, "<Item>", NULL },
  { "/Media/IDE/Simple 8-bit/Slave/_Commit", NULL, menu_media_ide_commit, 2, "<Item>", NULL },
  { "/Media/IDE/Simple 8-bit/Slave/_Eject", NULL, menu_media_ide_eject, 2, "<Item>", NULL },
  { "/Media/IDE/ZX_ATASP", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/IDE/ZXATASP/_Master", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/IDE/ZXATASP/Master/_Insert...", NULL, menu_media_ide_insert, 3, "<Item>", NULL },
  { "/Media/IDE/ZXATASP/Master/_Commit", NULL, menu_media_ide_commit, 3, "<Item>", NULL },
  { "/Media/IDE/ZXATASP/Master/_Eject", NULL, menu_media_ide_eject, 3, "<Item>", NULL },
  { "/Media/IDE/ZXATASP/_Slave", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/IDE/ZXATASP/Slave/_Insert...", NULL, menu_media_ide_insert, 4, "<Item>", NULL },
  { "/Media/IDE/ZXATASP/Slave/_Commit", NULL, menu_media_ide_commit, 4, "<Item>", NULL },
  { "/Media/IDE/ZXATASP/Slave/_Eject", NULL, menu_media_ide_eject, 4, "<Item>", NULL },
  { "/Media/IDE/ZX_CF CompactFlash", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/IDE/ZXCF CompactFlash/_Insert...", NULL, menu_media_ide_insert, 5, "<Item>", NULL },
  { "/Media/IDE/ZXCF CompactFlash/_Commit", NULL, menu_media_ide_commit, 5, "<Item>", NULL },
  { "/Media/IDE/ZXCF CompactFlash/_Eject", NULL, menu_media_ide_eject, 5, "<Item>", NULL },
  { "/Media/IDE/_DivIDE", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/IDE/DivIDE/_Master", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/IDE/DivIDE/Master/_Insert...", NULL, menu_media_ide_insert, 6, "<Item>", NULL },
  { "/Media/IDE/DivIDE/Master/_Commit", NULL, menu_media_ide_commit, 6, "<Item>", NULL },
  { "/Media/IDE/DivIDE/Master/_Eject", NULL, menu_media_ide_eject, 6, "<Item>", NULL },
  { "/Media/IDE/DivIDE/_Slave", NULL, NULL, 0, "<Branch>", NULL },
  { "/Media/IDE/DivIDE/Slave/_Insert...", NULL, menu_media_ide_insert, 7, "<Item>", NULL },
  { "/Media/IDE/DivIDE/Slave/_Commit", NULL, menu_media_ide_commit, 7, "<Item>", NULL },
  { "/Media/IDE/DivIDE/Slave/_Eject", NULL, menu_media_ide_eject, 7, "<Item>", NULL },
  { "/Help", NULL, NULL, 0, "<Branch>", NULL },
  { "/Help/_Keyboard...", NULL, menu_help_keyboard, 0, "<Item>", NULL },
  { "/Help/_About...", NULL, menu_help_about, 0, "<Item>", NULL },

};

guint gtkui_menu_data_size =
  sizeof( gtkui_menu_data ) / sizeof( GtkItemFactoryEntry );
