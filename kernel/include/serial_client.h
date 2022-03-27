#ifndef HEADER_SERIALCLIENT
#define HEADER_SERIALCLIENT

#include "kernel.h"

void serial_client_initalize( void );
void handle_data_ready( uint32_t size );
void ssvv_send( char * cmd );

#endif