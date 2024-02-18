#include "config.h"

#include "keyboard.h"
#include "ui/ui.h"
#include "../uijoystick.c"
#include "fuse.h"
#include "timer/timer.h"
#include "rzx.h"
#include "sound.h"
#include "settings.h"

/* True if we were paused via the Machine/Pause menu item */
static int paused = 0;

/* A copy of every pixel on the screen, replaceable by plotting directly into
   rgb_image below */
libspectrum_word
  qtdisplay_image[ 2 * DISPLAY_SCREEN_HEIGHT ][ DISPLAY_SCREEN_WIDTH ];

const int rgb_pitch = DeFuseWindow::Screen_t::Pitch;

/* The color palette */
static const unsigned char rgb_colors[16][3] = {

  {   0,   0,   0 },
  {   0,   0, 192 },
  { 192,   0,   0 },
  { 192,   0, 192 },
  {   0, 192,   0 },
  {   0, 192, 192 },
  { 192, 192,   0 },
  { 192, 192, 192 },
  {   0,   0,   0 },
  {   0,   0, 255 },
  { 255,   0,   0 },
  { 255,   0, 255 },
  {   0, 255,   0 },
  {   0, 255, 255 },
  { 255, 255,   0 },
  { 255, 255, 255 },

};

/* And the colors (and black and white 'colors') in 32-bit format */
libspectrum_dword qtdisplay_colors[16], qtdisplay_gigascreen_halfcolors[16];
static libspectrum_dword bw_colors[16];

static int
init_colors()
{
  size_t i;

  for( i = 0; i < 16; i++ ) {


    libspectrum_dword red, green, blue, grey;

    red   = rgb_colors[i][0];
    green = rgb_colors[i][1];
    blue  = rgb_colors[i][2];

    /* Addition of 0.5 is to avoid rounding errors */
    grey = ( 0.299 * red + 0.587 * green + 0.114 * blue ) + 0.5;

    qtdisplay_colors[i] =  red << 16 | green << 8 | blue;
    qtdisplay_gigascreen_halfcolors[i] = (red >> 1) << 16 | (green >> 1) << 8 | (blue >> 1);
    bw_colors[i] = grey << 16 |  grey << 8 | grey;
  }

  return 0;
}

static void
register_scalers( int force_scaler )
{
  scaler_type scaler;
  float drawing_area_scale, scaling_factor;

  scaler_register_clear();

  if( machine_current->timex ) {
  } else {
    scaler_register( SCALER_DOUBLESIZE );
    scaler_register( SCALER_TRIPLESIZE );
    scaler_register( SCALER_QUADSIZE );
  }
  scaler_register( SCALER_NORMAL );

  scaler =
    scaler_is_supported( current_scaler ) ? current_scaler : SCALER_NORMAL;

  int current_size = 1, image_scale = 1; // temporary
  drawing_area_scale = (float)current_size / image_scale;
  scaling_factor = scaler_get_scaling_factor( current_scaler );

  scaler_select_scaler( scaler );
}

scaler_type
menu_get_scaler( scaler_available_fn selector )
{
    DeFuseWindow::instance()->selectScaler( [=](int i)->int { return selector(i); } );
    DeFuseWindow::instance()->needToRepaint();
    return current_scaler;
}

int
menu_select_roms_with_title( const char *title, size_t start, size_t count,
    int is_peripheral )
{
    /* Firstly, stop emulation */
    fuse_emulation_pause();

    DeFuseWindow::instance()->selectRom(title, start, count, is_peripheral);

    /* And then carry on with emulation again */
    fuse_emulation_unpause();
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
  /* If we don't have a UI yet, we can't output widgets */
  if( !display_ui_initialised ) return 0;

  /* Set the appropriate title */
  switch( severity ) {
    case UI_ERROR_INFO:	 QMessageBox::information(DeFuseWindow::instance(), "De-Fuse - Info", message); break;
    case UI_ERROR_WARNING: QMessageBox::warning(DeFuseWindow::instance(), "De-Fuse - Warning", message); break;
    case UI_ERROR_ERROR:	 QMessageBox::critical(DeFuseWindow::instance(), "De-Fuse - Error", message); break;
    default:		 QMessageBox::critical(DeFuseWindow::instance(), "De-Fuse - (Unknown Error Level)", message); break;
  }
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
    QString _filename = QFileDialog::getOpenFileName(DeFuseWindow::instance(), title);
    if (_filename.isEmpty())
    {
        return nullptr;
    }
    char * filename = libspectrum_malloc(_filename.length() + 1);
    ::memset(filename, 0, _filename.length() + 1);
    ::strncpy(filename, _filename.toLocal8Bit().constData(), _filename.length());
    return filename;
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
    QString _filename = QFileDialog::getSaveFileName(DeFuseWindow::instance(), title);
    if (_filename.isEmpty())
    {
        return nullptr;
    }
    char * filename = libspectrum_malloc(_filename.length() + 1);
    ::memset(filename, 0, _filename.length() + 1);
    ::strncpy(filename, _filename.toLocal8Bit().constData(), _filename.length());
    return filename;
}

int
ui_init( int *argc, char ***argv )
{
    if (!argc || !argv)
    {
        return -1;
    }
    QApplication * app = new QApplication(* argc, * argv);
    app->setWindowIcon(QIcon(":/fuse.png"));
    DeFuseWindow::instance()->show();
    return 0;
}

int
ui_menu_item_set_active( const char *path, int active )
{
    DeFuseWindow::instance()->setMenuActive(path, active);
    return 0;
}

int
ui_mouse_grab( int startup )
{
    DeFuseWindow::instance()->grabMouse();
    ui_statusbar_update( UI_STATUSBAR_ITEM_MOUSE, UI_STATUSBAR_STATE_ACTIVE );
    return 0;
}

int
ui_mouse_release( int suspend )
{
    DeFuseWindow::instance()->releaseMouse();
    ui_statusbar_update( UI_STATUSBAR_ITEM_MOUSE, UI_STATUSBAR_STATE_INACTIVE );
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
    return DeFuseWindow::instance()->ask( message ) != QDialog::Accepted;
}

int
ui_statusbar_update( ui_statusbar_item item, ui_statusbar_state state )
{
  return DeFuseWindow::instance()->setStatusBar( item, state );
}

int
ui_statusbar_update_speed( float speed )
{
  DeFuseWindow::instance()->setSpeed(speed);
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
  DeFuseWindow::instance()->reset();
  return 0;
}

void
uidisplay_area( int x, int y, int w, int h )
{
    QImage * image = DeFuseWindow::instance()->getScreen().image;
    libspectrum_dword * palette = settings_current.bw_tv ? bw_colors : settings_current.pretty_gigascreen ? qtdisplay_gigascreen_halfcolors : qtdisplay_colors;
    for(int yy = y; yy < y + h; yy++ ) {
        libspectrum_word *display = &qtdisplay_image[yy][x];
        for(int i = 0; i < w; ++i, ++display ) image->setPixel( x + i, yy, palette[ *display ]);
    }
    DeFuseWindow::instance()->needToRepaint();
}

int
uidisplay_end( void )
{
    qApp->processEvents();
    return 0;
}

void
uidisplay_frame_end( void )
{
    DeFuseWindow::instance()->drawScreen();
    qApp->processEvents();
}

int
uidisplay_hotswap_gfx_mode( void )
{
    qApp->processEvents();
    return 0;
}

int
uidisplay_init( int width, int height )
{
    register_scalers(0);
    init_colors();
    ::memset(qtdisplay_image, 0 , 2 * DISPLAY_SCREEN_HEIGHT * DISPLAY_SCREEN_WIDTH * sizeof(libspectrum_word));
    DeFuseWindow::instance()->getScreen(width + DeFuseWindow::Screen_t::AddX, height + DeFuseWindow::Screen_t::AddY);
    DeFuseWindow::instance()->needToRepaint();
    return 0;
}

/* Set one pixel in the display */
void
uidisplay_putpixel( int x, int y, int color )
{
  if( machine_current->timex ) {
    x <<= 1; y <<= 1;
    qtdisplay_image[y  ][x  ] = color;
    qtdisplay_image[y  ][x+1] = color;
    qtdisplay_image[y+1][x  ] = color;
    qtdisplay_image[y+1][x+1] = color;
  } else {
    qtdisplay_image[y][x] = color;
  }
}

/* Print the 8 pixels in `data' using ink color `ink' and paper
   color `paper' to the screen at ( (8*x) , y ) */
void
uidisplay_plot8( int x, int y, libspectrum_byte data,
                 libspectrum_byte ink, libspectrum_byte paper )
{
  x <<= 3;

  if( machine_current->timex ) {
    int i;

    x <<= 1; y <<= 1;
    for( i=0; i<2; i++,y++ ) {
      qtdisplay_image[y][x+ 0] = ( data & 0x80 ) ? ink : paper;
      qtdisplay_image[y][x+ 1] = ( data & 0x80 ) ? ink : paper;
      qtdisplay_image[y][x+ 2] = ( data & 0x40 ) ? ink : paper;
      qtdisplay_image[y][x+ 3] = ( data & 0x40 ) ? ink : paper;
      qtdisplay_image[y][x+ 4] = ( data & 0x20 ) ? ink : paper;
      qtdisplay_image[y][x+ 5] = ( data & 0x20 ) ? ink : paper;
      qtdisplay_image[y][x+ 6] = ( data & 0x10 ) ? ink : paper;
      qtdisplay_image[y][x+ 7] = ( data & 0x10 ) ? ink : paper;
      qtdisplay_image[y][x+ 8] = ( data & 0x08 ) ? ink : paper;
      qtdisplay_image[y][x+ 9] = ( data & 0x08 ) ? ink : paper;
      qtdisplay_image[y][x+10] = ( data & 0x04 ) ? ink : paper;
      qtdisplay_image[y][x+11] = ( data & 0x04 ) ? ink : paper;
      qtdisplay_image[y][x+12] = ( data & 0x02 ) ? ink : paper;
      qtdisplay_image[y][x+13] = ( data & 0x02 ) ? ink : paper;
      qtdisplay_image[y][x+14] = ( data & 0x01 ) ? ink : paper;
      qtdisplay_image[y][x+15] = ( data & 0x01 ) ? ink : paper;
    }
  } else {
    qtdisplay_image[y][x+ 0] = ( data & 0x80 ) ? ink : paper;
    qtdisplay_image[y][x+ 1] = ( data & 0x40 ) ? ink : paper;
    qtdisplay_image[y][x+ 2] = ( data & 0x20 ) ? ink : paper;
    qtdisplay_image[y][x+ 3] = ( data & 0x10 ) ? ink : paper;
    qtdisplay_image[y][x+ 4] = ( data & 0x08 ) ? ink : paper;
    qtdisplay_image[y][x+ 5] = ( data & 0x04 ) ? ink : paper;
    qtdisplay_image[y][x+ 6] = ( data & 0x02 ) ? ink : paper;
    qtdisplay_image[y][x+ 7] = ( data & 0x01 ) ? ink : paper;
  }
}

/* Print the 16 pixels in `data' using ink color `ink' and paper
   color `paper' to the screen at ( (16*x) , y ) */
void
uidisplay_plot16( int x, int y, libspectrum_word data,
                 libspectrum_byte ink, libspectrum_byte paper )
{
  int i;
  x <<= 4; y <<= 1;

  for( i=0; i<2; i++,y++ ) {
    qtdisplay_image[y][x+ 0] = ( data & 0x8000 ) ? ink : paper;
    qtdisplay_image[y][x+ 1] = ( data & 0x4000 ) ? ink : paper;
    qtdisplay_image[y][x+ 2] = ( data & 0x2000 ) ? ink : paper;
    qtdisplay_image[y][x+ 3] = ( data & 0x1000 ) ? ink : paper;
    qtdisplay_image[y][x+ 4] = ( data & 0x0800 ) ? ink : paper;
    qtdisplay_image[y][x+ 5] = ( data & 0x0400 ) ? ink : paper;
    qtdisplay_image[y][x+ 6] = ( data & 0x0200 ) ? ink : paper;
    qtdisplay_image[y][x+ 7] = ( data & 0x0100 ) ? ink : paper;
    qtdisplay_image[y][x+ 8] = ( data & 0x0080 ) ? ink : paper;
    qtdisplay_image[y][x+ 9] = ( data & 0x0040 ) ? ink : paper;
    qtdisplay_image[y][x+10] = ( data & 0x0020 ) ? ink : paper;
    qtdisplay_image[y][x+11] = ( data & 0x0010 ) ? ink : paper;
    qtdisplay_image[y][x+12] = ( data & 0x0008 ) ? ink : paper;
    qtdisplay_image[y][x+13] = ( data & 0x0004 ) ? ink : paper;
    qtdisplay_image[y][x+14] = ( data & 0x0002 ) ? ink : paper;
    qtdisplay_image[y][x+15] = ( data & 0x0001 ) ? ink : paper;
  }
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
  int error;

  if( paused ) {
    paused = 0;
    ui_statusbar_update( UI_STATUSBAR_ITEM_PAUSED,
			 UI_STATUSBAR_STATE_INACTIVE );
    timer_estimate_reset();
    fuse_emulation_unpause();
  } else {

    /* Stop recording any competition mode RZX file */
    if( rzx_recording && rzx_competition_mode ) {
      ui_error( UI_ERROR_INFO, "Stopping competition mode RZX recording" );
      error = rzx_stop_recording(); if( error ) return;
    }

    paused = 1;
    ui_statusbar_update( UI_STATUSBAR_ITEM_PAUSED, UI_STATUSBAR_STATE_ACTIVE );
    fuse_emulation_pause();
  }
}

void
menu_machine_reset( int action )
{
  int hard_reset = action;
  const char *message = "Reset?";

  if( hard_reset )
    message = "Hard reset?";

  if( !DeFuseWindow::instance()->ask( message ) )
    return;

  /* Stop any ongoing RZX */
  rzx_stop_recording();
  rzx_stop_playback( 1 );

  if( machine_reset( hard_reset ) ) {
    ui_error( UI_ERROR_ERROR, "couldn't reset machine: giving up!" );

    /* FIXME: abort() seems a bit extreme here, but it'll do for now */
    fuse_abort();
  }
}

void
menu_machine_select( int action )
{
    /* Firstly, stop emulation */
    fuse_emulation_pause();

    DeFuseWindow::instance()->selectMachine();

    /* And then carry on with emulation again */
    fuse_emulation_unpause();
    event_reset(); // HACK: hangs without it
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
