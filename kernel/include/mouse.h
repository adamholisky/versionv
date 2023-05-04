#if !defined(MOUSE_INCLUDED)
#define MOUSE_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

void mouse_write( uint8_t byte );
uint8_t mouse_read( void );
void mouse_wait( uint8_t type );
void mouse_initalize( void );
void mouse_handler( void );


#ifdef __cplusplus
}
#endif

#endif