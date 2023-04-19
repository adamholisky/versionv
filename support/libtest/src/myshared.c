#include <stdio.h>

void my_lib_call( void );

void my_lib_call( void ) {
    printf( "Hello shared library, world!\n" );
}