#include "kernel.h"
#include "syscall.h"
#include "task.h"

#define kdebug_sched_yield

uint32_t sched_yield( void ) {
	syscall_args args;

	return syscall( 4, 0, &args );
}

// 4-2-23: next step -- strip out previous debugging crud, add new to address not flipping back from forward tasks, currently going ABBBBB. somehow isn't saving or restoring old context?
uint32_t syscall_sched_yield( x86_context ** _stack ) {
	x86_context * stack = *_stack;
	task *t, *t_next;

	t = get_current_task();
	t->context_at_interrupt = (uint32_t *)*_stack;
	memcpy( &(t->context), (uint32_t *)stack, sizeof( x86_context ) );

	klog( "pre switch id: %X\n", get_current_task_id() );
	klog( "saved eip to current task: %X\n", t->context.eip );

	#ifdef kdebug_sched_yield
	debugf( "pre switch:  *_stack: %08X  stack: %08X  eip: %08X\n", *_stack, stack, (*_stack)->eip );

	for( int i = 0; i < 22; i++ ) {
		//klog( "Stack 0x%08X: 0x%08X\n", _stack + i, *(_stack + i ) );
	}
	#endif
	
	t_next = switch_next_task();
	//*_stack = (x86_context *)t->context_at_interrupt;

	klog( "stack: 0x%08X\n", _stack );
	db1();

/* 	if( p->reset == true ) {
		p->stack_eip = p->entry;
	} */

	//memcpy( t->stack_base, _stack, 1024 * 16 );
	//_stack = t->stack_base;
	/* uint32_t *s0 = (uint32_t *)_stack;
	uint32_t *sESP = (uint32_t *)_stack + 0x30;
	*s0 = t->stack_base + 4;
	*s0 = 0xFAFAFAFA;
	*sESP = t->stack_base + 0x34; */

	klog( "id: %X\n", t_next->id );
	klog( "_esp: %08X\n", t_next->context._esp );
	klog( "eip: %X\n", t_next->context.eip );
	stack->_esp = t_next->context._esp;
	uint32_t * stack_post_unwind = t_next->context._esp;

	*(stack_post_unwind) = 0xFEEEFAAA;
	*(stack_post_unwind + 1) = t_next->context.eip;
	*(stack_post_unwind + 2) = t_next->context.cs;
	*(stack_post_unwind + 3) = t_next->context.eflags;

	db2();

	#ifdef kdebug_sched_yield 
	debugf( "post switch: *_stack: %08X  stack: %08X  eip: %08X\n", 0x0, stack_post_unwind, *(stack_post_unwind + 1) );

	for( int i = 0; i < 22; i++ ) {
		//klog( "Stack 0x%08X: 0x%08X\n", stack_post_unwind + i, *(stack_post_unwind + i ) );
	}
	#endif

	if( t->id != 0 ) {
		//set_task_pde( t->code_page_table );
	}

	#ifdef kdebug_sched_yield
	for( int i = 0; i < 10; i++ ) {
		uint32_t *eip = (uint32_t *)(*_stack)->eip + i;
		//klog( "0x%08X: 0x%08X\n", eip, *eip);
	}

	debugf( "sched_yield done\n\n" );
	#endif

	return SYSCALL_RT_SUCCESS;
}