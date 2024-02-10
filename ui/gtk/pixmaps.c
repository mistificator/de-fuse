/* pixmaps.c: icon pixmaps
   Copyright (c) 2003-2005 Fredrick Meunier, Philip Kendall, Darren Salt

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

#include "config.h"

#include "gtkinternals.h"

const char *gtkpixmap_tape_inactive[] = {
"27 17 13 1",
" 	c None",
".	c #D5D5D5",
"+	c #7C7C7C",
"@	c #A5A5A5",
"#	c #7F7F7F",
"$	c #979797",
"%	c #DEDEDE",
"&	c #F9F9F9",
"*	c #626262",
"=	c #F8F8F8",
"-	c #636363",
";	c #616161",
">	c #6A6A6A",
"...........................",
".+.......................+.",
"..@@@@@@@@@@@@@@@@@@@@@@@..",
".@@@@@@@@@@@@@@@@@@@@@@@@@.",
".@@@@@@@@@@@@@@@@@@@@@@@@@.",
".@@@@@###############@@@@@.",
".@@@@$#%&%@*****@%&%#$@@@@.",
".@@@@#@&&=@-****@&&=@#@@@@.",
".@@@@$#%=%@*;***@%=%#$@@@@.",
".@@@@@###############@@@@@.",
".@@@@@@@@@@@@@@@@@@@@@@@@@.",
".@@@@@@@@@@@@@@@@@@@@@@@@@.",
".....>>>>>>>>>>>>>>>>>.....",
"....$>...............>$....",
"....>$...............$>....",
".+..>.................>..+.",
"....>.................>...."};

const char *gtkpixmap_tape_active[] = {
"27 17 13 1",
" 	c None",
".	c #00D500",
"+	c #007C00",
"@	c #00A500",
"#	c #007F00",
"$	c #009700",
"%	c #00DE00",
"&	c #00F900",
"*	c #006200",
"=	c #00F800",
"-	c #006300",
";	c #006100",
">	c #006A00",
"...........................",
".+.......................+.",
"..@@@@@@@@@@@@@@@@@@@@@@@..",
".@@@@@@@@@@@@@@@@@@@@@@@@@.",
".@@@@@@@@@@@@@@@@@@@@@@@@@.",
".@@@@@###############@@@@@.",
".@@@@$#%&%@*****@%&%#$@@@@.",
".@@@@#@&&=@-****@&&=@#@@@@.",
".@@@@$#%=%@*;***@%=%#$@@@@.",
".@@@@@###############@@@@@.",
".@@@@@@@@@@@@@@@@@@@@@@@@@.",
".@@@@@@@@@@@@@@@@@@@@@@@@@.",
".....>>>>>>>>>>>>>>>>>.....",
"....$>...............>$....",
"....>$...............$>....",
".+..>.................>..+.",
"....>.................>...."};

const char *gtkpixmap_mdr_inactive[] = {
"15 20 6 1",
" 	c None",
".	c #000000",
"+	c #686868",
"@	c #888888",
"#	c #AFAFAF",
"$	c #D8D8D8",
"##+$$$$$$$$####",
"###+++..+++####",
"+##++++++++####",
"$+##+++++++####",
"$+#############",
"$+@##@@@@@##@@#",
"$+############@",
"+#############@",
"@#############@",
"@#############@",
"@#############@",
"@#############@",
"@#############@",
"@#############@",
"#@@@#######@@@#",
"###############",
"###############",
"+++++++++++++++",
"+++++++++++++++",
"+++++++++++++++"};

const char *gtkpixmap_mdr_active[] = {
"15 20 6 1",
" 	c None",
".	c #000000",
"+	c #686868",
"@	c #008800",
"#	c #00AF00",
"$	c #00D800",
"##+$$$$$$$$####",
"###+++..+++####",
"+##++++++++####",
"$+##+++++++####",
"$+#############",
"$+@##@@@@@##@@#",
"$+############@",
"+#############@",
"@#############@",
"@#############@",
"@#############@",
"@#############@",
"@#############@",
"@#############@",
"#@@@#######@@@#",
"###############",
"###############",
"+++++++++++++++",
"+++++++++++++++",
"+++++++++++++++"};

const char *gtkpixmap_disk_inactive[] = {
"15 20 7 1",
" 	c None",
".	c #A5A5A5",
"+	c #A6A6A6",
"@	c #6A6A6A",
"#	c #696969",
"$	c #DFDFDF",
"%	c #F9F9F9",
"..+.+++++..++++",
"+++++.+@.+.+.+.",
"+++.+..@..+.+.+",
"++.++++@+.++..+",
"...++..#+++..+.",
"++.+++.@++.+.+.",
"+.++.+.#.+++.++",
"+......+....+++",
"+.++..+..+.++++",
".++.++$%$+.+.+.",
".+.++.%%%+..++.",
"..+...$%$..+++.",
"+..+..+++++++..",
"++..+...++.+...",
"+++.++.++......",
"..@#@@###@#@#++",
"++@#@@@@@@##@..",
"+.@#@#@@@##@@.+",
"++@@@@@@@#@@#..",
"..##@#@@@@#@#.+"};

const char *gtkpixmap_disk_active[] = {
"15 20 7 1",
" 	c None",
".	c #00A500",
"+	c #00A600",
"@	c #006A00",
"#	c #006900",
"$	c #00DF00",
"%	c #00F900",
"..+.+++++..++++",
"+++++.+@.+.+.+.",
"+++.+..@..+.+.+",
"++.++++@+.++..+",
"...++..#+++..+.",
"++.+++.@++.+.+.",
"+.++.+.#.+++.++",
"+......+....+++",
"+.++..+..+.++++",
".++.++$%$+.+.+.",
".+.++.%%%+..++.",
"..+...$%$..+++.",
"+..+..+++++++..",
"++..+...++.+...",
"+++.++.++......",
"..@#@@###@#@#++",
"++@#@@@@@@##@..",
"+.@#@#@@@##@@.+",
"++@@@@@@@#@@#..",
"..##@#@@@@#@#.+"};

const char *gtkpixmap_pause_inactive[] = {
"30 21 7 1",
" 	c None",
".	c #6C6C6C",
"+	c #6A6A6A",
"@	c #6D6D6D",
"#	c #6E6E6E",
"$	c #696969",
"%	c #6B6B6B",
"     .+   @#                  ",
"    #$$+ %$$#                 ",
"     +$# #$$                  ",
" @$#         .+               ",
" $$$        #$$+   .+   @#    ",
" .$@  #+$.   %$#  #$$+ %$$#   ",
"     #$$$$+        +$# #$$    ",
"     $$$$$$.   @$#         .+ ",
"    @$$$$$$$   $$$        #$$+",
"    +$$$$$$$   .$@  #+$.   %$#",
"    $$$$$$$$#      #$$$$+     ",
"    $$$$$$$$#      $$$$$$.    ",
"    +$$$$$$$      @$$$$$$$    ",
"    #$$$$$$$      +$$$$$$$    ",
"     $$$$$$@      $$$$$$$$#   ",
"     #$$$$+       $$$$$$$$#   ",
"       %$@        +$$$$$$$    ",
"                  #$$$$$$$    ",
"                   $$$$$$@    ",
"                   #$$$$+     ",
"                     %$@      "};

const char *gtkpixmap_pause_active[] = {
"30 21 7 1",
" 	c None",
".	c #D80000",
"+	c #D40000",
"@	c #DA0000",
"#	c #DC0000",
"$	c #D20000",
"%	c #D60000",
"     .+   @#                  ",
"    #$$+ %$$#                 ",
"     +$# #$$                  ",
" @$#         .+               ",
" $$$        #$$+   .+   @#    ",
" .$@  #+$.   %$#  #$$+ %$$#   ",
"     #$$$$+        +$# #$$    ",
"     $$$$$$.   @$#         .+ ",
"    @$$$$$$$   $$$        #$$+",
"    +$$$$$$$   .$@  #+$.   %$#",
"    $$$$$$$$#      #$$$$+     ",
"    $$$$$$$$#      $$$$$$.    ",
"    +$$$$$$$      @$$$$$$$    ",
"    #$$$$$$$      +$$$$$$$    ",
"     $$$$$$@      $$$$$$$$#   ",
"     #$$$$+       $$$$$$$$#   ",
"       %$@        +$$$$$$$    ",
"                  #$$$$$$$    ",
"                   $$$$$$@    ",
"                   #$$$$+     ",
"                     %$@      "};

const char *gtkpixmap_tape_marker[] = {
"8 16 2 1",
" 	c None",
".	c #212FC6",
".       ",
"..      ",
"...     ",
"....    ",
".....   ",
"......  ",
"....... ",
"........",
"........",
"....... ",
"......  ",
".....   ",
"....    ",
"...     ",
"..      ",
".       "};

const char *gtkpixmap_mouse_inactive[] = {
"14 21 4 1",
"     c None",
"#    c #6C6C6C",
"+    c #A0A0A0",
".    c #FFFFFF",
"      ..      ",
"      ..      ",
" +####++####+ ",
" #####++##### ",
" ####++++#### ",
" ####+##+#### ",
" ####+##+#### ",
" ####+##+#### ",
" ####+##+#### ",
" ####+##+#### ",
" ++++++++++++ ",
" ############ ",
" ############ ",
" ############ ",
" ############ ",
" ############ ",
" ############ ",
" ############ ",
" +##########+ ",
" +##########+ ",
"  ++######++  "};

const char *gtkpixmap_mouse_active[] = {
"14 21 4 1",
"     c None",
"#    c #0000D0",
"+    c #6C6CD0",
".    c #FFFFFF",
"      ..      ",
"      ..      ",
" +####++####+ ",
" #####++##### ",
" ####++++#### ",
" ####+##+#### ",
" ####+##+#### ",
" ####+##+#### ",
" ####+##+#### ",
" ####+##+#### ",
" ++++++++++++ ",
" ############ ",
" ############ ",
" ############ ",
" ############ ",
" ############ ",
" ############ ",
" ############ ",
" +##########+ ",
" +##########+ ",
"  ++######++  "};
