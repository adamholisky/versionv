typedef unsigned int bool;

extern void set_debug_output( bool output_state );
extern int printf_(const char* format, ...);
extern void sched_yield( void );

#define true 1
#define false 0

void main( void ) {
	set_debug_output( true );
	//printf_( "Hello, world from gamma!\n" );
	set_debug_output( false );
	
	while ( true ) {
		sched_yield();
	}
}