#include "debug.h"
#include "interrupts.h"
#include "bootstrap.h"

uint32_t kernel_symbol_top = 0;
kdebug_symbol kernel_symbols[ KDEBUG_MAX_SYMBOLS ];
char kdebug_symbol_cannot_find[] = "KDEBUG_cannot_find_symbol";

char * sys_text_arr[] = { 
							"System",
							"Kernel",
							"Intel8254",
							"Memory",
							"PCI",
							"Interrupts",
							"Paging",
							"ELF"
						};

void kdebug_add_symbol( char * name, uint32_t addr, uint32_t size ) {
	kernel_symbols[ kernel_symbol_top ].name = name;
	kernel_symbols[ kernel_symbol_top ].addr = addr;
	kernel_symbols[ kernel_symbol_top ].size = size;
	kernel_symbol_top++;

	/* debugf( "kdebug_symbol readout:\n" );
	debugf( "    name: %s\n", kernel_symbols[ kernel_symbol_top - 1].name);
	debugf( "    addr: %d (0x%x)\n", kernel_symbols[ kernel_symbol_top - 1].addr, kernel_symbols[ kernel_symbol_top - 1 ].addr);
	debugf( "    size: %d (0x%x)\n", kernel_symbols[ kernel_symbol_top - 1].size, kernel_symbols[ kernel_symbol_top - 1 ].size); */
}

kdebug_symbol * kdebug_get_symbol_array( void ){
	return kernel_symbols;
}

char * kdebug_get_function_at( uint32_t addr ) {
	char * ret_val = kdebug_symbol_cannot_find;

	for( int i = 0; i<KDEBUG_MAX_SYMBOLS; i++ ) {
		if( kernel_symbols[i].size == 0 ) continue; 

		if( addr >= kernel_symbols[i].addr ) {
			if( addr < ( kernel_symbols[i].addr + kernel_symbols[i].size) ) {
				ret_val = kernel_symbols[i].name;
			}
		}
	}

	return ret_val;
}

kdebug_symbol * kdebug_get_symbol( char * name ) {
	kdebug_symbol * ret = NULL;

	for( int i = 0; i < KDEBUG_MAX_SYMBOLS; i++ ) {
		if( kernel_symbols[i].name[0] == 0 ) continue;

		if( strcmp( kernel_symbols[i].name, name ) == 0 ) {
			ret = kernel_symbols + i;
		}
	}

	return ret;
}

uint32_t kdebug_get_symbol_addr( char * name ) {
	uint32_t ret = 0;

	kdebug_symbol * sym = kdebug_get_symbol( name );

	if( sym != NULL ) {
		ret = sym->addr;
	}

	return ret;
}

char * kdebug_peek_at( uint32_t addr ) {
	printf( "\nLooking at 0x%08X\n", addr );
	debugf( "\nLooking at 0x%08X\n", addr );

	uint8_t *ptrn = (uint8_t *)addr;
	char *ptr = (char *)addr;

	for( int x = 0; x < 10; x++ ) {
		debugf( "0x%08X    %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X    %c%c%c%c%c%c%c%c%c%c\n",
		addr + (x * 10), 
		*(ptrn + 9), *(ptrn + 8), *(ptrn + 7), *(ptrn + 6), *(ptrn + 5), *(ptrn + 4), *(ptrn + 3), *(ptrn + 2), *(ptrn + 1), *(ptrn + 0), 
		peek_char( *(ptr + 9) ), peek_char( *(ptr + 8) ), peek_char( *(ptr + 7) ), peek_char( *(ptr + 6) ), peek_char( *(ptr + 5) ), peek_char( *(ptr + 4) ), peek_char( *(ptr + 3) ), peek_char( *(ptr + 2) ), peek_char( *(ptr + 1) ), peek_char( *(ptr + 0) ) );

		printf( "0x%08X    %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X    %c%c%c%c%c%c%c%c%c%c\n",
		addr + (x * 10), 
		*(ptrn + 9), *(ptrn + 8), *(ptrn + 7), *(ptrn + 6), *(ptrn + 5), *(ptrn + 4), *(ptrn + 3), *(ptrn + 2), *(ptrn + 1), *(ptrn + 0), 
		peek_char( *(ptr + 9) ), peek_char( *(ptr + 8) ), peek_char( *(ptr + 7) ), peek_char( *(ptr + 6) ), peek_char( *(ptr + 5) ), peek_char( *(ptr + 4) ), peek_char( *(ptr + 3) ), peek_char( *(ptr + 2) ), peek_char( *(ptr + 1) ), peek_char( *(ptr + 0) ) );

		ptr = ptr + 10;
		ptrn = ptrn + 10;
	}

	printf( "\n" );
}

void k_log( uint32_t system_id, uint32_t level, char * message, ... ) {
	va_list args;

	debug_out_on();

	printf( "[%s] ", sys_text[ system_id ] );
	va_start( args, message );
	vprintf_( message, args ); 
	va_end( args );
	printf( "\n" );

	debug_out_off();
}


char peek_char( char c ) {
	if( (c > 31) && (c < 127) ) {
		return c;
	} else {
		return '.';
	}
}

profile_information profile_from_latest_run;

void profile_start( void ) {
	profile_from_latest_run.start = get_timer_counter();
	profile_from_latest_run.stop = 0;
	profile_from_latest_run.length = 0;
}

void profile_stop( void ) {
	profile_from_latest_run.stop = get_timer_counter();
	profile_from_latest_run.length = profile_from_latest_run.stop - profile_from_latest_run.start;
}

profile_information * get_profile_information( void ) {
	return &profile_from_latest_run;
}

void profile_test( void ) {
	profile_test_run( 0xFFFFFFFF );
	profile_test_run( 0xFFFFFFFF / 2 );
	profile_test_run( 0xFFFFFFFF / 0xF );
}

void profile_test_run( uint32_t num_of_nops ) {
	uint32_t count;
	profile_information * test_info = get_profile_information();

	profile_start();
	for( count = 0; count < num_of_nops; count++ ) {
		asm( "nop" );
	}
	profile_stop();

	debugf( "\nProfile Test : 0x%08X\n", num_of_nops );
	debugf( "-------------------------------------------------------------\n" );
	debugf( "profile.start = 0x%08X\n", test_info->start );
	debugf( "profile.stop = 0x%08X\n", test_info->stop );
	debugf( "profile.length = 0x%08X / %d ticks / %d milliseconds\n", test_info->length, test_info->length, (test_info->length * 10) );
}

char * strcat( char * dest, char * src ) {
	char *rdest = dest;

    while (*dest)
      dest++;
    while (*dest++ = *src++)
      ;
    return rdest;
}

// lifted from apple
char * strstr(register char *string, char *substring)
{
    register char *a, *b;

    /* First scan quickly through the two strings looking for a
     * single-character match.  When it's found, then compare the
     * rest of the substring.
     */

    b = substring;
    if (*b == 0) {
	return string;
    }
    for ( ; *string != 0; string += 1) {
	if (*string != *b) {
	    continue;
	}
	a = string;
	while (1) {
	    if (*b == 0) {
		return string;
	    }
	    if (*a++ != *b++) {
		break;
	    }
	}
	b = substring;
    }
    return NULL;
}
