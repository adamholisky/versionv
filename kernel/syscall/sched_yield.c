#include "kernel.h"
#include "syscall.h"
#include "task.h"

#define kdebug_sched_yield

uint32_t sched_yield( void ) {
	syscall_args args;

	return syscall( 4, 0, &args );
}

// 4-2-23: next step -- strip out previous debugging crud, add new to address not flipping back from forward tasks, currently going ABBBBB. somehow isn't saving or restoring old context?
uint32_t syscall_sched_yield( uint32_t ** stack, x86_context ** _context ) {
	x86_context * context = *_context;
	task *t, *t_next;
	klog( "\n" );
	klog( "Enter.\n" );

	t = get_current_task();
	t->context_at_interrupt = (uint32_t *)*_context;
	memcpy( &(t->context), (uint32_t *)context, sizeof( x86_context ) );
	

	klog( "Task ID:          %X\n", get_current_task_id() );
	klog( "Stack Base:       %X\n", (uint32_t)t->stack_base );
	klog( "Stack Top:        %X\n", t->stack_top );
	klog( "Context EIP:      %X\n", context->eip );
	klog( "Saved ESP:        %X\n", t->saved_esp );

	for( int i = 0; i < 30; i++ ) {
		klog( "Stack -%02X (-%02X) 0x%08X: 0x%08X\n", i, i * 0x4, stack - i, *(stack - i) );
	}

	for( int i = 0; i < 10; i++ ) {
		klog( "_esp    %02X  (%02X)  0x%08X: 0x%08X\n", i, i * 0x4, (uint32_t *)(context->_esp) + i, *((uint32_t *)(context->_esp) + i) );
	}

	t_next = switch_next_task();
	//*_context = (x86_context *)t->context_at_interrupt;

/* 	if( p->reset == true ) {
		p->context_eip = p->entry;
	} */

	t->saved_esp = stack;
	*(stack - 1) = t_next->saved_esp;
	stack = t_next->saved_esp;
	uint32_t * context_post_unwind = t_next->context._esp;

/* 	*(context_post_unwind) = 0xFEEEFAAA;
	*(context_post_unwind + 1) = t_next->context.eip;
	*(context_post_unwind + 2) = t_next->context.cs;
	*(context_post_unwind + 3) = t_next->context.eflags;
	*(context_post_unwind + 4) = t_next->context.useresp;
	*(context_post_unwind + 5) = t_next->context.ss; */

	if( t->id != 0 ) {
		//set_task_pde( t->code_page_table );
	}

	klog( "Task ID:          %X\n", get_current_task_id() );
	klog( "Stack Base:       %X\n", (uint32_t)t_next->stack_base );
	klog( "Stack Top:        %X\n", t_next->stack_top );
	klog( "Context EIP:      %X\n", t_next->context.eip );
	klog( "Saved ESP:        %X\n", t_next->saved_esp );

	for( int i = 0; i < 30; i++ ) {
		klog( "Stack -%02X (-%02X) 0x%08X: 0x%08X\n", i, i * 0x4, stack - i, *(stack - i) );
	}

	for( int i = 0; i < 10; i++ ) {
		klog( "_esp    %02X  (%02X)  0x%08X: 0x%08X\n", i, i * 0x4, (uint32_t *)(t_next->context._esp) + i, *((uint32_t *)(t_next->context._esp) + i) );
	}


	klog( "Done.\n" );
	return SYSCALL_RT_SUCCESS;
}