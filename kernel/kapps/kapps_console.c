#include <kernel.h>
#include <terminal.h>
#include <vui/vui.h>
#include <vui/console.h>
//-----
#include <vui/window.h>
#include <vui/label.h>
#include <kapps/console.h>

typedef struct {
	vui_window *win;
	vui_console *con;

	rect pane;
} console_app_state;

console_app_state capp_state;

int vui_console_main( int argc, char *argv[] ) {
	log_entry_enter();

	rect *r;

	capp_state.win = vui_window_new( 10, 10, 750, (14 * 25) + 30, "Fully Instanced vUI Console" );
	vui_set_parent( capp_state.win, vui_get_main_desktop() );

	r = vui_window_get_inner_rect( capp_state.win, &capp_state.pane );
	capp_state.con = vui_console_new( r->x, r->y, r->w, r->h );
	vui_set_parent( capp_state.con, capp_state.win );

	capp_state.con->transparent_text_background = true;
	capp_state.con->foreground = CONSOLE_COLOR_BLACK;

	vui_console_clear( capp_state.con );

    klog( "done.\n" );

/* 	vui_console_puts( capp_state.con, "Hello, world!" );
	vui_console_puts( capp_state.con, "\n\nThis is a line of text!\nAnd another...\n" ); */

	// scroll test

	/* char str[100];
	// capp_state.con->rows
	for( int i = 1; i < 21; i++ ) {
		memset( str, 0, 100 );
		snprintf( str, 100, "0x%02X: This is line %d (Max: %d). Test scrolling. cur_x: %d, cur_y: %d\n", i, i, capp_state.con->rows, capp_state.con->current_x, capp_state.con->current_y );
		vui_console_puts( capp_state.con, str );
	} */

	//vui_console_puts( capp_state.con, "A little extra" );

 	vui_console_puts( capp_state.con, "The first duty of every \x1b[0;31;49mStarfleet officer\x1b[0;0;0m is to the truth, whether it's scientific truth or historical truth or personal truth." );

	vui_console_puts( capp_state.con, "\nNew line.\nAnother." );

    klog( "done2.\n" );

    set_terminal_redirect( kapps_console_putc );

    klog( "done3.\n" );
 
	vui_refresh();

	log_entry_exit();

	return 0;
}

void kapps_console_putc( char c ) {
    vui_console_putc( capp_state.con, c );
    //vui_handle_draw( capp_state.con->common.handle );
}