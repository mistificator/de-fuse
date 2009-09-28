#!/usr/bin/perl -w

# options-header.pl: generate options dialog boxes
# Copyright (c) 2001-2002,2004 Philip Kendall

# $Id: options-header.pl 2889 2007-05-26 17:45:08Z zubzero $

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

# Author contact information:

# E-mail: philip-fuse@shadowmagic.org.uk

use strict;

use lib '../perl';

use Fuse;
use Fuse::Dialog;

die "No data file specified" unless @ARGV;

my @dialogs = Fuse::Dialog::read( shift @ARGV );

print Fuse::GPL( 'options.h: options dialog boxes',
		 '2001-2002,2004 Philip Kendall' ) . << "CODE";

/* This file is autogenerated from options.dat by options-header.pl.
   Do not edit unless you know what you\'re doing! */

#ifndef FUSE_WIDGETOPTIONS_H
#define FUSE_WIDGETOPTIONS_H

#ifndef FUSE_SETTINGS_H
#include "settings.h"
#endif

#ifndef FUSE_WIDGET_H
#include "widget.h"
#endif

extern settings_info widget_options_settings;

CODE

foreach( @dialogs ) {

    print << "CODE";
int widget_$_->{name}_draw( void *data );
void widget_$_->{name}_keyhandler( input_key key );

CODE
}

print << "CODE";
#endif				/* #ifndef FUSE_WIDGETOPTIONS_H */
CODE
