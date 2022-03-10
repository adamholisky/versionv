#ifndef VV_DEV_HEADER_WRAP
#define VV_DEV_HEADER_WRAP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>

#define VV_DEV_OPTIONAL_MAIN( name )	int main( void )

#define vv_malloc( size )			malloc( size )
#define vv_free( ptr )				asm("nop")
#define vv_printf( ... )			printf( __VA_ARGS__ )
#endif