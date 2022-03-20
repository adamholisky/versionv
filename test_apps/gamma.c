#include <printf.h>
#include <string.h>
#include <stdbool.h>
#include "debug.h"
#include "syscall.h"

void main( void ) {
	klog( "Hello, world from gamma!\n" );
	
	while ( true ) {
		sched_yield();
	}
}