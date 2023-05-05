#include <kernel.h>

#include <vui/vui.h>

#include <vui/desktop.h>
#include <vui/label.h>
#include <vui/window.h>
#include <vui/console.h>
#include <vui/button.h>

#include <vui/font/fira.h>
#include <vui/font/verab.h>
#include <vui/font/verar.h>
#include <vui/font/dvsm.h>

uint8_t *DVSM = dvsm;

#define SSFN_IMPLEMENTATION
#include <ssfn.h>

/*
 * I hate fonts
 * 
 * ./sfnconv.exe -T -M 14 -A DejaVuSansMono.ttf mono.sfn
 * ./sfnconv.exe -C mono.sfn
 * 
 */

vui_handle_data handles[ VUI_MAX_HANDLES ];

vui_handle  vui_handle_top;
vui_error   vui_last_error;

vui_desktop	*main_desktop;

int mouse_x;
int mouse_y;


void vui_initalize( void ) {
	log_entry_enter();

	vui_handle_top = 0;
	vui_last_error = 0;

	mouse_x = 0;
	mouse_y = 0;
	
	vga_information *v = vga_get_info();

	main_desktop = vui_desktop_new( 0, 0, v->width, v->height, 0x00333399 );

	vui_set_main_desktop( main_desktop );

	vui_refresh();

	log_entry_exit();
}


void vui_refresh( void ) {
	log_entry_enter();

	vui_handle_draw( main_desktop->common.handle );
	//console_draw();
	vga_draw_screen();

	log_entry_exit();
}

void *vui_add_handle( int handle_type ) {
	void *ret = NULL;

	if( vui_handle_top == VUI_MAX_HANDLES ) {
		vui_last_error = VUI_ERROR_MAX_HANDLES;
		return 0;
	}

	handles[vui_handle_top].handle = vui_handle_top;
	handles[vui_handle_top].handle_type = handle_type;
	handles[vui_handle_top].in_use = true;

	switch( handle_type ) {
		case VUI_TYPE_DESKTOP:
			ret = malloc( sizeof(vui_desktop) );
			break;
		case VUI_TYPE_LABEL:
			ret = malloc( sizeof(vui_label) );
			break;
		case VUI_TYPE_WINDOW:
			ret = malloc( sizeof(vui_window) );
			break;
        case VUI_TYPE_CONSOLE:
            ret = malloc( sizeof(vui_console) );
            break;
		case VUI_TYPE_BUTTON:
			ret = malloc( sizeof(vui_button) );
			break;
		default:
			klog( "Unknown type: 0x%X\n", handle_type );
			dump_stack_trace();
			return NULL;
	}

	if( ret == NULL ) {
		klog( "Ret is NULL\n" );
		return NULL;
	}

	vui_object *obj = (vui_object *)ret;
	obj->handle = vui_handle_top;
	obj->type = handle_type;

	handles[vui_handle_top].resource = ret;

	vui_handle_top++;

	return ret;
}

void vui_free_handle( vui_handle handle ) {
	vui_handle_data *hd = &handles[ handle ];

	switch( hd->handle_type ) {
		case VUI_TYPE_DESKTOP:
			vui_desktop_destroy( (vui_desktop *)hd->resource );
			break;
		case VUI_TYPE_LABEL:
			vui_label_destroy( (vui_label *)hd->resource );
			break;
		case VUI_TYPE_WINDOW:
			vui_window_destroy( (vui_window *)hd->resource );
			break;
		default:
			klog( "Unknown type: 0x%X\n", hd->handle_type );
			return false;
	}

	handles[handle].in_use = false;

	free( handles[handle].resource );
}

bool vui_handle_draw( vui_handle handle ) {
	log_entry_enter();

	vui_handle *h;
	vui_handle_data *hd;

	// TODO: Check if handle is legit

	hd = &handles[ handle ];

	switch( hd->handle_type ) {
		case VUI_TYPE_DESKTOP:
			vui_desktop_draw( (vui_desktop *)hd->resource );
			break;
		case VUI_TYPE_LABEL:
			vui_label_draw( (vui_label *)hd->resource );
			break;
		case VUI_TYPE_WINDOW:
			vui_window_draw( (vui_window *)hd->resource );
			break;
        case VUI_TYPE_CONSOLE:
            vui_console_draw( (vui_console *)hd->resource );

			rect r = {
				.x = ((vui_console *)hd->resource)->x,
				.y = ((vui_console *)hd->resource)->y,
				.w = ((vui_console *)hd->resource)->width,
				.h = ((vui_console *)hd->resource)->height
			};

			vga_draw_screen_box( &r );
            break;
		case VUI_TYPE_BUTTON:
			vui_button_draw( (vui_button *)hd->resource );
			break;
		default:
			klog( "Unknown type: 0x%X\n", hd->handle_type );
			return false;
	}

	// Handle children
	for( int i = 1; i < vui_handle_top; i++ ) {
		vui_object *obj = NULL;

		if( handles[i].in_use == true ) {
			obj = (vui_object *)handles[i].resource;

			if( obj->parent == handle ) {
				vui_handle_draw( obj->handle );
			}
		}
	}

	if( hd->handle_type == VUI_TYPE_WINDOW ) {
		if( ((vui_window *)hd->resource)->common.custom_paint_func ) {
			((vui_window *)hd->resource)->common.custom_paint_func( hd->resource );
		}
		
	}

	log_entry_exit();

	return true;
}

bool vui_set_parent( void *child, void *parent ) {
	vui_object *obj_child = (vui_object *)child;
	vui_object *obj_parent = (vui_object *)parent;

	obj_child->parent = obj_parent->handle;

	return true;
}

void vui_draw_rectangle( int x, int y, int width, int height, uint32_t color ) {
	rect r = {
		.x = x,
		.y = y,
		.h = height,
		.w = width
	};

	draw_rect( r, color );
}

int vui_get_string_width( int font, int size, char *s ) {
	int width = 0;
	int height = 0;
	int left = 0;
	int top = 0;

	ssfn_t ctx = { 0 };

	memset( &ctx, 0, sizeof( ssfn_t ) );

	ssfn_font_t *user_font = NULL;

	switch( font ) {
		case VUI_FONT_FIRA:
			user_font = (ssfn_font_t *)fira;
			break;
		case VUI_FONT_VERA:
			user_font = (ssfn_font_t *)VeraR;
			break;
		case VUI_FONT_VERAB:
			user_font = (ssfn_font_t *)VeraB;
			break;
		case VUI_FONT_DVSM:
			user_font = (ssfn_font_t *)DVSM;
			break;
		default:
			user_font = (ssfn_font_t *)fira;
	}

	int err = ssfn_load(&ctx, user_font);

	if( err < 0 ) {
		klog( "ssfn_load err: %d\n", err );
		return;
	}
	
	err = ssfn_select( &ctx, SSFN_FAMILY_ANY, NULL, SSFN_STYLE_REGULAR, size );

	if( err < 0 ) {
		klog( "ssfn_select err: %d\n", err );
		return;
	}

	int bbox_result = ssfn_bbox( &ctx, s, &width, &height, &left, &top );

	return width;
}

void vui_draw_string( int x, int y, int size, uint32_t fg, int font, char *s ) {
	vga_information *v = vga_get_info();

	ssfn_t ctx = { 0 };

	memset( &ctx, 0, sizeof( ssfn_t ) );

	ssfn_buf_t buf = {
		.ptr = v->buffer,
		.w = v->width,
		.h = v->height,
		.p = (v->width * 4),
		.x = x,
		.y = y,
		.fg = fg
	};

	ssfn_font_t *user_font = NULL;

	switch( font ) {
		case VUI_FONT_FIRA:
			user_font = (ssfn_font_t *)fira;
			break;
		case VUI_FONT_VERA:
			user_font = (ssfn_font_t *)VeraR;
			break;
		case VUI_FONT_VERAB:
			user_font = (ssfn_font_t *)VeraB;
			break;
		case VUI_FONT_DVSM:
			user_font = (ssfn_font_t *)DVSM;
			break;
		default:
			user_font = (ssfn_font_t *)fira;
	}

	int err = ssfn_load(&ctx, user_font);

	if( err < 0 ) {
		klog( "ssfn_load err: %d\n", err );
		return;
	}

	int family = SSFN_FAMILY_ANY;

	if( font == VUI_FONT_DVSM ) {
		family = SSFN_FAMILY_ANY;
	}
	
	err = ssfn_select( &ctx, family, NULL, SSFN_STYLE_REGULAR, size );

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
}

void vui_draw_string_mono( int x, int y, int size, uint32_t fg, int font, char *s ) {
	vga_information * vga = vga_get_info();

	for( int i = 0; i < strlen(s); i++ ) {
		draw_char( vga->buffer, x + (i * vga->char_width), y, fg, 0x00CCCCCC, s[i] );
		draw_char( vga->fbuffer, x + (i * vga->char_width), y, fg, 0x00CCCCCC, s[i] );
	}
	//draw_string( s, x, y, fg, 0x00FFFFFF );
}

void vui_draw_string_mono_with_background( int x, int y, int size, uint32_t bg, uint32_t fg, int font, char *s ) {
	vga_information * vga = vga_get_info();

	for( int i = 0; i < strlen(s); i++ ) {
		draw_char( vga->buffer, x + (i * vga->char_width), y, fg, bg, s[i] );
		draw_char( vga->fbuffer, x + (i * vga->char_width), y, fg, bg, s[i] );
	}
	//draw_string( s, x, y, fg, 0x00FFFFFF );
}

void vui_mouse_move( int32_t x, int32_t y ) {
	int old_x = mouse_x;
	int old_y = mouse_y;

	mouse_x = mouse_x + x;
	mouse_y = mouse_y + y;

	if( mouse_x >= 1280 ) {
		mouse_x = 1280;
	}

	if( mouse_y >= 720 ) {
		mouse_y = 720;
	}

	if( mouse_x < 0 ) {
		mouse_x = 0;
	}

	if( mouse_y < 0 ) {
		mouse_y = 0;
	}

	rect r = {
		.x = mouse_x,
		.y = mouse_y,
		.w = 7,
		.h = 14
	};

	

	vui_draw_rectangle( r.x, r.y, r.w, r.h, 0x00000000 );
	vga_draw_screen();
	//klog( "Mouse move. Direction: %d, amount %d --- (old: %d, %d.  new: %d, %d.)\n", direction, amount, old_x, old_y, mouse_x, mouse_y );
}