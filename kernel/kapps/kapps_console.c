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

 	vui_console_puts( capp_state.con, "The first duty of every \x1b[0;31;49mStarfleet officer\x1b[0;0;0m is to the truth, whether it's scientific truth or historical truth or personal truth." );

	vui_console_puts( capp_state.con, "\nNew line.\nAnother." );

    klog( "done2.\n" );

    set_terminal_redirect( kapps_console_putc );
	vui_window_set_event_handler( capp_state.win, kapps_console_handle_events );

	vui_set_active_window( capp_state.win->common.handle );
	
    klog( "done3.\n" );
 
	vui_refresh();

	log_entry_exit();

	return 0;
}

void kapps_console_putc( char c ) {
    vui_console_putc( capp_state.con, c );
    //vui_handle_draw( capp_state.con->common.handle );
}

void kapps_console_handle_key_down( int scanecode ) {

}

/**
 * @brief 
 * 
 * @param id 
 * @param obj 
 */
void kapps_console_handle_events( vui_handle h, char *id, void *obj ) {
	if( strcmp( "keypress", id ) == 0 ) {
		klog( "got a keypress event\n" );
	}
}