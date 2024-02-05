/* debugger.c: the GTK debugger
   Copyright (c) 2002-2015 Philip Kendall
   Copyright (c) 2013 Sergio Baldoví
   Copyright (c) 2015 Stuart Brady
   Copyright (c) 2016 BogDan Vatra
   Copyright (c) 2024 M.P.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

   Author contact information:

   E-mail: philip-fuse@shadowmagic.org.uk

*/

#include <config.h>

#include <math.h>
#include <stdio.h>
#include <string.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include <libspectrum.h>

#include "debugger/debugger.h"
#include "event.h"
#include "fuse.h"
#include "gtkcompat.h"
#include "gtkinternals.h"
#include "machine.h"
#include "memory_pages.h"
#include "peripherals/ide/zxcf.h"
#include "peripherals/scld.h"
#include "peripherals/ula.h"
#include "settings.h"
#include "ui/ui.h"
#include "z80/z80.h"
#include "z80/z80_macros.h"

/* The various debugger panes */
typedef enum debugger_pane {

  DEBUGGER_PANE_BEGIN = 1,	/* Start marker */

  DEBUGGER_PANE_REGISTERS = DEBUGGER_PANE_BEGIN,
  DEBUGGER_PANE_MEMORYMAP,
  DEBUGGER_PANE_BREAKPOINTS,
  DEBUGGER_PANE_DISASSEMBLY,
  DEBUGGER_PANE_STACK,
  DEBUGGER_PANE_EVENTS,

  DEBUGGER_PANE_END		/* End marker */

} debugger_pane;

/* The columns used in the breakpoints pane */

enum {
  BREAKPOINTS_COLUMN_ID,
  BREAKPOINTS_COLUMN_TYPE,
  BREAKPOINTS_COLUMN_VALUE,
  BREAKPOINTS_COLUMN_IGNORE,
  BREAKPOINTS_COLUMN_LIFE,
  BREAKPOINTS_COLUMN_CONDITION,

  BREAKPOINTS_COLUMN_COUNT
};

/* The columns used in the disassembly pane */

enum {
  DISASSEMBLY_COLUMN_PC,
  DISASSEMBLY_COLUMN_BREAKPOINT,
  DISASSEMBLY_COLUMN_ADDRESS,
  DISASSEMBLY_COLUMN_INSTRUCTION,

  DISASSEMBLY_COLUMN_COUNT
};

/* The columns used in the stack pane */

enum {
  STACK_COLUMN_ADDRESS,
  STACK_COLUMN_VALUE_TEXT,
  STACK_COLUMN_VALUE_INT,

  STACK_COLUMN_COUNT
};

/* The columns used in the events pane */

enum {
  EVENTS_COLUMN_TIME,
  EVENTS_COLUMN_TYPE,

  EVENTS_COLUMN_COUNT
};

static int create_dialog( void );
static PangoFontDescription * monospaced_font( void );
static int hide_hidden_panes( void );
static GtkCheckMenuItem* get_pane_menu_item( debugger_pane pane );
static GtkWidget* get_pane( debugger_pane pane );
static int create_menu_bar( GtkBox *parent, GtkAccelGroup **accel_group );
static void do_selection( GtkWidget* widget, GdkEventButton *event );
static void toggle_display( GtkToggleAction* action, debugger_pane pane );
static void toggle_colorize_disassembly( GtkToggleAction* action, gpointer data );
static void toggle_display_registers( GtkToggleAction* action, gpointer data );
static void toggle_display_memory_map( GtkToggleAction* action, gpointer data );
static void toggle_display_breakpoints( GtkToggleAction* action,
                                        gpointer data );
static void toggle_display_disassembly( GtkToggleAction* action,
                                        gpointer data );
static void toggle_display_stack( GtkToggleAction* action, gpointer data );
static void toggle_display_events( GtkToggleAction* action, gpointer data );
static int create_register_display( GtkBox *parent, PangoFontDescription *font );
static int create_memory_map( GtkBox *parent, PangoFontDescription *font );
static void create_breakpoints( GtkBox *parent, PangoFontDescription *font );
static void create_disassembly( GtkBox *parent, PangoFontDescription *font );
static void disassembly_activate( GtkTreeView *tree_view, GtkTreePath *path,
			    GtkTreeViewColumn *column, gpointer user_data );
static void create_stack_display( GtkBox *parent, PangoFontDescription *font );
static void stack_activate( GtkTreeView *tree_view, GtkTreePath *path,
			    GtkTreeViewColumn *column, gpointer user_data );
static void breakpoints_activate( GtkTreeView *tree_view, GtkTreePath *path,
	        GtkTreeViewColumn *column, gpointer user_data );          
static void create_events( GtkBox *parent, PangoFontDescription *font );
static void events_activate( GtkTreeView *tree_view, GtkTreePath *path,
			     GtkTreeViewColumn *column, gpointer user_data );
static int create_command_entry( GtkBox *parent, GtkAccelGroup *accel_group );
static int create_buttons( GtkDialog *parent, GtkAccelGroup *accel_group );

static int activate_debugger( void );
static void update_memory_map( void );
static void update_breakpoints( void );
static void update_disassembly( void );
static void update_events( void );
static void add_event( gpointer data, gpointer user_data );
static int deactivate_debugger( void );

static gboolean
disassembly_key_press( GtkTreeView *list, GdkEventKey *event,
                       gpointer user_data );
static gboolean
disassembly_wheel_scroll( GtkTreeView *list GCC_UNUSED, GdkEvent *event,
                          gpointer user_data );

static void move_disassembly( GtkAdjustment *adjustment, gpointer user_data );
#if GTK_CHECK_VERSION( 3, 0, 0 )
static void debugger_goto_offset( GtkWidget *widget, gpointer user_data );
#endif

static void evaluate_command( GtkWidget *widget, gpointer user_data );
static void gtkui_debugger_done_step( GtkWidget *widget, gpointer user_data );
static void gtkui_debugger_done_continue( GtkWidget *widget,
					  gpointer user_data );
static void gtkui_debugger_break( GtkWidget *widget, gpointer user_data );
static gboolean delete_dialog( GtkWidget *widget, GdkEvent *event,
			       gpointer user_data );
static void gtkui_debugger_done_close( GtkWidget *widget, gpointer user_data );

static GtkWidget *dialog,		/* The debugger dialog box */
  *step_button, *continue_button, *break_button,	/* buttons */
  *register_display,			/* The register display */
  *registers_frame, 
  *registers[18],			/* Individual registers */
  *memory_map,				/* The memory map display */
  *memory_box,
  *memory_map_table,                    /* The table for the memory map */
  *map_label[MEMORY_PAGES_IN_64K][4],   /* Labels in the memory map */
  *breakpoints = NULL,				/* The breakpoint display */
  *disassembly_box,			/* A box to hold the disassembly */
  *disassembly,				/* The actual disassembly widget */
  *stack,				/* The stack display */
  *events;				/* The events display */

static GtkListStore *breakpoints_model, *disassembly_model, *stack_model,
  *events_model;

static GtkAdjustment *disassembly_scrollbar_adjustment;

/* The top line of the current disassembly */
static libspectrum_word disassembly_top;

/* The next line below the current disassembly */
static libspectrum_word disassembly_bottom;

/* Have we created the above yet? */
static int dialog_created = 0;

/* Is the debugger window active (as opposed to the debugger itself)? */
static int debugger_active;

/* The UIManager used to create the menu bar */
static GtkUIManager *ui_manager_debugger = NULL;

static int colorize_disassembly = 1;

/* The debugger's menu bar */
const gchar debugger_menu[] =
"<menubar name='DebuggerMenu'>"
"  <menu name='View' action='VIEW'>"
"    <menuitem name='Colorize disassembly' action='VIEW_COLORIZE_DISASSEMBLY'/>"  
"  </menu>"
"  <menu name='Window' action='WINDOW'>"
"    <menuitem name='Registers' action='VIEW_REGISTERS'/>"
"    <menuitem name='Memory Map' action='VIEW_MEMORY_MAP'/>"
"    <menuitem name='Breakpoints' action='VIEW_BREAKPOINTS'/>"
"    <menuitem name='Disassembly' action='VIEW_DISASSEMBLY'/>"
"    <menuitem name='Stack' action='VIEW_STACK'/>"
"    <menuitem name='Events' action='VIEW_EVENTS'/>"
"  </menu>"
"</menubar>";

/* The debugger's menu actions */
static GtkActionEntry menu_data[] = {
  { "VIEW", NULL, "_View", NULL, NULL, NULL },
  { "WINDOW", NULL, "_Window", NULL, NULL, NULL },
};

static GtkToggleActionEntry menu_toggles[] = {

  { "VIEW_COLORIZE_DISASSEMBLY", NULL, "_Colorize disassembly", NULL, NULL, G_CALLBACK( toggle_colorize_disassembly ), TRUE },
  { "VIEW_REGISTERS", NULL, "_Registers", NULL, NULL, G_CALLBACK( toggle_display_registers ), TRUE },
  { "VIEW_MEMORY_MAP", NULL, "_Memory Map", NULL, NULL, G_CALLBACK( toggle_display_memory_map ), TRUE },
  { "VIEW_BREAKPOINTS", NULL, "_Breakpoints", NULL, NULL, G_CALLBACK( toggle_display_breakpoints ), TRUE },
  { "VIEW_DISASSEMBLY", NULL, "_Disassembly", NULL, NULL, G_CALLBACK( toggle_display_disassembly ), TRUE },
  { "VIEW_STACK", NULL, "_Stack", NULL, NULL, G_CALLBACK( toggle_display_stack ), TRUE },
  { "VIEW_EVENTS", NULL, "_Events", NULL, NULL, G_CALLBACK( toggle_display_events ), TRUE },

};

static const char*
format_8_bit( void )
{
  return debugger_output_base == 10 ? "%3d" : "0x%02X";
}

static const char*
format_16_bit( void )
{
  return debugger_output_base == 10 ? "%5d" : "0x%04X";
}

int
ui_debugger_activate( void )
{
  int error;

  fuse_emulation_pause();

  /* Create the dialog box if it doesn't already exist */
  if( !dialog_created ) if( create_dialog() ) return 1;

  gtk_widget_show_all( dialog );
  error = hide_hidden_panes(); if( error ) return error;

  gtk_widget_set_sensitive( continue_button, 1 );
  gtk_widget_set_sensitive( break_button, 0 );
  if( !debugger_active ) activate_debugger();

  return 0;
}

void
ui_breakpoints_updated( void )
{
  if ( breakpoints == NULL ) return;
  update_breakpoints();
}

static int
hide_hidden_panes( void )
{
  debugger_pane i;
  GtkCheckMenuItem *checkitem; GtkWidget *pane;

  for( i = DEBUGGER_PANE_BEGIN; i < DEBUGGER_PANE_END; i++ ) {

    checkitem = get_pane_menu_item( i ); if( !checkitem ) return 1;

    if( gtk_check_menu_item_get_active( checkitem ) ) continue;

    pane = get_pane( i ); if( !pane ) return 1;

    gtk_widget_hide( pane );
  }

  return 0;
}

static GtkCheckMenuItem*
get_pane_menu_item( debugger_pane pane )
{
  const gchar *path;
  GtkWidget *menu_item;

  path = NULL;

  switch( pane ) {
  case DEBUGGER_PANE_REGISTERS: path = "/Window/Registers"; break;
  case DEBUGGER_PANE_MEMORYMAP: path = "/Window/Memory Map"; break;
  case DEBUGGER_PANE_BREAKPOINTS: path = "/Window/Breakpoints"; break;
  case DEBUGGER_PANE_DISASSEMBLY: path = "/Window/Disassembly"; break;
  case DEBUGGER_PANE_STACK: path = "/Window/Stack"; break;
  case DEBUGGER_PANE_EVENTS: path = "/Window/Events"; break;

  case DEBUGGER_PANE_END: break;
  }

  if( !path ) {
    ui_error( UI_ERROR_ERROR, "unknown debugger pane %u", pane );
    return NULL;
  }

  gchar *full_path = g_strdup_printf( "/DebuggerMenu%s", path );
  menu_item = gtk_ui_manager_get_widget( ui_manager_debugger, full_path );
  g_free( full_path );

  if( !menu_item ) {
    ui_error( UI_ERROR_ERROR, "couldn't get menu item '%s'",
	      path );
    return NULL;
  }

  return GTK_CHECK_MENU_ITEM( menu_item );
}

static GtkWidget*
get_pane( debugger_pane pane )
{
  switch( pane ) {
  case DEBUGGER_PANE_REGISTERS: return registers_frame;
  case DEBUGGER_PANE_MEMORYMAP: return memory_box;
  case DEBUGGER_PANE_BREAKPOINTS: return breakpoints;
  case DEBUGGER_PANE_DISASSEMBLY: return disassembly_box;
  case DEBUGGER_PANE_STACK: return stack;
  case DEBUGGER_PANE_EVENTS: return events;

  case DEBUGGER_PANE_END: break;
  }

  ui_error( UI_ERROR_ERROR, "unknown debugger pane %u", pane );
  return NULL;
}
  
int
ui_debugger_deactivate( int interruptable )
{
  if( debugger_active ) deactivate_debugger();

  if( dialog_created ) {
    gtk_widget_set_sensitive( continue_button, !interruptable );
    gtk_widget_set_sensitive( break_button,     interruptable );
  }

  return 0;
}

static PangoFontDescription * monospaced_font() {
  PangoFontDescription *font;
  if ( gtkui_get_monospaced_font( &font ) ) {
    return NULL;
  }
  return font;
}

static int
create_dialog( void )
{
  int error;
  GtkWidget *hbox, *vbox, *hbox2, *content_area;
  GtkAccelGroup *accel_group;

  PangoFontDescription *font;

  font = monospaced_font(); if( font == NULL ) return -1;

  dialog = gtkstock_dialog_new( "Fuse - Debugger",
				G_CALLBACK( delete_dialog ) );
  content_area = gtk_dialog_get_content_area( GTK_DIALOG( dialog ) );

  /* The menu bar */
  error = create_menu_bar( GTK_BOX( content_area ), &accel_group );
  if( error ) return error;

  /* Keyboard shortcuts */
  gtk_window_add_accel_group( GTK_WINDOW( dialog ), accel_group );

  /* Some boxes to contain the things we want to display */
  hbox = gtk_box_new( GTK_ORIENTATION_HORIZONTAL, 0 );
  gtk_box_pack_start( GTK_BOX( content_area ), hbox, TRUE, TRUE, 5 );

  vbox = gtk_box_new( GTK_ORIENTATION_VERTICAL, 5 );
  gtk_box_pack_start( GTK_BOX( hbox ), vbox, TRUE, TRUE, 5 );

  hbox2 = gtk_box_new( GTK_ORIENTATION_HORIZONTAL, 5 );
  gtk_box_pack_start( GTK_BOX( vbox ), hbox2, TRUE, TRUE, 0 );

  /* The main display areas */
  error = create_register_display( GTK_BOX( hbox2 ), font );
  if( error ) return error;

  error = create_memory_map( GTK_BOX( hbox2 ), font ); if( error ) return error;

  create_breakpoints( GTK_BOX( vbox ), font );
  create_disassembly( GTK_BOX( hbox ), font );
  create_stack_display( GTK_BOX( hbox ), font );
  create_events( GTK_BOX( hbox ), font );

  error = create_command_entry( GTK_BOX( content_area ), accel_group );
  if( error ) return error;

  /* The action buttons */

  error = create_buttons( GTK_DIALOG( dialog ), accel_group );
  if( error ) return error;

  gtkui_free_font( font );

  dialog_created = 1;

  return 0;
}

static int
create_menu_bar( GtkBox *parent, GtkAccelGroup **accel_group )
{
  GError *error = NULL;
  GtkActionGroup *menu_action_group;
  GtkWidget *menu_bar;
  guint ui_menu_id;

  /* FIXME: we should unref this at some point */
  ui_manager_debugger = gtk_ui_manager_new();

  /* Load actions */
  menu_action_group = gtk_action_group_new( "DebuggerActionGroup" );
  gtk_action_group_add_actions( menu_action_group, menu_data,
				ARRAY_SIZE( menu_data ), NULL );
  gtk_action_group_add_toggle_actions( menu_action_group, menu_toggles,
                                       ARRAY_SIZE( menu_toggles ), NULL );
  gtk_ui_manager_insert_action_group( ui_manager_debugger, menu_action_group,
                                      0 );
  g_object_unref( menu_action_group );

  /* Load the menu */
  ui_menu_id = gtk_ui_manager_add_ui_from_string( ui_manager_debugger,
                                                  debugger_menu,
                                                  sizeof( debugger_menu ),
                                                  &error );
  if( error ) {
    g_error_free( error );
    return 1;
  }
  else if( !ui_menu_id ) return 1;

  *accel_group = gtk_ui_manager_get_accel_group( ui_manager_debugger );

  menu_bar = gtk_ui_manager_get_widget( ui_manager_debugger, "/DebuggerMenu" );

  gtk_box_pack_start( parent, menu_bar, FALSE, FALSE, 0 );
  
  return 0;
}

static void
toggle_display( GtkToggleAction* action, debugger_pane pane_id )
{
  GtkWidget *pane;

  pane = get_pane( pane_id ); if( !pane ) return;

  if( gtk_toggle_action_get_active( action ) ) {
    gtk_widget_show_all( pane );
  } else {
    gtk_widget_hide( pane );
  }
}

static void
toggle_colorize_disassembly( GtkToggleAction* action, gpointer data GCC_UNUSED )
{
  colorize_disassembly = gtk_toggle_action_get_active( action );
  update_disassembly();
}

static void
toggle_display_registers( GtkToggleAction* action, gpointer data GCC_UNUSED )
{
  toggle_display( action, DEBUGGER_PANE_REGISTERS );
}

static void
toggle_display_memory_map( GtkToggleAction* action, gpointer data GCC_UNUSED )
{
  toggle_display( action, DEBUGGER_PANE_MEMORYMAP );
}

static void
toggle_display_breakpoints( GtkToggleAction* action, gpointer data GCC_UNUSED )
{
  toggle_display( action, DEBUGGER_PANE_BREAKPOINTS );
}

static void
toggle_display_disassembly( GtkToggleAction* action, gpointer data GCC_UNUSED )
{
  toggle_display( action, DEBUGGER_PANE_DISASSEMBLY );
}

static void
toggle_display_stack( GtkToggleAction* action, gpointer data GCC_UNUSED )
{
  toggle_display( action, DEBUGGER_PANE_STACK );
}

static void
toggle_display_events( GtkToggleAction* action, gpointer data GCC_UNUSED )
{
  toggle_display( action, DEBUGGER_PANE_EVENTS );
}

static int
create_register_display( GtkBox *parent, PangoFontDescription *font )
{
  size_t i;

  registers_frame = gtk_frame_new( "Registers, flags, states..." );
  gtk_box_pack_start( parent, registers_frame, TRUE, TRUE, 0 );

#if GTK_CHECK_VERSION( 3, 0, 0 )

  register_display = gtk_grid_new();
  gtk_grid_set_row_spacing( GTK_GRID( register_display ), 4 );
  gtk_container_set_border_width( GTK_CONTAINER( register_display ), 6 );

#else                /* #if GTK_CHECK_VERSION( 3, 0, 0 ) */

  register_display = gtk_table_new( 9, 2, FALSE );

#endif

  gtk_container_add( GTK_CONTAINER( registers_frame ), register_display );

  for( i = 0; i < 18; i++ ) {
    PangoAttrList *list;
    PangoAttribute *attr;

    registers[i] = gtk_label_new( "" );
    gtk_label_set_selectable( registers[i], TRUE );

    list = pango_attr_list_new();
    attr = pango_attr_font_desc_new( font );
    pango_attr_list_insert( list, attr );
    gtk_label_set_attributes( GTK_LABEL( registers[i] ), list );
    pango_attr_list_unref( list );

#if GTK_CHECK_VERSION( 3, 0, 0 )
    gtk_grid_attach( GTK_GRID( register_display ), registers[i],
                     i%2, i/2, 1, 1 );
#else
    gtk_table_attach( GTK_TABLE( register_display ), registers[i],
                      i%2, i%2+1, i/2, i/2+1, 0, 0, 2, 2 );
#endif

  }

  return 0;
}

static int
create_memory_map( GtkBox *parent, PangoFontDescription *font )
{
  GtkWidget *label_address, *label_source, *label_writable, *label_contended;
  GtkWidget *search_label, *search_box, *search_offset;

  label_address   = gtk_label_new( "Address" );
  label_source    = gtk_label_new( "Source" );
  label_writable  = gtk_label_new( "W?" );
  label_contended = gtk_label_new( "C?" );

  gtk_widget_set_tooltip_text( GTK_WIDGET( label_writable ), "Writable" ); 
  gtk_widget_set_tooltip_text( GTK_WIDGET( label_contended ), "Contended" ); 

  memory_box = gtk_box_new( GTK_ORIENTATION_VERTICAL, 0 );
  gtk_box_pack_start( parent, memory_box, TRUE, TRUE, 0 );

  memory_map = gtk_frame_new( "Memory Map" );
  gtk_box_pack_start( GTK_BOX( memory_box ), memory_map, TRUE, TRUE, 0 );

#if GTK_CHECK_VERSION( 3, 0, 0 )

  memory_map_table = gtk_grid_new();
  gtk_grid_set_row_spacing( GTK_GRID( memory_map_table ), 4 );
  gtk_grid_set_column_spacing( GTK_GRID( memory_map_table ), 6 );
  gtk_container_set_border_width( GTK_CONTAINER( memory_map_table ), 6 );
  gtk_container_add( GTK_CONTAINER( memory_map ), memory_map_table );

  gtk_grid_attach( GTK_GRID( memory_map_table ), label_address, 0, 0, 1, 1 );
  gtk_grid_attach( GTK_GRID( memory_map_table ), label_source, 1, 0, 1, 1 );
  gtk_grid_attach( GTK_GRID( memory_map_table ), label_writable, 2, 0, 1, 1 );
  gtk_grid_attach( GTK_GRID( memory_map_table ), label_contended, 3, 0, 1, 1 );

  /* Go to offset */
  search_box = gtk_box_new( GTK_ORIENTATION_HORIZONTAL, 8 );
#if GTK_CHECK_VERSION( 3, 6, 0 )
  search_offset = gtk_search_entry_new();
#else
  search_offset = gtk_entry_new();
#endif

  /*
   * Entry is max 6 chars wide ("0xXXXX") but the GTK widget adds
   * a search icon and "clear contents" icon, which between them
   * take up about 6 char's widths. So it needs to be wider.
   */
  gtk_entry_set_width_chars( GTK_ENTRY( search_offset ), 15 );
  gtk_entry_set_max_length( GTK_ENTRY( search_offset ), 6 );
  gtk_box_pack_end( GTK_BOX( search_box ), search_offset, FALSE, FALSE, 0 );

  search_label = gtk_label_new( "Go to offset" );
  gtk_box_pack_end( GTK_BOX( search_box ), search_label, FALSE, FALSE, 0 );

  gtk_box_pack_start( GTK_BOX( memory_box ), search_box, FALSE, FALSE, 8 );

  g_signal_connect( G_OBJECT( search_offset ), "activate",
                    G_CALLBACK( debugger_goto_offset ), NULL );

#else                /* #if GTK_CHECK_VERSION( 3, 0, 0 ) */

  memory_map_table = gtk_table_new( 1 + MEMORY_PAGES_IN_64K, 4, FALSE );
  gtk_container_add( GTK_CONTAINER( memory_map ), memory_map_table );

  gtk_table_attach( GTK_TABLE( memory_map_table ), label_address,
                    0, 1, 0, 1, 0, 0, 2, 2 );
  gtk_table_attach( GTK_TABLE( memory_map_table ), label_source,
                    1, 2, 0, 1, 0, 0, 2, 2 );
  gtk_table_attach( GTK_TABLE( memory_map_table ), label_writable,
                    2, 3, 0, 1, 0, 0, 2, 2 );
  gtk_table_attach( GTK_TABLE( memory_map_table ), label_contended,
                    3, 4, 0, 1, 0, 0, 2, 2 );

#endif

  return 0;
}

static void breakpoints_popup_menu_offset( GtkWidget *menuitem GCC_UNUSED, gpointer userdata GCC_UNUSED ) {

  GtkTreeIter iter;
  GtkTreeSelection *selection;

  selection = gtk_tree_view_get_selection( GTK_TREE_VIEW( breakpoints ) );

  if ( gtk_tree_selection_get_selected (
    selection,
    &breakpoints_model,
    &iter
  ) ) {

    gchar *address, *endptr;
    int base_num, offset;

    gtk_tree_model_get( breakpoints_model, &iter, BREAKPOINTS_COLUMN_VALUE, &address, -1 );
    if ( address ) {
      base_num = ( g_str_has_prefix( address, "0x" ) )? 16 : 10;
      offset = strtol( address, &endptr, base_num );
      g_free( address );

      ui_debugger_disassemble( offset );
      ui_debugger_update();

    }
  }

}

static void breakpoints_popup_menu_delete( GtkWidget *menuitem GCC_UNUSED, gpointer userdata GCC_UNUSED ) {
  GtkTreeIter iter;
  GtkTreeSelection *selection;

  selection = gtk_tree_view_get_selection( GTK_TREE_VIEW( breakpoints ) );

  if ( gtk_tree_selection_get_selected (
    selection,
    &breakpoints_model,
    &iter
  ) ) {

    int id;
    gtk_tree_model_get( breakpoints_model, &iter, BREAKPOINTS_COLUMN_ID, &id, -1 );

    if ( id > 0 ) {
      char cmd[40];
      snprintf( cmd, sizeof( cmd ), "del %i", id );
      debugger_command_evaluate( cmd );
    }

    update_disassembly();
  }
}

static void breakpoints_popup_menu_delete_all( GtkWidget *menuitem GCC_UNUSED, gpointer userdata GCC_UNUSED ) {

  debugger_command_evaluate( "del" );
  update_disassembly();

}

static gboolean breakpoints_popup_menu (
  GtkWidget* widget,
  GdkEventButton *event,
  gpointer user_data GCC_UNUSED
)  {
  const int RIGHT_CLICK = 3;
  if (event->button != RIGHT_CLICK) return FALSE;

  do_selection( widget, event );

  GtkWidget *menu, *menuitem;
  menu = gtk_menu_new();

  menuitem = gtk_menu_item_new_with_label("Go to offset");
  g_signal_connect( menuitem, "activate", G_CALLBACK( breakpoints_popup_menu_offset ), NULL );
  gtk_menu_shell_append( GTK_MENU_SHELL( menu ), menuitem );

  menuitem = gtk_menu_item_new_with_label("Delete breakpoint");
  g_signal_connect( menuitem, "activate", G_CALLBACK( breakpoints_popup_menu_delete ), NULL );
  gtk_menu_shell_append( GTK_MENU_SHELL( menu ), menuitem );

  menuitem = gtk_menu_item_new_with_label("Delete all breakpoints");
  g_signal_connect( menuitem, "activate", G_CALLBACK( breakpoints_popup_menu_delete_all ), NULL );
  gtk_menu_shell_append( GTK_MENU_SHELL( menu ), menuitem );

  gtk_widget_show_all( menu );
  gtk_menu_popup( GTK_MENU( menu ), NULL, NULL, NULL, NULL, event->button, gdk_event_get_time( ( GdkEvent* )event ) );

  return TRUE;
}

static void
create_breakpoints( GtkBox *parent, PangoFontDescription *font )
{
  size_t i;

  static const gchar *const titles[] =
    { "ID", "Type", "Value", "Ignore", "Life", "Condition" };

  breakpoints_model = gtk_list_store_new( BREAKPOINTS_COLUMN_COUNT, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING );

  breakpoints = gtk_tree_view_new_with_model( GTK_TREE_MODEL( breakpoints_model ) );
  for( i = 0; i < BREAKPOINTS_COLUMN_COUNT; i++ ) {
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes( titles[i], renderer, "text", i, NULL );
    g_object_set( G_OBJECT( renderer ), "font-desc", font, "height", 18, NULL );
    gtk_tree_view_append_column( GTK_TREE_VIEW( breakpoints ), column );
  }

  gtk_box_pack_start( parent, breakpoints, TRUE, TRUE, 0 );

  g_signal_connect( G_OBJECT( breakpoints ), "row-activated", G_CALLBACK( breakpoints_activate ), NULL );

  g_signal_connect( GTK_TREE_VIEW( breakpoints ), "button-press-event", G_CALLBACK( breakpoints_popup_menu ), NULL );
}

// command, foreground, background
const char * disassembly_color_table[] = {
  "JP",   "Brown",        "",
  "JR",   "Dark Orange",  "",
  "CALL", "Blue",         "",
  "DJNZ", "Dark Cyan",    "",
  "NOP",  "Light Gray",   "",
  "RET",  "Green",        "",
  "CP ",  "Dark Magenta", "",
  "RST",  "Orange",       "Black",
  "OUT",  "Light Green",  "Black",
  "IN ",  "Yellow",       "Black",
  "HALT", "Pink",         "Black",
  "DI",   "White",        "Pink",
  "EI",   "White",        "Pink",
  "EX",   "White",        "Dark Blue",
  "IM",   "White",        "Dark Green",
  ""
};

void
disassembly_cell_data( GtkTreeViewColumn *col,
                        GtkCellRenderer   *renderer,
                        GtkTreeModel      *model,
                        GtkTreeIter       *iter,
                        gpointer           user_data )
{
  gchar * instr;
  int offset;

  g_object_set( renderer, "foreground-set", FALSE, NULL ); 
  g_object_set( renderer, "background-set", FALSE, NULL ); 

  if ( colorize_disassembly > 0 ) {

    gtk_tree_model_get( model, iter, DISASSEMBLY_COLUMN_INSTRUCTION, &instr, -1 );

    offset = 0;
    while ( strlen( disassembly_color_table[offset] ) > 0 )
    {
      if ( strncmp( instr, disassembly_color_table[offset], strlen(disassembly_color_table[offset] ) ) == 0 ) {
        if ( strlen( disassembly_color_table[offset + 1] ) > 0 ) g_object_set( renderer, "foreground", disassembly_color_table[offset + 1], "foreground-set", TRUE, NULL );
        if ( strlen( disassembly_color_table[offset + 2] ) > 0 ) g_object_set( renderer, "background", disassembly_color_table[offset + 2], "background-set", TRUE, NULL );
      }    
      offset = offset + 3;
    }

    g_free( instr );

  }
}

static void disassembly_toggle_breakpoint( GtkTreeIter * iter ) {
  gchar *str, *endptr;
  int base_num, offset, id;

  gtk_tree_model_get( disassembly_model, iter, DISASSEMBLY_COLUMN_BREAKPOINT, &str, -1 );
  id = strtol( str, &endptr, base_num );
  g_free( str );

  if ( id == 0 ) {
    gtk_tree_model_get( disassembly_model, iter, DISASSEMBLY_COLUMN_ADDRESS, &str, -1 );
    if ( str ) {
      base_num = ( g_str_has_prefix( str, "0x" ) )? 16 : 10;
      offset = strtol( str, &endptr, base_num );
      g_free( str );

      debugger_breakpoint_add_address(
        DEBUGGER_BREAKPOINT_TYPE_EXECUTE, memory_source_any, 0, offset, 0,
        DEBUGGER_BREAKPOINT_LIFE_PERMANENT, NULL
      );
    }
  } else if ( id > 0 ) {
    char cmd[40];
    snprintf( cmd, sizeof( cmd ), "del %i", id );
    debugger_command_evaluate( cmd );
  }

  update_disassembly();
}

static void disassembly_popup_menu_breakpoint( GtkWidget *menuitem GCC_UNUSED, gpointer userdata GCC_UNUSED ) {
  GtkTreeIter iter;
  GtkTreeSelection *selection;

  selection = gtk_tree_view_get_selection( GTK_TREE_VIEW( disassembly ) );

  if ( gtk_tree_selection_get_selected (
    selection,
    &disassembly_model,
    &iter
  ) ) {

    disassembly_toggle_breakpoint( &iter );

  }
}

static void disassembly_popup_menu_goto_pc( GtkWidget *menuitem GCC_UNUSED, gpointer userdata GCC_UNUSED ) {
  ui_debugger_disassemble( PC ); 
}

static void disassembly_popup_menu_goto_instr_addr( GtkWidget *menuitem GCC_UNUSED, gpointer userdata GCC_UNUSED ) {
  GtkTreeIter iter;
  GtkTreeSelection *selection;

  selection = gtk_tree_view_get_selection( GTK_TREE_VIEW( disassembly ) );

  if ( gtk_tree_selection_get_selected (
    selection,
    &disassembly_model,
    &iter
  ) ) {

    gchar *str, *endptr, *addr_substr;
    int addr;

    gtk_tree_model_get( disassembly_model, &iter, DISASSEMBLY_COLUMN_INSTRUCTION, &str, -1 );
    if ( str ) {
      addr_substr = strstr(str, ",");
      if ( addr_substr ) {
        if ( addr_substr[2] == ' ' || addr_substr[3] == ' ' ) {
          addr_substr = 0;
        }
      }
      if ( addr_substr == 0 || addr_substr[1] == '(' ) {
        addr_substr = strstr(str, "(");
        if ( addr_substr )
        {
          if ( addr_substr[5] != ')' ) {
            addr_substr = 0;
            g_free( str );
            return;
          }
        }
      }
      if ( addr_substr == 0 ) {
        addr_substr = strstr(str, " ");
        if ( addr_substr ) {
          if ( addr_substr[2] == ' ' || addr_substr[3] == ' ' || addr_substr[2] == ',' || addr_substr[3] == ',' ) {
            if ( ! ( toupper( str[0] ) == 'R' && toupper( str[1] ) == 'S' && toupper( str[2] ) == 'T' ) ) {
              addr_substr = 0;
              g_free( str );
              return;
            }
          }
        }
      }
      if ( addr_substr ) {
        addr_substr++;
        addr_substr[4] = 0;
        addr = strtol( addr_substr, &endptr, 16 );
        if ( addr >= 0 && addr < 65536 ) {
          ui_debugger_disassemble( addr ); 
        }
      }
      g_free( str );
    }
  }
}

static void do_selection( GtkWidget* widget, GdkEventButton *event ) {
  GtkTreeSelection *selection;

  selection = gtk_tree_view_get_selection( GTK_TREE_VIEW( widget ) );

  /* Note: gtk_tree_selection_count_selected_rows() does not
    *   exist in gtk+-2.0, only in gtk+ >= v2.2 ! */
  if (gtk_tree_selection_count_selected_rows( selection )  <= 1) {
      GtkTreePath *path;

      /* Get tree path for row that was clicked */
      if (gtk_tree_view_get_path_at_pos( GTK_TREE_VIEW( widget ),
                                        event->x, event->y,
                                        &path, NULL, NULL, NULL ) ) {
        gtk_tree_selection_unselect_all( selection) ;
        gtk_tree_selection_select_path( selection, path );
        gtk_tree_path_free( path );
      }
  }      
}

static gboolean disassembly_popup_menu (
  GtkWidget* widget,
  GdkEventButton *event,
  gpointer user_data GCC_UNUSED
)  {
  const int RIGHT_CLICK = 3;
  if (event->button != RIGHT_CLICK) return FALSE;

  do_selection( widget, event );

  GtkWidget *menu, *menuitem;
  menu = gtk_menu_new();

  menuitem = gtk_menu_item_new_with_label("Toggle breakpoint");
  g_signal_connect( menuitem, "activate", G_CALLBACK( disassembly_popup_menu_breakpoint ), NULL );
  gtk_menu_shell_append( GTK_MENU_SHELL( menu ), menuitem );

  menuitem = gtk_menu_item_new_with_label("Go to offset in instruction");
  g_signal_connect( menuitem, "activate", G_CALLBACK( disassembly_popup_menu_goto_instr_addr ), NULL );
  gtk_menu_shell_append( GTK_MENU_SHELL( menu ), menuitem );

  menuitem = gtk_menu_item_new_with_label("Go to current program counter (PC)");
  g_signal_connect( menuitem, "activate", G_CALLBACK( disassembly_popup_menu_goto_pc ), NULL );
  gtk_menu_shell_append( GTK_MENU_SHELL( menu ), menuitem );

  gtk_widget_show_all( menu );
  gtk_menu_popup( GTK_MENU( menu ), NULL, NULL, NULL, NULL, event->button, gdk_event_get_time( ( GdkEvent* )event ) );

  return TRUE;
}

static void
create_disassembly( GtkBox *parent, PangoFontDescription *font )
{
  size_t i;

  GtkWidget *scrollbar;
  static const gchar *const titles[] =
    { "PC", "ID", "Address", "Instruction" };

  /* A box to hold the disassembly listing and the scrollbar */
  disassembly_box = gtk_box_new( GTK_ORIENTATION_HORIZONTAL, 0 );
  gtk_box_pack_start( parent, disassembly_box, TRUE, TRUE, 0 );

  /* The disassembly itself */
  disassembly_model =
    gtk_list_store_new( DISASSEMBLY_COLUMN_COUNT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING );

  disassembly = gtk_tree_view_new_with_model( GTK_TREE_MODEL( disassembly_model ) );
  for( i = 0; i < DISASSEMBLY_COLUMN_COUNT; i++ ) {
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes( titles[i], renderer, "text", i, NULL );
    g_object_set( G_OBJECT( renderer ), "font-desc", font, "height", 18, NULL );

    /* connect a cell data function */
    gtk_tree_view_column_set_cell_data_func(column, renderer, disassembly_cell_data, NULL, NULL);
        
    gtk_tree_view_append_column( GTK_TREE_VIEW( disassembly ), column );
  }

  gtk_box_pack_start( GTK_BOX( disassembly_box ), disassembly, TRUE, TRUE, 0 );

  /* The disassembly scrollbar */
  disassembly_scrollbar_adjustment = GTK_ADJUSTMENT(
    gtk_adjustment_new( 0, 0x0000, 0x10000, 1, 20, 20 ) );
  g_signal_connect( G_OBJECT( disassembly_scrollbar_adjustment ),
		    "value-changed", G_CALLBACK( move_disassembly ),
		    NULL );
  scrollbar = gtk_scrollbar_new( GTK_ORIENTATION_VERTICAL,
                                 disassembly_scrollbar_adjustment );
  gtk_box_pack_start( GTK_BOX( disassembly_box ), scrollbar, FALSE, FALSE, 0 );

  /* Scrolling with keys */
  g_signal_connect( GTK_TREE_VIEW( disassembly ), "key-press-event",
                    G_CALLBACK( disassembly_key_press ),
                    disassembly_scrollbar_adjustment );

  /* Scrolling with mouse wheel */
  g_signal_connect( GTK_TREE_VIEW( disassembly ), "scroll-event",
                    G_CALLBACK( disassembly_wheel_scroll ),
                    disassembly_scrollbar_adjustment );

  g_signal_connect( GTK_TREE_VIEW( disassembly ), "button-press-event", G_CALLBACK( disassembly_popup_menu ), NULL );

  g_signal_connect( G_OBJECT( disassembly ), "row-activated", G_CALLBACK( disassembly_activate ), NULL );
}

static void disassembly_activate( GtkTreeView *tree_view, GtkTreePath *path,
			    GtkTreeViewColumn *column, gpointer user_data ) {
  GtkTreeIter iter;
  GtkTreeModel *model = gtk_tree_view_get_model( tree_view );

  if( model && gtk_tree_model_get_iter( model, &iter, path ) ) {

    disassembly_toggle_breakpoint( &iter );

  }
}

static void
create_stack_display( GtkBox *parent, PangoFontDescription *font )
{
  size_t i;
  static const gchar *const titles[] = { "Address", "Instruction" };
  
  stack_model =
    gtk_list_store_new( STACK_COLUMN_COUNT, G_TYPE_STRING, G_TYPE_STRING,
			G_TYPE_INT );

  stack = gtk_tree_view_new_with_model( GTK_TREE_MODEL( stack_model ) );

  for( i = 0; i < 2; i++ ) {
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes( titles[i], renderer, "text", i, NULL );
    g_object_set( G_OBJECT( renderer ), "font-desc", font, "height", 18, NULL );
    gtk_tree_view_append_column( GTK_TREE_VIEW( stack ), column );
  }

  gtk_box_pack_start( parent, stack, TRUE, TRUE, 5 );

  g_signal_connect( G_OBJECT( stack ), "row-activated", G_CALLBACK( stack_activate ), NULL );
}

static void
stack_activate( GtkTreeView *tree_view, GtkTreePath *path,
	        GtkTreeViewColumn *column GCC_UNUSED,
		gpointer user_data GCC_UNUSED )
{
  GtkTreeIter it;
  GtkTreeModel *model = gtk_tree_view_get_model( tree_view );

  if( model && gtk_tree_model_get_iter( model, &it, path ) ) {
    gint address;
    int error;

    gtk_tree_model_get( model, &it, STACK_COLUMN_VALUE_INT, &address, -1 );

    error = debugger_breakpoint_add_address(
      DEBUGGER_BREAKPOINT_TYPE_EXECUTE, memory_source_any, 0, address, 0,
      DEBUGGER_BREAKPOINT_LIFE_PERMANENT, NULL
    );
    if( error ) return;

  update_disassembly();
//    debugger_run();
  }
}

static void
breakpoints_activate( GtkTreeView *tree_view, GtkTreePath *path,
	        GtkTreeViewColumn *column GCC_UNUSED,
		gpointer user_data GCC_UNUSED )
{
  GtkTreeIter it;
  GtkTreeModel *model = gtk_tree_view_get_model( tree_view );

  if( model && gtk_tree_model_get_iter( model, &it, path ) ) {
    gchar *type, *address, *endptr;
    int base_num, offset;

    gtk_tree_model_get( model, &it, BREAKPOINTS_COLUMN_TYPE, &type, -1 );
    if ( type ) {
      if ( strcmp(type, debugger_breakpoint_type_text[ DEBUGGER_BREAKPOINT_TYPE_EXECUTE ] ) == 0 ||
          strcmp(type, debugger_breakpoint_type_text[ DEBUGGER_BREAKPOINT_TYPE_READ ] ) == 0 || 
          strcmp(type, debugger_breakpoint_type_text[ DEBUGGER_BREAKPOINT_TYPE_WRITE ] ) == 0) {
        gtk_tree_model_get( model, &it, BREAKPOINTS_COLUMN_VALUE, &address, -1 );
        if ( address ) {
          base_num = ( g_str_has_prefix( address, "0x" ) )? 16 : 10;
          offset = strtol( address, &endptr, base_num );
          g_free( address );

          ui_debugger_disassemble( offset );
          ui_debugger_update();
        }
      }
    }
    g_free( type );
  }
}

static void
create_events( GtkBox *parent, PangoFontDescription *font )
{
  static const gchar *const titles[] = { "Time", "Type" };
  size_t i;

  events_model =
    gtk_list_store_new( EVENTS_COLUMN_COUNT, G_TYPE_INT, G_TYPE_STRING );

  events = gtk_tree_view_new_with_model( GTK_TREE_MODEL( events_model ) );

  for( i = 0; i < EVENTS_COLUMN_COUNT; i++ ) {
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *column = gtk_tree_view_column_new_with_attributes( titles[i], renderer, "text", i, NULL );
    g_object_set( G_OBJECT( renderer ), "font-desc", font, "height", 18, NULL );
    gtk_tree_view_append_column( GTK_TREE_VIEW( events ), column );
  }

  gtk_box_pack_start( parent, events, TRUE, TRUE, 5 );

  g_signal_connect( G_OBJECT( events ), "row-activated", G_CALLBACK( events_activate ), NULL );
}

static void
events_activate( GtkTreeView *tree_view, GtkTreePath *path,
	         GtkTreeViewColumn *column GCC_UNUSED,
		 gpointer user_data GCC_UNUSED )
{
  GtkTreeIter it;
  GtkTreeModel *model = gtk_tree_view_get_model( tree_view );

  if( model && gtk_tree_model_get_iter( model, &it, path ) ) {
    libspectrum_dword event_tstates;
    int error;

    gtk_tree_model_get( model, &it, EVENTS_COLUMN_TIME, &event_tstates, -1 );

    error = debugger_breakpoint_add_time(
      DEBUGGER_BREAKPOINT_TYPE_TIME, event_tstates, 0,
      DEBUGGER_BREAKPOINT_LIFE_PERMANENT, NULL
    );
    if( error ) return;

 //    debugger_run();
  }
}

static int
create_command_entry( GtkBox *parent, GtkAccelGroup *accel_group )
{
  GtkWidget *hbox, *entry, *eval_button;

  /* An hbox to hold the command entry widget and the 'evaluate' button */
  hbox = gtk_box_new( GTK_ORIENTATION_HORIZONTAL, 5 );
  gtk_box_pack_start( parent, hbox, FALSE, FALSE, 0 );

  /* The command entry widget */
  entry = gtk_entry_new();
  g_signal_connect( G_OBJECT( entry ), "activate",
		    G_CALLBACK( evaluate_command ), NULL );
  gtk_box_pack_start( GTK_BOX( hbox ), entry, TRUE, TRUE, 0 );

  /* The 'command evaluate' button */
  eval_button = gtk_button_new_with_label( "Evaluate" );
  g_signal_connect_swapped( G_OBJECT( eval_button ), "clicked",
			    G_CALLBACK( evaluate_command ),
			    G_OBJECT( entry ) );
  gtk_box_pack_start( GTK_BOX( hbox ), eval_button, FALSE, FALSE, 0 );

  gtk_button_set_always_show_image( eval_button, TRUE );
  gtk_button_set_image ( eval_button, gtk_image_new_from_stock( "gtk-execute", 1 ) );

  /* Return is equivalent to clicking on 'evaluate' */
  // conflicts with "Go to offset"
#if 0  
  gtk_widget_add_accelerator( eval_button, "clicked", accel_group,
			      GDK_KEY_Return, 0, 0 );
#endif
  return 0;
}

static int
create_buttons( GtkDialog *parent, GtkAccelGroup *accel_group )
{
  static const gtkstock_button
    step  = { "Single step", G_CALLBACK( gtkui_debugger_done_step ), NULL, NULL, 0, 0, 0, 0, GTK_RESPONSE_NONE },
    cont  = { "Continue", G_CALLBACK( gtkui_debugger_done_continue ), NULL, NULL, 0, 0, 0, 0, GTK_RESPONSE_NONE },
    brk   = { "Break", G_CALLBACK( gtkui_debugger_break ), NULL, NULL, 0, 0, 0, 0, GTK_RESPONSE_NONE };

  /* Create the action buttons for the dialog box */
  step_button = gtkstock_create_button( GTK_WIDGET( parent ), accel_group, &step );
  continue_button = gtkstock_create_button( GTK_WIDGET( parent ), accel_group,
					    &cont );
  break_button = gtkstock_create_button( GTK_WIDGET( parent ), accel_group,
					 &brk );
  gtkstock_create_close( GTK_WIDGET( parent ), accel_group,
			 G_CALLBACK( gtkui_debugger_done_close ), TRUE );

  gtk_button_set_always_show_image( step_button, TRUE );
  gtk_button_set_always_show_image( continue_button, TRUE );
  gtk_button_set_always_show_image( break_button, TRUE );

  gtk_button_set_image ( step_button, gtk_image_new_from_stock( "gtk-media-next", 1 ) );
  gtk_button_set_image ( continue_button, gtk_image_new_from_stock( "gtk-media-play", 1 ) );
  gtk_button_set_image ( break_button, gtk_image_new_from_stock( "gtk-media-pause", 1 ) );

  return 0;
}

static int
activate_debugger( void )
{
  debugger_active = 1;

  ui_debugger_disassemble( PC );
  ui_debugger_update();

  gtk_main();
  return 0;
}

/* Update the debugger's display */
int
ui_debugger_update( void )
{
  size_t i;
  char buffer[1024], format_string[1024];
  gchar buffer1[80], buffer2[80];
  libspectrum_word address;
  int capabilities; size_t length;

  const char *register_name[] = { 
          "PC", "SP",
				  "AF", "AF'",
				  "BC", "BC'",
				  "DE", "DE'",
				  "HL", "HL'",
				  "IX", "IY",
                                };

  libspectrum_word *value_ptr[] = { 
            &PC, &SP,  &AF, &AF_,
				    &BC, &BC_, &DE, &DE_,
				    &HL, &HL_, &IX, &IY,
				  };

  if( !dialog_created ) return 0;

  for( i = 0; i < 12; i++ ) {
    snprintf( buffer, 5, "%3s ", register_name[i] );
    snprintf( &buffer[4], 76, format_16_bit(), *value_ptr[i] );
    gtk_label_set_text( GTK_LABEL( registers[i] ), buffer );
  }

  strcpy( buffer, "  I   " ); snprintf( &buffer[6], 76, format_8_bit(), I );
  gtk_label_set_text( GTK_LABEL( registers[12] ), buffer );
  strcpy( buffer, "  R   " );
  snprintf( &buffer[6], 80, format_8_bit(), ( R & 0x7f ) | ( R7 & 0x80 ) );
  gtk_label_set_text( GTK_LABEL( registers[13] ), buffer );

  snprintf( buffer, 80, "T-states %5d\nHalted %d", tstates, z80.halted );
  gtk_label_set_text( GTK_LABEL( registers[14] ), buffer );
  snprintf( buffer, 80, "  IM %d\nIFF1 %d\nIFF2 %d", IM, IFF1, IFF2 );
  gtk_label_set_text( GTK_LABEL( registers[15] ), buffer );

  strcpy( buffer, "SZ5H3PNC\n" );
  for( i = 0; i < 8; i++ ) buffer[i+9] = ( F & ( 0x80 >> i ) ) ? '1' : '0';
  buffer[17] = '\0';
  gtk_label_set_text( GTK_LABEL( registers[16] ), buffer );

  capabilities = libspectrum_machine_capabilities( machine_current->machine );

  sprintf( format_string, "   ULA %s", format_8_bit() );
  snprintf( buffer, 1024, format_string, ula_last_byte() );

  if( capabilities & LIBSPECTRUM_MACHINE_CAPABILITY_AY ) {
    sprintf( format_string, "\n    AY %s", format_8_bit() );
    length = strlen( buffer );
    snprintf( &buffer[length], 1024-length, format_string,
	      machine_current->ay.current_register );
  }

  if( capabilities & LIBSPECTRUM_MACHINE_CAPABILITY_128_MEMORY ) {
    sprintf( format_string, "\n128Mem %s", format_8_bit() );
    length = strlen( buffer );
    snprintf( &buffer[length], 1024-length, format_string,
	      machine_current->ram.last_byte );
  }

  if( capabilities & LIBSPECTRUM_MACHINE_CAPABILITY_PLUS3_MEMORY ) {
    sprintf( format_string, "\n+3 Mem %s", format_8_bit() );
    length = strlen( buffer );
    snprintf( &buffer[length], 1024-length, format_string,
	      machine_current->ram.last_byte2 );
  }

  if( capabilities & LIBSPECTRUM_MACHINE_CAPABILITY_TIMEX_VIDEO  ||
      capabilities & LIBSPECTRUM_MACHINE_CAPABILITY_TIMEX_MEMORY ||
      capabilities & LIBSPECTRUM_MACHINE_CAPABILITY_SE_MEMORY       ) {
    sprintf( format_string, "\nTmxDec %s", format_8_bit() );
    length = strlen( buffer );
    snprintf( &buffer[length], 1024-length, format_string,
	      scld_last_dec.byte );
  }

  if( capabilities & LIBSPECTRUM_MACHINE_CAPABILITY_TIMEX_MEMORY ||
      capabilities & LIBSPECTRUM_MACHINE_CAPABILITY_SE_MEMORY       ) {
    sprintf( format_string, "\nTmxHsr %s", format_8_bit() );
    length = strlen( buffer );
    snprintf( &buffer[length], 1024-length, format_string, scld_last_hsr );
  }

  if( settings_current.zxcf_active ) {
    sprintf( format_string, "\n  ZXCF %s", format_8_bit() );
    length = strlen( buffer );
    snprintf( &buffer[length], 1024-length, format_string,
	      zxcf_last_memctl() );
  }

  gtk_label_set_text( GTK_LABEL( registers[17] ), buffer );

  update_memory_map();
  update_breakpoints();
  update_disassembly();

  /* And the stack display */
  gtk_list_store_clear( stack_model );

  for( i = 0, address = SP + 38; i < 20; i++, address -= 2 ) {

    GtkTreeIter it;
    
    libspectrum_word contents = readbyte_internal( address ) +
				0x100 * readbyte_internal( address + 1 );

    snprintf( buffer1, sizeof( buffer1 ), format_16_bit(), address );
    snprintf( buffer2, sizeof( buffer2 ), format_16_bit(), contents );

    gtk_list_store_append( stack_model, &it );
    gtk_list_store_set( stack_model, &it, STACK_COLUMN_ADDRESS, buffer1, STACK_COLUMN_VALUE_TEXT, buffer2, STACK_COLUMN_VALUE_INT, (gint)contents, -1 );
  }

  /* And the events display */
  update_events();

  return 0;
}

static void
update_memory_map( void )
{
  int source, page_num, writable, contended;
  libspectrum_word offset;
  size_t i, j, block, row;
  PangoFontDescription *font;

  for( i = 0; i < MEMORY_PAGES_IN_64K; i++ ) {
    if( map_label[i][0] ) {
      for( j = 0; j < 4; j++ ) {
        gtk_container_remove( GTK_CONTAINER( memory_map_table ), map_label[i][j] );
        map_label[i][j] = NULL;
      }
    }
  }

  source = page_num = writable = contended = -1;
  offset = 0;
  row = 0;

  font = monospaced_font(); if( font == NULL ) return;

  for( block = 0; block < MEMORY_PAGES_IN_64K; block++ ) {
    memory_page *page = &memory_map_read[block];

    if( page->source != source ||
      page->page_num != page_num ||
      page->offset != offset ||
      page->writable != writable ||
      page->contended != contended ) {

      char buffer[40];
      GtkWidget **row_labels = map_label[row];

      snprintf( buffer, 40, format_16_bit(),
                (unsigned)block * MEMORY_PAGE_SIZE );
      row_labels[0] = gtk_label_new( buffer );

      snprintf( buffer, 40, "%s %d",
        memory_source_description( page->source ), page->page_num );
      row_labels[1] = gtk_label_new( buffer );

      row_labels[2] = gtk_label_new( page->writable ? "Y" : "N" );
      row_labels[3] = gtk_label_new( page->contended ? "Y" : "N" );

      for( i = 0; i < 4; i++ ) {
        PangoAttrList *list;
        PangoAttribute *attr;

        list = pango_attr_list_new();
        attr = pango_attr_font_desc_new( font );
        pango_attr_list_insert( list, attr );
        gtk_label_set_attributes( GTK_LABEL( row_labels[i] ), list );
        pango_attr_list_unref( list );

#if GTK_CHECK_VERSION( 3, 0, 0 )
        gtk_grid_attach( GTK_GRID( memory_map_table ), row_labels[i],
                         i, row + 1, 1, 1 );
#else
        gtk_table_attach( GTK_TABLE( memory_map_table ), row_labels[i],
                          i, i + 1, row + 1, row + 2, 0, 0, 2, 2 );
#endif

      }

      row++;

      source = page->source;
      page_num = page->page_num;
      writable = page->writable;
      contended = page->contended;
      offset = page->offset;
    }

    /* We expect the next page to have an increased offset */
    offset += MEMORY_PAGE_SIZE;
  }

  gtkui_free_font( font );

  gtk_widget_show_all( GTK_WIDGET( memory_map_table ) );
}

static void
update_breakpoints( void )
{
  GSList *ptr;

  gtk_list_store_clear( breakpoints_model );

  for( ptr = debugger_breakpoints; ptr; ptr = ptr->next ) {

    debugger_breakpoint *bp = ptr->data;
    GtkTreeIter it;
    gchar buffer[40], format_string[40];

    switch( bp->type ) {

    case DEBUGGER_BREAKPOINT_TYPE_EXECUTE:
    case DEBUGGER_BREAKPOINT_TYPE_READ:
    case DEBUGGER_BREAKPOINT_TYPE_WRITE:
      if( bp->value.address.source == memory_source_any ) {
	snprintf( buffer, sizeof( buffer ), format_16_bit(),
		  bp->value.address.offset );
      } else {
	snprintf( format_string, sizeof( format_string ), "%%s:%s:%s",
		  format_16_bit(), format_16_bit() );
	snprintf( buffer, sizeof( buffer ), format_string,
                  memory_source_description( bp->value.address.source ),
                  bp->value.address.page, bp->value.address.offset );
      }
      break;

    case DEBUGGER_BREAKPOINT_TYPE_PORT_READ:
    case DEBUGGER_BREAKPOINT_TYPE_PORT_WRITE:
      snprintf( format_string, sizeof( format_string ), "%s:%s",
		format_16_bit(), format_16_bit() );
      snprintf( buffer, sizeof( buffer ), format_string, bp->value.port.mask,
		bp->value.port.port );
      break;

    case DEBUGGER_BREAKPOINT_TYPE_TIME:
      snprintf( buffer, sizeof( buffer ), "%5d", bp->value.time.tstates );
      break;

    case DEBUGGER_BREAKPOINT_TYPE_EVENT:
      snprintf( buffer, sizeof( buffer ), "%s:%s", bp->value.event.type,
		bp->value.event.detail );
      break;

    }

    gtk_list_store_append( breakpoints_model, &it );
    gtk_list_store_set(
      breakpoints_model, &it,
      BREAKPOINTS_COLUMN_ID, bp->id,
      BREAKPOINTS_COLUMN_TYPE, debugger_breakpoint_type_text[ bp->type ],
      BREAKPOINTS_COLUMN_VALUE, buffer,
      BREAKPOINTS_COLUMN_IGNORE, bp->ignore,
      BREAKPOINTS_COLUMN_LIFE, debugger_breakpoint_life_text[ bp->life ],
      -1
    );

    if( bp->condition ) {
      gchar buffer2[80];
      debugger_expression_deparse( buffer2, sizeof( buffer2 ), bp->condition );
      gtk_list_store_set( breakpoints_model, &it, BREAKPOINTS_COLUMN_CONDITION, buffer2, -1 );
    }

  }
}

static void
update_disassembly( void )
{
  size_t i; libspectrum_word address;
  GtkTreeIter it;

  gtk_list_store_clear( disassembly_model );

  for( i = 0, address = disassembly_top; i < 20; i++ ) {
    size_t l, length;
    char buffer[DISASSEMBLY_COLUMN_COUNT][40];
    GSList *ptr;

    bzero( buffer[DISASSEMBLY_COLUMN_PC], sizeof( buffer[DISASSEMBLY_COLUMN_PC] ));
    bzero( buffer[DISASSEMBLY_COLUMN_BREAKPOINT], sizeof( buffer[DISASSEMBLY_COLUMN_BREAKPOINT] ));

    if ( address == PC )
    {
      snprintf( buffer[DISASSEMBLY_COLUMN_PC], sizeof( buffer[DISASSEMBLY_COLUMN_PC] ), "->");
    }

    for( ptr = debugger_breakpoints; ptr; ptr = ptr->next ) {

      debugger_breakpoint *bp = ptr->data;

      switch( bp->type ) {

      case DEBUGGER_BREAKPOINT_TYPE_EXECUTE:
      case DEBUGGER_BREAKPOINT_TYPE_READ:
      case DEBUGGER_BREAKPOINT_TYPE_WRITE:
        if ( bp->value.address.offset == address ) {
          snprintf( buffer[DISASSEMBLY_COLUMN_BREAKPOINT], sizeof( buffer[DISASSEMBLY_COLUMN_BREAKPOINT] ), "%lu", bp->id);
        }
        break;
      default:
        break;
      }
    }

    snprintf( buffer[DISASSEMBLY_COLUMN_ADDRESS], sizeof( buffer[DISASSEMBLY_COLUMN_ADDRESS] ), format_16_bit(), address );
    debugger_disassemble( buffer[DISASSEMBLY_COLUMN_INSTRUCTION], sizeof( buffer[DISASSEMBLY_COLUMN_INSTRUCTION] ), &length, address );

    /* pad to 16 characters (long instruction) to avoid varying width */
    l = strlen( buffer[DISASSEMBLY_COLUMN_INSTRUCTION] );
    while( l < 16 ) buffer[DISASSEMBLY_COLUMN_INSTRUCTION][l++] = ' ';
    buffer[DISASSEMBLY_COLUMN_INSTRUCTION][l] = 0;

    gtk_list_store_append( disassembly_model, &it );
    gtk_list_store_set( disassembly_model, &it,
      DISASSEMBLY_COLUMN_PC, buffer[DISASSEMBLY_COLUMN_PC], DISASSEMBLY_COLUMN_BREAKPOINT, buffer[DISASSEMBLY_COLUMN_BREAKPOINT],
      DISASSEMBLY_COLUMN_ADDRESS, buffer[DISASSEMBLY_COLUMN_ADDRESS], DISASSEMBLY_COLUMN_INSTRUCTION, buffer[DISASSEMBLY_COLUMN_INSTRUCTION], 
      -1 );

    address += length;
  }

  disassembly_bottom = address;
}

static void
update_events( void )
{
  gtk_list_store_clear( events_model );
  event_foreach( add_event, NULL );
}

static void
add_event( gpointer data, gpointer user_data GCC_UNUSED )
{
  event_t *ptr = data;
  GtkTreeIter it;

  if( ptr->type != event_type_null ) {
    gtk_list_store_append( events_model, &it );
    gtk_list_store_set( events_model, &it, EVENTS_COLUMN_TIME, ptr->tstates, EVENTS_COLUMN_TYPE, event_name( ptr->type ), -1 );
  }
}

static int
deactivate_debugger( void )
{
  gtk_main_quit();
  debugger_active = 0;
  fuse_emulation_unpause();
  return 0;
}

/* Set the disassembly to start at 'address' */
int
ui_debugger_disassemble( libspectrum_word address )
{
  disassembly_top = address;

  /* Block further events while adjusting scrollbar. */
  g_signal_handlers_block_by_func( G_OBJECT( disassembly_scrollbar_adjustment ),
                                   G_CALLBACK( move_disassembly ), NULL );

  /* Note: GtkAdjustment can not cope with "upper bound - page_size" value and
     higher */
  gtk_adjustment_set_value( disassembly_scrollbar_adjustment, address );

  /* Enable events for scrollbar */
  g_signal_handlers_unblock_by_func( G_OBJECT(disassembly_scrollbar_adjustment),
                                     G_CALLBACK( move_disassembly ),  NULL );

  /* And update the disassembly if the debugger is active */
  if( debugger_active ) {
    update_disassembly();
  }

  return 0;
}

/* Called when the disassembly scrollbar is moved */
static void
move_disassembly( GtkAdjustment *adjustment, gpointer user_data GCC_UNUSED )
{
  gdouble value;
  int cursor_row;
  libspectrum_word addresss;

  /* FIXME: Movements are imprecise while dragging the scroll bar */
  value = gtk_adjustment_get_value( adjustment );

  cursor_row = gtkui_list_get_cursor( GTK_TREE_VIEW( disassembly ) );

  /* disassembly_top < value <= disassembly_top + 1 => 'down' button pressed
     Move the disassembly on by one instruction */
  if( value > disassembly_top && value - disassembly_top <= 1 ) {

    addresss = debugger_search_instruction( disassembly_top, 1 );
    ui_debugger_disassemble( addresss );

  /* disassembly_top - 1 <= value < disassembly_top => 'up' button pressed
     
     The desired state after this is for the current top instruction
     to be the second instruction shown in the disassembly.

     Unfortunately, it's not trivial to determine where disassembly
     should now start, as we have variable length instructions of
     unbounded length (multiple DD and FD prefixes on one instruction
     are possible).

     In general, we want the _longest_ opcode which produces the
     current top in second place (consider something like LD A,nn:
     we're not interested if nn happens to represent a one-byte
     opcode), so look back a reasonable length (say, 8 bytes) and see
     what we find.

     In some cases (eg if we're currently pointing to a data byte of a
     multi-byte opcode), it will be impossible to get the current top
     second. In this case, just move back a byte.

  */
  } else if( value < disassembly_top && disassembly_top - value <= 1 ) {

    addresss = debugger_search_instruction( disassembly_top, -1 );
    ui_debugger_disassemble( addresss );

  /* Anything else, just set disassembly_top to that value */
  } else if( value != disassembly_top ) {

    ui_debugger_disassemble( value );

  }

  /* Mark selected row */
  gtkui_list_set_cursor( GTK_TREE_VIEW( disassembly ), cursor_row );
}

static gboolean
disassembly_key_press( GtkTreeView *list, GdkEventKey *event,
                       gpointer user_data )
{
  GtkAdjustment *adjustment = user_data;
  gdouble page_size, page_increment;
  int cursor_row;
  libspectrum_word initial_top, addresss;

  initial_top = disassembly_top;
  page_size = gtk_adjustment_get_page_size( adjustment );
  page_increment = gtk_adjustment_get_page_increment( adjustment );

  /* Get selected row */
  cursor_row = gtkui_list_get_cursor( list );

  switch( event->keyval ) {

  case GDK_KEY_Down:
    if( cursor_row == page_size - 1 ) {
      addresss = debugger_search_instruction( disassembly_top, 1 );
      ui_debugger_disassemble( addresss );
    }
    break;

  case GDK_KEY_Up:
    if( cursor_row == 0 ) {
      addresss = debugger_search_instruction( disassembly_top, -1 );
      ui_debugger_disassemble( addresss );
    }
    break;

  case GDK_KEY_Page_Down:
    ui_debugger_disassemble( disassembly_bottom );
    break;

  case GDK_KEY_Page_Up:
    addresss = debugger_search_instruction( disassembly_top, -page_increment );
    ui_debugger_disassemble( addresss );
    break;

  case GDK_KEY_Home:
    cursor_row = 0;
    ui_debugger_disassemble( 0x0000 );
    break;

  case GDK_KEY_End:
    cursor_row = page_size - 1;
    addresss = debugger_search_instruction( 0x0000, -page_size );
    ui_debugger_disassemble( addresss );
    break;

  default:
    return FALSE;
  }

  if( initial_top != disassembly_top ) {
    update_disassembly();

    /* Mark selected row */
    gtkui_list_set_cursor( list, cursor_row );
    return TRUE;
  }

  return FALSE;
}

/* Called when the wheel mouse is moved on the list (not on the scrollbar) */
static gboolean
disassembly_wheel_scroll( GtkTreeView *list GCC_UNUSED, GdkEvent *event,
                          gpointer user_data )
{
  libspectrum_word initial_top, addresss;
  int cursor_row;

  initial_top = disassembly_top;

  /* Get selected row */
  cursor_row = gtkui_list_get_cursor( list );

  switch( event->scroll.direction ) {
  case GDK_SCROLL_UP:
    addresss = debugger_search_instruction( disassembly_top, -1 );
    ui_debugger_disassemble( addresss );
    break;

  case GDK_SCROLL_DOWN:
    addresss = debugger_search_instruction( disassembly_top, 1 );
    ui_debugger_disassemble( addresss );
    break;

#if GTK_CHECK_VERSION( 3, 4, 0 )

  case GDK_SCROLL_SMOOTH:
    {
      GtkAdjustment *adjustment = user_data;
      static gdouble total_dy = 0;
      gdouble dx, dy, page_size;
      int delta;

      if( gdk_event_get_scroll_deltas( event, &dx, &dy ) ) {
        /* Calculate number of instructions to jump */
        total_dy += dy;
        page_size = gtk_adjustment_get_page_size( adjustment );
        delta = total_dy * pow( page_size, 2.0 / 3.0 );

        /* Is movement significative? */
        if( delta ) {
          addresss = debugger_search_instruction( disassembly_top, delta );
          ui_debugger_disassemble( addresss );
          total_dy = 0;
        }
      }
      break;
    }

#endif

  default:
    return FALSE;
  }

  if( initial_top != disassembly_top ) {
    /* Mark selected row */
    gtkui_list_set_cursor( list, cursor_row );
    return TRUE;
  }

  return FALSE;
}

#if GTK_CHECK_VERSION( 3, 0, 0 )
static void
debugger_goto_offset( GtkWidget *widget, gpointer user_data GCC_UNUSED )
{
  long offset;
  const gchar *entry;
  char *endptr;
  int base_num;

  if( gtk_entry_get_text_length( GTK_ENTRY( widget ) ) == 0 ) {
    ui_debugger_disassemble( PC );  
    return;
  }

  /* Parse address */
  entry = gtk_entry_get_text( GTK_ENTRY( widget ) );
  errno = 0;
  base_num = ( g_str_has_prefix( entry, "0x" ) )? 16 : 10;
  offset = strtol( entry, &endptr, base_num );

  /* Validate address */
  if( errno || offset < 0 || offset > 65535 || endptr == entry ||
      *endptr != '\0' ) {
    return;
  }

  ui_debugger_disassemble( offset );  
}
#endif

/* Evaluate the command currently in the entry box */
static void
evaluate_command( GtkWidget *widget, gpointer user_data GCC_UNUSED )
{
  debugger_command_evaluate( gtk_entry_get_text( GTK_ENTRY( widget ) ) );
}

static void
gtkui_debugger_done_step( GtkWidget *widget GCC_UNUSED,
			  gpointer user_data GCC_UNUSED )
{
  debugger_step();
}

static void
gtkui_debugger_done_continue( GtkWidget *widget GCC_UNUSED,
			      gpointer user_data GCC_UNUSED )
{
  debugger_run();
}

static void
gtkui_debugger_break( GtkWidget *widget GCC_UNUSED,
		      gpointer user_data GCC_UNUSED )
{
  debugger_mode = DEBUGGER_MODE_HALTED;
  gtk_widget_set_sensitive( continue_button, 1 );
  gtk_widget_set_sensitive( break_button, 0 );
}

static gboolean
delete_dialog( GtkWidget *widget, GdkEvent *event GCC_UNUSED,
	       gpointer user_data )
{
  gtkui_debugger_done_close( widget, user_data );
  return TRUE;
}

static void
gtkui_debugger_done_close( GtkWidget *widget, gpointer user_data GCC_UNUSED )
{
  gtk_widget_hide( widget );
  gtkui_debugger_done_continue( NULL, NULL );
}
