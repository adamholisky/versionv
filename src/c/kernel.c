#include "kernel.h"
#include "multiboot.h"
#include "elf.h"
#include "interrupts.h"
#include "pci.h"
#include "intel8254.h"
#include "vv_list.h"
#include "ata.h"
#include <cpuid.h>
#include "syscall.h"

#define END_IMMEDIATELY
#undef kdebug_process_loader

typedef void (*make_call)(bool);

void kernel_main( unsigned long mb_magic, multiboot_info_t * mb_info ) 
{
	int x = 0;
	
	multiboot_initalize( mb_magic, mb_info );
	term_initalize();
	initalize_serial();
 
	printf( "VersionV\n" );
	k_log( sys_kernel, level_info, "\nVersionV Serial Out\n" );

	memory_initalize();
	elf_initalize( (uint32_t)kernel_main );
	interrupts_initalize();

	pci_initalize();
	intel8254_initalize();

	ata_initalize();

	process_initalize();

	#ifdef kdebug_paging

	char * page_fault_addr = NULL;
	page_fault_addr = (char *)0xA0000000;	
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

	modules_initalize();

	while( true ) {
		sched_yield();
	}

	#ifdef END_IMMEDIATELY

	klog( "Shutdown via END_IMMEDIATELY at end of kernel.c.\n");
	outportb( 0xF4, 0x00 );

	#endif

	klog( "\n\nEnd of line." );

	while( true ) { x = x - x + 1; }
}

int register_io_device( char * name, void (*read_func)(), void (*write_func)() ) {
	
}

uint32_t write( int file, void * buff, uint32_t count ) {

}