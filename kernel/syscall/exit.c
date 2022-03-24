#include "kernel.h"
#include "syscall.h"
#include "task.h"

#undef kdebug_exit

uint32_t exit_from_wrapper( void ) {
	syscall_args args;

	return syscall( SYSCALL_END, 0, &args );
}

uint32_t syscall_exit_from_wrapper( void ) {
	task_end_from_wrapper();

	return SYSCALL_RT_SUCCESS;
}