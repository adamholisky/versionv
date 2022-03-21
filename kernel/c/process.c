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

	log_entry_exit();
}

uint32_t setup_kernel_process( void ) {
	proc[ PROC_KERNEL ].present = true;
	proc[ PROC_KERNEL ].status = 1;
	proc[ PROC_KERNEL ].id = PROC_KERNEL;
	proc[ PROC_KERNEL ].code_start_phys = kernel_main - KERNEL_VIRT_LOAD_BASE;
	proc[ PROC_KERNEL ].code_start_virt = kernel_main;
	proc[ PROC_KERNEL ].data_start_phys = (void *)get_physical_memory_base();
	proc[ PROC_KERNEL ].data_start_virt = (void *)KERNEL_VIRT_HEAP_BASE;
	strcpy( proc[ PROC_KERNEL ].name, "kernel_main" );
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
	proc[i].virt_heap_top = (void *)PROC_VIRT_HEAP_BASE;	
	proc[i].entry = (void *)p.entry;
	proc[i].stack_eip = (uint32_t)p.entry;
	proc[i].stack_at_interrupt = p.stack;
	
	interrupt_stack * is = (interrupt_stack *)proc[i].stack;
	is->_esp = (uint32_t)&is->_esp + (uint32_t)proc[i].stack_at_interrupt;
	stack_initial._esp = (uint32_t)&is->_esp + (uint32_t)proc[i].stack_at_interrupt;

	proc[i].code_page_table = kmalloc( sizeof( page_directory_entry ) * 1024 );
	memset( proc[i].code_page_table, 0, sizeof( page_directory_entry ) * 1024 );
	proc[i].code_page_table[0].rw = 1;
	proc[i].code_page_table[0].present = 1;
	proc[i].code_page_table[0].address = ((uint32_t)get_physical_memory_base() + (uint32_t)proc[i].code_start_virt - KERNEL_VIRT_HEAP_BASE)>>11;
	klog( "pte address created: 0x%08X\n", (uint32_t)get_physical_memory_base() + (uint32_t)proc[i].code_start_virt - KERNEL_VIRT_HEAP_BASE );
	klog( "full: 0x%08X\n", ((uint32_t)get_physical_memory_base() + (uint32_t)proc[i].code_start_virt - KERNEL_VIRT_HEAP_BASE)>>11 );

	proc[i].code_page_table[1].rw = 1;
	proc[i].code_page_table[1].present = 1;
	proc[i].code_page_table[1].address = ((uint32_t)get_physical_memory_base() + (uint32_t)proc[i].code_start_virt + 0x1000 - KERNEL_VIRT_HEAP_BASE)>>11;

	//kdebug_peek_at( proc[i].code_start_virt + proc[i].stack_eip);
	
	// debugf( "page_table.addr: 0x%08X\n", proc[i].page_table[0].address << 11);
	// debugf( "stack_initial._esp: %08X\n", stack_initial._esp );
	// debugf( "is->_esp: %08X\n", is->_esp );

	return i;
}

process * get_current_process( void ) {
	return (proc + proc_current);
}

void process_set_name( uint32_t proc_id, char * n ) {
	strcpy( proc[proc_id].name, n );
}

process * switch_next_process( void ) {
	int proc_next = -1;

	// do a simple round-robin process scheduler, array based for easy debugging
	// starting from current proc spot + 1, iterate through end of possible processes
	for( int i = proc_current + 1; i < PROC_MAX; i++ ) {
		if( (proc[i].present == true) && (proc[i].status == 1) ) {
			proc_next = i;
			break;
		}
	}

	// if we still don't have a new process, then start over at 0
	// iterate up through and including the current process spot, so we can handle a single process system
	if( proc_next == -1 ) {
		for( int j = 0; j < proc_current + 1; j++ ) {
			if( (proc[j].present == true) && (proc[j].status == 1) ) {
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

/* 	if( process_switch_counter > 100000 ) {
		klog( "END. Processes switched over 100,000 times.\n");
		outportb( 0xF4, 0x00 );
	} */

	return (proc + proc_current);
}

void process_set_active( uint32_t proc_id ) {
	proc[proc_id].status = 1;
}

void process_set_inactive( uint32_t proc_id ) {
	proc[proc_id].status = 0;
}

void process_reset( void ) {
	proc[proc_current].status = 0;
	proc[proc_current].reset = true;

	sched_yield();
}

process * get_processes( void ) {
	return proc;
}

volatile void process_test_a( void ) {
	debugf( "+" );
	sched_yield();
}

void process_test_b( void ) {
	debugf( "-" );
	sched_yield();
}