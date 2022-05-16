#include <stdlib.h>
#include <stdio.h>
#include <debug.h>
#include <syscall.h>

extern "C" void module_init( void ) {
	printf( "In Module: Init\n" );
}

extern "C" void module_exit( void ) {
	printf( "In Module: Exit\n" );
}

int main( int argc, char *argv[] ) {
	debugf( "In Module: Main\n" );

	while ( true ) {
		sched_yield();
	}

	return 0;
}