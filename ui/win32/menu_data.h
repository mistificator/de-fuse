/* menu_data.h: menu structure for Fuse
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

/* This file is autogenerated from menu_data.dat by ../../../ui/win32/../../menu_data.pl.
   Any changes made here will not be preserved. */

#include <config.h>

#include "menu.h"

#include <windows.h>

#define IDM_MENU_FILE 100
#define IDM_MENU_FILE_OPEN 101
#define IDM_MENU_FILE_SAVESNAPSHOT 102
#define IDM_MENU_FILE_RECORDING 103
#define IDM_MENU_FILE_RECORDING_RECORD 104
#define IDM_MENU_FILE_RECORDING_RECORDFROMSNAPSHOT 105
#define IDM_MENU_FILE_RECORDING_INSERTSNAPSHOT 106
#define IDM_MENU_FILE_RECORDING_ROLLBACK 107
#define IDM_MENU_FILE_RECORDING_ROLLBACKTO 108
#define IDM_MENU_FILE_RECORDING_PLAY 109
#define IDM_MENU_FILE_RECORDING_STOP 110
#define IDM_MENU_FILE_AYLOGGING 111
#define IDM_MENU_FILE_AYLOGGING_RECORD 112
#define IDM_MENU_FILE_AYLOGGING_STOP 113
#define IDM_MENU_FILE_OPENSCRSCREENSHOT 114
#define IDM_MENU_FILE_SAVESCREENASSCR 115
#define IDM_MENU_FILE_SAVESCREENASPNG 116
#define IDM_MENU_FILE_MOVIES 117
#define IDM_MENU_FILE_MOVIES_RECORDMOVIEASSCR 118
#define IDM_MENU_FILE_MOVIES_RECORDMOVIEASPNG 119
#define IDM_MENU_FILE_MOVIES_STOPMOVIERECORDING 120
#define IDM_MENU_FILE_LOADBINARYDATA 121
#define IDM_MENU_FILE_SAVEBINARYDATA 122
#define IDM_MENU_FILE_EXIT 123
#define IDM_MENU_OPTIONS 124
#define IDM_MENU_OPTIONS_GENERAL 125
#define IDM_MENU_OPTIONS_SOUND 126
#define IDM_MENU_OPTIONS_PERIPHERALS 127
#define IDM_MENU_OPTIONS_RZX 128
#define IDM_MENU_OPTIONS_JOYSTICKS 129
#define IDM_MENU_OPTIONS_JOYSTICKS_KEYBOARD 130
#define IDM_MENU_OPTIONS_SELECTROMS 131
#define IDM_MENU_OPTIONS_SELECTROMS_SPECTRUM16K 132
#define IDM_MENU_OPTIONS_SELECTROMS_SPECTRUM48K 133
#define IDM_MENU_OPTIONS_SELECTROMS_SPECTRUM128K 134
#define IDM_MENU_OPTIONS_SELECTROMS_SPECTRUM2 135
#define IDM_MENU_OPTIONS_SELECTROMS_SPECTRUM2A 136
#define IDM_MENU_OPTIONS_SELECTROMS_SPECTRUM3 137
#define IDM_MENU_OPTIONS_SELECTROMS_SPECTRUM3E 138
#define IDM_MENU_OPTIONS_SELECTROMS_TIMEXTC2048 139
#define IDM_MENU_OPTIONS_SELECTROMS_TIMEXTC2068 140
#define IDM_MENU_OPTIONS_SELECTROMS_TIMEXTS2068 141
#define IDM_MENU_OPTIONS_SELECTROMS_PENTAGON128K 142
#define IDM_MENU_OPTIONS_SELECTROMS_PENTAGON512K 143
#define IDM_MENU_OPTIONS_SELECTROMS_PENTAGON1024K 144
#define IDM_MENU_OPTIONS_SELECTROMS_SCORPIONZS256 145
#define IDM_MENU_OPTIONS_SELECTROMS_SPECTRUMSE 146
#define IDM_MENU_OPTIONS_SELECTROMS_INTERFACEI 147
#define IDM_MENU_OPTIONS_SELECTROMS_BETA128 148
#define IDM_MENU_OPTIONS_SELECTROMS_D 149
#define IDM_MENU_OPTIONS_FILTER 150
#define IDM_MENU_OPTIONS_SAVE 151
#define IDM_MENU_MACHINE 152
#define IDM_MENU_MACHINE_PAUSE 153
#define IDM_MENU_MACHINE_RESET 154
#define IDM_MENU_MACHINE_HARDRESET 155
#define IDM_MENU_MACHINE_SELECT 156
#define IDM_MENU_MACHINE_DEBUGGER 157
#define IDM_MENU_MACHINE_POKEFINDER 158
#define IDM_MENU_MACHINE_MEMORYBROWSER 159
#define IDM_MENU_MACHINE_PROFILER 160
#define IDM_MENU_MACHINE_PROFILER_START 161
#define IDM_MENU_MACHINE_PROFILER_STOP 162
#define IDM_MENU_MACHINE_NMI 163
#define IDM_MENU_MEDIA 164
#define IDM_MENU_MEDIA_TAPE 165
#define IDM_MENU_MEDIA_TAPE_OPEN 166
#define IDM_MENU_MEDIA_TAPE_PLAY 167
#define IDM_MENU_MEDIA_TAPE_BROWSE 168
#define IDM_MENU_MEDIA_TAPE_REWIND 169
#define IDM_MENU_MEDIA_TAPE_CLEAR 170
#define IDM_MENU_MEDIA_TAPE_WRITE 171
#define IDM_MENU_MEDIA_TAPE_RECORDSTART 172
#define IDM_MENU_MEDIA_TAPE_RECORDSTOP 173
#define IDM_MENU_MEDIA_INTERFACEI 174
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE1 175
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE1_INSERTNEW 176
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE1_INSERT 177
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE1_EJECT 178
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE1_EJECTANDWRITE 179
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE1_WRITEPROTECT 180
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE1_WRITEPROTECT_ENABLE 181
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE1_WRITEPROTECT_DISABLE 182
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE2 183
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE2_INSERTNEW 184
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE2_INSERT 185
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE2_EJECT 186
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE2_EJECTANDWRITE 187
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE2_WRITEPROTECT 188
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE2_WRITEPROTECT_ENABLE 189
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE2_WRITEPROTECT_DISABLE 190
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE3 191
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE3_INSERTNEW 192
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE3_INSERT 193
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE3_EJECT 194
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE3_EJECTANDWRITE 195
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE3_WRITEPROTECT 196
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE3_WRITEPROTECT_ENABLE 197
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE3_WRITEPROTECT_DISABLE 198
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE4 199
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE4_INSERTNEW 200
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE4_INSERT 201
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE4_EJECT 202
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE4_EJECTANDWRITE 203
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE4_WRITEPROTECT 204
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE4_WRITEPROTECT_ENABLE 205
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE4_WRITEPROTECT_DISABLE 206
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE5 207
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE5_INSERTNEW 208
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE5_INSERT 209
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE5_EJECT 210
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE5_EJECTANDWRITE 211
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE5_WRITEPROTECT 212
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE5_WRITEPROTECT_ENABLE 213
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE5_WRITEPROTECT_DISABLE 214
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE6 215
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE6_INSERTNEW 216
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE6_INSERT 217
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE6_EJECT 218
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE6_EJECTANDWRITE 219
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE6_WRITEPROTECT 220
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE6_WRITEPROTECT_ENABLE 221
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE6_WRITEPROTECT_DISABLE 222
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE7 223
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE7_INSERTNEW 224
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE7_INSERT 225
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE7_EJECT 226
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE7_EJECTANDWRITE 227
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE7_WRITEPROTECT 228
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE7_WRITEPROTECT_ENABLE 229
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE7_WRITEPROTECT_DISABLE 230
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE8 231
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE8_INSERTNEW 232
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE8_INSERT 233
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE8_EJECT 234
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE8_EJECTANDWRITE 235
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE8_WRITEPROTECT 236
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE8_WRITEPROTECT_ENABLE 237
#define IDM_MENU_MEDIA_INTERFACEI_MICRODRIVE8_WRITEPROTECT_DISABLE 238
#define IDM_MENU_MEDIA_INTERFACEI_RS232 239
#define IDM_MENU_MEDIA_INTERFACEI_RS232_PLUGRXD 240
#define IDM_MENU_MEDIA_INTERFACEI_RS232_UNPLUGRXD 241
#define IDM_MENU_MEDIA_INTERFACEI_RS232_PLUGTXD 242
#define IDM_MENU_MEDIA_INTERFACEI_RS232_UNPLUGTXD 243
#define IDM_MENU_MEDIA_DISK 244
#define IDM_MENU_MEDIA_DISK_3 245
#define IDM_MENU_MEDIA_DISK_3_DRIVEA 246
#define IDM_MENU_MEDIA_DISK_3_DRIVEA_INSERTNEW 247
#define IDM_MENU_MEDIA_DISK_3_DRIVEA_INSERT 248
#define IDM_MENU_MEDIA_DISK_3_DRIVEA_EJECT 249
#define IDM_MENU_MEDIA_DISK_3_DRIVEA_EJECTANDWRITE 250
#define IDM_MENU_MEDIA_DISK_3_DRIVEA_WRITEPROTECT 251
#define IDM_MENU_MEDIA_DISK_3_DRIVEA_WRITEPROTECT_ENABLE 252
#define IDM_MENU_MEDIA_DISK_3_DRIVEA_WRITEPROTECT_DISABLE 253
#define IDM_MENU_MEDIA_DISK_3_DRIVEB 254
#define IDM_MENU_MEDIA_DISK_3_DRIVEB_INSERTNEW 255
#define IDM_MENU_MEDIA_DISK_3_DRIVEB_INSERT 256
#define IDM_MENU_MEDIA_DISK_3_DRIVEB_EJECT 257
#define IDM_MENU_MEDIA_DISK_3_DRIVEB_EJECTANDWRITE 258
#define IDM_MENU_MEDIA_DISK_3_DRIVEB_WRITEPROTECT 259
#define IDM_MENU_MEDIA_DISK_3_DRIVEB_WRITEPROTECT_ENABLE 260
#define IDM_MENU_MEDIA_DISK_3_DRIVEB_WRITEPROTECT_DISABLE 261
#define IDM_MENU_MEDIA_DISK_BETA 262
#define IDM_MENU_MEDIA_DISK_BETA_DRIVEA 263
#define IDM_MENU_MEDIA_DISK_BETA_DRIVEA_INSERTNEW 264
#define IDM_MENU_MEDIA_DISK_BETA_DRIVEA_INSERT 265
#define IDM_MENU_MEDIA_DISK_BETA_DRIVEA_EJECT 266
#define IDM_MENU_MEDIA_DISK_BETA_DRIVEA_EJECTANDWRITE 267
#define IDM_MENU_MEDIA_DISK_BETA_DRIVEA_WRITEPROTECT 268
#define IDM_MENU_MEDIA_DISK_BETA_DRIVEA_WRITEPROTECT_ENABLE 269
#define IDM_MENU_MEDIA_DISK_BETA_DRIVEA_WRITEPROTECT_DISABLE 270
#define IDM_MENU_MEDIA_DISK_BETA_DRIVEB 271
#define IDM_MENU_MEDIA_DISK_BETA_DRIVEB_INSERTNEW 272
#define IDM_MENU_MEDIA_DISK_BETA_DRIVEB_INSERT 273
#define IDM_MENU_MEDIA_DISK_BETA_DRIVEB_EJECT 274
#define IDM_MENU_MEDIA_DISK_BETA_DRIVEB_EJECTANDWRITE 275
#define IDM_MENU_MEDIA_DISK_BETA_DRIVEB_WRITEPROTECT 276
#define IDM_MENU_MEDIA_DISK_BETA_DRIVEB_WRITEPROTECT_ENABLE 277
#define IDM_MENU_MEDIA_DISK_BETA_DRIVEB_WRITEPROTECT_DISABLE 278
#define IDM_MENU_MEDIA_DISK_BETA_DRIVEC 279
#define IDM_MENU_MEDIA_DISK_BETA_DRIVEC_INSERTNEW 280
#define IDM_MENU_MEDIA_DISK_BETA_DRIVEC_INSERT 281
#define IDM_MENU_MEDIA_DISK_BETA_DRIVEC_EJECT 282
#define IDM_MENU_MEDIA_DISK_BETA_DRIVEC_EJECTANDWRITE 283
#define IDM_MENU_MEDIA_DISK_BETA_DRIVEC_WRITEPROTECT 284
#define IDM_MENU_MEDIA_DISK_BETA_DRIVEC_WRITEPROTECT_ENABLE 285
#define IDM_MENU_MEDIA_DISK_BETA_DRIVEC_WRITEPROTECT_DISABLE 286
#define IDM_MENU_MEDIA_DISK_BETA_DRIVED 287
#define IDM_MENU_MEDIA_DISK_BETA_DRIVED_INSERTNEW 288
#define IDM_MENU_MEDIA_DISK_BETA_DRIVED_INSERT 289
#define IDM_MENU_MEDIA_DISK_BETA_DRIVED_EJECT 290
#define IDM_MENU_MEDIA_DISK_BETA_DRIVED_EJECTANDWRITE 291
#define IDM_MENU_MEDIA_DISK_BETA_DRIVED_WRITEPROTECT 292
#define IDM_MENU_MEDIA_DISK_BETA_DRIVED_WRITEPROTECT_ENABLE 293
#define IDM_MENU_MEDIA_DISK_BETA_DRIVED_WRITEPROTECT_DISABLE 294
#define IDM_MENU_MEDIA_DISK_D 295
#define IDM_MENU_MEDIA_DISK_D_DRIVE1 296
#define IDM_MENU_MEDIA_DISK_D_DRIVE1_INSERTNEW 297
#define IDM_MENU_MEDIA_DISK_D_DRIVE1_INSERT 298
#define IDM_MENU_MEDIA_DISK_D_DRIVE1_EJECT 299
#define IDM_MENU_MEDIA_DISK_D_DRIVE1_EJECTANDWRITE 300
#define IDM_MENU_MEDIA_DISK_D_DRIVE1_WRITEPROTECT 301
#define IDM_MENU_MEDIA_DISK_D_DRIVE1_WRITEPROTECT_ENABLE 302
#define IDM_MENU_MEDIA_DISK_D_DRIVE1_WRITEPROTECT_DISABLE 303
#define IDM_MENU_MEDIA_DISK_D_DRIVE2 304
#define IDM_MENU_MEDIA_DISK_D_DRIVE2_INSERTNEW 305
#define IDM_MENU_MEDIA_DISK_D_DRIVE2_INSERT 306
#define IDM_MENU_MEDIA_DISK_D_DRIVE2_EJECT 307
#define IDM_MENU_MEDIA_DISK_D_DRIVE2_EJECTANDWRITE 308
#define IDM_MENU_MEDIA_DISK_D_DRIVE2_WRITEPROTECT 309
#define IDM_MENU_MEDIA_DISK_D_DRIVE2_WRITEPROTECT_ENABLE 310
#define IDM_MENU_MEDIA_DISK_D_DRIVE2_WRITEPROTECT_DISABLE 311
#define IDM_MENU_MEDIA_CARTRIDGE 312
#define IDM_MENU_MEDIA_CARTRIDGE_TIMEXDOCK 313
#define IDM_MENU_MEDIA_CARTRIDGE_TIMEXDOCK_INSERT 314
#define IDM_MENU_MEDIA_CARTRIDGE_TIMEXDOCK_EJECT 315
#define IDM_MENU_MEDIA_CARTRIDGE_INTERFACEII 316
#define IDM_MENU_MEDIA_CARTRIDGE_INTERFACEII_INSERT 317
#define IDM_MENU_MEDIA_CARTRIDGE_INTERFACEII_EJECT 318
#define IDM_MENU_MEDIA_IDE 319
#define IDM_MENU_MEDIA_IDE_SIMPLE8BIT 320
#define IDM_MENU_MEDIA_IDE_SIMPLE8BIT_MASTER 321
#define IDM_MENU_MEDIA_IDE_SIMPLE8BIT_MASTER_INSERT 322
#define IDM_MENU_MEDIA_IDE_SIMPLE8BIT_MASTER_COMMIT 323
#define IDM_MENU_MEDIA_IDE_SIMPLE8BIT_MASTER_EJECT 324
#define IDM_MENU_MEDIA_IDE_SIMPLE8BIT_SLAVE 325
#define IDM_MENU_MEDIA_IDE_SIMPLE8BIT_SLAVE_INSERT 326
#define IDM_MENU_MEDIA_IDE_SIMPLE8BIT_SLAVE_COMMIT 327
#define IDM_MENU_MEDIA_IDE_SIMPLE8BIT_SLAVE_EJECT 328
#define IDM_MENU_MEDIA_IDE_ZXATASP 329
#define IDM_MENU_MEDIA_IDE_ZXATASP_MASTER 330
#define IDM_MENU_MEDIA_IDE_ZXATASP_MASTER_INSERT 331
#define IDM_MENU_MEDIA_IDE_ZXATASP_MASTER_COMMIT 332
#define IDM_MENU_MEDIA_IDE_ZXATASP_MASTER_EJECT 333
#define IDM_MENU_MEDIA_IDE_ZXATASP_SLAVE 334
#define IDM_MENU_MEDIA_IDE_ZXATASP_SLAVE_INSERT 335
#define IDM_MENU_MEDIA_IDE_ZXATASP_SLAVE_COMMIT 336
#define IDM_MENU_MEDIA_IDE_ZXATASP_SLAVE_EJECT 337
#define IDM_MENU_MEDIA_IDE_ZXCFCOMPACTFLASH 338
#define IDM_MENU_MEDIA_IDE_ZXCFCOMPACTFLASH_INSERT 339
#define IDM_MENU_MEDIA_IDE_ZXCFCOMPACTFLASH_COMMIT 340
#define IDM_MENU_MEDIA_IDE_ZXCFCOMPACTFLASH_EJECT 341
#define IDM_MENU_MEDIA_IDE_DIVIDE 342
#define IDM_MENU_MEDIA_IDE_DIVIDE_MASTER 343
#define IDM_MENU_MEDIA_IDE_DIVIDE_MASTER_INSERT 344
#define IDM_MENU_MEDIA_IDE_DIVIDE_MASTER_COMMIT 345
#define IDM_MENU_MEDIA_IDE_DIVIDE_MASTER_EJECT 346
#define IDM_MENU_MEDIA_IDE_DIVIDE_SLAVE 347
#define IDM_MENU_MEDIA_IDE_DIVIDE_SLAVE_INSERT 348
#define IDM_MENU_MEDIA_IDE_DIVIDE_SLAVE_COMMIT 349
#define IDM_MENU_MEDIA_IDE_DIVIDE_SLAVE_EJECT 350
#define IDM_MENU_HELP 351
#define IDM_MENU_HELP_KEYBOARD 352