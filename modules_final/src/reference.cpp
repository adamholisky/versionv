#include <stdlib.h>
#include <stdio.h>

void init( void ) {
	printf( "In Module: Init\n" );
}

void exit( void ) {
	printf( "In Module: Exit\n" );
}

void main( int argc, char *argv[] ) {
	printf( "In Module: Main\n" );
}