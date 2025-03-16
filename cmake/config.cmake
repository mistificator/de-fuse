find_package(PkgConfig)

set(UIs)
set(SoundDevices)

# Qt

find_package(Qt5 COMPONENTS Core Widgets Gui Multimedia)
if (Qt5_FOUND)
    set(UIs ${UIs} Qt)
    set(SoundDevices ${SoundDevices} Qt)
endif()

# SDL

find_package(SDL)
if (SDL_FOUND)
    set(UIs ${UIs} SDL)
    set(SoundDevices ${SoundDevices} SDL)
endif()

# UI

pkg_check_modules(GTK4 gtk4)
if(GTK4_VERSION)
    set(UIs ${UIs} Gtk4)
    set_define(HAVE_GTK)
endif()
pkg_check_modules(GTK3 gtk+-3.0)
if (GTK3_VERSION)
    set(UIs ${UIs} Gtk3)
    set_define(HAVE_GTK)
endif()
pkg_check_modules(GTK2 gtk+-2.0)
if (GTK2_VERSION)
    set(UIs ${UIs} Gtk2)
    set_define(HAVE_GTK)
endif()

if (${HAVE_GTK})
    set(OPTIONS_DIR gtk)
endif()

find_package(X11)
if (X11_FOUND)
    set(UIs ${UIs} X11)
endif()

if (WIN32)
    set(UIs ${UIs} Generic)
endif()

if (LINUX)
    set(UIs ${UIs} FrameBuffer)
endif()

set(UIs ${UIs} null)

set(UI Qt CACHE STRING "UI")
set_property(CACHE UI PROPERTY STRINGS ${UIs})

set(SimpleUI OFF CACHE BOOL "")
if (${SimpleUI})
    set(OPTIONS_DIR widget)
elseif(${UI} STREQUAL "Qt")
    set(OPTIONS_DIR qt)
elseif(${UI} MATCHES "$Gtk")
    set(OPTIONS_DIR gtk)
elseif(${UI} STREQUAL "SDL")
    set(OPTIONS_DIR sdl)
elseif(${UI} STREQUAL "Generic" AND WIN32)
    set(OPTIONS_DIR win32)
endif()

# Audio

find_package(PulseAudio)
if (PULSEAUDIO_FOUND)
    set(SoundDevices ${SoundDevices} PulseAudio)
endif()

find_package(ALSA)
if (ALSA_FOUND)
    set(SoundDevices ${SoundDevices} ALSA)
endif()

pkg_check_modules(LIBAO ao)
if (LIBAO_VERSION)
    set(SoundDevices ${SoundDevices} LibAO)
endif()

if (WIN32)
    set(SoundDevices ${SoundDevices} DirectX Generic)
endif()

set(SoundDevices ${SoundDevices} null)

set(SoundDevice Qt CACHE STRING "Sound device")
set_property(CACHE SoundDevice PROPERTY STRINGS ${SoundDevices})

# configure

check_include(linux/if_tun.h    HAVE_IFTUN_H)

set(BLIP_BUFFER_ACCURACY 32 CACHE STRING "Blip Buffer accuracy ")
set(BUILD_SPECCYBOOT ON CACHE BOOL "SpeccyBoot support")
set(BUILD_SPECTRANET ON CACHE BOOL "spectranet support")
set(BUILD_TTX2000S ON CACHE BOOL "ttx2000s support")
