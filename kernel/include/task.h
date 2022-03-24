#if !defined(TASK_INCLUDED)
#define TASK_INCLUDED

#include "bootstrap.h"
#include "interrupts.h"
#include "memory.h"

#define TASK_MAX 255

#define TASK_ID_INVALID -1
#define TASK_ID_KERNEL 0

#define TASK_TYPE_INVALID -1
#define TASK_TYPE_PROCESS 0
#define TASK_TYPE_THREAD  1
#define TASK_TYPE_SERVICE 2
#define TASK_TYPE_MODULE  3

#define TASK_STATUS_INVALID -1
#define TASK_STATUS_INACTIVE 0
#define TASK_STATUS_ACTIVE 1
#define TASK_STATUS_WAIT 2
#define TASK_STATUS_MODHACK 9

#define TASK_VIRT_HEAP_BASE 0x40000000

typedef struct {
	int32_t id;
	int32_t type;
	char name[25];

	int32_t status;

	x86_context	context;
	uint32_t * context_at_interrupt;

	uint32_t * stack;
	uint32_t stack_eip;
	void * code_start_phys;
	void * data_start_phys;
	void * code_start_virt;
	void * data_start_virt;
	void * virt_heap_top;
	void * stack_base;
	void * entry;

	page_directory_entry * code_page_table;
	page_directory_entry * data_page_table;

	uint32_t start_time;
	uint32_t total_share_time;
	uint32_t share_time_start;
} task;

void task_initalize( void );
int32_t task_add( task *t );
task * switch_next_task( void );
task * get_current_task( void );
void task_set_name( int32_t task_id, char * n );
void task_set_active( int32_t task_id );
void task_set_inactive( int32_t task_id );
void task_set_modhack( int32_t task_id );
task * get_tasks( void );
void task_initalize_and_run( int32_t task_id );
char * task_type_to_string( int32_t type );
char * task_status_to_string( int32_t status );

#endif