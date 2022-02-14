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

unsigned int VGA_WIDTH = 80;
unsigned int VGA_HEIGHT = 25;
unsigned int y_start;

bool is_debug_output = false;

void term_initalize( void ) {
	unsigned int x = 0;
	unsigned int y = 0;

	term_current_row = 0;
	term_current_column = 0;
	y_start = 0;
	term_current_color = vga_entry_color( VGA_COLOR_WHITE, VGA_COLOR_BLUE );
	term_buffer = ( unsigned short * )( 0xC00B8000 );

	for( y = 0; y < VGA_HEIGHT; y++ ) {
		for( x = 0; x < VGA_WIDTH; x++ ) {
			term_buffer[( y * VGA_WIDTH ) + x] = vga_entry( ' ', term_current_color );
		}
	}
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

	if( is_debug_output == true ) {
		serial_write( c );

		return;
	}

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

	//update_cursor( term_current_row, term_current_column );
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