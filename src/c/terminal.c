#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "vga.h"
#include "terminal.h"
#include "bootstrap.h"
#include "serial.h"

unsigned int term_current_row;
unsigned int term_current_column;
unsigned char term_current_color;
unsigned short * term_buffer;

char ansi_capture[25];
bool term_capture_ansi_escape_code = false;
uint32_t capture_i = 0;

unsigned int VGA_WIDTH = 80;
unsigned int VGA_HEIGHT = 25;
unsigned int y_start;

bool is_debug_output = false;

void term_initalize( void ) {
	// DO NOT PUT KLOG FUNCTIONS HERE
	unsigned int x = 0;
	unsigned int y = 0;

	term_current_row = 0;
	term_current_column = 0;
	y_start = 0;
	term_current_color = vga_entry_color( VGA_COLOR_WHITE, VGA_COLOR_BLACK );
	term_buffer = ( unsigned short * )( 0xC00B8000 );

	for( y = 0; y < VGA_HEIGHT; y++ ) {
		for( x = 0; x < VGA_WIDTH; x++ ) {
			term_buffer[( y * VGA_WIDTH ) + x] = vga_entry( ' ', term_current_color );
		}
	}
}

void term_set_color( uint32_t foreground, uint32_t background ) {
	term_current_color = vga_entry_color( VGA_COLOR_RED, VGA_COLOR_BLUE );
}

void term_put_char_at( char c, unsigned char color, unsigned int x, unsigned int y ) {
	color = term_current_color;

	if( c != '\n' ) {
		term_buffer[( y * VGA_WIDTH ) + x] = vga_entry( c, color );
	}
}

void term_put_char( char c ) {
	unsigned int x;
	unsigned int y;
	unsigned int max_row;
	unsigned short fg, bg;
	bool send_to_com1 = false;
	bool send_to_com2 = false;
	bool send_to_screen = false;

	if( is_debug_output == true ) {
		send_to_com1 = true;
		send_to_com2 = true;
	}

	if( c == '\x1b' ) {
		term_capture_ansi_escape_code = true;
		capture_i = 0;
		send_to_com1 = false;
	} else if( term_capture_ansi_escape_code ) {
		if( c == 'm' ) {
			ansi_capture[capture_i] = 0;
			term_capture_ansi_escape_code = false;
			capture_i = 0;

			// Process escape seq
			// char 3 & 4 = fg
			// char 6 & 7 = bg
			fg = ((ansi_capture[3] - '0') * 10) + (ansi_capture[4] - '0');
			bg = ((ansi_capture[6] - '0') * 10) + (ansi_capture[7] - '0');

			switch( fg ) {
				case 30:
					fg = VGA_COLOR_BLACK;
					break;
				case 31:
					fg = VGA_COLOR_RED;
					break;
				case 32:
					fg = VGA_COLOR_GREEN;
					break;
				case 34:
					fg = VGA_COLOR_BLUE;
					break;
				case 37:
				case 39:
				case 0:
				default:
					fg = VGA_COLOR_WHITE;
			}

			switch( bg ) {
				case 40:
					bg = VGA_COLOR_BLACK;
					break;
				case 41:
					bg = VGA_COLOR_RED;
					break;
				case 42:
					bg = VGA_COLOR_GREEN;
					break;
				case 44:
					bg = VGA_COLOR_BLUE;
					break;
				case 47:
				case 49:
				case 0:
				default:
					bg = VGA_COLOR_BLACK;
			}

			term_current_color = vga_entry_color( fg, bg );
			send_to_com1 = false;
		} else {
			ansi_capture[capture_i] = c;
			capture_i++;
			send_to_com1 = false;
		}
	} else {
		send_to_screen = true;

		//update_cursor( term_current_row, term_current_column );
	}

	if( send_to_com1 ) {
		serial_write_port( c, COM1 );
	}

	if( send_to_com2 ) {
		serial_write_port( c, COM2 );
	}

	if( send_to_screen ) {
		if( c != '\n' ) {
			term_put_char_at( c, term_current_color, term_current_column, term_current_row );
		} else {
			term_current_column = VGA_WIDTH - 1;
		}

		term_current_column++;

		if( term_current_column == VGA_WIDTH ) {
			term_current_column = 0;

			term_current_row++;

			max_row = VGA_HEIGHT;

			if( term_current_row == max_row ) {
				term_current_row = max_row - 1;

				for( y = y_start; y < max_row - 1; y++ ) {
					for( x = 0; x < VGA_WIDTH; x++ ) {
						term_buffer[( y * VGA_WIDTH ) + x] = term_buffer[( ( y + 1 ) * VGA_WIDTH ) + x];
					}
				}

				for( x = 0; x < VGA_WIDTH; x++ ) {
					const size_t index = ( VGA_HEIGHT - 1 ) * VGA_WIDTH + x;
					term_buffer[index] = vga_entry( ' ', term_current_color );
				}
			}
		}
	}
}

void term_clear_last_char( void ) {
	int term_new_column = term_current_column - 1;

	//printf( "cc: %d --> nc: %d", term_current_column, term_new_column );
	if( term_new_column > 0 ) {
		term_put_char_at( ' ', term_current_color, term_new_column, term_current_row );

		term_current_column = term_new_column;
	}

	//update_cursor( term_current_row, term_current_column );
}

/* Outputs a string data of size the terminal
 */
void term_put_string( const char * data, size_t size ) {
	for( size_t i = 0; i < size; i++ ) {
		term_put_char( data[i] );
	}
}

/* Calculates the size of *data and outputs the string *data
 */
void term_write_string( const char * data ) {
	term_put_string( data, strlen( data ) );
}

void set_debug_output( bool d ) {
	is_debug_output = d;
}

void write_to_serial_port( char c ) {
	serial_write( c );
}