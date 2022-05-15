#include <stdlib.h>
#include <stdio.h>

extern "C" void module_init( void ) {
	printf( "In Module: Init\n" );
}

extern "C" void module_exit( void ) {
	printf( "In Module: Exit\n" );
}

int main( int argc, char *argv[] ) {
	printf( "In Module: Main\n" );

	return 0;
}