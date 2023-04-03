#include "kernel.h"
#include <kernel_main.h>
#include "multiboot.h"
#include "elf.h"
#include "task.h"
#include "interrupts.h"
#include "pci.h"
#include "task.h"
#include "debug.h"
#include "callback.h"
#include "keyboard.h"
#include "observer.h"
#include <ftp.h>
#include <modules.h>
#include <vshell.h>
#include <string.h>
#include <device.h>
#include <uione.h>
#include <kshell.h>
#include "intel8254.h"

#define END_IMMEDIATELY
#define TRIGGER_DIVIDE_BY_ZERO false

extern void cpp_tests( void );

void test_func( void );

void kernel_main( unsigned long mb_magic, multiboot_info_t *mb_info ) {
	int x = 0;
	char c = ' ';
	bool process_keypress;

	multiboot_initalize( mb_magic, mb_info );
	term_initalize();
	initalize_serial();

	printf( "\x1b[0;31;49mVersionV\x1b[0;0;0m\n" );
	debugf( "\x1b[0;31;49mVersionV\x1b[0;0;0m Serial Out\n" );

	// Handle CLI from multiboot header
 	if( strstr( (char *)mb_info->cmdline, "graphics_on" ) ) {
		debugf( "CLI: Graphics on\n" );
		GRAPHICS_ACTIVE = false;
	} else {
		debugf( "CLI: Graphics off\n" );
		GRAPHICS_ACTIVE = false;
		DF_COM4_ONLY = true;
	}

	GRAPHICS_ACTIVE = false;

	multiboot_echo_to_serial();
	memory_initalize();
	kdebug_initalize();
	elf_initalize( reinterpret_cast<uint32_t>(kernel_main) );
	interrupts_initalize();
	observer_initalize();

	if( GRAPHICS_ACTIVE ) {
		vga_initalize();
		console_init( "default-console", 3, 3, 7 * 120, 14 * 50, 0x00282C34, 0x00AAAAAA );
		console_draw();
	}

	serial_enable_interrupts();
	task_initalize();
	
	pci_initalize();
	intel8254_initalize();
	//ata_initalize();
	keyboard_initalize();

	serial_clear_buffer( COM2 );
	READY_FOR_INPUT = true;

	task_check();
	
	kshell_run();

	if( TRIGGER_DIVIDE_BY_ZERO ) {
		asm volatile( 
			"movl 0, %eax \n\t"
			"movl 0, %ecx \n\t"
			"div %ecx \n\t"
		);
	}

	do_immediate_shutdown();

	test_func();
	init_devices();

	cpp_tests();

	//uione_test();

	/* FTP *host_ftp = new FTP();

	host_ftp->login( "vv", "vv" );
	host_ftp->cwd( "/usr/local/osdev/versions/v/modules/build" );
	host_ftp->get_file( "reference.vvs" );
	
	Module m;
	m.load( (uint32_t *)host_ftp->data_buffer, "reference.vvs" );
	m.call_main();
	

	VShell v;
	v.init( host_ftp, &m );
	v.run();

	*/

	klog( "\n\nEnd of line." );

	while( true ) { x = x - x + 1; }
}

void test_func( void ) {
	//
}