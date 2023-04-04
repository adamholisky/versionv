#include "kernel.h"
#include "syscall.h"
#include "task.h"
#include "interrupts.h"

/*
	Call Num.		Function
					Return
					Param List
					Notes
	
	0	read
		uint32_t	number of bytes read
		1			fd
		2			buff pointer
		3			max num of bytes to read

	1	write

	2	open

	3	close

	4	sched_yield	
*/

uint32_t syscall_handler( uint32_t * stack, x86_context ** _context ) {
	x86_context *context = *_context;

	switch( context->eax ) {
		case SYSCALL_READ:
			//debugf( "[SYSCALL] Read :: fd = %d, buff = 0x%08X, size = %d\n", stack->edi, stack->esi, stack->edx );
			syscall_read( context->edi, (void *)context->esi, context->edx );
			break;
		case SYSCALL_WRITE:
			//debugf( "[SYSCALL] Write\n" );
			break;
		case SYSCALL_SCHED_YIELD:
			//debugf( "[SYSCALL] sched_yield\n" );
			syscall_sched_yield( stack, _context );
			break;
		case SYSCALL_PARTIAL_CONTEXT_SWITCH:
			syscall_partial_context_switch( _context, (x86_context *)context->edi );
			break;
		case SYSCALL_SBRK:
			syscall_sbrk( context->edi );
			break;
		case SYSCALL_ACTTASK:
			syscall_activate_task( context->edi );
			break;
		case SYSCALL_END:
			syscall_exit_from_wrapper();
			break;
		case SYSCALL_EXIT:
			syscall_exit( context->edi );
			break;
		default:
			klog( "Undefined syscall number: 0x%04X\n", context->eax );
	}

	return SYSCALL_RT_SUCCESS;
}

uint32_t syscall( uint32_t call_num, uint32_t num_args, syscall_args * args ) {
	uint32_t ret = 0;

	switch( num_args ) {
		case 6:
		case 5:
		case 4:
		case 3:
			asm	volatile ( 
				"movl %1, %%eax \n"
				"movl %2, %%edi \n"
				"movl %3, %%esi \n"
				"movl %4, %%edx \n"
				"int %5 \n"
				"movl %%eax, %0"
				:"=r"(ret)
				:"r"(call_num), "m"(args->arg_1), "m"(args->arg_2), "m"(args->arg_3), "i"(0x99)
				:"%eax" 
			);
			break;
		case 2:
			asm	volatile ( 
				"movl %1, %%eax \n"
				"movl %2, %%edi \n"
				"movl %3, %%esi \n"
				"int %4 \n"
				"movl %%eax, %0"
				:"=r"(ret)
				:"r"(call_num), "m"(args->arg_1), "m"(args->arg_2), "i"(0x99)
				:"%eax" 
			);
			break;
		case 1:
			asm	volatile ( 
				"movl %1, %%eax \n"
				"movl %2, %%edi \n"
				"int %3 \n"
				"movl %%eax, %0"
				:"=r"(ret)
				:"r"(call_num), "m"(args->arg_1), "i"(0x99)
				:"%eax" 
			);
			break;
		case 0:
			asm	volatile ( 
				"movl %1, %%eax \n"
				"int %2 \n"
				"movl %%eax, %0"
				:"=r"(ret)
				:"r"(call_num), "i"(0x99)
				:"%eax" 
			);
			break;
		default:
			klog( "Syscall called with more than six args.\n" );
	}
}
