#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "bootstrap.h"

size_t strlen(const char *str)
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

uint64_t __udivmoddi4(uint64_t num, uint64_t den, uint64_t *rem_p)
 {
   uint64_t quot = 0, qbit = 1;
 
   if ( den == 0 ) {
     return 1/((unsigned)den); /* Intentional divide by zero, without
                                  triggering a compiler warning which
                                  would abort the build */
   }
 
   /* Left-justify denominator and count shift */
   while ( (int64_t)den >= 0 ) {
     den <<= 1;
     qbit <<= 1;
   }
 
   while ( qbit ) {
     if ( den <= num ) {
       num -= den;
       quot += qbit;
     }
     den >>= 1;
     qbit >>= 1;
   }
 
   if ( rem_p )
     *rem_p = num;
 
   return quot;
 }

void * memcpy (void *dest, const void *src, size_t len)
{
  char *d = dest;
  const char *s = src;
  while (len--)
    *d++ = *s++;
  return dest;
}

char *strcpy(char *dest, const char *src)
{
   char *save = dest;
   while(*dest++ = *src++);
   return save;
}

int strcmp (const char * s1, const char * s2)
{
    for(; *s1 == *s2; ++s1, ++s2)
        if(*s1 == 0)
            return 0;
    return *(unsigned char *)s1 < *(unsigned char *)s2 ? -1 : 1;
}

int atoi(const char* str) {
	int result = 0;
	while (isspace(*str))
		str++;
	while (isdigit(*str))
		result = (result * 10) + (*(str++) - '0');
	return result;
}

unsigned long hex2int(char *a, unsigned int len)
{
	int i;
	unsigned long val = 0;

	for(i=0;i<len;i++)
	   if(a[i] <= 57)
		val += (a[i]-48)*(1<<(4*(len-1-i)));
	   else
		val += (a[i]-55)*(1<<(4*(len-1-i)));

	return val;
}