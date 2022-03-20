#if !defined(SYSCALL_INCLUDED)
#define SYSCALL_INCLUDED

#include "interrupts.h"

#define SYSCALL_READ	0
#define SYSCALL_WRITE	1
#define SYSCALL_OPEN	2
#define SYSCALL_CLOSE	3
#define SYSCALL_SCHED_YIELD	4
#define SYSCALL_SBRK	5


#define SYSCALL_RT_SUCCESS 0
#define SYSCALL_RT_ERROR 1

typedef struct {
	uint32_t	arg_1;
	uint32_t	arg_2;
	uint32_t	arg_3;
	uint32_t	arg_4;
	uint32_t	arg_5;
	uint32_t	arg_6;
} syscall_args;

uint32_t syscall_handler( interrupt_stack ** stack );
uint32_t syscall( uint32_t call_num, uint32_t num_args, syscall_args * args );

uint32_t read( int fd, void * buff, uint32_t size );
uint32_t syscall_read( int fd, void * buff, uint32_t size );

uint32_t sched_yield( void );
uint32_t syscall_sched_yield( interrupt_stack ** _stack );

uint32_t sbrk( int inc );
uint32_t syscall_sbrk( int inc );

#endif