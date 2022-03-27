#include "kernel.h"
#include "serial_client.h"

char *data;

void serial_client_initalize( void ) {
	data = kmalloc( 1024 );
	set_data_buffer( data );
	set_data_ready_callback( handle_data_ready );
}

void handle_data_ready( uint32_t size ) {
	set_data_is_being_read( true );

	debugf( "\nsize: %d\n", size );

	*(data + size ) = '\0';
	debugf( "%s", data );

	set_data_is_being_read( false );
}

void ssvv_send( char * cmd ) {
	int len = strlen( cmd );

	debugf( "\nlen: %d\n", len );
	for( int i = 0; i < len; i++ ) {
		serial_write_port( cmd[i], COM1 );
	}

	serial_write_port( 26, COM1 );
}