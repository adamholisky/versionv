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
#include <vui/button.h>

typedef struct {
	vui_window *win;
	vui_label *top_header;
	vui_button *ok_button;

	rect pane;

	char message[255];
} alert_state;

void alert_custom_paint( void *obj );

alert_state astate;

void test_app_main( void ) {
	log_entry_enter();

	astate.win = vui_window_new( 600, 400, 400, 150, "Alert" );
	vui_set_parent( astate.win, vui_get_main_desktop() );

	rect *r = vui_window_get_inner_rect( astate.win, &astate.pane );
	astate.top_header = vui_label_new( r->x + 5, r->y + 16, VUI_FONT_FIRA, 14, "This is some alert text that we are displaying" );
	vui_set_parent( astate.top_header, astate.win );

	astate.ok_button = vui_button_new( r->x + r->w - 60, r->y + r->h - 35, 50, 25, "btn_ok", "Ok" );
	vui_set_parent( astate.ok_button, astate.win );

	astate.win->common.custom_paint_func = alert_custom_paint;

	vui_refresh();

	log_entry_exit();
}

void alert_custom_paint( void *obj ) {
	log_entry_enter();

	log_entry_exit();
}