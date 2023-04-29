#include <kernel.h>
#include <vui/vui.h>
#include <vui/window.h>
#include <vui/parts/window.h>

int ui_top_height = 20;
int ui_top_l_width = 22;
int ui_top_r_width = 39;
int ui_bottom_height = 2;

vui_window *vui_window_new( int x, int y, int width, int height, char *title ) {
	vui_window *window = vui_add_handle( VUI_TYPE_WINDOW );

	window->x = x;
	window->y = y;
	window->width = width;
	window->height = height;
	window->title = malloc( strlen(title) );
	strcpy( window->title, title );

	return window;
}

void vui_window_destroy( vui_window *window ) {
	free( window->title );
}

bool vui_window_draw( vui_window *window ) {
	int _x = window->x;
	int _y = window->y;
	int middle_repeat = window->width - ui_top_l_width - ui_top_r_width - 1;

	// Window UI Top
	// left
	for( int i = 0; i < ui_top_height; i++ ) {
		for( int j = 0; j < ui_top_l_width; j++) {
			put_pixel(_x + j, _y + i, window_ui_top_left[(i * ui_top_l_width) + j]);
		}
	}

	_x = _x + ui_top_l_width;

	// middle
	for( int n = 0; n < middle_repeat; n++ ) {
		for( int j = 0; j < ui_top_height; j++ ) {
			put_pixel( _x + n, _y + j, window_ui_top_mid[j] );
		}
	}

	_x = _x + middle_repeat;

	// right
	for( int i = 0; i < ui_top_height; i++ ) {
		for( int j = 0; j < ui_top_r_width; j++) {
			put_pixel(_x + j, _y + i, window_ui_top_right[(i * ui_top_r_width) + j]);
		}
	}

	// Window UI Left and Right
	for( int i = ui_top_height; i < (window->height - 1); i++ ) {
		put_pixel( window->x, window->y + i, window_ui_left[0] );
		put_pixel( window->x + 1, window->y + i, window_ui_left[1] );

		put_pixel( window->x + window->width - 3, window->y + i, window_ui_right[0] );
		put_pixel( window->x + window->width - 2, window->y + i, window_ui_right[1] );
	}

	// Right shade effect
	for( int i = 2; i < window->height; i++ ) {
		put_pixel( window->x + window->width - 1, window->y + i, 0x00262626 );
		put_pixel( window->x + window->width, window->y + i, 0x00262626 );
	}

	// Bottom
	for( int i = 1; i < window->width - 2; i++ ) {
		put_pixel( window->x + i, window->y + window->height - 3, window_ui_bottom[0]);
		put_pixel( window->x + i, window->y + window->height - 2, window_ui_bottom[1]);
	}

	// Bottom shade effect
	for( int i = 2; i < window->width; i++ ) {
		put_pixel( window->x + i, window->y + window->height - 1, 0x00262626 );
		put_pixel( window->x + i, window->y + window->height, 0x00262626 );
	}

	// inner window
	vui_draw_rectangle( window->x + 2, window->y + ui_top_height, window->width - 4, window->height - ui_top_height - 4, 0x00CCCCCC );

	// title
	int title_width = vui_get_string_width( VUI_FONT_VERA, 11, window->title );
	int title_x = window->x + (window->width/2) - (title_width/2);
	int title_y = window->y + 4;

	int title_box_x = title_x - 10;
	int title_box_y = window->y + 2;
	int title_box_width = title_width + 20;
	int title_box_height = ui_top_height - 4;

	klog( "title width: %d\n", title_width );

	vui_draw_rectangle( title_box_x, title_box_y, title_box_width, title_box_height, 0x00CCCCCC );

	vui_draw_string( title_x, title_y + 10, 11, 0xFF000000, VUI_FONT_VERA, window->title );

	return true;
}

rect *vui_window_get_inner_rect( vui_window *window, rect *r ) {
	r->x = window->x + 2;
	r->y = window->y + ui_top_height;
	r->w = window->width - 6;
	r->h = window->height - ui_top_height - 3;

	return r;
}