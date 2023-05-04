#include <kernel.h>
#include <mouse.h>
#include <vui/vui.h>

volatile uint8_t mouse_cycle = 0;
volatile int8_t mouse_byte[ 3 ];
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
	uint8_t _time_out=100000;
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

    
	
    klog( "Done. Status: %d \n", status );

    log_entry_exit();
} 

void mouse_handler( void ) {
    //log_entry_enter();

	volatile char move_x = 0;
	volatile char move_y = 0;
	mouse_byte[ mouse_cycle++ ] = inportb( 0x60 );

	if( mouse_cycle == 3 ) {
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

		if( !(mouse_byte[0] & 0x20) ) {
			move_y |= 0xFFFFFF00; 				//delta-y is a negative value
		}

		if( !(mouse_byte[0] & 0x10) ) {
			move_x |= 0xFFFFFF00; 				//delta-x is a negative value
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

		if( move_x > 0 ) {
			vui_mouse_move( cursor_right, move_x );
		} else if( move_x < 0 ) {
			vui_mouse_move( cursor_left, move_x * -1);
		}

		if( move_y > 0 ) {
			vui_mouse_move( cursor_up, move_y );
		} else if( move_y < 0 ) {
			vui_mouse_move( cursor_down, move_y * -1 );
		}
	}

	//debug_f( ". %d\n", inportb( 0x60 ) );
	//pic_acknowledge( 0x2C );

   // log_entry_exit();
}