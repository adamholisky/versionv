#include <kernel.h>
#include <vui/vui.h>
#include <vui/testapp.h>
#include <fs.h>
#include <afs.h>
#include <syscall.h>
//#include <vui/parts/window.h>
#include <vui/font/fira.h>
#include <vui/font/verab.h>
#include <vui/font/verar.h>

//void vui_draw_window( int x, int y, int width, int height );

void test_app_main( void ) {
	//vui_draw_window_around( (1280/4), 150, 7 * 80, 14 * 25 );

	//vui_draw_string( 1280/4, 125, 12, 0xFF000000, VUI_FONT_VERAB, "Hello, world!" );
}
/* 
void vui_draw_string( int _x, int _y, int _size, uint32_t _fg, int _font, char *s ) {
	vga_information *v = vga_get_info();

	ssfn_t ctx = { 0 };                                 

	memset( &ctx, 0, sizeof( ssfn_t ) );

	ssfn_buf_t buf = {                                  
		.ptr = v->buffer,                      
		.w = v->width,                             
		.h = v->height,                            
		.p = (v->width * 4),                         
		.x = _x,                                      
		.y = _y,
		.fg = _fg
	};

	ssfn_font_t *font = NULL;

	switch( _font ) {
		case VUI_FONT_FIRA:
			font = (ssfn_font_t *)fira;
			break;
		case VUI_FONT_VERA:
			font = (ssfn_font_t *)VeraR;
			break;
		case VUI_FONT_VERAB:
			font = (ssfn_font_t *)VeraB;
			break;
		default:
			font = (ssfn_font_t *)fira;
	}

	int err = ssfn_load(&ctx, font);       

	if( err < 0 ) {
		klog( "ssfn_load err: %d\n", err );
		return;
	}
	
	err = ssfn_select( &ctx, SSFN_FAMILY_ANY, NULL, SSFN_STYLE_REGULAR, _size );

	if( err < 0 ) {
		klog( "ssfn_select err: %d\n", err );
		return;
	}

	for( int i = 0; i < strlen(s); i++ ) {
		err = ssfn_render( &ctx, &buf, (s + i) );

		if( err < 0 ) {
			klog( "ssfn_render[%d] err: %d\n", i, err );
			return;
		}
	}

	vga_draw_screen();
}
 */
/* int ui_top_height = 20;
int ui_top_l_width = 22;
int ui_top_r_width = 39;
int ui_bottom_height = 2;

void vui_draw_window_around( int x, int y, int width, int height ) {
	vui_draw_window( x - 2, y - ui_top_height, width + 5, height + ui_top_height + ui_bottom_height + 1 );
} */

/*
	window_ui_top_left      window_ui_top_mid       window_ui_top_right
	22w x 20h				1w x 20h			    39w x 20h

	window_ui_left								   	window_ui_right
	2w x 1h											2w x 1h

	window_ui_bottom
	1w x 2h

*/	

/* void vui_draw_window( int x, int y, int width, int height ) {
	int _x = x;
	int _y = y;
	int middle_repeat = width - ui_top_l_width - ui_top_r_width - 1;

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
	for( int i = ui_top_height; i < (height - 1); i++ ) {
		put_pixel( x, y + i, window_ui_left[0] );
		put_pixel( x + 1, y + i, window_ui_left[1] );

		put_pixel( x + width - 3, y + i, window_ui_right[0] );
		put_pixel( x + width - 2, y + i, window_ui_right[1] );
	}

	// Right shade effect
	for( int i = 2; i < height; i++ ) {
		put_pixel( x + width - 1, y + i, 0x00262626 );
		put_pixel( x + width, y + i, 0x00262626 );
	}

	// Bottom
	for( int i = 1; i < width - 2; i++ ) {
		put_pixel( x + i, y + height - 3, window_ui_bottom[0]);
		put_pixel( x + i, y + height - 2, window_ui_bottom[1]);
	}

	// Bottom shade effect
	for( int i = 2; i < width; i++ ) {
		put_pixel( x + i, y + height - 1, 0x00262626 );
		put_pixel( x + i, y + height, 0x00262626 );
	}

	/* rect r = {
		.h = height - ui_top_height - ui_bottom_height,
		.w = width - 4,
		.x = x + 2,
		.y = y + ui_top_height
	};

	draw_rect( r, 0x00FFFFFF );

	vga_draw_screen();
} */