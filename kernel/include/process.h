#if !defined(PROCESS_INCLUDED)
#define PROCESS_INCLUDED

#include "memory.h"

#define PROC_MAX	256
#define PROC_KERNEL 0

#define PROC_STATUS_UNKNOWN 0
#define PROC_STATUS_ACTIVE 1

#define PROC_VIRT_HEAP_BASE 0x40000000

typedef struct {
	bool present;
	bool reset;
	uint32_t id;
	uint32_t status;
	uint32_t stack_eip;

	uint32_t *stack;
	uint32_t *stack_at_interrupt;

	void * code_start_phys;
	void * data_start_phys;
	void * code_start_virt;
	void * data_start_virt;

	void * virt_heap_top;

	void * entry;

	page_directory_entry * code_page_table;
	page_directory_entry * data_page_table;

	char name[25];
} process;

extern void process_test_alpha( void );
extern void process_test_beta( void );

void process_initalize( void );
uint32_t setup_kernel_process( void );
uint32_t add_process( process p );
process * get_current_process( void );
process * switch_next_process( void );
process * get_processes( void );
void process_set_name( uint32_t proc_id, char * n );
void process_set_active( uint32_t proc_id );
void process_set_inactive( uint32_t proc_id );
void process_test_a( void );
void process_test_b( void );
void process_reset( void );

#endif