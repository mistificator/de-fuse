## Process this file with automake to produce Makefile.in
## Copyright (c) 2004 Philip Kendall
## Copyright (c) 2015 Sergio Baldoví

## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License along
## with this program; if not, write to the Free Software Foundation, Inc.,
## 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
##
## Author contact information:
##
## E-mail: philip-fuse@shadowmagic.org.uk

de_fuse_SOURCES += sound/blipbuffer.c

EXTRA_de_fuse_SOURCES += \
                      sound/alsasound.c \
                      sound/aosound.c \
                      sound/coreaudiosound.c \
                      sound/dxsound.c \
                      sound/hpsound.c \
                      sound/nullsound.c \
                      sound/osssound.c \
                      sound/pulsesound.c \
                      sound/sdlsound.c \
                      sound/sfifo.c \
                      sound/sunsound.c \
                      sound/wiisound.c \
                      sound/win32sound.c

noinst_HEADERS += \
                  sound/blipbuffer.h \
                  sound/sfifo.h

de_fuse_DEPENDENCIES += $(SOUND_LIBADD)
de_fuse_LDADD += $(SOUND_LIBS) $(SOUND_LIBADD)
