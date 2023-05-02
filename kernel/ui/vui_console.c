#include <kernel.h>
#include <vui/vui.h>
#include <vui/console.h>
//-----
#include <vui/window.h>
#include <vui/label.h>

typedef struct {
	vui_window *win;
	vui_console *con;

	rect pane;
} console_app_state;

console_app_state capp_state;

vui_console *vui_console_new( int x, int y, int width, int height ) {
	vui_console *console = vui_add_handle( VUI_TYPE_CONSOLE );

	console->font_height = 14;
	console->font_width = 7;

	console->cols = width / console->font_width;
	console->rows = height / console->font_height;

	console->x = x;
	console->y = y;
	console->width = width;
	console->height = height;

	console->current_x = 0;
	console->current_y = 0;

	console->foreground = CONSOLE_COLOR_BLACK;
	console->background = CONSOLE_COLOR_WHITE;
	console->transparent_text_background = false;

	console->data = malloc( sizeof(uint16_t) * console->cols * console->rows );
	memset( console->data, 0, sizeof(uint16_t) * console->cols * console->rows );

	klog( "Rows: %d    Cols: %d\n", console->rows, console->cols );

	return console;
}

void vui_console_destroy( vui_console *console ) {

}

bool vui_console_draw( vui_console *console ) {
	for( int i = 0; i < console->rows; i++ ) {
		int y_loc = console->y + (i * console->font_height);

		for( int j = 0; j < console->cols; j++ ) {
			int x_loc = console->x + (j * console->font_width);
			char to_draw[2];

			to_draw[0] = *(console->data + (i * console->cols) + j) & 0x00FF;
			to_draw[1] = 0;

			int fg = 0;
			int bg = 0;

			switch( (*(console->data + (i * console->cols) + j) & 0xF000)>>12 ) {
				case CONSOLE_COLOR_BLACK:
					bg = CONSOLE_COLOR_BLACK;
					break;
				case CONSOLE_COLOR_BLUE:
					bg = CONSOLE_COLOR_RGB_BLUE;
					break;
				case CONSOLE_COLOR_GREEN:
					bg = CONSOLE_COLOR_RGB_GREEN;
					break;
				case CONSOLE_COLOR_CYAN:
					bg = CONSOLE_COLOR_RGB_CYAN;
					break;
				case CONSOLE_COLOR_RED:
					bg = CONSOLE_COLOR_RGB_RED;
					break;
				case CONSOLE_COLOR_MAGENTA:
					bg = CONSOLE_COLOR_RGB_MAGENTA;
					break;
				case CONSOLE_COLOR_BROWN:
					bg = CONSOLE_COLOR_RGB_BROWN;
					break;
				case CONSOLE_COLOR_LIGHT_GREY:
					bg = CONSOLE_COLOR_RGB_LIGHT_GREY;
					break;
				case CONSOLE_COLOR_DARK_GREY:
					bg = CONSOLE_COLOR_RGB_DARK_GREY;
					break;
				case CONSOLE_COLOR_LIGHT_BLUE:
					bg = CONSOLE_COLOR_RGB_LIGHT_BLUE;
					break;
				case CONSOLE_COLOR_LIGHT_GREEN:
					bg = CONSOLE_COLOR_RGB_LIGHT_GREEN;
					break;
				case CONSOLE_COLOR_LIGHT_CYAN:
					bg = CONSOLE_COLOR_RGB_LIGHT_CYAN;
					break;
				case CONSOLE_COLOR_LIGHT_RED:
					bg = CONSOLE_COLOR_RGB_LIGHT_RED;
					break;
				case CONSOLE_COLOR_LIGHT_MAGENTA:
					bg = CONSOLE_COLOR_RGB_LIGHT_MAGENTA;
					break;
				case CONSOLE_COLOR_YELLOW:
					bg = CONSOLE_COLOR_RGB_YELLOW;
					break;
				case CONSOLE_COLOR_WHITE:
					bg = CONSOLE_COLOR_RGB_WHITE;
					break;
				default:
					bg = CONSOLE_COLOR_RGB_BLACK;
			}

			switch( (*(console->data + (i * console->cols) + j) & 0x0F00)>>8 ) {
				case CONSOLE_COLOR_BLACK:
					fg = CONSOLE_COLOR_BLACK;
					break;
				case CONSOLE_COLOR_BLUE:
					fg = CONSOLE_COLOR_RGB_BLUE;
					break;
				case CONSOLE_COLOR_GREEN:
					fg = CONSOLE_COLOR_RGB_GREEN;
					break;
				case CONSOLE_COLOR_CYAN:
					fg = CONSOLE_COLOR_RGB_CYAN;
					break;
				case CONSOLE_COLOR_RED:
					fg = CONSOLE_COLOR_RGB_RED;
					break;
				case CONSOLE_COLOR_MAGENTA:
					fg = CONSOLE_COLOR_RGB_MAGENTA;
					break;
				case CONSOLE_COLOR_BROWN:
					fg = CONSOLE_COLOR_RGB_BROWN;
					break;
				case CONSOLE_COLOR_LIGHT_GREY:
					fg = CONSOLE_COLOR_RGB_LIGHT_GREY;
					break;
				case CONSOLE_COLOR_DARK_GREY:
					fg = CONSOLE_COLOR_RGB_DARK_GREY;
					break;
				case CONSOLE_COLOR_LIGHT_BLUE:
					fg = CONSOLE_COLOR_RGB_LIGHT_BLUE;
					break;
				case CONSOLE_COLOR_LIGHT_GREEN:
					fg = CONSOLE_COLOR_RGB_LIGHT_GREEN;
					break;
				case CONSOLE_COLOR_LIGHT_CYAN:
					fg = CONSOLE_COLOR_RGB_LIGHT_CYAN;
					break;
				case CONSOLE_COLOR_LIGHT_RED:
					fg = CONSOLE_COLOR_RGB_LIGHT_RED;
					break;
				case CONSOLE_COLOR_LIGHT_MAGENTA:
					fg = CONSOLE_COLOR_RGB_LIGHT_MAGENTA;
					break;
				case CONSOLE_COLOR_YELLOW:
					fg = CONSOLE_COLOR_RGB_YELLOW;
					break;
				case CONSOLE_COLOR_WHITE:
					fg = CONSOLE_COLOR_RGB_WHITE;
					break;
				default:
					fg = CONSOLE_COLOR_RGB_BLACK;
			}
			
			if( console->transparent_text_background ) {
				vui_draw_string_mono( x_loc , y_loc, 14, fg, VUI_FONT_DVSM, to_draw );
			} else {
				vui_draw_string_mono_with_background( x_loc , y_loc, 14, bg, fg, VUI_FONT_DVSM, to_draw );
			}
			
		}
	}
	
}

void vui_console_clear( vui_console *console ) {
	for( int i = 0; i < console->rows * console->cols; i++ ) {
		*(console->data + i) = ( console->background<<12 | console->foreground<<8 | ' ');
	}
}

/** 
 * Puts a character into the console's current r,c position
 * 
 * returns number of characters put (should be 1)
*/
int vui_console_putc( vui_console *console, char c ) {
	vui_console_putc_color( console, c, console->background, console->foreground );
}

int vui_console_putc_color( vui_console * console, char c, int bg, int fg ) {
	uint16_t *chars = console->data;

	*(chars + (console->current_x) + (console->current_y * console->cols) ) = ( console->background<<12 | console->foreground<<8 | c);

	if( console->current_x + 1 >= console->cols ) {
		console->current_x = 0;
		console->current_y++;
	} else {
		console->current_x++;
	}
	
	return 1;
}

/**
 * @brief Puts a string into the console's current r,c position
 * 
 * @param s null terminated string
 * @return int number of characters put
 */
int vui_console_puts( vui_console *console, char *s ) {
	int i = 0;

	while( *s ) {
		vui_console_putc( console, *s );
		s++;
		i++;
	}

	return i;
}

int vui_console_main( void ) {
	log_entry_enter();

	rect *r;

	capp_state.win = vui_window_new( 700, 50, 500, 300, "Console" );
	vui_set_parent( capp_state.win, vui_get_main_desktop() );

	r = vui_window_get_inner_rect( capp_state.win, &capp_state.pane );
	capp_state.con = vui_console_new( r->x, r->y, r->w, r->h );
	vui_set_parent( capp_state.con, capp_state.win );

	capp_state.con->background = CONSOLE_COLOR_BLACK;
	capp_state.con->foreground = CONSOLE_COLOR_WHITE;

	vui_console_clear( capp_state.con );

	vui_console_puts( capp_state.con, "Hello, world!" );

	vui_refresh();

	log_entry_exit();

	return 0;
}