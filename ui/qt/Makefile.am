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

if USE_QT

de_fuse_SOURCES += $(ui_qt_files)

BUILT_SOURCES += $(ui_qt_built)

endif

CLEANFILES += $(ui_qt_built)

ui_qt_files = \
                ui/qt/moc_qt_ui.cpp \
                ui/qt/qrc_qt_ui.cpp \
                ui/qt/qt_ui.cpp \
                ui/qt/keysyms.cpp \
                ui/qt/moc_debugger.cpp \
                ui/qt/debugger.cpp \
                ui/qt/moc_hexview.cpp \
                ui/qt/hexview.cpp

ui_qt_built = \
               ui/qt/moc_qt_ui.cpp \
               ui/qt/qrc_qt_ui.cpp \
               ui/qt/ui_qt_ui.h \
               ui/qt/menu_data.ui \
               ui/qt/menu_data.cpp \
               ui/qt/options.cpp \
               ui/qt/options_internals.h \
               ui/qt/keysyms.cpp \
               ui/qt/moc_debugger.cpp \
               ui/qt/ui_debugger.h \
               ui/qt/moc_hexview.cpp \
               ui/qt/ui_hexview.h

EXTRA_DIST += \
              ui/qt/options.pl \
              ui/qt/options-header.pl

ui/qt/keysyms.cpp: $(srcdir)/keysyms.pl $(srcdir)/keysyms.dat
	@$(MKDIR_P) ui/qt
	$(AM_V_GEN)$(PERL) -I$(srcdir)/perl $(srcdir)/keysyms.pl qt $(srcdir)/keysyms.dat > $@.tmp && mv $@.tmp $@

ui/qt/menu_data.ui: $(srcdir)/perl/cpp-perl.pl $(srcdir)/menu_data.pl $(srcdir)/menu_data.dat config.h
	@$(MKDIR_P) ui/qt
	$(AM_V_GEN)$(PERL) $(srcdir)/perl/cpp-perl.pl config.h $(srcdir)/menu_data.dat | $(PERL) -I$(srcdir)/perl $(srcdir)/menu_data.pl qt ui > $@.tmp && mv $@.tmp $@

ui/qt/menu_data.cpp: $(srcdir)/perl/cpp-perl.pl $(srcdir)/menu_data.pl $(srcdir)/menu_data.dat config.h
	@$(MKDIR_P) ui/qt
	$(AM_V_GEN)$(PERL) $(srcdir)/perl/cpp-perl.pl config.h $(srcdir)/menu_data.dat | $(PERL) -I$(srcdir)/perl $(srcdir)/menu_data.pl qt cpp > $@.tmp && mv $@.tmp $@

ui/qt/options.cpp: $(srcdir)/perl/cpp-perl.pl config.h $(srcdir)/ui/qt/options.pl $(srcdir)/ui/options.dat $(srcdir)/perl/Fuse.pm $(srcdir)/perl/Fuse/Dialog.pm
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

ui/qt/qrc_qt_ui.cpp: $(srcdir)/ui/qt/qt_ui.qrc
	$(AM_V_GEN)$(RCC) $(srcdir)/ui/qt/qt_ui.qrc > $@.tmp && mv $@.tmp $@

ui/qt/ui_debugger.h: $(srcdir)/ui/qt/debugger.ui
	$(AM_V_GEN)$(UIC) $(srcdir)/ui/qt/debugger.ui > $@.tmp && mv $@.tmp $@

ui/qt/moc_debugger.cpp: $(srcdir)/ui/qt/debugger.h
	$(AM_V_GEN)$(MOC) $(srcdir)/ui/qt/debugger.h > $@.tmp && mv $@.tmp $@

ui/qt/ui_hexview.h: $(srcdir)/ui/qt/hexview.ui
	$(AM_V_GEN)$(UIC) $(srcdir)/ui/qt/hexview.ui > $@.tmp && mv $@.tmp $@

ui/qt/moc_hexview.cpp: $(srcdir)/ui/qt/hexview.h
	$(AM_V_GEN)$(MOC) $(srcdir)/ui/qt/hexview.h > $@.tmp && mv $@.tmp $@
