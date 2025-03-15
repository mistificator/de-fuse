find_package(PkgConfig)

set(UIs)
set(SoundDevices)

# Qt

find_package(Qt5 COMPONENTS Core Widgets Gui Multimedia)
if (Qt5_FOUND)
    set(UIs ${UIs} Qt)
    set(SoundDevices ${SoundDevices} Qt)
    set_define(HAVE_QT)
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
endif()
pkg_check_modules(GTK3 gtk+-3.0)
if (GTK3_VERSION)
    set(UIs ${UIs} Gtk3)
endif()
pkg_check_modules(GTK2 gtk+-2.0)
if (GTK2_VERSION)
    set(UIs ${UIs} Gtk2)
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
    if (GTK2_VERSION OR GTK3_VERSION OR GTK4_VERSION)
        set(UIs ${UIs} Widget)
    endif()
endif()

set(UIs ${UIs} null)

set(UI Qt CACHE STRING "UI")
set_property(CACHE UI PROPERTY STRINGS ${UIs})

# Audio

find_package(PulseAudio)
if (PULSEAUDIO_FOUND)
    set(SoundDevices ${SoundDevices} PulseAudio)
endif()

find_package(ALSA)
if (ALSA_FOUND)
    set(SoundDevices ${SoundDevices} ALSA)
endif()

if (WIN32)
    set(SoundDevices ${SoundDevices} DirectX Generic)
endif()

set(SoundDevices ${SoundDevices} null)

set(SoundDevice Qt CACHE STRING "Sound device")
set_property(CACHE SoundDevice PROPERTY STRINGS ${SoundDevices})

# configure

set(BLIP_BUFFER_ACCURACY 32 CACHE STRING "Blip Buffer accuracy ")
set(BUILD_SPECCYBOOT ON CACHE BOOL "SpeccyBoot support")
set(BUILD_SPECTRANET ON CACHE BOOL "spectranet support")
set(BUILD_TTX2000S ON CACHE BOOL "ttx2000s support")
