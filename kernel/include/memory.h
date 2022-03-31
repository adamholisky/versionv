#if !defined(MEMORY_INCLUDED)
#define MEMORY_INCLUDED

#ifdef PAGING4K
	#define page_size_in_bytes 0x00001000
#else
	#define page_size_in_bytes 0x00400000
#endif

#define KERNEL_VIRT_LOAD_BASE 0xC0000000
#define KERNEL_VIRT_HEAP_BASE 0xD0000000

typedef struct {
	uint8_t		present : 1;
	uint8_t		rw : 1;
	uint8_t		privilege : 1;
	uint8_t		write_through : 1;
	uint8_t		cache_disabled : 1;
	uint8_t		accessed : 1;
	uint8_t		page_size : 1;
	uint8_t		ignored : 1;
	uint8_t		available : 3;
	uint32_t	address : 20;
} page_directory_entry;

void memory_initalize( void );
uint32_t * page_map( uint32_t *virt_addr, uint32_t *phys_addr );
uint32_t * page_allocate( uint32_t num );
void set_task_pde( page_directory_entry * pte );
uint32_t * get_physical_memory_base( void );
void dump_active_pt( void );
uint32_t * get_physical_addr_from_virt( uint32_t * virt );

#endif