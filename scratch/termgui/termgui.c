#include <stdio.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>


#define unicode_vertical_bar "\u2502"
#define unicode_horizontal_bar "\u2500"
#define unicode_corner_top_left "\u250C"
#define unicode_corner_top_right "\u2510"
#define unicode_corner_bottom_left "\u2514"
#define unicode_corner_bottom_right "\u2518"
#define unicode_title_line_left "\u251C"
#define unicode_title_line_right "\u2524"

#define normal_weight 0
#define double_weight 1

typedef struct {
	int	height;
	int	width;
	char *buffer;
} term_info;

typedef struct {
	int x_left;
	int y_top;
	int width;
	int height; 
} rect;

typedef struct {
	char * top_left;
	char * top_right;
	char * bottom_left;
	char * bottom_right;
	char * vertical_bar;
	char * horizontal_bar;
	char * title_line_left;
	char * title_line_right;
} unicode_info;

typedef struct {
	void (draw *)();

} grid;

typedef struct {
	
} component;

void print_at( int x, int y, char  * fmt, ... );
unicode_info * get_weight( int weight );
void draw_box( int x_left, int y_top, int width, int height, int weight );
void clear_screen( void );

term_info term;
unicode_info double_weight_unicode;
unicode_info normal_weight_unicode;

void main( void ) {
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);

	term.height = w.ws_row;
	term.width = w.ws_col;
	term.buffer = malloc( sizeof(char)*term.width*term.height );

	normal_weight_unicode.top_left = unicode_corner_top_left;
	normal_weight_unicode.top_right = unicode_corner_top_right;
	normal_weight_unicode.bottom_left = unicode_corner_bottom_left;
	normal_weight_unicode.bottom_right = unicode_corner_bottom_right;
	normal_weight_unicode.vertical_bar = unicode_vertical_bar;
	normal_weight_unicode.horizontal_bar = unicode_horizontal_bar;
	normal_weight_unicode.title_line_left = unicode_title_line_left;
	normal_weight_unicode.title_line_right = unicode_title_line_right;

	clear_screen();

	rect r;
	r.height = 15;
	r.width = 30;
	r.x_left = 5;
	r.y_top = 3;

	draw_window( &r, normal_weight, "Hello, world!" );

	print_at( 0, 20, " " );
}	

void clear_screen( void ) {
	printf( "\e[2J" );
}

void print_at( int x, int y, char  * fmt, ... ) {
	va_list args;

	printf( "\e[%d;%dH", y, x );
	//printf( "y" );
	
	va_start( args, fmt );
	vprintf( fmt, args ); 
	va_end( args );
}

unicode_info * get_weight( int weight ) {
	switch( weight ) {
		case double_weight:
			return (unicode_info *)&double_weight_unicode;
			break;
		case normal_weight:
		default:
			return (unicode_info *)&normal_weight_unicode;
	}
}

void draw_window( rect * r, int weight, char * title ) {
	draw_box( r->x_left, r->y_top, r->width, r->height, weight );
	draw_title_line( r->x_left, r->y_top + 2, r->width );
	print_at( r->x_left + 2, r->y_top + 1, title );
}

void draw_box( int x_left, int y_top, int width, int height, int weight ) {
	unicode_info * unicode = get_weight( weight );

	print_at( x_left, y_top, unicode->top_left );
	print_at( x_left + width, y_top, unicode->top_right );
	print_at( x_left, y_top + height, unicode->bottom_left );
	print_at( x_left + width, y_top + height, unicode->bottom_right );
	
	for( int i = 1; i < width; i++ ) {
		print_at( x_left + i, y_top, unicode->horizontal_bar );
		print_at( x_left + i, y_top + height, unicode->horizontal_bar );
	}

	for( int i = 1; i < height; i++ ) {
		print_at( x_left, y_top + i, unicode->vertical_bar );
		print_at( x_left + width, y_top + i, unicode->vertical_bar );
	}
}

void draw_title_line( int x_left, int y_top, int width, int weight ) {
	unicode_info * unicode = get_weight( weight );

	print_at( x_left, y_top, unicode->title_line_left );
	print_at( x_left + width, y_top, unicode->title_line_right );
	
	for( int i = 1; i < width; i++ ) {
		print_at( x_left + i, y_top, unicode->horizontal_bar );
	}
}