Dirty patched fork of Fuse

![image](https://github.com/mistificator/de-fuse/assets/2280081/0ec9ef12-54d7-4eb2-84d2-81cd1323199b)
![image](https://github.com/mistificator/de-fuse/assets/2280081/34f8ea19-b3f0-421b-9a54-5000915d1901)
![image](https://github.com/mistificator/de-fuse/assets/2280081/61dac719-3acc-4e24-bd7b-5fb1b603fbc4)

Original Fuse README goes below
============================================

The Free Unix Spectrum Emulator (Fuse) 1.6.0
============================================

Fuse (the Free Unix Spectrum Emulator) was originally, and somewhat
unsurprisingly, an emulator of the ZX Spectrum (a popular 1980s home
computer, especially in the UK) for Unix. However, it has now also
been ported to Mac OS X, which may or may not count as a Unix variant
depending on your advocacy position and Windows which definitely isn't
a Unix variant. Fuse also emulates some of the better-known ZX Spectrum
clones as well.

What Fuse does have:

* Accurate Spectrum 16K/48K/128K/+2/+2A/+3 emulation.
* Working Spectrum +3e and SE, Timex TC2048, TC2068 and TS2068,
  Pentagon 128, "512" (Pentagon 128 with extra memory) and 1024 and
  Scorpion ZS 256 emulation.
* Runs at true Speccy speed on any computer you're likely to try it on.
* Support for loading from .tzx files, including accelerated loading.
* Sound (on systems supporting the Open Sound System, SDL, OpenBSD/
  Solaris's /dev/audio, CoreAudio or PulseAudio).
* Emulation of most of the common joysticks used on the Spectrum
  (including Kempston, Sinclair and Cursor joysticks).
* Emulation of some of the printers you could attach to a Spectrum.
* Support for the RZX input recording file format, including
  rollback and 'competition mode'.
* Emulation of the Currah µSource, Interface 1, Kempston mouse,
  Multiface One/128/3 and TTX2000S interfaces.
* Emulation of the Covox, Currah µSpeech, Fuller audio box, Melodik and
  SpecDrum audio interfaces.
* Emulation of the DivIDE, DivMMC, Spectrum +3e, ZXATASP, ZXCF and ZXMMC
  storage interfaces.
* Emulation of the Beta 128, +D, Didaktik 80/40, DISCiPLE and Opus Discovery
  disk interfaces.
* Emulation of the Spectranet and SpeccyBoot network interfaces.
* Emulation of the TTX2000 S Teletext adapter.
* Support for the Recreated ZX Spectrum Bluetooth keyboard.

Help! <xyz> doesn't work
------------------------

If you're having a problem using/running/building Fuse, the two places
you're most likely to get help are the development mailing list
<fuse-emulator-devel@lists.sf.net> or the official forums at
<http://sourceforge.net/p/fuse-emulator/discussion/>.

What you'll need to run Fuse
----------------------------

Unix, Linux, BSD, etc.

Required:

* X, SDL or framebuffer support. If you have GTK, you'll get
  a (much) nicer user interface under X.
* libspectrum: this is available from
  http://fuse-emulator.sourceforge.net/libspectrum.php

Optional:

* Other libraries will give you some extended functionality:
  * libgcrypt: the ability to digitally sign input recordings (note that
    Fuse requires version 1.1.42 or later).
  * libpng: the ability to save screenshots
  * libxml2: the ability to load and save Fuse's current configuration
  * zlib: support for compressed RZX files

If you've used Fuse prior to version 0.5.0, note that the external
utilities (tzxlist, etc) are now available separately from Fuse
itself. See http://fuse-emulator.sourceforge.net/ for details.

Mac OS X

* Either the native port by Fredrick Meunier, or the original version
  will compile on OS X 10.3 (Panther) or later.
* On Mac OS X Lion you will need to use clang as gcc-llvm-4.2.1 fails to
  correctly compile z80_ops.c.

Windows

* The Win32 and SDL UIs can be used under Windows.
* pthreads-win32 library will give the ability to use posix threads, needed by
  some peripherals.

Building Fuse
-------------

See the file `INSTALL' for more detailed information.

Closing comments
----------------

Fuse has its own home page, which you can find at:

http://fuse-emulator.sourceforge.net/

and contains much of the information listed here. 

News of new versions of Fuse (and other important Fuse-related
announcements) are distributed via the fuse-emulator-announce mailing
list on SourceForge; see
http://lists.sourceforge.net/lists/listinfo/fuse-emulator-announce
for details on how to subscribe and the like.

If you've got any bug reports, suggestions or the like for Fuse, or
just want to get involved in the development, this is coordinated via
the fuse-emulator-devel mailing list,
http://lists.sourceforge.net/lists/listinfo/fuse-emulator-devel
and the Fuse project page on SourceForge,
http://sourceforge.net/projects/fuse-emulator/

For Spectrum discussions not directly related to Fuse, visit either the
Usenet newsgroup `comp.sys.sinclair' or the World of Spectrum forums
<http://www.worldofspectrum.org/forums/>.

Philip Kendall <philip-fuse@shadowmagic.org.uk>
27th February, 2021
