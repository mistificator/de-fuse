cmake_minimum_required(VERSION 3.25)

project(
  de-fuse
  LANGUAGES C CXX)

include(libspectrum/cmake/config.cmake)
add_subdirectory(libspectrum)

add_executable(${PROJECT_NAME})
add_definitions(-DVERSION="1.6.0.1")
add_definitions("-DFUSE_COPYRIGHT=\"(c) 1999-2024 Philip Kendall and respected others, and ZXLDR\"")
add_definitions(-DFUSE_URL="https://github.com/mistificator/de-fuse")
add_definitions(-DPACKAGE_URL="https://github.com/mistificator/de-fuse")
add_definitions(-DFUSE_BUGREPORT="https://github.com/mistificator/de-fuse/issues")
add_definitions(-DFUSEDATADIR="${CMAKE_CURRENT_SOURCE_DIR}/roms")

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 17)

if(MSVC AND WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

add_dependencies(${PROJECT_NAME} libspectrum)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    libspectrum
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    .
    compat
    libspectrum
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    libspectrum
)

include(cmake/config.cmake)

#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

set(CHDIR ${CMAKE_COMMAND} -E chdir ${CMAKE_CURRENT_SOURCE_DIR})
set(RM ${CMAKE_COMMAND} -E rm -f --)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/settings.c
    COMMAND ${CHDIR} ${PERL_EXECUTABLE} -I./perl settings.pl ./ settings.dat > ${CMAKE_CURRENT_SOURCE_DIR}/settings.c
    DEPENDS settings.dat settings.pl
    VERBATIM
)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/settings.h
    COMMAND ${CHDIR} ${PERL_EXECUTABLE} -I./perl settings-header.pl ./ settings.dat > ${CMAKE_CURRENT_SOURCE_DIR}/settings.h
    DEPENDS settings.dat settings-header.pl
    VERBATIM
)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/ui/${OPTIONS_DIR}/options.h
    COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_SOURCE_DIR}/tmp-config-0.h
    COMMAND ${CHDIR} ${PERL_EXECUTABLE} -I./perl ./perl/cpp-perl.pl tmp-config-0.h ./ui/options.dat | ${CHDIR} ${PERL_EXECUTABLE} -I./perl ./ui/${OPTIONS_DIR}/options-header.pl - public > ${CMAKE_CURRENT_SOURCE_DIR}/ui/${OPTIONS_DIR}/options.h
    COMMAND ${RM} ${CMAKE_CURRENT_SOURCE_DIR}/tmp-config-0.h
    DEPENDS ./ui/options.dat ./ui/${OPTIONS_DIR}/options-header.pl ./perl/cpp-perl.pl ./perl/Fuse.pm ./perl/Fuse/Dialog.pm
    VERBATIM
)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/ui/scaler/scalers_4.c
    COMMAND ${RM} ${CMAKE_CURRENT_SOURCE_DIR}/ui/scaler/scalers_4.c
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/ui/scaler/scalers.c ${CMAKE_CURRENT_SOURCE_DIR}/ui/scaler/scalers_4.c
    DEPENDS ./ui/scaler/scalers.c
    VERBATIM
)
set_source_files_properties(./ui/scaler/scalers.c PROPERTIES COMPILE_DEFINITIONS "SCALER_DATA_SIZE=2")
set_source_files_properties(./ui/scaler/scalers_4.c PROPERTIES COMPILE_DEFINITIONS "SCALER_DATA_SIZE=4")

add_custom_target(__generated_${PROJECT_NAME}
    SOURCES
    settings.c settings.h ./ui/${OPTIONS_DIR}/options.h ./ui/scaler/scalers_4.c
)
add_dependencies(${PROJECT_NAME} __generated_${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
#sources
    ./compat/dirname.c
    ./compat/getopt.c
    ./compat/getopt1.c
    ./debugger/breakpoint.c
    ./debugger/command.c
    ./debugger/commandl.c
    ./debugger/commandy.c
    ./debugger/debugger.c
    ./debugger/disassemble.c
    ./debugger/event.c
    ./debugger/expression.c
    ./debugger/system_variable.c
    ./debugger/variable.c
    ./display.c
    ./event.c
    ./fuse.c
    ./infrastructure/startup_manager.c
    ./input.c
    ./keyboard.c
    ./loader.c
    ./machine.c
    ./machines/machines_periph.c
    ./machines/pentagon.c
    ./machines/pentagon1024.c
    ./machines/pentagon512.c
    ./machines/scorpion.c
    ./machines/spec128.c
    ./machines/spec16.c
    ./machines/spec48.c
    ./machines/spec48_ntsc.c
    ./machines/specplus2.c
    ./machines/specplus2a.c
    ./machines/specplus3.c
    ./machines/specplus3e.c
    ./machines/spec_se.c
    ./machines/tc2048.c
    ./machines/tc2068.c
    ./machines/ts2068.c
    ./memory_pages.c
    ./mempool.c
    ./menu.c
    ./module.c
    ./movie.c
    ./periph.c
    ./peripherals/dck.c
    ./peripherals/disk/beta.c
    ./peripherals/disk/crc.c
    ./peripherals/disk/didaktik.c
    ./peripherals/disk/disciple.c
    ./peripherals/disk/disk.c
    ./peripherals/disk/fdd.c
    ./peripherals/disk/opus.c
    ./peripherals/disk/plusd.c
    ./peripherals/disk/trdos.c
    ./peripherals/disk/upd_fdc.c
    ./peripherals/disk/wd_fdc.c
    ./peripherals/flash/am29f010.c
    ./peripherals/ide/divide.c
    ./peripherals/ide/divmmc.c
    ./peripherals/ide/divxxx.c
    ./peripherals/ide/ide.c
    ./peripherals/ide/simpleide.c
    ./peripherals/ide/zxatasp.c
    ./peripherals/ide/zxcf.c
    ./peripherals/ide/zxmmc.c
    ./peripherals/if1.c
    ./peripherals/if2.c
    ./peripherals/joystick.c
    ./peripherals/kempmouse.c
    ./peripherals/multiface.c
    ./peripherals/nic/enc28j60.c
    ./peripherals/nic/w5100.c
    ./peripherals/nic/w5100_socket.c
    ./peripherals/printer.c
    ./peripherals/scld.c
    ./peripherals/sound/ay.c
    ./peripherals/sound/covox.c
    ./peripherals/sound/fuller.c
    ./peripherals/sound/melodik.c
    ./peripherals/sound/sp0256.c
    ./peripherals/sound/specdrum.c
    ./peripherals/sound/uspeech.c
    ./peripherals/speccyboot.c
    ./peripherals/spectranet.c
    ./peripherals/ttx2000s.c
    ./peripherals/ula.c
    ./peripherals/usource.c
    ./phantom_typist.c
    ./pokefinder/pokefinder.c
    ./pokefinder/pokemem.c
    ./profile.c
    ./psg.c
    ./rectangle.c
    ./roms/README.copyright
    ./rzx.c
    ./screenshot.c
    ./settings.c
    ./slt.c
    ./snapshot.c
    ./sound/blipbuffer.c
    ./sound/sfifo.c
    ./sound.c
    ./spectrum.c
    ./svg.c
    ./tape.c
    ./timer/native.c
    ./timer/timer.c
    ./ui/scaler/scaler.c
    ./ui/scaler/scalers.c
    ./ui/scaler/scalers_4.c
#    ./ui/scaler/scaler_hq2x.c
#    ./ui/scaler/scaler_hq3x.c
#    ./ui/scaler/scaler_hq4x.c
    ./ui.c
    ./uidisplay.c
    ./uimedia.c
    ./utils.c
#    ./z80/opcodes_base.c
    ./z80/z80.c
#    ./z80/z80_cb.c
#    ./z80/z80_ddfd.c
#    ./z80/z80_ddfdcb.c
    ./z80/z80_debugger_variables.c
#    ./z80/z80_ed.c
    ./z80/z80_ops.c

    ./unittests/unittests.c

    ./bitmap.h
    ./compat/getopt.h
    ./compat.h
    ./debugger/breakpoint.h
    ./debugger/commandy.h
    ./debugger/debugger.h
    ./debugger/debugger_internals.h
    ./display.h
    ./event.h
    ./fuse.h
    ./infrastructure/startup_manager.h
    ./input.h
    ./keyboard.h
    ./loader.h
    ./machine.h
    ./machines/machines.h
    ./machines/machines_periph.h
    ./machines/pentagon.h
    ./machines/scorpion.h
    ./machines/spec128.h
    ./machines/spec48.h
    ./machines/specplus3.h
    ./machines/tc2068.h
    ./memory_pages.h
    ./mempool.h
    ./menu.h
    ./module.h
    ./movie.h
    ./movie_tables.h
    ./options.h
    ./periph.h
    ./peripherals/dck.h
    ./peripherals/disk/beta.h
    ./peripherals/disk/crc.h
    ./peripherals/disk/didaktik.h
    ./peripherals/disk/disciple.h
    ./peripherals/disk/disk.h
    ./peripherals/disk/fdd.h
    ./peripherals/disk/opus.h
    ./peripherals/disk/plusd.h
    ./peripherals/disk/trdos.h
    ./peripherals/disk/upd_fdc.h
    ./peripherals/disk/wd_fdc.h
    ./peripherals/flash/am29f010.h
    ./peripherals/ide/divide.h
    ./peripherals/ide/divmmc.h
    ./peripherals/ide/divxxx.h
    ./peripherals/ide/ide.h
    ./peripherals/ide/simpleide.h
    ./peripherals/ide/zxatasp.h
    ./peripherals/ide/zxcf.h
    ./peripherals/ide/zxmmc.h
    ./peripherals/if1.h
    ./peripherals/if2.h
    ./peripherals/joystick.h
    ./peripherals/kempmouse.h
    ./peripherals/multiface.h
    ./peripherals/nic/enc28j60.h
    ./peripherals/nic/w5100.h
    ./peripherals/nic/w5100_internals.h
    ./peripherals/printer.h
    ./peripherals/scld.h
    ./peripherals/sound/ay.h
    ./peripherals/sound/covox.h
    ./peripherals/sound/fuller.h
    ./peripherals/sound/melodik.h
    ./peripherals/sound/sp0256.h
    ./peripherals/sound/specdrum.h
    ./peripherals/sound/uspeech.h
    ./peripherals/speccyboot.h
    ./peripherals/spectranet.h
    ./peripherals/ttx2000s.h
    ./peripherals/ula.h
    ./peripherals/usource.h
    ./phantom_typist.h
    ./pokefinder/pokefinder.h
    ./pokefinder/pokemem.h
    ./profile.h
    ./psg.h
    ./rectangle.h
    ./rzx.h
    ./screenshot.h
    ./settings.h
    ./slt.h
    ./snapshot.h
    ./sound/blipbuffer.h
    ./sound/sfifo.h
    ./sound.h
    ./spectrum.h
    ./svg.h
    ./tape.h
    ./timer/timer.h
    ./ui/scaler/scaler.h
    ./ui/scaler/scaler_internals.h
    ./ui/ui.h
    ./ui/uidisplay.h
    ./ui/uijoystick.h
    ./ui/uimedia.h
    ./utils.h
    ./z80/z80.h
    ./z80/z80_checks.h
    ./z80/z80_internals.h
    ./z80/z80_macros.h
)

if (UNIX)
    if (LINUX)
        target_sources(${PROJECT_NAME}
            PRIVATE
            ./compat/linux/relative_paths.c
        )
    else()
        target_sources(${PROJECT_NAME}
            PRIVATE
            ./compat/unix/relative_paths.c
        )
    endif()
    target_sources(${PROJECT_NAME}
        PRIVATE
        ./compat/unix/dir.c
        ./compat/unix/file.c
        ./compat/unix/osname.c
        ./compat/unix/paths.c
        ./compat/unix/socket.c
        ./compat/unix/timer.c
        ./compat/unix/tuntap.c
    )
endif()

if (WIN32)
    set_define(PTW32_STATIC_LIB)
    unset(PTHREAD_BUILD_SHARED)
    set(PTHREAD_BUILD_SHARED OFF)
    add_subdirectory(./compat/win32/pthread-win)

    set_define(UNICODE)
    target_include_directories(${PROJECT_NAME}
        PRIVATE
        ./compat/win32
        ./compat/win32/pthread-win/include
    )
    target_sources(${PROJECT_NAME}
        PRIVATE
        ./compat/win32/osname.c
        ./compat/win32/paths.c
        ./compat/win32/socket.c
        ./compat/win32/timer.c

        ./compat/unix/file.c
        ./compat/unix/tuntap.c
    )
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
        ws2_32

        pthread
    )
endif()

if (${SoundDevice} STREQUAL "Qt" OR ${UI} STREQUAL "Qt")
    set_property(TARGET ${PROJECT_NAME} PROPERTY AUTOMOC ON)
    set_property(TARGET ${PROJECT_NAME} PROPERTY AUTOUIC ON)
    set_property(TARGET ${PROJECT_NAME} PROPERTY AUTORCC ON)
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
        Qt5::Core Qt5::Multimedia Qt5::Widgets Qt5::Gui
    )
endif()

if (${SoundDevice} STREQUAL "null")
    target_sources(${PROJECT_NAME}
        PRIVATE
        ./sound/nullsound.c
    )
endif()

if (${SoundDevice} STREQUAL "SDL")
    target_sources(${PROJECT_NAME}
        PRIVATE
        ./sound/sdlsound.c
    )
endif()

if (WIN32)
    if (${SoundDevice} STREQUAL "Generic")
        target_sources(${PROJECT_NAME}
            PRIVATE
            ./sound/win32sound.c
        )
        target_link_libraries(${PROJECT_NAME}
            PRIVATE
            winmm
        )
    endif()
    if (${SoundDevice} STREQUAL "DirectX")
        target_sources(${PROJECT_NAME}
            PRIVATE
            ./sound/dxsound.c
        )
        target_link_libraries(${PROJECT_NAME}
            PRIVATE
            dsound
        )
    endif()
endif()

if (${SoundDevice} STREQUAL "LibAO")
    target_sources(${PROJECT_NAME}
        PRIVATE
        ./sound/aosound.c
    )
endif()

if (${SoundDevice} STREQUAL "ALSA")
    target_sources(${PROJECT_NAME}
        PRIVATE
        ./sound/alsasound.c
    )
endif()

if (${SoundDevice} STREQUAL "PulseAudio")
    target_sources(${PROJECT_NAME}
        PRIVATE
        ./sound/pulsesound.c
    )
endif()

if (${SoundDevice} STREQUAL "Qt")
    target_sources(${PROJECT_NAME}
        PRIVATE
        ./sound/qtsound.cpp
        ./sound/qtsound.h
    )
endif()

if (${UI} MATCHES "$Gtk")
    set_define(UI_GTK)
    target_sources(${PROJECT_NAME}
        PRIVATE
        ./ui/gtk/binary.c
        ./ui/gtk/browse.c
        ./ui/gtk/confirm.c
        ./ui/gtk/debugger.c
        ./ui/gtk/fileselector.c
        ./ui/gtk/gtkcompat.c
        ./ui/gtk/gtkdisplay.c
        ./ui/gtk/gtkjoystick.c
        ./ui/gtk/gtkkeyboard.c
        ./ui/gtk/gtkmouse.c
        ./ui/gtk/gtkui.c
        ./ui/gtk/memory.c
        ./ui/gtk/memory_gtk2.c
        ./ui/gtk/picture.c
        ./ui/gtk/pokefinder.c
        ./ui/gtk/pokemem.c
        ./ui/gtk/rollback.c
        ./ui/gtk/roms.c
        ./ui/gtk/statusbar.c
        ./ui/gtk/stock.c

        ./ui/gtk/gtkcompat.h
        ./ui/gtk/gtkinternals.h
    )
endif()

if (${UI} STREQUAL "FrameBuffer")
    set_define(UI_FB)
    target_sources(${PROJECT_NAME}
        PRIVATE
        ./ui/fb/fbdisplay.c
        ./ui/fb/fbjoystick.c
        ./ui/fb/fbkeyboard.c
        ./ui/fb/fbmouse.c
        ./ui/fb/fbui.c

        ./ui/fb/fbdisplay.h
        ./ui/fb/fbkeyboard.h
        ./ui/fb/fbmouse.h
    )
endif()

if (${SimpleUI})
    set_define(USE_WIDGET)
    target_sources(${PROJECT_NAME}
        PRIVATE
        ./ui/widget/about.c
        ./ui/widget/binary.c
        ./ui/widget/browse.c
        ./ui/widget/debugger.c
        ./ui/widget/error.c
        ./ui/widget/filesel.c
        ./ui/widget/memory.c
        ./ui/widget/menu.c
        ./ui/widget/menu_data.c
        ./ui/widget/options.c
        ./ui/widget/picture.c
        ./ui/widget/pokefinder.c
        ./ui/widget/pokemem.c
        ./ui/widget/query.c
        ./ui/widget/roms.c
        ./ui/widget/select.c
        ./ui/widget/text.c
        ./ui/widget/widget.c

        ./ui/widget/options_internals.h
        ./ui/widget/widget.h
        ./ui/widget/widget_internals.h
    )
else()

endif()

if (${UI} STREQUAL "X11")
    set_define(UI_X)
    target_sources(${PROJECT_NAME}
        PRIVATE
        ./ui/xlib/keysyms.c
        ./ui/xlib/xdisplay.c
        ./ui/xlib/xerror.c
        ./ui/xlib/xjoystick.c
        ./ui/xlib/xkeyboard.c
        ./ui/xlib/xpixmaps.c
        ./ui/xlib/xpixmaps.c.in
        ./ui/xlib/xui.c

        ./ui/xlib/xdisplay.h
        ./ui/xlib/xkeyboard.h
        ./ui/xlib/xui.h
    )
endif()

if (${UI} STREQUAL "null")
    set_define(UI_NULL)
    target_sources(${PROJECT_NAME}
        PRIVATE
        ./ui/null/null_ui.c
    )
endif()

if (${UI} STREQUAL "Qt")
    set_define(UI_QT)

    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/ui/${OPTIONS_DIR}/keysyms.cpp
        COMMAND ${CHDIR} ${PERL_EXECUTABLE} -I./perl keysyms.pl qt keysyms.dat > ${CMAKE_CURRENT_SOURCE_DIR}/ui/${OPTIONS_DIR}/keysyms.cpp
        DEPENDS keysyms.dat keysyms.pl
        VERBATIM
    )

    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/ui/${OPTIONS_DIR}/menu_data.ui
        COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_SOURCE_DIR}/tmp-config-1.h
        COMMAND ${CHDIR} ${PERL_EXECUTABLE} ./perl/cpp-perl.pl tmp-config-1.h menu_data.dat | ${CHDIR} ${PERL_EXECUTABLE} -I./perl menu_data.pl qt ui > ${CMAKE_CURRENT_SOURCE_DIR}/ui/${OPTIONS_DIR}/menu_data.ui
        COMMAND ${RM} ${CMAKE_CURRENT_SOURCE_DIR}/tmp-config-1.h
        DEPENDS menu_data.dat menu_data.pl ./perl/cpp-perl.pl
        VERBATIM
    )

    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/ui/${OPTIONS_DIR}/menu_data.cpp
        COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_SOURCE_DIR}/tmp-config-2.h
        COMMAND ${CHDIR} ${PERL_EXECUTABLE} ./perl/cpp-perl.pl tmp-config-2.h menu_data.dat | ${CHDIR} ${PERL_EXECUTABLE} -I./perl menu_data.pl qt cpp > ${CMAKE_CURRENT_SOURCE_DIR}/ui/${OPTIONS_DIR}/menu_data.cpp
        COMMAND ${RM} ${CMAKE_CURRENT_SOURCE_DIR}/tmp-config-2.h
        DEPENDS menu_data.dat menu_data.pl ./perl/cpp-perl.pl
        VERBATIM
    )

    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/ui/${OPTIONS_DIR}/options.cpp
        COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_SOURCE_DIR}/tmp-config-3.h
        COMMAND ${CHDIR} ${PERL_EXECUTABLE} ./perl/cpp-perl.pl tmp-config-3.h ./ui/options.dat | ${CHDIR} ${PERL_EXECUTABLE} -I./perl ./ui/${OPTIONS_DIR}/options.pl - > ${CMAKE_CURRENT_SOURCE_DIR}/ui/${OPTIONS_DIR}/options.cpp
        COMMAND ${RM} ${CMAKE_CURRENT_SOURCE_DIR}/tmp-config-3.h
        DEPENDS ./ui/options.dat ./ui/${OPTIONS_DIR}/options.pl ./perl/cpp-perl.pl ./perl/Fuse.pm ./perl/Fuse/Dialog.pm
        VERBATIM
    )

    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/ui/${OPTIONS_DIR}/options_internals.h
        COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_SOURCE_DIR}/tmp-config-4.h
        COMMAND ${CHDIR} ${PERL_EXECUTABLE} ./perl/cpp-perl.pl tmp-config-4.h ./ui/options.dat | ${CHDIR} ${PERL_EXECUTABLE} -I./perl ./ui/${OPTIONS_DIR}/options-header.pl - > ${CMAKE_CURRENT_SOURCE_DIR}/ui/${OPTIONS_DIR}/options_internals.h
        COMMAND ${RM} ${CMAKE_CURRENT_SOURCE_DIR}/tmp-config-4.h
        DEPENDS ./ui/options.dat ./ui/${OPTIONS_DIR}/options-header.pl ./perl/cpp-perl.pl ./perl/Fuse.pm ./perl/Fuse/Dialog.pm
        VERBATIM
    )

    target_sources(__generated_${PROJECT_NAME}
        PRIVATE
        ./ui/${OPTIONS_DIR}/keysyms.cpp
        ./ui/${OPTIONS_DIR}/menu_data.ui
        ./ui/${OPTIONS_DIR}/menu_data.cpp
        ./ui/${OPTIONS_DIR}/options.cpp
        ./ui/${OPTIONS_DIR}/options_internals.h
    )

    target_sources(${PROJECT_NAME}
        PRIVATE
        ./ui/qt/debugger.cpp
        ./ui/qt/hexview.cpp
        ./ui/qt/keysyms.cpp
#        ./ui/qt/menu_data.cpp
#        ./ui/qt/options.cpp
        ./ui/qt/qt_ui.cpp
        ./ui/qt/tapebrowser.cpp

        ./ui/qt/debugger.h
        ./ui/qt/hexview.h
        ./ui/qt/options_internals.h
        ./ui/qt/qt_ui.h
        ./ui/qt/tapebrowser.h

        ./ui/qt/qt_ui.qrc
        ./ui/qt/debugger.ui
        ./ui/qt/hexview.ui
        ./ui/qt/menu_data.ui
        ./ui/qt/tapebrowser.ui

        ./ui/uijoystick.c
    )
endif()

if (${UI} STREQUAL "SDL")
    set_define(UI_SDL)
    target_sources(${PROJECT_NAME}
        PRIVATE
        ./timer/sdl.c
        ./ui/sdl/sdldisplay.c
        ./ui/sdl/sdljoystick.c
        ./ui/sdl/sdlkeyboard.c
        ./ui/sdl/sdlui.c

        ./ui/sdl/sdldisplay.h
        ./ui/sdl/sdljoystick.h
        ./ui/sdl/sdlkeyboard.h
    )
endif()

if (WIN32 AND ${UI} STREQUAL "Generic")
    set_define(UI_WIN32)

    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/ui/${OPTIONS_DIR}/keysyms.c
        COMMAND ${CHDIR} ${PERL_EXECUTABLE} -I./perl keysyms.pl win32 keysyms.dat > ${CMAKE_CURRENT_SOURCE_DIR}/ui/${OPTIONS_DIR}/keysyms.c
        DEPENDS keysyms.dat keysyms.pl
        VERBATIM
    )

    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/ui/${OPTIONS_DIR}/menu_data.h
        COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_SOURCE_DIR}/tmp-config-1.h
        COMMAND ${CHDIR} ${PERL_EXECUTABLE} ./perl/cpp-perl.pl tmp-config-1.h menu_data.dat | ${CHDIR} ${PERL_EXECUTABLE} -I./perl menu_data.pl win32 h > ${CMAKE_CURRENT_SOURCE_DIR}/ui/${OPTIONS_DIR}/menu_data.h
        COMMAND ${RM} ${CMAKE_CURRENT_SOURCE_DIR}/tmp-config-1.h
        DEPENDS menu_data.dat menu_data.pl ./perl/cpp-perl.pl
        VERBATIM
    )

    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/ui/${OPTIONS_DIR}/menu_data.c
        COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_SOURCE_DIR}/tmp-config-2.h
        COMMAND ${CHDIR} ${PERL_EXECUTABLE} ./perl/cpp-perl.pl tmp-config-2.h menu_data.dat | ${CHDIR} ${PERL_EXECUTABLE} -I./perl menu_data.pl win32 c > ${CMAKE_CURRENT_SOURCE_DIR}/ui/${OPTIONS_DIR}/menu_data.c
        COMMAND ${RM} ${CMAKE_CURRENT_SOURCE_DIR}/tmp-config-2.h
        DEPENDS menu_data.dat menu_data.pl ./perl/cpp-perl.pl
        VERBATIM
    )

    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/ui/${OPTIONS_DIR}/menu_data.rc
        COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_SOURCE_DIR}/tmp-config-3.h
        COMMAND ${CHDIR} ${PERL_EXECUTABLE} ./perl/cpp-perl.pl tmp-config-3.h menu_data.dat | ${CHDIR} ${PERL_EXECUTABLE} -I./perl menu_data.pl win32 rc > ${CMAKE_CURRENT_SOURCE_DIR}/ui/${OPTIONS_DIR}/menu_data.rc
        COMMAND ${RM} ${CMAKE_CURRENT_SOURCE_DIR}/tmp-config-3.h
        DEPENDS menu_data.dat menu_data.pl ./perl/cpp-perl.pl
        VERBATIM
    )

    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/ui/${OPTIONS_DIR}/options.c
        COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_SOURCE_DIR}/tmp-config-4.h
        COMMAND ${CHDIR} ${PERL_EXECUTABLE} ./perl/cpp-perl.pl tmp-config-4.h ./ui/options.dat | ${CHDIR} ${PERL_EXECUTABLE} -I./perl ./ui/${OPTIONS_DIR}/options.pl - > ${CMAKE_CURRENT_SOURCE_DIR}/ui/${OPTIONS_DIR}/options.c
        COMMAND ${RM} ${CMAKE_CURRENT_SOURCE_DIR}/tmp-config-4.h
        DEPENDS ./ui/options.dat ./ui/${OPTIONS_DIR}/options.pl ./perl/cpp-perl.pl ./perl/Fuse.pm ./perl/Fuse/Dialog.pm
        VERBATIM
    )

    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/ui/${OPTIONS_DIR}/options_internals.h
        COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_SOURCE_DIR}/tmp-config-5.h
        COMMAND ${CHDIR} ${PERL_EXECUTABLE} ./perl/cpp-perl.pl tmp-config-5.h ./ui/options.dat | ${CHDIR} ${PERL_EXECUTABLE} -I./perl ./ui/${OPTIONS_DIR}/options-header.pl - > ${CMAKE_CURRENT_SOURCE_DIR}/ui/${OPTIONS_DIR}/options_internals.h
        COMMAND ${RM} ${CMAKE_CURRENT_SOURCE_DIR}/tmp-config-5.h
        DEPENDS ./ui/options.dat ./ui/${OPTIONS_DIR}/options-header.pl ./perl/cpp-perl.pl ./perl/Fuse.pm ./perl/Fuse/Dialog.pm
        VERBATIM
    )

    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/ui/${OPTIONS_DIR}/options.rc
        COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_SOURCE_DIR}/tmp-config-6.h
        COMMAND ${CHDIR} ${PERL_EXECUTABLE} ./perl/cpp-perl.pl tmp-config-6.h ./ui/options.dat | ${CHDIR} ${PERL_EXECUTABLE} -I./perl ./ui/${OPTIONS_DIR}/options-resource.pl - > ${CMAKE_CURRENT_SOURCE_DIR}/ui/${OPTIONS_DIR}/options.rc
        COMMAND ${RM} ${CMAKE_CURRENT_SOURCE_DIR}/tmp-config-6.h
        DEPENDS ./ui/options.dat ./ui/${OPTIONS_DIR}/options-resource.pl ./perl/cpp-perl.pl ./perl/Fuse.pm ./perl/Fuse/Dialog.pm
        VERBATIM
    )

    target_sources(__generated_${PROJECT_NAME}
        PRIVATE
        ./ui/${OPTIONS_DIR}/keysyms.c
        ./ui/${OPTIONS_DIR}/menu_data.h
        ./ui/${OPTIONS_DIR}/menu_data.c
        ./ui/${OPTIONS_DIR}/menu_data.rc
        ./ui/${OPTIONS_DIR}/options.c
        ./ui/${OPTIONS_DIR}/options_internals.h
        ./ui/${OPTIONS_DIR}/options.rc
    )

    target_sources(${PROJECT_NAME}
        PRIVATE
        ./ui/win32/about.c
        ./ui/win32/binary.c
        ./ui/win32/browse.c
        ./ui/win32/confirm.c
        ./ui/win32/debugger.c
        ./ui/win32/fileselector.c
        ./ui/win32/hyperlinks.c
        ./ui/win32/memorybrowser.c
        ./ui/win32/picture.c
        ./ui/win32/pokefinder.c
        ./ui/win32/pokemem.c
        ./ui/win32/rollback.c
        ./ui/win32/roms.c
        ./ui/win32/statusbar.c
        ./ui/win32/win32display.c
        ./ui/win32/win32joystick.c
        ./ui/win32/win32keyboard.c
        ./ui/win32/win32mouse.c
        ./ui/win32/win32ui.c

        ./ui/win32/about.h
        ./ui/win32/binary.h
        ./ui/win32/browse.h
        ./ui/win32/debugger.h
        ./ui/win32/hyperlinks.h
        ./ui/win32/memorybrowser.h
        ./ui/win32/picture.h
        ./ui/win32/pokefinder.h
        ./ui/win32/pokemem.h
        ./ui/win32/rollback.h
        ./ui/win32/roms.h
        ./ui/win32/select_template.h
        ./ui/win32/win32internals.h
        ./ui/win32/win32joystick.h

        ./ui/${OPTIONS_DIR}/keysyms.c
        ./ui/${OPTIONS_DIR}/menu_data.h
        ./ui/${OPTIONS_DIR}/menu_data.c
        ./ui/${OPTIONS_DIR}/options.c
        ./ui/${OPTIONS_DIR}/options_internals.h
    )

    target_link_libraries(${PROJECT_NAME}
        PRIVATE
        comctl32
    )

endif()

if (HAVE_ZLIB_H)
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
        z
    )
endif()

if (HAVE_LIB_GLIB)
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
        ${GLIB2_LIBRARIES}
    )
endif()

add_custom_target(__autotools_files_${PROJECT_NAME}
    SOURCES
    configure.ac
    Makefile.am
    compat/Makefile.am
    data/Makefile.am
    debugger/Makefile.am
    hacking/Makefile.am
    infrastructure/Makefile.am
    lib/Makefile.am
    machines/Makefile.am
    man/Makefile.am
    peripherals/Makefile.am
    perl/Makefile.am
    pokefinder/Makefile.am
    sound/Makefile.am
    timer/Makefile.am
    ui/Makefile.am
    ui/qt/Makefile.am
    ui/fb/Makefile.am
    ui/gtk/Makefile.am
    ui/null/Makefile.am
    ui/scaler/Makefile.am
    ui/sdl/Makefile.am
    ui/widget/Makefile.am
    ui/wii/Makefile.am
    ui/win32/Makefile.am
    ui/xlib/Makefile.am
    unittests/Makefile.am
    z80/Makefile.am

    config.h
)

add_custom_target(__perl_scripts_${PROJECT_NAME}
    SOURCES
    ./keysyms.pl
    ./menu_data.pl
    ./perl/cpp-perl.pl
    ./perl/Fuse.pm
    ./perl/Fuse/Dialog.pm
    ./settings-header.pl
    ./settings.pl
    ./ui/gtk/options-header.pl
    ./ui/gtk/options.pl
    ./ui/null/options-header.pl
    ./ui/null/options.pl
    ./ui/qt/options-header.pl
    ./ui/qt/options.pl
    ./ui/widget/mkfusefont.pl
    ./ui/widget/options-header.pl
    ./ui/widget/options.pl
    ./ui/win32/options-header.pl
    ./ui/win32/options-resource.pl
    ./ui/win32/options.pl
    ./ui/xlib/xstatusbar.pl
    ./z80/z80.pl

    ./ui/options.dat
    ./menu_data.dat
    ./settings.dat
)
