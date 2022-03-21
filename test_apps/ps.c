#include <printf.h>
#include <string.h>
#include <stdbool.h>
#include "debug.h"
#include "syscall.h"
#include "modules.h"
#include "process.h"

void main( void ) {
	debugf( "PS command exec!\n" );

	process *p = get_processes();

	debugf( "ID   A S    EIP           Name\n" );

	for( int i; i < PROC_MAX; i++ ) {
		if( p[i].present == 1 ) {
			debugf( "%d    %d %d    0x%08X    %s\n", i, p[i].present, p[i].status, p[i].stack_eip, p[i].name );
		}
	}
	
	process_reset();
}