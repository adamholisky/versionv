#include <stdint.h>
#include <stdbool.h>
#include "vga.h"
#include "printf.h"

#if !defined(TERMINAL_INCLUDED)
#define TERMINAL_INCLUDED

typedef struct {
    uint32_t	current_row;
    uint32_t	current_column;
    uint32_t	foreground_color;
    uint32_t	background_color;
} term;

void term_initalize( void );
void term_print_color( void );
void term_set_color( uint32_t foreground, uint32_t background );
void term_put_char( char c );
void term_put_char_at( char c, unsigned char color, unsigned int x, unsigned int y );
void term_clear_last_char( void );
void term_put_string( const char* data, size_t size );
void term_write_string( const char* data );
bool is_gui_active( void );
void set_debug_output( bool d );
void write_serial(char a);
void write_to_serial_port( char c );

#endif