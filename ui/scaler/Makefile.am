## Process this file with automake to produce Makefile.in
## Copyright (c) 2001 Philip Kendall
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

de_fuse_SOURCES += ui/scaler/scaler.c

de_fuse_LDADD += \
              ui/scaler/scalers16.o \
              ui/scaler/scalers32.o

de_fuse_DEPENDENCIES += \
                     ui/scaler/scalers16.o \
                     ui/scaler/scalers32.o

ui/scaler/scalers16.o: $(srcdir)/ui/scaler/scalers.c
	$(AM_V_CC)$(COMPILE) -DSCALER_DATA_SIZE=2 -c $(srcdir)/ui/scaler/scalers.c -o $@

ui/scaler/scalers32.o: $(srcdir)/ui/scaler/scalers.c
	$(AM_V_CC)$(COMPILE) -DSCALER_DATA_SIZE=4 -c $(srcdir)/ui/scaler/scalers.c -o $@

noinst_HEADERS += \
                  ui/scaler/scaler.h \
                  ui/scaler/scaler_internals.h

EXTRA_DIST += \
              ui/scaler/scalers.c \
              ui/scaler/scaler_hq2x.c \
              ui/scaler/scaler_hq3x.c \
              ui/scaler/scaler_hq4x.c

CLEANFILES += \
              ui/scaler/scalers16.o \
              ui/scaler/scalers32.o
