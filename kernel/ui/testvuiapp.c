#include <kernel.h>
#include <vui/vui.h>
#include <vui/testapp.h>
#include <fs.h>
#include <afs.h>
#include <syscall.h>
#include <vui/parts/window.h>
#include <vui/font/fira.h>

#define SSFN_IMPLEMENTATION
#include <ssfn.h>


void vui_draw_window( int x, int y, int width, int height );

void test_app_main( void ) {
	vui_draw_window_around( (1280/4), 150, 7 * 80, 14 * 25 );

	
	int x = 0;
	int font_file = open( "/etc/vera.sfn", 0 );
	int file_size = get_file_size(font_file);
	uint8_t *buff = malloc( file_size );
	int bytes_read = read( font_file, buff, file_size );
	vga_information *v = vga_get_info();

	klog( "Size: %d\n", file_size );
	klog( "Bytes Read: %d\n", bytes_read );
	
	if( bytes_read != 0 ) {
		//kdebug_peek_at_n( buff, (file_size / 0xF) + 0xA );

		ssfn_t ctx = { 0 };                                 /* the renderer context */


		memset( &ctx, 0, sizeof( ssfn_t ) );

		ssfn_buf_t buf = {                                  /* the destination pixel buffer */
			.ptr = v->buffer,                      /* address of the buffer */
			.w = 1280,                             /* width */
			.h = 720,                             /* height */
			.p = (1280*4),                         /* bytes per line */
			.x = 50,                                       /* pen position */
			.y = 50,
			.fg = 0xffffffff,                                /* foreground color */
			.bg = 0x00000000
		};

		klog( "0\n" );

		ssfn_font_t *font = (ssfn_font_t *)fira;

		/* add one or more fonts to the context. Fonts must be already in memory */
		int err = ssfn_load(&ctx, font);          /* you can add different styles... */
		klog( "ssfn_load err: %d\n", err );

		klog( "1\n" );
		/* select the typeface to use */
		err = ssfn_select(&ctx,
			SSFN_FAMILY_ANY, NULL,                        /* family */
			SSFN_STYLE_REGULAR,      /* style */
			16                                            /* size */
		);

		klog( "ssfn_select err: %d\n", err );

		klog( "2\n" );

		/* rasterize the first glyph in an UTF-8 string into a 32 bit packed pixel buffer */
		/* returns how many bytes were consumed from the string */
		err = ssfn_render(&ctx, &buf, "Hello");
		err = ssfn_render(&ctx, &buf, "ello");
		err = ssfn_render(&ctx, &buf, "llo");
		err = ssfn_render(&ctx, &buf, "lo");
		err = ssfn_render(&ctx, &buf, "o");
		klog( "ssfn_render err: %d\n", err );

		klog( "3\n" );

		fillrect( v->buffer, 0x00ffffff, 1000, 400, 100, 100 );

		vga_draw_screen();
	}
}

int ui_top_height = 20;
int ui_top_l_width = 22;
int ui_top_r_width = 39;
int ui_bottom_height = 2;

void vui_draw_window_around( int x, int y, int width, int height ) {
	vui_draw_window( x - 2, y - ui_top_height, width + 5, height + ui_top_height + ui_bottom_height + 1 );
}

/*
	window_ui_top_left      window_ui_top_mid       window_ui_top_right
	22w x 20h				1w x 20h			    39w x 20h

	window_ui_left								   	window_ui_right
	2w x 1h											2w x 1h

	window_ui_bottom
	1w x 2h

*/	

void vui_draw_window( int x, int y, int width, int height ) {
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

	draw_rect( r, 0x00FFFFFF ); */

	vga_draw_screen();
}