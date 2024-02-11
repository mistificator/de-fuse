## Process this file with automake to produce Makefile.in
## Copyright (c) 2024 ZXLDR

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
## E-mail: ZXLDR@yandex.ru

if UI_QT

de_fuse_SOURCES += $(ui_qt_files)

BUILT_SOURCES += $(ui_qt_built)

endif

CLEANFILES += $(ui_qt_built)

ui_qt_files = \
                ui/qt/moc_qt_ui.cpp \
                ui/qt/qt_ui.cpp \
                ui/qt/menu_data.c \
                ui/qt/options.c

ui_qt_built = \
               ui/qt/moc_qt_ui.cpp \
               ui/qt/ui_qt_ui.h \
               ui/qt/menu_data.c \
               ui/qt/menu_data.ui \
               ui/qt/options.c \
               ui/qt/options_internals.h
EXTRA_DIST += \
              ui/qt/options.pl \
              ui/qt/options-header.pl
  
ui/qt/menu_data.c: $(srcdir)/perl/cpp-perl.pl $(srcdir)/menu_data.pl $(srcdir)/menu_data.dat config.h
	@$(MKDIR_P) ui/qt
	$(AM_V_GEN)$(PERL) $(srcdir)/perl/cpp-perl.pl config.h $(srcdir)/menu_data.dat | $(PERL) -I$(srcdir)/perl $(srcdir)/menu_data.pl qt c > $@.tmp && mv $@.tmp $@

ui/qt/menu_data.ui: $(srcdir)/perl/cpp-perl.pl $(srcdir)/menu_data.pl $(srcdir)/menu_data.dat config.h
	@$(MKDIR_P) ui/qt
	$(AM_V_GEN)$(PERL) $(srcdir)/perl/cpp-perl.pl config.h $(srcdir)/menu_data.dat | $(PERL) -I$(srcdir)/perl $(srcdir)/menu_data.pl qt ui > $@.tmp && mv $@.tmp $@

ui/qt/options.c: $(srcdir)/perl/cpp-perl.pl config.h $(srcdir)/ui/qt/options.pl $(srcdir)/ui/options.dat $(srcdir)/perl/Fuse.pm $(srcdir)/perl/Fuse/Dialog.pm
	@$(MKDIR_P) ui/qt
	$(AM_V_GEN)$(PERL) $(srcdir)/perl/cpp-perl.pl config.h $(srcdir)/ui/options.dat | $(PERL) -I$(srcdir)/perl $(srcdir)/ui/qt/options.pl - > $@.tmp && mv $@.tmp $@

ui/qt/options_internals.h: $(srcdir)/perl/cpp-perl.pl config.h $(srcdir)/ui/qt/options-header.pl $(srcdir)/ui/options.dat $(srcdir)/perl/Fuse.pm $(srcdir)/perl/Fuse/Dialog.pm
	@$(MKDIR_P) ui/qt
	$(AM_V_GEN)$(PERL) $(srcdir)/perl/cpp-perl.pl config.h $(srcdir)/ui/options.dat | $(PERL) -I$(srcdir)/perl $(srcdir)/ui/qt/options-header.pl - > $@.tmp && mv $@.tmp $@



QT_CXXFLAGS = @QT_CXXFLAGS@
QT_LIBS     = @QT_LIBS@
MOC         = @QT_MOC@
UIC         = @QT_UIC@
RCC         = @QT_RCC@

ui/qt/ui_qt_ui.h: $(srcdir)/ui/qt/menu_data.ui
	$(AM_V_GEN)$(UIC) $(srcdir)/ui/qt/menu_data.ui > $@.tmp && mv $@.tmp $@

ui/qt/moc_qt_ui.cpp: $(srcdir)/ui/qt/qt_ui.h
	$(AM_V_GEN)$(MOC) $(srcdir)/ui/qt/qt_ui.h > $@.tmp && mv $@.tmp $@
