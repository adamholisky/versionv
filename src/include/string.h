#if !defined(STRINGH_INCLUDED)
#define STRINGH_INCLUDED

char * strcat( char * dest, char * src );
char * strstr(register char *string, char *substring);
void * memcpy (void *dest, const void *src, size_t len);
char *strcpy(char *dest, const char *src);
int strcmp (const char * s1, const char * s2);
int atoi(const char* str);
size_t strlen(const char *str);

#endif