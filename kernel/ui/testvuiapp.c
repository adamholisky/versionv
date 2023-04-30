#include <kernel.h>
#include <vui/vui.h>
#include <vui/testapp.h>
#include <fs.h>
#include <afs.h>
#include <syscall.h>
#include <vui/window.h>
#include <vui/label.h>
#include <vui/font/fira.h>
#include <vui/font/verab.h>
#include <vui/font/verar.h>
#include <observer.h>

typedef struct {
	vui_window *win;
	vui_label *top_header;

	rect pane;

	void *mem_start;
} mem_viewer_state;

void mem_viewer_refresh_message_handler( event_message *e );

mem_viewer_state state;

void test_app_main( void ) {
	log_entry_enter();

	rect *r;

	state.win = vui_window_new( 700, 400, 500, 310, "Mem Viewer" );
	vui_set_parent( state.win, vui_get_main_desktop() );

	r = vui_window_get_inner_rect( state.win, &state.pane );
	state.top_header = vui_label_new( r->x + 5, r->y + 16, VUI_FONT_FIRA, 16, "Memory at: 0xC0000000" );
	vui_set_parent( state.top_header, state.win );

	observer_register( "mem_viewer_vui_refresh", mem_viewer_refresh_message_handler );
	observer_attach_to_subject( "vui_refresh", "mem_viewer_vui_refresh", 1 );

	vui_refresh();

	log_entry_exit();
}

void mem_viewer_refresh_message_handler( event_message *e ) {
	log_entry_enter();

	mem_viewer_draw();
	vga_draw_screen();
}

void mem_viewer_draw( void ) {
	log_entry_enter();

	rect *r;

	r = vui_window_get_inner_rect( state.win, &state.pane );
	vui_draw_string(  r->x + 5, r->y + 32, 15, 0xFF000000, VUI_FONT_FIRA, "              00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F  Decoded Text" );

	klog( "DONE!\n" );
}
