#if !defined(PROCESS_INCLUDED)
#define PROCESS_INCLUDED

#define PROC_MAX	256
#define PROC_KERNEL 0

#define PROC_STATUS_UNKNOWN 0
#define PROC_STATUS_ACTIVE 1

typedef struct {
	bool present;
	uint32_t id;
	uint32_t status;
	uint32_t stack_eip;

	uint32_t *stack;
	uint32_t *stack_at_interrupt;

	void * code_start_phys;
	void * data_start_phys;
	void * code_start_virt;
	void * data_start_virt;

	void * entry;

	page_directory_entry * page_table;
} process;

extern void process_test_alpha( void );
extern void process_test_beta( void );

void process_initalize( void );
uint32_t setup_kernel_process( void );
uint32_t add_process( process p );
process * get_current_process( void );
process * switch_next_process( void );
void process_test_a( void );
void process_test_b( void );

#endif