#include "kernel.h"
#include "syscall.h"

#undef kdebug_sched_yield

uint32_t sched_yield( void ) {
	syscall_args args;

	return syscall( 4, 0, &args );
}

uint32_t syscall_sched_yield( interrupt_stack ** _stack ) {
	interrupt_stack * stack = *_stack;
	process *p;

	p = get_current_process();
	p->stack_eip = stack->eip;
	p->stack_at_interrupt = (uint32_t *)*_stack;

	#ifdef kdebug_sched_yield
	debugf( "pre switch:  *_stack: %08X  stack: %08X  eip: %08X\n", *_stack, stack, (*_stack)->eip );
	#endif
	
	p = switch_next_process();
	*_stack = (interrupt_stack *)p->stack_at_interrupt;
	(*_stack)->eip = p->stack_eip;

	#ifdef kdebug_sched_yield
	debugf( "post switch: *_stack: %08X  stack: %08X  eip: %08X\n", *_stack, stack, (*_stack)->eip );
	#endif

	if( p->id != 0 ) {
		set_process_pde( p->page_table );
	}

	#ifdef kdebug_sched_yield
	debugf( "sched_yield done\n" );
	#endif

	return SYSCALL_RT_SUCCESS;
}