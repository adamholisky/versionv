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
#include "serial_client.h"
#include "debug.h"
#include "callback.h"
#include "keyboard.h"
#include "observer.h"
#include <ftp.h>
#include <modules.h>

#define END_IMMEDIATELY
#define SERIAL_CONSOLE_ACTIVE false
#define TRIGGER_DIVIDE_BY_ZERO false

void kernel_main( unsigned long mb_magic, multiboot_info_t *mb_info ) {
	int x = 0;
	char c = ' ';
	bool process_keypress;

	multiboot_initalize( mb_magic, mb_info );
	term_initalize();
	initalize_serial();

	printf( "\x1b[0;31;49mVersionV\x1b[0;0;0m\n" );
	debugf( "\x1b[0;31;49mVersionV\x1b[0;0;0m Serial Out\n" );

	//multiboot_echo_to_serial();
	memory_initalize();
	kdebug_initalize();

	uint32_t km = reinterpret_cast<uint32_t>(kernel_main);
	elf_initalize( km );
	interrupts_initalize();
	observer_initalize();
	memory_test();
	//dump_active_pt();

	#ifdef DGRAPHICS_ON
		vga_initalize();
		console_init( "default-console", 3, 3, 7 * 120, 14 * 50, 0x00282C34, 0x00AAAAAA );
		console_draw();
	#endif

/* 	uint32_t cpuid_return = 0;
	uint32_t eax, unused;
	__get_cpuid( 1, &eax, &unused, &unused, &cpuid_return );
	klog( "CPUID edx feature output:\n" );
	debugf_bit_array( cpuid_return ); */

	serial_enable_interrupts();
	task_initalize();
	//process_initalize();
	modules_initalize();

	pci_initalize();
	intel8254_initalize();
	//ata_initalize();

	//page_fault_test();
	serial_client_initalize();

	observer_test();

	keyboard_initalize();

	if( TRIGGER_DIVIDE_BY_ZERO ) {
		asm volatile( 
			"movl 0, %eax \n\t"
			"movl 0, %ecx \n\t"
			"div %ecx \n\t"
		);
	}

	//multiboot_echo_to_serial();

	//ftp_test();

	FTP ftp;

	ftp.init();
	ftp.login( "vv", "vv" );
	ftp.cwd( "/usr/local/osdev/versions/v/modules_final/build" );
	ftp.get_file( "reference.vvs" );
	
	Module m;
	m.load( (uint32_t *)ftp.data_buffer );

	klog( "Starting run of 0x%x.\n", m.task_id );
	task_initalize_and_run( m.task_id );
	sched_yield();
	klog( "Post run.\n" );

	debugf( "\nGoodbye, Dave.\n" );
	outportb( 0xF4, 0x00 );

	if( SERIAL_CONSOLE_ACTIVE ) {
		debugf( "Serial console active.\n" );
		debugf( "\nVersionV: " );
	} else {
		printf( "\nVersionV: ");
	}

	bool show_prompt = false;

	while( true ) {
		c = ' ';
		process_keypress = false;

		if( SERIAL_CONSOLE_ACTIVE ) {
			if( serial_buffer_is_ready() ) {
				c = serial_buffer_get_char();
				process_keypress = true;

				debugf( "%c", c );
			}
		} else {
			if( c = keyboard_get_char() ) {
				printf( "%c", c );

				process_keypress = true;
			}
		}

		if( process_keypress ) {
			switch( c ) {
				case 'a':
					run_module_by_name( "alpha" );
					break;
				case 'b':
					run_module_by_name( "beta" );
					break;
				case 'g':
					run_module_by_name( "gamma" );
					break;
				case 'p':
					run_module_by_name( "ps" );
					break;
				case 'f':
					ftp_test();
					break;
				case 'q':
					debugf( "\nGoodbye, Dave.\n" );
					outportb( 0xF4, 0x00 );
					break;
				case 't':
					ssvv_exec_test_app();
					break;
				case '1':
					ssvv_send( "ls /usr/local/osdev/versions/v" );
					break;
				case '2':
					ssvv_send( "vv:close-connection" );
					break;
				case '3':
					ssvv_read_file_test();
					break;
				case '4':
					callback_test_run();
					break;
				case '5':
					console_scroll_forever_test();
					break;
			}

			show_prompt = true;
		}

		sched_yield();

		if( process_keypress ) {
			if( SERIAL_CONSOLE_ACTIVE ) {
				debugf( "\n" );

				if( show_prompt ) {
					debugf( "VersionV: " );
					show_prompt = false;
				}
			} else {
				printf( "\n" );
				if( show_prompt ) {
					printf( "VersionV: " );
					show_prompt = false;
				}
			}
		}
	}

	#ifdef END_IMMEDIATELY

	klog( "Shutdown via END_IMMEDIATELY at end of kernel.c.\n" );
	outportb( 0xF4, 0x00 );

	#endif

	#ifdef kdebug_paging

	char *page_fault_addr = NULL;
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

int register_io_device( char *name, void (*read_func)(), void (*write_func)() ) {

}

uint32_t write( int file, void *buff, uint32_t count ) {

}

