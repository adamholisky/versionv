#include <stdint.h>
#include <stdbool.h>
#include "bootstrap.h"
#include "serial.h"
#include "debug.h"

uint32_t default_port;
char serial_in_buffer[256];
uint32_t buffer_add_loc;
uint32_t buffer_read_loc;
void (*data_ready_callback)(int);
char *data_buff;
uint32_t data_buff_loc;
bool data_is_being_read;
int32_t data_buffer_task;
bool data_ready;

void initalize_serial(void)
{
	data_buff = NULL;
	data_buff_loc = 0;
	data_is_being_read = false;
	data_ready = false;

	// DO NOT PUT KLOG FUNCTIONS HERE
	serial_setup_port(COM1);
	serial_setup_port(COM2);
	serial_setup_port(COM4);

	default_port = COM1;

	for( int i = 0; i < 256; i++ ) {
		serial_in_buffer[i] = '\0';
	}

	buffer_add_loc = 0;
	buffer_read_loc = 0;
}

void serial_setup_port(uint32_t port)
{
	outportb(port + 1, 0x00); // Disable all interrupts
	outportb(port + 3, 0x80); // Enable DLAB (set baud rate divisor)
	outportb(port + 0, 0x03); // Set divisor to 3 (lo byte) 38400 baud
	outportb(port + 1, 0x00); //                  (hi byte)
	outportb(port + 3, 0x03); // 8 bits, no parity, one stop bit
	outportb(port + 2, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
	outportb(port + 4, 0x0B); // IRQs enabled, RTS/DSR set
}

void serial_enable_interrupts( void ) {
	outportb(COM1 + 1, 0x01);
	outportb(COM2 + 1, 0x01);
}

void serial_set_default_port(uint32_t port)
{
	default_port = port;
}

void serial_write_port(char c, uint32_t port)
{
	if (port == serial_use_default_port)
	{
		port = default_port;
	}

	// Make sure the transmit queue is empty
	while((inportb(port + 5) & 0x20) == 0) {
		;
	}

	outportb(port, c);
}

char serial_read_port(uint32_t port)
{
	char c = '\0';

	if (port == serial_use_default_port)
	{
		port = default_port;
	}

	// Wait until we can get something
	while ((inportb(port + 5) & 1) == 0)
	{
		;
	}

	c = inportb( port );

	if( port == COM1 ) {
		while( data_is_being_read ) {
			;
		}

		data_buff[ data_buff_loc ] = c;
		data_buff_loc++;

		if( c == 26 ) {
			data_ready_callback( data_buff_loc );

			data_buff_loc = 0;
		}
	} else { // this is com2
		serial_in_buffer[ buffer_add_loc ] = c;
		buffer_add_loc++;

		if( buffer_add_loc == 256 ) {
			buffer_add_loc = 0;
		}
	}

	return c;
}

bool serial_buffer_is_ready( void ) {
	return serial_in_buffer[ buffer_read_loc ] != '\0' ? true : false;
}

char serial_buffer_get_char( void ) {
	char ret_c = serial_in_buffer[ buffer_read_loc ];

	serial_in_buffer[ buffer_read_loc ] = '\0';
	buffer_read_loc++;

	if( buffer_read_loc == 256 ) {
		buffer_read_loc = 0;
	}

	return ret_c;
}

void set_data_ready_callback( void *f ) {
	data_ready_callback = f;
}

void set_data_buffer( char *buff ) {
	data_buff = buff;
}

void set_data_is_being_read( bool b ) {
	data_is_being_read = b;
}
