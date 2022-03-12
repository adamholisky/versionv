#include "kernel.h"
#include "string.h"

char * strcat( char * dest, char * src ) {
	char *rdest = dest;

    while( *dest )
      dest++;
    while ( *dest++ = *src++ )
      ;
    
	return rdest;
}

// lifted from apple
char * strstr( register char * string, char * substring ) {
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