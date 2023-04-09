#if !defined(AHCI_INCLUDED)
#define AHCI_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

void ahci_initalize( void );
bool ahci_read_sector( uint32_t sector, uint32_t *buffer );

#ifdef __cplusplus
}
#endif

#endif