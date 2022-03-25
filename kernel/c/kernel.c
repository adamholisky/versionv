#include "kernel.h"
#include "multiboot.h"
#include "elf.h"
#include "task.h"
#include "interrupts.h"
#include "pci.h"
#include "intel8254.h"
#include "vv_list.h"
#include "ata.h"
#include <cpuid.h>
#include "task.h"
#include "syscall.h"
#include "debug.h"

#define END_IMMEDIATELY

void kernel_main( unsigned long mb_magic, multiboot_info_t * mb_info ) 
{
	int x = 0;
	
	multiboot_initalize( mb_magic, mb_info );
	term_initalize();
	initalize_serial();
 
	printf( "\x1b[0;31;49mVersionV\x1b[0;0;0m\n" );
	debugf( "\x1b[0;31;49mVersionV\x1b[0;0;0m Serial Out\n" );

	memory_initalize();
	elf_initalize( (uint32_t)kernel_main );
	interrupts_initalize();
	serial_enable_interrupts();
	task_initalize();
	//process_initalize();
	modules_initalize();

	pci_initalize();
	intel8254_initalize();
	//ata_initalize();

	page_fault_test();

	debugf( "Serial console active.\n" );
	debugf( "\nVersionV: " );

	bool show_carrot = false;

	while( true ) {
		if( serial_buffer_is_ready() ) {
			char c = serial_buffer_get_char();

			debugf( "%c", c );
			
			switch( c ) {
				case 'a':
					run_module_by_name( "alpha" );
					break;
				case 'b':
					run_module_by_name( "beta" );
					break;
				case 'p':
					run_module_by_name( "ps" );
					break;
				case 'q':
					debugf( "\nGoodbye, Dave.\n");
					outportb( 0xF4, 0x00 );
					break;
			}

			debugf( "\n" );
			show_carrot = true;
		}
		sched_yield();

		if( show_carrot ) {
			debugf( "VersionV: " );
			show_carrot = false;
		}
		
		//debugf( "!" );
	}

	#ifdef END_IMMEDIATELY

	klog( "Shutdown via END_IMMEDIATELY at end of kernel.c.\n");
	outportb( 0xF4, 0x00 );

	#endif

	#ifdef kdebug_paging

	char * page_fault_addr = NULL;
	page_fault_addr = (char *)KERNEL_VIRT_HEAP_BASE;	
	klog( "String at 0x%08X: \"%s\"\n", page_fault_addr, page_fault_addr );
	page_fault_addr = (char *)page_allocate( 1 );
	klog( "String at 0x%08X: \"%s\"\n", page_fault_addr, page_fault_addr );

	#endif

	#ifdef kdebug_cpuid

	uint32_t cpuid_return = 0;
	uint32_t eax, unused;
	__get_cpuid( 1, &eax, &unused, &unused, &cpuid_return );
	klog( "CPUID edx feature output:\n" );
	debugf_bit_array( cpuid_return );

	#endif

	#ifdef kdebug_profile_test

	profile_test();

	#endif

	klog( "\n\nEnd of line." );

	while( true ) { x = x - x + 1; }
}

int register_io_device( char * name, void (*read_func)(), void (*write_func)() ) {
	
}

uint32_t write( int file, void * buff, uint32_t count ) {

}

