#if !defined(DEVICE_INCLUDED)
#define DEVICE_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <kernel.h>

#define DEVICE_DEFAULT_BUFFER_SIZE 4096

void init_devices( void );



#ifdef __cplusplus
}
#endif

#endif