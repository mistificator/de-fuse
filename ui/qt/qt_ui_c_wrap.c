#include "config.h"

#include "keyboard.h"
#include "ui/ui.h"

#include "../uijoystick.c"

#include "fuse.h"

keysyms_map_t keysyms_map[] = {
  { 0, 0 } /* End marker */
};

static void
register_scalers( int force_scaler )
{
  scaler_type scaler;
  float drawing_area_scale, scaling_factor;

  scaler_register_clear();

  if( machine_current->timex ) {
    scaler_register( SCALER_HALF );
    scaler_register( SCALER_HALFSKIP );
    scaler_register( SCALER_TIMEXTV );
    scaler_register( SCALER_TIMEX1_5X );
    scaler_register( SCALER_TIMEX2X );
  } else {
    scaler_register( SCALER_DOUBLESIZE );
    scaler_register( SCALER_TRIPLESIZE );
    scaler_register( SCALER_QUADSIZE );
    scaler_register( SCALER_TV2X );
    scaler_register( SCALER_TV3X );
    scaler_register( SCALER_TV4X );
    scaler_register( SCALER_PALTV2X );
    scaler_register( SCALER_PALTV3X );
    scaler_register( SCALER_PALTV4X );
    scaler_register( SCALER_HQ2X );
    scaler_register( SCALER_HQ3X );
    scaler_register( SCALER_HQ4X );
    scaler_register( SCALER_ADVMAME2X );
    scaler_register( SCALER_ADVMAME3X );
    scaler_register( SCALER_2XSAI );
    scaler_register( SCALER_SUPER2XSAI );
    scaler_register( SCALER_SUPEREAGLE );
    scaler_register( SCALER_DOTMATRIX );
  }
  scaler_register( SCALER_NORMAL );
  scaler_register( SCALER_PALTV );

  scaler =
    scaler_is_supported( current_scaler ) ? current_scaler : SCALER_NORMAL;

  int current_size = 1, image_scale = 1; // temporary
  drawing_area_scale = (float)current_size / image_scale;
  scaling_factor = scaler_get_scaling_factor( current_scaler );

  /* Override scaler if the image doesn't fit well in the drawing area */
  if( force_scaler && drawing_area_scale != scaling_factor ) {

    switch( current_size ) {
    case 1: scaler = machine_current->timex ? SCALER_HALF : SCALER_NORMAL;
      break;
    case 2: scaler = machine_current->timex ? SCALER_NORMAL : SCALER_DOUBLESIZE;
      break;
    case 3: scaler = machine_current->timex ? SCALER_TIMEX1_5X :
                                              SCALER_TRIPLESIZE;
      break;
    case 4: scaler = machine_current->timex ? SCALER_TIMEX2X :
                                              SCALER_QUADSIZE;
      break;
    }
  }

  scaler_select_scaler( scaler );
}

scaler_type
menu_get_scaler( scaler_available_fn selector )
{
  /* No scaler selected */
//  return SCALER_NUM;
    DeFuseWindow::instance()->selectScaler( [=](int i)->int { return selector(i); } );
    return current_scaler;
}

int
menu_select_roms_with_title( const char *title, size_t start, size_t count,
    int is_peripheral )
{
  /* No error */
  return 0;
}

void
ui_breakpoints_updated( void )
{
  /* Do nothing */
}

ui_confirm_save_t
ui_confirm_save_specific( const char *message )
{
  return UI_CONFIRM_SAVE_DONTSAVE;
}

ui_confirm_joystick_t
ui_confirm_joystick( libspectrum_joystick libspectrum_type, int inputs )
{
  return UI_CONFIRM_JOYSTICK_NONE;
}

int
ui_debugger_activate( void )
{
  /* No error */
  return 0;
}

int
ui_debugger_deactivate( int interruptable )
{
  /* No error */
  return 0;
}

int
ui_debugger_disassemble( libspectrum_word addr )
{
  /* No error */
  return 0;
}

int
ui_debugger_update( void )
{
  /* No error */
  return 0;
}

int
ui_end( void )
{
  return 0;
}

int
ui_error_specific( ui_error_level severity, const char *message )
{
  /* No error */
  return 0;
}

int
ui_event( void )
{
  qApp->processEvents();
  return 0;
}

char*
ui_get_open_filename( const char *title )
{
  /* No filename */
  return NULL;
}

int
ui_get_rollback_point( GSList *points )
{
  /* No rollback point */
  return -1;
}

char*
ui_get_save_filename( const char *title )
{
  /* No filename */
  return NULL;
}

int
ui_init( int *argc, char ***argv )
{
    if (!argc || !argv)
    {
        return -1;
    }
    new QApplication(* argc, * argv);
    return 0;
}

int
ui_menu_item_set_active( const char *path, int active )
{
  /* No error */
  return 0;
}

int
ui_mouse_grab( int startup )
{
  /* Successful grab */
  return 1;
}

int
ui_mouse_release( int suspend )
{
  /* No error */
  return 0;
}

void
ui_pokemem_selector( const char *filename )
{
  /* Do nothing */
}

int
ui_query( const char *message )
{
  /* Query confirmed */
  return 1;
}

int
ui_statusbar_update( ui_statusbar_item item, ui_statusbar_state state )
{
  /* No error */
  return 0;
}

int
ui_statusbar_update_speed( float speed )
{
  /* No error */
  return 0;
}

int
ui_tape_browser_update( ui_tape_browser_update_type change,
    libspectrum_tape_block *block )
{
  /* No error */
  return 0;
}

int
ui_widgets_reset( void )
{
  /* No error */
  return 0;
}

void
uidisplay_area( int x, int y, int w, int h )
{
  /* Do nothing */
}

int
uidisplay_end( void )
{
  /* No error */
  return 0;
}

void
uidisplay_frame_end( void )
{
    qApp->processEvents();
}

int
uidisplay_hotswap_gfx_mode( void )
{
  /* No error */
  return 0;
}

int
uidisplay_init( int width, int height )
{
    DeFuseWindow::instance()->show();
    register_scalers(0);
    return 0;
}

void
uidisplay_plot16( int x, int y, libspectrum_word data,
    libspectrum_byte ink, libspectrum_byte paper )
{
  /* Do nothing */
}

void
uidisplay_plot8( int x, int y, libspectrum_byte data,
    libspectrum_byte ink, libspectrum_byte paper )
{
  /* Do nothing */
}

void
uidisplay_putpixel( int x, int y, int colour )
{
  /* Do nothing */
}

void
menu_file_loadbinarydata( int action )
{

}

void
menu_file_savebinarydata( int action )
{

}

void
menu_file_exit( int )
{
    if ( fuse_exiting )
    {
        return;
    }
    if( DeFuseWindow::instance()->ask( "Exit De-Fuse?" ) ) 
    {
        if( menu_check_media_changed() ) 
        {
            return;
        }
        fuse_exiting = 1;
    }
}

void
menu_options_joysticks_select( int action )
{

}

void
menu_machine_pause( int action )
{

}

void
menu_machine_reset( int action )
{

}

void
menu_machine_select( int action )
{
    /* Stop emulation */
    fuse_emulation_pause();

    DeFuseWindow::instance()->selectMachine();

  /* And then carry on with emulation again */
    fuse_emulation_unpause();
}

void
menu_debug_debugger( int action )
{

}

void
menu_debug_memorybrowser( int action )
{

}

void
menu_debug_pokefinder( int action )
{

}

void
menu_debug_pokememory( int action )
{

}

void
menu_media_tape_browse( int action )
{

}

void
menu_help_keyboard( int action )
{
    DeFuseWindow::instance()->showKeyboard();
}

void
menu_help_about( int action )
{
    DeFuseWindow::instance()->about();
}
