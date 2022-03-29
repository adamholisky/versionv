#include "kernel.h"
#include "serial_client.h"

char * data;
bool ssvv_read_is_waiting = false;
bool ssvv_read_data_is_ready = false;
uint8_t * ssvv_read_buff;
uint32_t ssvv_read_size;

void serial_client_initalize( void ) {
	data = kmalloc( 1024 );
	set_data_buffer( data );
	set_data_ready_callback( handle_data_ready );
}

void handle_data_ready( uint32_t size ) {
	set_data_is_being_read( true );

	if( ssvv_read_is_waiting ) {
		memcpy( ssvv_read_buff, data, size );
		ssvv_read_size = size;

		ssvv_read_data_is_ready = true;
	} else {
		debugf( "\nsize: %d\n", size );
		debugf( "%s", data );
	}

	set_data_is_being_read( false );
}

uint32_t ssvv_read( uint8_t * buff ) {
	//
}

void ssvv_send( char * cmd ) {
	int len = strlen( cmd );

	//debugf( "\nlen: %d\n", len );
	for( int i = 0; i < len; i++ ) {
		serial_write_port( cmd[i], COM1 );
	}

	serial_write_port( 26, COM1 );
}

uint32_t ssvv_send_ask( char * cmd, uint8_t * buff, uint32_t size ) {
	uint32_t _size;
	int i = 0;

	ssvv_read_buff = buff;
	ssvv_read_is_waiting = true;
	
	ssvv_send( cmd );

	while( ssvv_read_data_is_ready == false ) {
		;
	}
	
	_size = ssvv_read_size;
	ssvv_read_size = 0;
	ssvv_read_buff = NULL;
	ssvv_read_is_waiting = false;
	ssvv_read_data_is_ready = false;

	return _size;
}

uint32_t ssvv_read_file( char * full_path_to_file, uint8_t * buff ) {
	char cmd[100];
	int32_t size;

	strcpy( cmd, "READ " );
	strcat( cmd, full_path_to_file );

	size = ssvv_send_ask( cmd, buff, 2048 );

	return size;
}

void ssvv_read_file_test( void ) {
	char * buff;
	uint32_t size;

	buff = kmalloc( 14 );

	size = ssvv_read_file( "/home/adam/helloworld.txt", buff );

	for( int i = 0; i < size; i++, buff++ ) {
		debugf( "%c", *buff );
	}
}