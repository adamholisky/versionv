#if !defined(INTERRUPTS_INCLUDED)
#define INTERRUPTS_INCLUDED

#define INT_0 0x8E00     // 1000111000000000 = present, ring0, int_gate
#define INT_3 0xEE00     // 1110111000000000 = present, ring3, int_gate

#define ALL       0xFF
#define TIMER     0
#define KEYBOARD  1
#define CASCADE   2
#define COM2_4    3
#define COM1_3    4
#define LPT       5
#define FLOPPY    6
#define FREE7     7
#define CLOCK     8
#define FREE9     9
#define FREE10    10
#define FREE11    11
#define PS2MOUSE  12
#define COPROC    13
#define IDE_1     14
#define IDE_2     15

#define PIC_PRIMARY			0x20
#define PIC_PRIMARY_DATA	0x21
#define PIC_SECONDARY		0xA0
#define PIC_SECONDARY_DATA	0xA1
#define PIC_EOI				0x20

#define ICW1_INIT    0x10               // required for PIC initialisation
#define ICW1_EDGE    0x08               // edge triggered IRQs
#define ICW1_SINGLE  0x02               // only MASTER (not cascaded)
#define	ICW1_ICW4    0x01               // there IS an ICW4 control word

#define ICW4_SFNM    0x10               // Special Fully Nested Mode
#define ICW4_BUFFER  0x08               // Buffered Mode
#define ICW4_MASTER  0x04               // this is the Master PIC
#define ICW4_AEOI    0x02               // Auto EOI
#define ICW4_8086    0x01               // 80/86 Mode

typedef struct {
	uint16_t            low_offset;                         // low nibble of offset to handler of interrupt 
	uint16_t            selector;                           // GDT selector used 
	uint16_t            settings;                           // settings for int 
	uint16_t            high_offset;                        // high nibble to handler code 
}  __attribute__ ((packed)) x86_interrupt;

typedef struct {
     uint16_t           limit;                             // limit or Size of IDT 
     x86_interrupt  	*base;                    // a pointer to the base of the IDT 
} __attribute__ ((packed)) idtr;

typedef struct {
	uint16_t	gs;
	uint16_t	gs_padding;
	uint16_t	fs;
	uint16_t	fs_padding;
	uint16_t	es;
	uint16_t	es_padding;
	uint16_t	ds;
	uint16_t	ds_padding;
	
	uint32_t	edi;
	uint32_t	esi;
	uint32_t	ebp;
	uint32_t	esp;
	uint32_t	ebx;
	uint32_t	edx;
	uint32_t	ecx;
	uint32_t	eax;

	uint32_t	_esp;
	
	uint32_t	err;
	uint32_t	eip;
	uint16_t	cs;
	uint16_t	cs_padding;
	uint32_t	eflags;
	uint32_t  	useresp;
	uint32_t	ss;
} interrupt_stack ;

union x86flags {
	uint32_t	all_flags;

	struct {
		uint32_t cf:1; 
		uint32_t must_be_1:1;
		uint32_t pf:1;
		uint32_t must_be_0_1:1;
		uint32_t af:1; 
		uint32_t must_be_0_2:1;
		uint32_t zf:1;
		uint32_t sf:1;
		uint32_t tf:1;  
		uint32_t ifen:1;  
		uint32_t df:1;
		uint32_t of:1;
		uint32_t iopl:2; 
		uint32_t nt:1;
		uint32_t must_be_0_3:1;
		uint32_t rf:1; 
		uint32_t vm:1;
		uint32_t ac:1;
		uint32_t vif:1;
		uint32_t vip:1; 
		uint32_t id:1;   
		uint32_t must_be_0_4:2;  
		uint32_t must_be_0_5:4; 
	} eflags_bits;
};

extern void interrupt_0( void );
extern void interrupt_1( void );
extern void interrupt_2( void );
extern void interrupt_3( void );
extern void interrupt_4( void );
extern void interrupt_5( void );
extern void interrupt_6( void );
extern void interrupt_7( void );
extern void interrupt_8( void );
extern void interrupt_9( void );
extern void interrupt_10( void );
extern void interrupt_11( void );
extern void interrupt_12( void );
extern void interrupt_13( void );
extern void interrupt_14( void );
extern void interrupt_16( void );
extern void interrupt_17( void );
extern void interrupt_18( void );
extern void interrupt_19( void );
extern void interrupt_0x20( void );
extern void interrupt_0x21( void );
extern void interrupt_0x22( void );
extern void interrupt_0x23( void );
extern void interrupt_0x24( void );
extern void interrupt_0x25( void );
extern void interrupt_0x26( void );
extern void interrupt_0x27( void );
extern void interrupt_0x28( void );
extern void interrupt_0x29( void );
extern void interrupt_0x2A( void );
extern void interrupt_0x2B( void );
extern void interrupt_0x2C( void );
extern void interrupt_0x2D( void );
extern void interrupt_0x2E( void );
extern void interrupt_0x2F( void );
extern void interrupt_0x30( void );
extern void interrupt_0x31( void );
extern void interrupt_0x32( void );
extern void interrupt_0x99( void );

void interrupts_initalize( void );
void interrupt_default_handler( unsigned long interrupt_num, unsigned long route_code, interrupt_stack ** _stack );
void load_idtr( void );
void add_interrupt( int number, void (*handler)(), uint32_t dpl );
void load_exceptions();
void remap_pic( int pic1, int pic2 );
void interrupt_mask_irq( uint8_t irq );
void interrupt_unmask_irq( uint8_t irq );
uint32_t get_timer_counter( void );
void replace_stack_on_int_exit( interrupt_stack * stack );


#endif