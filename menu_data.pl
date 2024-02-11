#!/usr/bin/perl -w

# menu_data.pl: generate the menu structure from menu_data.dat
# Copyright (c) 2004-2024 Philip Kendall, Stuart Brady, Marek Januszewski, ZXLDR

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

# Philip Kendall <philip-fuse@shadowmagic.org.uk>

use strict;

use Fuse;

sub get_branch ($$);
sub cname ($);
sub dump_widget ($);
sub _dump_widget ($$);
sub dump_gtk ($$);
sub _dump_gtk ($$$$$);
sub dump_win32 ($$);
sub _dump_win32 ($$$$);
sub dump_qt ($$);
sub _dump_qt ($$$$);

die "usage: $0 <ui>" unless @ARGV >= 1;

my $ui = shift;
my $filename;
my $mode = 'none';

# for Win32:
my $idmnum = 100;

if( $ui eq 'win32' ) {
  die "$0: dump_win32: which mode -- c, h, or rc?" unless @ARGV >= 1;

  $mode = shift;
  $filename = 'menu_data.' . $mode;
} elsif( $ui eq 'gtk' ) {
  die "$0: dump_gtk: which mode -- c, or ui?" unless @ARGV >= 1;

  $mode = shift;
  $filename = 'menu_data.' . $mode;
} elsif( $ui eq 'qt' ) {
  die "$0: dump_qt: which mode -- c, or ui?" unless @ARGV >= 1;

  $mode = shift;
  $filename = 'menu_data.' . $mode;  
} else {
  $filename = 'menu_data.c';
}

print Fuse::GPL( $filename . ': menu structure for Fuse',
		 '2004-2007 Philip Kendall, Stuart Brady, Marek Januszewski' ) . << "CODE" if $mode ne 'ui';

/* This file is autogenerated from menu_data.dat by $0.
   Any changes made here will not be preserved. */

#include "config.h"

#include "menu.h"

CODE

my %menus = ( name => 'Main menu', submenu => [ ] );

while(<>) {

    s/#.*//;
    next if /^\s*$/;

    chomp;

    my( $path, $type, $hotkey, $function, $detail, $action ) = split /\s*,\s*/;

    my @segments = split '/', $path;

    my $entry = { };

    $entry->{name} = pop @segments;
    $entry->{type} = $type;
    $entry->{hotkey} = $hotkey if $hotkey;

    my $walk = $menus{submenu};
    $walk = get_branch( $walk, $_ ) foreach @segments;

    if( $type eq 'Branch' ) {

	$entry->{submenu} = [ ];

    } elsif( $type eq 'Item' ) {

	$entry->{function} = $function if $function;
	$entry->{action} = $action if $action;

    }

    $entry->{detail} = $detail if $detail;

    push @$walk, $entry;

}

if( $ui eq 'gtk' ) {
    dump_gtk( $mode, \%menus );
} elsif( $ui eq 'widget' ) {
    dump_widget( \%menus );
} elsif( $ui eq 'win32' ) {
    dump_win32( $mode, \%menus );
} elsif( $ui eq 'qt' ) {
    dump_qt( $mode, \%menus );
} else {
    die "$0: unknown ui: $ui";
}

sub get_branch ($$) {

    my( $menus, $branch ) = @_;

    foreach my $entry ( @$menus ) {

	next unless $entry->{submenu};

	my $name = $entry->{name};
	$name =~ s/_//;

	return $entry->{submenu} if $name eq $branch;
    }
}

sub cname ($) {

    my( $name ) = @_;

    my $cname = lc $name;
    $cname =~ s/\\01[12]//g if $ui eq 'widget';
    $cname =~ tr/a-z0-9_//cd;

    return $cname;
}

sub dump_widget ($) {

    my( $menu ) = @_;

    print << "HEADERS";
#include "input.h"
#include "ui/widget/options_internals.h"
#include "ui/widget/widget_internals.h"

HEADERS

    _dump_widget( $menu, 'menu' );

}

sub _dump_widget ($$) {

    my( $menu, $path ) = @_;

    my $menu_name = $menu->{name};
    $menu_name =~ s/_//;

    my $s;

    if( $path eq 'menu' ) {
	$s = 'widget_menu_entry widget_menu[]';
    } else {
    	# Slight ugliness here is because "${path}[]" doesn't work under
	# Perl 5.6
	$s = "static widget_menu_entry $path" . "[]";
    }

    $s .= " = {\n  { \"$menu_name\" },\n";

    foreach my $item ( @{ $menu->{submenu} } ) {

	next if $item->{type} eq 'Separator';

	my $name = $item->{name};
	my $key;
	if( $ui eq 'widget' ) {
	    $name =~ s/_(.)/\\012$1\\011/;
	    $key = lc $1 if $1;
	} else {
	    $name =~ s/_(.)/($1)/;
	    $key = lc $1 if $1;
	}
	
	$s .= "  { \"$name\", INPUT_KEY_" . ( $key || 'NONE' ) . ', ';

	my $cname = cname( $name );
	
        my $detail = $item->{detail} || "NULL";

	if( $item->{submenu} ) {
	    $s .= "${path}_$cname, NULL, $detail, 0";
	    _dump_widget( $item, "${path}_$cname" );
	} else {
	    my $function = $item->{function} || "${path}_$cname";
	    $s .= "NULL, $function, $detail, " . ( $item->{action} || 0 );
	}

	$s .= " },\n";
    }

    $s .= "  { NULL }\n};\n\n";

    print $s;
}












sub dump_qt ($$) {

  my( $mode, $menu ) = @_;

  if( $mode eq 'c' ) {
  } elsif( $mode eq 'ui' ) {

    print << "XML";
<?xml version="1.0" encoding="UTF-8"?>
<ui version="4.0">
  <class>DeFuseWindow</class>
  <widget class="QMainWindow" name="window">
    <property name="geometry">
    <rect>
      <x>0</x>
      <y>0</y>
      <width>800</width>
      <height>600</height>
    </rect>
    </property>  
    <property name="windowTitle">
      <string>De-Fuse</string>
    </property>
    <widget class="QWidget" name="centralwidget"/>
    <widget class="QMenuBar" name="menubar">
XML

    _dump_qt( $mode, $menu, 'menu', '      ' );

    print << "XML";
    </widget>
    <widget class="QStatusBar" name="statusbar"/>
XML

    _dump_qt( 'actions', $menu, 'menu', '  ' );

    print << "XML";
  </widget>
  <resources/>
  <connections/>
</ui>
XML

  }

}

sub _dump_qt ($$$$) {

  my( $mode, $menu, $path, $spaces ) = @_;

  my $menu_name = $menu->{name};
  $menu_name =~ s/_//;

  if( $mode eq 'actions' ) {
    foreach my $item ( @{ $menu->{submenu} } ) {
      if( $item->{type} eq 'Separator' ) {
        next;
      }

      my $name = $item->{name};
      $name =~ s/_/&/;
      my $cname = cname( $name );
      $name =~ s/&/&amp;/;

      if( $item->{submenu} ) {
        _dump_qt( $mode, $item, "${path}_$cname", $spaces . "  " );
      } else {
            print << "XML";
    <action name="action_${cname}">
      <property name="text">
        <string>$name</string>
      </property>
    </action>            
XML

      }
    }
  } elsif( $mode eq 'ui' ) {
    foreach my $item ( @{ $menu->{submenu} } ) {

      if( $item->{type} eq 'Separator' ) {
        print "${spaces}<addaction name=\"separator\"/>\n";
        next;
      }

      my $name = $item->{name};
      $name =~ s/_/&/;
      my $cname = cname( $name );
      $name =~ s/&/&amp;/;

      if( $item->{submenu} ) {
            print << "XML";
${spaces}<widget class="QMenu" name="menu_${cname}">
${spaces}  <property name="title">
${spaces}    <string>$name</string>
${spaces}  </property>
XML

            _dump_qt( $mode, $item, "${path}_$cname", $spaces . "  " );

            print "${spaces}</widget>\n";
            print "${spaces}<addaction name=\"menu_${cname}\"/>\n";
      } else {
          print "${spaces}<addaction name=\"action_${cname}\"/>\n";
      }
    }
  }
}









sub dump_gtk ($$) {

  my( $mode, $menu ) = @_;

  if( $mode eq 'c' ) {

    print << "HEADERS";
#include <gtk/gtk.h>

HEADERS

    print "/* Bindings to callbacks with action */\n";

    _dump_gtk( 'callbacks', $menu, '', 'menu', '  ' );

    print "GtkActionEntry gtkui_menu_data[] = {\n\n";

    _dump_gtk( 'actions', $menu, '', 'menu', '  ' );

    print << "CODE";

};

guint gtkui_menu_data_size = ARRAY_SIZE( gtkui_menu_data );
CODE

 } elsif( $mode eq 'ui' ) {

    print << "XML";
<?xml version="1.0" encoding="utf-8"?>
<ui>
  <menubar name='MainMenu'>
XML

    _dump_gtk( 'ui', $menu, '', 'menu', '    ' );

    print << "XML";
  </menubar>
</ui>
XML

  }
}

sub _dump_gtk ($$$$$) {

  my( $mode, $menu, $gtk_path, $cpath, $spaces ) = @_;

  foreach my $item ( @{ $menu->{submenu} } ) {

    next if $item->{type} eq 'Separator' && $mode ne 'ui';

    #Remove toplevel accelerators
    my $name = $item->{name};
    $name =~ s/_// if !$gtk_path;
    my $label = $name;

    my $action_name = $name;
    $action_name =~ s/_//;
    $action_name = $gtk_path . "/" . $action_name;
    $action_name =~ s|/|_|g;
    $action_name =~ s/_//;
    $action_name = uc( cname( $action_name ) );

    $name =~ s/_// if $gtk_path;
    my $new_cpath = "${cpath}_" . cname( $name );
    my $function;
    my $binded_function = $item->{function} || $new_cpath;

    if( $item->{type} eq 'Item' && $item->{action} ) {
      $function = $new_cpath;
    } else {
      $function = $binded_function;
    }

    if( $mode eq 'callbacks' ) {
      if( $item->{type} eq 'Item' && $item->{action} ) {
        print "static MENU_CALLBACK( ", $function, " )\n{\n";
        print "  $binded_function( gtk_action, $item->{action} );\n}\n\n";
      }
    } elsif( $mode eq 'ui' ) {
      if( $item->{type} eq 'Item' ) {
        print "$spaces<menuitem name='$name' action='$action_name'/>\n";
      } elsif( $item->{type} eq 'Separator' ) {
        print "$spaces<separator/>\n";
      } else {
        print "$spaces<menu name='", $name, "' action='", $action_name, "'>\n";
      }
    } else {
      #action_name, stock_id, label
      print "  { \"$action_name\", NULL, \"$label\", ";

      #hotkey
      if( $item->{hotkey} ) {
        print "\"$item->{hotkey}\"";
      } else {
        print 'NULL';
      }

      #tooltip
      print ", NULL, ";

      #callback
      if( $item->{type} eq 'Item' ) {
        print "G_CALLBACK( ", $function, " )";
      } else {
        print "NULL";
      }

      print " },\n";
    }

    _dump_gtk( $mode, $item, "$gtk_path/$name", $new_cpath, $spaces . "  " )
               if $item->{submenu};

    print "$spaces</menu>\n" if $mode eq 'ui' && $item->{type} eq 'Branch';
  }
}

sub dump_win32 ($$) {

    my( $mode, $menu ) = @_;

    if( $mode eq 'c' ) {
	print << "CODE";
#include "ui/win32/menu_data.h"
#include "ui/win32/win32internals.h"

int handle_menu( DWORD cmd, HWND window )
{
  switch( cmd )
  {
CODE
    } elsif( $mode eq 'h' ) {
	print << "CODE";
#include <windows.h>

CODE
    } elsif( $mode eq 'rc' ) {
	print << "CODE";
#include <windows.h>
#include "ui/win32/menu_data.h"

win32_menu MENU
{
CODE
    }

    _dump_win32( $mode, $menu, 'menu', '  ' );

    if( $mode eq 'c' ) {
	print << "CODE";
  }
  return 1;
}
CODE
    } elsif( $mode eq 'rc' ) {
	print << "CODE";
}

win32_accel ACCELERATORS
{
CODE
	_dump_win32( 'a', $menu, 'menu', '' );
	print << "CODE";
}
CODE
    }

}

sub _dump_win32 ($$$$) {

    my( $mode, $menu, $path, $spaces ) = @_;

    my $menu_name = $menu->{name};
    $menu_name =~ s/_//;

    foreach my $item ( @{ $menu->{submenu} } ) {

	if( $item->{type} eq 'Separator' ) {
	    if( $mode eq 'rc' ) {
		print "${spaces}MENUITEM SEPARATOR\n";
	    }
	    next;
	}

	my $name = $item->{name};

	$name =~ s/_/&/;

	my $cname = cname( $name );
	my $idmname = "IDM_" . uc( "${path}_$cname" );

	if( $mode eq 'h' ) {
	    print "#define $idmname $idmnum\n";
	    $idmnum++;
	} elsif( $mode eq 'a' ) {
	    if( $item->{hotkey} ) {
		print "  VK_" . uc( $item->{hotkey} ) . ", $idmname, VIRTKEY\n";
	    }
	}

	if( $item->{submenu} ) {
	    if( $mode eq 'rc' ) {
	        print "${spaces}POPUP \"$name\"\n";
		print "${spaces}\{\n";
	    }
	    _dump_win32( $mode, $item, "${path}_$cname", $spaces . "  " );
	    if( $mode eq 'rc' ) {
	        print "${spaces}}\n";
	    }
	} else {
	    if( $mode eq 'c' ) {
	        my $function = $item->{function} || "${path}_$cname";
		print "    case $idmname:\n";
		print "      $function( " . ( $item->{action} || 0 ) . " ); "
		      . "return 0;\n";
	    } elsif( $mode eq 'rc' ) {
		my $hotkey;
		if( $item->{hotkey} ) {
		    $hotkey = "\\t" . $item->{hotkey};
		} else {
		    $hotkey = "";
		}
		print "${spaces}MENUITEM \"$name$hotkey\", $idmname\n";
	    }
	}
    }
}
