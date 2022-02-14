#include "kernel.h"
#include "interrupts.h"

idtr            sIDTR;
x86_interrupt   IDT[256];
uint8_t	        pic1_irq_mask;
uint8_t	        pic2_irq_mask;
bool	        debug_interrupts = false;
bool 	        gpf_fired = false;
bool			can_switch = true;
uint32_t 		timer_var = 0;
uint32_t		timer_counter = 0;

void interrupts_initalize( void ) {
    remap_pic( 0x20, 0x28 );

    add_interrupt(0, interrupt_0, 0);
    add_interrupt(1, interrupt_1, 0);
    add_interrupt(2, interrupt_2, 0);
    add_interrupt(3, interrupt_3, 0);
    add_interrupt(4, interrupt_4, 0);
    add_interrupt(5, interrupt_5, 0);
    add_interrupt(6, interrupt_6, 0);
    add_interrupt(7, interrupt_7, 0);
    add_interrupt(8, interrupt_8, 0);
    add_interrupt(9, interrupt_9, 0);
    add_interrupt(10, interrupt_10, 0);
    add_interrupt(11, interrupt_11, 0);
    add_interrupt(12, interrupt_12, 0);
    add_interrupt(13, interrupt_13, 0);
    add_interrupt(14, interrupt_14, 0);
    add_interrupt(16, interrupt_16, 0);
    add_interrupt(17, interrupt_17, 0);
    add_interrupt(18, interrupt_18, 0);
    add_interrupt(19, interrupt_19, 0);

	add_interrupt( 0x20, interrupt_0x20, 0 );
	add_interrupt( 0x21, interrupt_0x21, 0 );
	add_interrupt( 0x22, interrupt_0x22, 0 );
	add_interrupt( 0x23, interrupt_0x23, 0 );
	add_interrupt( 0x24, interrupt_0x24, 0 );
	add_interrupt( 0x25, interrupt_0x25, 0 );
	add_interrupt( 0x26, interrupt_0x26, 0 );
	add_interrupt( 0x27, interrupt_0x27, 0 );
	add_interrupt( 0x28, interrupt_0x28, 0 );
	add_interrupt( 0x29, interrupt_0x29, 0 );
	add_interrupt( 0x2A, interrupt_0x2A, 0 );
	add_interrupt( 0x2B, interrupt_0x2B, 0 );
	add_interrupt( 0x2C, interrupt_0x2C, 0 );
	add_interrupt( 0x2D, interrupt_0x2D, 0 );
	add_interrupt( 0x2E, interrupt_0x2E, 0 );
	add_interrupt( 0x2F, interrupt_0x2F, 0 );
	add_interrupt( 0x30, interrupt_0x30, 0 );

	// mask everything

	outportb( 0x21, 0xFF );
	outportb( 0xA1, 0xFF );

	uint16_t divisor = 11931;      // Calculate our divisor, default 65535 --> 1193180/hz
    outportb( 0x43, 0x36 );             // Set our command byte 0x36
    outportb( 0x40, divisor & 0xFF );   // Set low byte of divisor
    outportb( 0x40, divisor >> 8 );     // Set high byte of divisor

	// unmask the timer
	interrupt_unmask_irq( 0x20 );
	interrupt_unmask_irq( 0x21 );

    load_idtr();

    asm( "sti" );

	k_log( sys_interrupt, level_info, "Enabled" );

	asm( "int %0" : : "i"(0x30) );
}

void interrupt_default_handler( unsigned long interrupt_num, unsigned long route_code, interrupt_stack * stack ) {
	//dbC();
	//debugf( "interrupt_default_handler:\n    interrupt_num: 0x%X\n    route_code: 0x%0X\n", interrupt_num, route_code );

	if( route_code == 0x01 ) {
        switch( interrupt_num ) {
            case 0:
				printf( "[SYSTEM] Exception: divide by zero.\n" );
                break;
            default:
                debugf( "[SYSTEM] Unhandled exception %02X.\n", interrupt_num );
				debugf( "  eax:  0x%08X  ebx:  0x%08X  ecx:  0x%08X  edx:  0x%08X\n", stack->eax, stack->ebx, stack->ecx, stack->edx );
				debugf( "  esp:  0x%08X  ebp:  0x%08X  esi:  0x%08X  edi:  0x%08X\n", stack->esp, stack->ebp, stack->esi, stack->edi );
				debugf( "  ds:   0x%04X  es:   0x%04X  fs:   0x%04X  gs:   0x%04X\n", stack->ds, stack->es, stack->fs, stack->gs );
				debugf( "  _esp: 0x%08X  cs:   0x%04X  ef:   0x%08X  err:  0x%08X\n", stack->_esp, stack->cs, stack->eflags, stack->err );
				debugf( "  eip:  0x%08X\n", stack->eip );
				uint32_t * pointer = (uint32_t *)stack;
				for( int i = -10; i < 5; i++ ) {
					//debugf( "0x%08X:    0x%08X\n", (pointer + i), *(pointer + i) );
				}
				asm( "cli" );
				asm( "hlt" );
        }
    }

	if( route_code == 0x02 ) {
        switch( interrupt_num ) {
			case 0x20:
				//debugf( "." );
				timer_counter++;
				if( timer_var < 101 ) {  // default 19
					timer_var++;
				} else {
					//debugf( "!" );
					timer_var = 0;
				}
				break;
		}
	}
	
	// Acknowledge the interrupt with the pic
	if( interrupt_num > 0x28 ) {
		outportb( 0xA0, 0x20 );
	}

	outportb( 0x20, 0x20 );
}

uint32_t get_timer_counter( void ) {
	return timer_counter;
}

void load_idtr( void ) {
    sIDTR.limit  = 256*(sizeof(x86_interrupt)-1);
    sIDTR.base   = IDT;

	idtr *IDTRptr = &sIDTR;

	//debug_f( "IDTR: 0x%08X\n", IDTRptr );

    asm volatile("lidt (%0) ": : "r"(IDTRptr));
}

void remap_pic(int pic1, int pic2) {
	uint8_t primary_data;
	uint8_t secondary_data;

	primary_data = inportb( PIC_PRIMARY_DATA );                     // save state of MASTER DATA
	secondary_data = inportb( PIC_SECONDARY_DATA );                      // save state of SLAVE DATA

	outportb( PIC_PRIMARY, PIC_EOI );                      // Send EOI | resets the chip

	outportb( PIC_PRIMARY, ICW1_INIT + ICW1_ICW4 );      // ICW1 control word setup | just basic PIC stuff
	outportb( PIC_SECONDARY, ICW1_INIT + ICW1_ICW4 );       // see pic.h for more details about the values

	outportb( PIC_PRIMARY_DATA, pic1 );                 // ICW2 maps IRQs 0-7 to whatever kernel passes
	outportb( PIC_SECONDARY_DATA, pic2 );                  // and same here except with IRQs 8-15 

	outportb( PIC_PRIMARY_DATA, 0x04 );                 // ICW3 
	outportb( PIC_SECONDARY_DATA, 0x02 );

	outportb( PIC_PRIMARY_DATA, ICW4_8086 );            // ICW4 control word setup
	outportb( PIC_SECONDARY_DATA, ICW4_8086 );

	outportb( PIC_PRIMARY_DATA, primary_data );                    // restore both MASTER DATA
	outportb( PIC_SECONDARY_DATA, secondary_data );                     // restore SLAVE DATA
}

void add_interrupt( int number, void (*handler)(), uint32_t dpl ) {
	 uint16_t selector = 0x08;
	 uint16_t settings = 0;
     uint32_t offset = (uint32_t)handler;

	 /* get CS selector */
     asm volatile("movw %%cs,%0" :"=g"(selector));

	 /* set settings options depending on dpl */
	 switch(dpl) {
	 	case 0: 
			settings = INT_0;
			break;
	 	case 1:
	 	case 2:
	 	case 3: 
			settings = INT_3;
			break;
	 }
	 
	 /* set actual values of int */
	 IDT[number].low_offset   = (offset & 0xFFFF);
	 IDT[number].selector     = selector;
	 IDT[number].settings     = settings;
     IDT[number].high_offset  = (offset >> 16);
}

/* makes IRQ unavailable so it can't fire an interrupt */
void interrupt_mask_irq( uint8_t irq ) {
	if( irq == ALL ) {
		outportb( PIC_PRIMARY_DATA, 0xFF );
		outportb( PIC_SECONDARY_DATA, 0xFF );
		pic1_irq_mask = 0xFF;
		pic2_irq_mask = 0xFF;
	} else {
		irq = irq | (1 << irq);
		if( irq < 8 )
			outportb( PIC_PRIMARY_DATA, irq & 0xFF );
		else
			outportb( PIC_SECONDARY_DATA, irq >> 8 );
	}
}

/* opposite of above */
void interrupt_unmask_irq( uint8_t irq ) {
	if( irq == ALL ) {
		outportb( PIC_PRIMARY_DATA, 0x00 );
		outportb( PIC_SECONDARY_DATA, 0x00 );
		pic1_irq_mask = 0x00;
		pic2_irq_mask = 0x00;
	} else {
		irq = irq & (1 << irq);

		if( irq < 8 ) {
			pic1_irq_mask = pic1_irq_mask ^ (1 << irq);
			outportb( PIC_PRIMARY_DATA, pic1_irq_mask );
		}
		else {
			pic2_irq_mask = pic2_irq_mask ^ (1 << irq);
			outportb( PIC_SECONDARY_DATA, pic2_irq_mask );
		}
	}
}