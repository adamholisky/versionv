#include <kernel.h>
#include <mouse.h>
#include <vui/vui.h>

uint8_t mouse_cycle = 0;
uint8_t mouse_bytes[ 3 ];
bool middle_button = false;
bool right_button = false;
bool left_button = false;


uint8_t mouse_read( void ) {
	mouse_wait(0);
	return inportb(0x60);
}

void mouse_write( uint8_t byte ) {
	mouse_wait(1);
	outportb(0x64, 0xD4);
	
    mouse_wait(1);
	outportb(0x60, byte);
}

void mouse_wait( uint8_t type ) {
	uint32_t _time_out=100000;
	if(type==0) {
		while(_time_out--) {
			if((inportb(0x64) & 1)==1) {
				return;
			}
		}

		return;
	} else {
		while(_time_out--) {
			if((inportb(0x64) & 2)==0) {
				return;
			}
		}

		return;
	}
}

void mouse_initalize( void ) { 
    log_entry_enter();

	uint8_t status;

	// Port: 64
    // Command: A8 -- Enable second PS2 port
	mouse_wait(1);
	outportb(0x64, 0xA8);

	// Enable interrupts

    // Port: 64
    // Command: 20 -- Read byte 0 from internal RAM
	mouse_wait(1);
	outportb(0x64, 0x20);

    // Port: 60 -- Read controller config byte from port 60 (with an |2 applied)
	mouse_wait(0);
	status=(inportb(0x60) | 2);

    // Port: 64
    // Command 60 -- Write controller config byte from port 60
	mouse_wait(1);
	outportb(0x64, 0x60);

    // Write controller config byte prev saved and modified
	mouse_wait(1);
	outportb(0x60, status);

	// Use default settings
	mouse_write(0xF6);
	mouse_read();

	// Enable the mouse
	mouse_write(0xF4);
	mouse_read();

    mouse_cycle = 0;
	mouse_bytes[0] = 0;
	mouse_bytes[1] = 0;
	mouse_bytes[2] = 0;
	
    klog( "Done. Status: %d \n", status );

    log_entry_exit();
} 

void mouse_handler( void ) {
    //log_entry_enter();

	int move_x = 0;
	int move_y = 0;
	uint8_t in_byte = inportb( 0x60 );

	switch( mouse_cycle ) {
		case 0:
			if( test_bit(in_byte,3) ) {
				mouse_bytes[0] = in_byte;
				mouse_cycle++;
			} else {
				klog( "bit 3 is NOT set!\n" );
			}
			break;
		case 1:
			mouse_bytes[1] = in_byte;
			mouse_cycle++;
			break;
		case 2:
			mouse_bytes[2] = in_byte;
			mouse_cycle++;
			break;
	}

	if( mouse_cycle == 3 ) {
		mouse_cycle = 0;

		//klog( "mb[0] = 0x%X     mb[1] = 0x%X    mb[2] = 0x%X\n", mouse_bytes[0], mouse_bytes[1], mouse_bytes[2] );

		move_x = mouse_bytes[1];
		move_y = mouse_bytes[2];

		if( test_bit(mouse_bytes[0], 4) ) {
			move_x = move_x * -1;
		}

		if( test_bit(mouse_bytes[0], 5) ) {
			move_y = move_y * -1;
		}

		//klog( "x: %d, y: %d\n", move_x, move_y );
	}

	return;

	

/* 	if( mouse_cycle == 3 ) {
		move_x = mouse_byte[1];
		move_y = mouse_byte[2];
		mouse_cycle = 0;
		middle_button = false;
		right_button = false;
		left_button = false;

		if( (mouse_byte[0] & 0x80) || (mouse_byte[0] & 0x40) ) {
			//debug_f( "Dropped due to overflow\n" );
			//pic_acknowledge( 0x2C );
			return;
		}

		if( mouse_byte[0] & 0x4 ) {
			middle_button = true;
		}

		if( mouse_byte[0] & 0x2 ) {
			right_button = true;
		}

		if( mouse_byte[0] & 0x1 ) {
			left_button = true;
		}

		//debug_f( "At 3: (%d, %d) with M: %d, R: %d, L: %d\n", move_x, move_y, middle_button, right_button, left_button );

		klog( "group move_x: %d, move_y: %d\n", move_x, move_y );

		if( move_x > 0 ) {
			vui_mouse_move( cursor_right, move_x );
		} else if( move_x < 0 ) {
			vui_mouse_move( cursor_left, move_x);
		}

		if( move_y > 0 ) {
			vui_mouse_move( cursor_up, move_y );
		} else if( move_y < 0 ) {
			vui_mouse_move( cursor_down, move_y );
		} 
	}
 */
	//debug_f( ". %d\n", inportb( 0x60 ) );
	//pic_acknowledge( 0x2C );

   // log_entry_exit();
}