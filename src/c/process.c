#include "kernel.h"
#include "interrupts.h"
#include "syscall.h"

extern uint32_t * boot_page_directory;
extern uint32_t * boot_page_table;

uint32_t proc_current;
uint32_t proc_last;
uint32_t process_switch_counter;

process proc[ PROC_MAX ];

void process_initalize( void ) {
	log_entry_enter();

	int i;
	process proc_a, proc_b;

	klog( "Initalizing processes...\n" );

	for( i = 0; i < PROC_MAX; i++ ) {
		proc[i].present = false;
	}

	setup_kernel_process();

	proc_current = 0;
	proc_last = 0;

	klog( "Process begin tests...\n" );
	
	/*
	proc_a.code_start_virt = page_allocate( 4 );
	proc_a.code_start_phys = proc_a.code_start_virt - 0xA0000000;
	proc_a.stack = page_allocate( 4 );
	uint32_t * proc_a_code = (uint32_t *)proc_a.code_start_virt;


	kdebug_symbol * test_proc = kdebug_get_symbol( "process_test_a" );
	debugf( "process_test_a() @ 0x%08X for 0x%X\n", test_proc->addr, test_proc->size );
	memcpy( proc_a.code_start_virt, test_proc->addr, test_proc->size + 2 );

	// CD30 CD32 EBFA
	//proc_a_code[0] = 0x32CD30CD;
	//proc_a_code[1] = 0x0000FAEB;

	debugf( "    proc_a code virt:  0x%08X\n", proc_a.code_start_virt );
	kdebug_peek_at( (uint32_t)test_proc->addr );
	kdebug_peek_at( (uint32_t)proc_a.code_start_virt );
	//debugf( "    proc_a code out:   0x%08X 0x%08X\n", *proc_a_code, *(proc_a_code + 1) );
	debugf( "    proc_a stack virt: 0x%08X\n", proc_a.stack );

	proc_b.code_start_virt = page_allocate( 4 );
	proc_b.code_start_phys = proc_b.code_start_virt - 0xA0000000;
	proc_b.stack = page_allocate( 4 );
	uint32_t * proc_b_code = (uint32_t *)proc_b.code_start_virt;

	// CD31 CD32 EBFA
	proc_b_code[0] = 0x32CD31CD;
	proc_b_code[1] = 0x0000FAEB;

	debugf( "    proc_b code virt:  0x%08X\n", proc_b.code_start_virt );
	debugf( "    proc_b code out:   0x%08X 0x%08X\n", *proc_b_code, *(proc_b_code + 1) );
	debugf( "    proc_b stack virt: 0x%08X\n", proc_b.stack );
	
	add_process( proc_a );
	add_process( proc_b );

	proc_current = 0;
	proc_last = 2;

	//asm( "int %0" : : "i"(0x32) );
	*/
	/*
	void (*start)() = proc_a.code_start_virt;

	debugf( "starting at: 0x%08X\n", start );
	start();
	*/

	log_entry_exit();
}

uint32_t setup_kernel_process( void ) {
	proc[ PROC_KERNEL ].present = true;
	proc[ PROC_KERNEL ].status = 1;
	proc[ PROC_KERNEL ].id = PROC_KERNEL;
	proc[ PROC_KERNEL ].code_start_phys = kernel_main - 0xC0000000;
	proc[ PROC_KERNEL ].code_start_virt = kernel_main;
	proc[ PROC_KERNEL ].data_start_phys = (void *)0x06400000;
	proc[ PROC_KERNEL ].data_start_virt = (void *)0xA0000000;
}

uint32_t add_process( process p ) {
	int i = 0;

	for( i = 0; i < PROC_MAX; i++ ) {
		if( proc[i].present == false ) {
			break;
		}
	}

	interrupt_stack stack_initial;
	
	stack_initial.gs = 0x10;
	stack_initial.gs_padding = 0;
	stack_initial.fs = 0x10;
	stack_initial.fs_padding = 0;
	stack_initial.es = 0x10;
	stack_initial.es_padding = 0;
	stack_initial.ds = 0x10;
	stack_initial.ds_padding = 0;
	stack_initial.edi = 0;
	stack_initial.esi = 0;
	stack_initial.ebp = 0;
	stack_initial.esp = (uint32_t)p.stack; // ignored in popad, but doing so for good measure
	stack_initial.ebx = 0;
	stack_initial.edx = 0;
	stack_initial.ecx = 0;
	stack_initial.eax = 0;
	stack_initial._esp = (uint32_t)&stack_initial._esp;
	// err element not present? TODO fix logic
	stack_initial.eip = (uint32_t)p.entry;
	stack_initial.cs = 0x08;
	stack_initial.eflags = 0x202;

	stack_initial.ss = 0x10;


	//debugf( "stack_initial._esp: %08X\n", stack_initial._esp );

	memcpy( p.stack, &stack_initial, sizeof( interrupt_stack ) );


	proc[i].present = true;
	proc[i].status = 0;
	proc[i].id = i;
	proc[i].code_start_phys = p.code_start_phys;
	proc[i].code_start_virt = p.code_start_virt;
	proc[i].data_start_phys = p.data_start_phys;
	proc[i].data_start_virt = p.data_start_virt;	
	proc[i].entry = (void *)p.entry;
	proc[i].stack_eip = (uint32_t)p.entry;
	proc[i].stack_at_interrupt = p.stack;
	
	interrupt_stack * is = (interrupt_stack *)proc[i].stack;
	is->_esp = (uint32_t)&is->_esp + (uint32_t)proc[i].stack_at_interrupt;
	stack_initial._esp = (uint32_t)&is->_esp + (uint32_t)proc[i].stack_at_interrupt;

	proc[i].page_table = kmalloc( sizeof( page_directory_entry ) * 1024 );
	proc[i].page_table[0].rw = 1;
	proc[i].page_table[0].present = 1;
	proc[i].page_table[0].address = (0x06400000 + (uint32_t)proc[i].code_start_virt - 0xA0000000)>>11;

	proc[i].page_table[1].rw = 1;
	proc[i].page_table[1].present = 1;
	proc[i].page_table[1].address = (0x06400000 + (uint32_t)proc[i].code_start_virt + 0x1000 - 0xA0000000)>>11;

	//kdebug_peek_at( proc[i].code_start_virt );
	
	// debugf( "page_table.addr: 0x%08X\n", proc[i].page_table[0].address << 11);
	// debugf( "stack_initial._esp: %08X\n", stack_initial._esp );
	// debugf( "is->_esp: %08X\n", is->_esp );

	return i;
}

process * get_current_process( void ) {
	return (proc + proc_current);
}

process * switch_next_process( void ) {
	int proc_next = -1;

	// do a simple round-robin process scheduler, array based for easy debugging
	// starting from current proc spot + 1, iterate through end of possible processes
	for( int i = proc_current + 1; i < PROC_MAX; i++ ) {
		if( proc[i].present == true ) {
			proc_next = i;
			break;
		}
	}

	// if we still don't have a new process, then start over at 0
	// iterate up through and including the current process spot, so we can handle a single process system
	if( proc_next == -1 ) {
		for( int j = 0; j < proc_current + 1; j++ ) {
			if( proc[j].present == true ) {
				proc_next = j;
				break;
			}
		}
	}

	// we should never hit this, so die if we do
	if( proc_next == -1 ) {
		klog( "END. proc_next is -1.\n");
		outportb( 0xF4, 0x00 );
	}

	proc_current = proc_next;

	process_switch_counter++;

	if( process_switch_counter > 100000 ) {
		klog( "END. Processes switched over 100,000 times.\n");
		outportb( 0xF4, 0x00 );
	}

	return (proc + proc_current);
}

volatile void process_test_a( void ) {
	debugf( "+" );
	sched_yield();
}

void process_test_b( void ) {
	debugf( "-" );
	sched_yield();
}