#if !defined(MEMORY_INCLUDED)
#define MEMORY_INCLUDED

#define page_size_in_bytes 0x00001000
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
void set_process_pde( page_directory_entry * pte );
uint32_t * get_physical_memory_base( void );
void dump_active_pt( void );
uint32_t * get_physical_addr_from_virt( uint32_t * virt );


/** This function is supposed to lock the memory data structures. It
 * could be as simple as disabling interrupts or acquiring a spinlock.
 * It's up to you to decide. 
 *
 * \return 0 if the lock was acquired successfully. Anything else is
 * failure.
 */
int liballoc_lock();

/** This function unlocks what was previously locked by the liballoc_lock
 * function.  If it disabled interrupts, it enables interrupts. If it
 * had acquiried a spinlock, it releases the spinlock. etc.
 *
 * \return 0 if the lock was successfully released.
 */
int liballoc_unlock();

/** This is the hook into the local system which allocates pages. It
 * accepts an integer parameter which is the number of pages
 * required.  The page size was set up in the liballoc_init function.
 *
 * \return NULL if the pages were not allocated.
 * \return A pointer to the allocated memory.
 */
void* liballoc_alloc(size_t);

/** This frees previously allocated memory. The void* parameter passed
 * to the function is the exact same value returned from a previous
 * liballoc_alloc call.
 *
 * The integer value is the number of pages to free.
 *
 * \return 0 if the memory was successfully freed.
 */
int liballoc_free(void*,size_t);

void    *kmalloc(size_t);				///< The standard function.
void    *krealloc(void *, size_t);		///< The standard function.
void    *kcalloc(size_t, size_t);		///< The standard function.
void     kfree(void *);					///< The standard function.

void memory_test( void );
void * __attribute__((weak)) memset(void * dest, int c, size_t n);
void liballoc_dump( void );
#endif