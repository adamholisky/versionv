#include "kernel.h"

static const char * vv_magic_word = "VersionV";
uint32_t * phsyical_memory_top = (uint32_t *)0x06400000;
uint32_t * kernel_virtual_memory_top = (uint32_t *)0xA0000000;

extern page_directory_entry * boot_page_directory;
extern page_directory_entry * boot_page_table;

extern void asm_refresh_cr3( void );

page_directory_entry second_page_table[1024] __attribute__ ((aligned (4096)));

void memory_initalize( void ) {
	page_allocate( 1 );

	#if kdebug_memory

	memory_test();

	#endif

	#ifdef kdebug_memory_pages

	page_directory_entry * kernel_page = (page_directory_entry *)(&boot_page_directory + 768);

	debugf( "pde: %X\n", sizeof( page_directory_entry ) );
	debugf( "bpd: 0x%08X\n", (uint32_t)&boot_page_directory );
	debugf( "bpt: 0x%08X\n", (uint32_t)&boot_page_table );
	debugf( "kernel_page->present: %d\n", kernel_page->present ); 
	debugf( "kernel_page->rw: %d\n", kernel_page->rw ); 
	debugf( "kernel_page->privilege: %d\n", kernel_page->privilege );
	debugf( "kernel_page->write_through: %d\n", kernel_page->write_through );
	debugf( "kernel_page->cache_disabled: %d\n", kernel_page->cache_disabled );
	debugf( "kernel_page->accessed: %d\n", kernel_page->accessed );
	debugf( "kernel_page->page_size: %d\n", kernel_page->page_size );
	debugf( "kernel_page->ignored: %d\n", kernel_page->ignored );
	debugf( "kernel_page->address: 0x%08X\n", kernel_page->address<<11 );

	#endif
}

uint32_t * page_map( uint32_t *virt_addr, uint32_t *phys_addr ) {
	uint32_t pt_addr_physical = ((uint32_t)second_page_table) - 0xC0000000;
	uint32_t pd_index = 0;
	uint32_t pt_index = 0;
	page_directory_entry * pd;
	page_directory_entry * pt;

	// Find entry in BPD
	// virt_addr: 0xA000 0000 >> 8 = 0x00A0 0000 / 0x4000 = 0x280 (640d)
	pd_index = ((uint32_t)virt_addr >> 8) / 0x4000;
	pt_index = ((uint32_t)virt_addr >> 12) % 0x4000;

	// Set the page directory entry up correctly
	pd = (page_directory_entry *)(&boot_page_directory + pd_index);
	pd->present = 1;
	pd->rw = 1;
	pd->address = pt_addr_physical >> 11;

	// Set the page table entry up correctly
	// Physical memory allocation starts at 0x0640 0000 (100mb)
	pt = (page_directory_entry *)(second_page_table + pt_index);
	pt->present = 1;
	pt->rw = 1;
	pt->address = (uint32_t)phys_addr >> 11;

	#ifdef kdebug_memory_pages

	debugf( "bpd_index:          0x%08X\n", pd_index );
	debugf( "pt_index:           0x%08X\n", pt_index );
	debugf( "pt_addr_physical:   0x%08X\n", pt_addr_physical );
	debugf( "spt:                0x%08X\n", second_page_table );
	debugf( "pt_addr >> 11:      0x%08X\n", pt_addr_physical >> 11 );
	debugf( "PD contents:        0x%08X\n", *pd );
	debugf( "PT contents:        0x%08X\n", *pt );

	#endif

	// Refresh the page directory in the cpu
	asm volatile("invlpg (%0)" ::"r" (pt) : "memory");

	// return pointer to first byte
	return virt_addr;
}

uint32_t * page_allocate( uint32_t num ) {
	uint32_t * return_pointer = kernel_virtual_memory_top; 

	for( uint32_t i = 0; i < num; i++ ) {
		page_map( kernel_virtual_memory_top, phsyical_memory_top );
		kernel_virtual_memory_top = (uint32_t *)((uint32_t)kernel_virtual_memory_top + page_size_in_bytes);
		phsyical_memory_top = (uint32_t *)((uint32_t)phsyical_memory_top + page_size_in_bytes);

		#ifdef kdebug_memory_pages

		debugf( "kvm_top: 0x%08X    pmt: 0x%08X\n", kernel_virtual_memory_top, phsyical_memory_top );

		#endif
	}

	k_log( sys_memory, level_info, "%d page(s) allocated at 0x%08X", num, return_pointer );

	return return_pointer;
}

#define memtest_dump( v ) k_log( sys_memory, level_info, #v ": 0x%04X %04X",( ( uint32_t )( v ) >> 16 ), ( uint32_t )( v )&0xFFFF)

void memory_test( void ) {
	void * p2;
	void * p3;
	void * p4;
	void * p5;

	memtest_dump( kernel_virtual_memory_top );

	/*
	void * p;
	p = liballoc_alloc( 4096 );
	printf( "liballoc_alloc( 4096 ) page into p\n" );
	memtest_dump( p );
	*/
	
	p2 = kmalloc( 0x256 );
	k_log( sys_memory, level_info, "kmalloc(0x256) into p2" );
	memtest_dump( p2 );

	k_log( sys_memory, level_info, "kmalloc(0x512) into p3" );
	p3 = kmalloc( 0x512 );
	memtest_dump( p3 );

	k_log( sys_memory, level_info, "kmalloc(0x11000) into p4" );
	p4 = kmalloc( 0x11000 );
	memtest_dump( p4 );

	k_log( sys_memory, level_info, "kmalloc(0x11000) into p5" );
	p5 = kmalloc( 0x11000 );
	memtest_dump( p5 );

	memtest_dump( kernel_virtual_memory_top );
	
	liballoc_dump();
}


/*
 *
 *
 *
 * 
 * 
 * 
 */

/**  Durand's Amazing Super Duper Memory functions.  */

#define VERSION 	"1.1"
#define ALIGNMENT	16ul//4ul				///< This is the byte alignment that memory must be allocated on. IMPORTANT for GTK and other stuff.

#define ALIGN_TYPE		char ///unsigned char[16] /// unsigned short
#define ALIGN_INFO		sizeof(ALIGN_TYPE)*16	///< Alignment information is stored right before the pointer. This is the number of bytes of information stored there.

/** This macro will conveniently align our pointer upwards */
#define ALIGN( ptr )													\
		if ( ALIGNMENT > 1 )											\
		{																\
			uintptr_t diff;												\
			ptr = (void*)((uintptr_t)ptr + ALIGN_INFO);					\
			diff = (uintptr_t)ptr & (ALIGNMENT-1);						\
			if ( diff != 0 )											\
			{															\
				diff = ALIGNMENT - diff;								\
				ptr = (void*)((uintptr_t)ptr + diff);					\
			}															\
			*((ALIGN_TYPE*)((uintptr_t)ptr - ALIGN_INFO)) = 			\
				diff + ALIGN_INFO;										\
		}															


#define UNALIGN( ptr )													\
		if ( ALIGNMENT > 1 )											\
		{																\
			uintptr_t diff = *((ALIGN_TYPE*)((uintptr_t)ptr - ALIGN_INFO));	\
			if ( diff < (ALIGNMENT + ALIGN_INFO) )						\
			{															\
				ptr = (void*)((uintptr_t)ptr - diff);					\
			}															\
		}
				


#define LIBALLOC_MAGIC	0xc001c0de
#define LIBALLOC_DEAD	0xdeaddead

/** A structure found at the top of all system allocated 
 * memory blocks. It details the usage of the memory block.
 */
struct liballoc_major
{
	struct liballoc_major *prev;		///< Linked list information.
	struct liballoc_major *next;		///< Linked list information.
	unsigned int pages;					///< The number of pages in the block.
	unsigned int size;					///< The number of pages in the block.
	unsigned int usage;					///< The number of bytes used in the block.
	struct liballoc_minor *first;		///< A pointer to the first allocated memory in the block.	
};


/** This is a structure found at the beginning of all
 * sections in a major block which were allocated by a
 * malloc, calloc, realloc call.
 */
struct	liballoc_minor
{
	struct liballoc_minor *prev;		///< Linked list information.
	struct liballoc_minor *next;		///< Linked list information.
	struct liballoc_major *block;		///< The owning block. A pointer to the major structure.
	unsigned int magic;					///< A magic number to idenfity correctness.
	unsigned int size; 					///< The size of the memory allocated. Could be 1 byte or more.
	unsigned int req_size;				///< The size of memory requested.
};


static struct liballoc_major *l_memRoot = NULL;	///< The root memory block acquired from the system.
static struct liballoc_major *l_bestBet = NULL; ///< The major with the most free memory.

static unsigned int l_pageSize  = 4096;			///< The size of an individual page. Set up in liballoc_init.
static unsigned int l_pageCount = 16;			///< The number of pages to request per chunk. Set up in liballoc_init.
static unsigned long long l_allocated = 0;		///< Running total of allocated memory.
static unsigned long long l_inuse	 = 0;		///< Running total of used memory.


static long long l_warningCount = 0;		///< Number of warnings encountered
static long long l_errorCount = 0;			///< Number of actual errors
static long long l_possibleOverruns = 0;	///< Number of possible overruns





// ***********   HELPER FUNCTIONS  *******************************

static void *liballoc_memset(void* s, int c, size_t n)
{
	unsigned int i;
	for ( i = 0; i < n ; i++)
		((char*)s)[i] = c;
	
	return s;
}

static void* liballoc_memcpy(void* s1, const void* s2, size_t n)
{
  char *cdest;
  char *csrc;
  unsigned int *ldest = (unsigned int*)s1;
  unsigned int *lsrc  = (unsigned int*)s2;

  while ( n >= sizeof(unsigned int) )
  {
	  *ldest++ = *lsrc++;
	  n -= sizeof(unsigned int);
  }

  cdest = (char*)ldest;
  csrc  = (char*)lsrc;
  
  while ( n > 0 )
  {
	  *cdest++ = *csrc++;
	  n -= 1;
  }
  
  return s1;
}
 

void liballoc_dump( void )
{
	struct liballoc_major *maj = l_memRoot;
	struct liballoc_minor *min = NULL;

	printf( "liballoc: ------ Memory data ---------------\n");
	printf( "liballoc: System memory allocated: %i bytes\n", l_allocated );
	printf( "liballoc: Memory in used (malloc'ed): %i bytes\n", l_inuse );
	printf( "liballoc: Warning count: %i\n", l_warningCount );
	printf( "liballoc: Error count: %i\n", l_errorCount );
	printf( "liballoc: Possible overruns: %i\n", l_possibleOverruns );

	while ( maj != NULL )
	{
		printf( "liballoc: %x: total = %i, used = %i\n",
					maj, 
					maj->size,
					maj->usage );

		min = maj->first;
		while ( min != NULL )
		{
			printf( "liballoc:    %x: %i bytes\n",
						min, 
						min->size );
			min = min->next;
		}

		maj = maj->next;
	}

	//FLUSH();
}



// ***************************************************************

static struct liballoc_major *allocate_new_page( unsigned int size )
{
	unsigned int st;
	struct liballoc_major *maj;

	// This is how much space is required.
	st  = size + sizeof(struct liballoc_major);
	st += sizeof(struct liballoc_minor);

	// Perfect amount of space?
	if ( (st % l_pageSize) == 0 )
		st  = st / (l_pageSize);
	else
		st  = st / (l_pageSize) + 1;
		// No, add the buffer. 

		
	// Make sure it's >= the minimum size.
	if ( st < l_pageCount ) st = l_pageCount;
		
	maj = (struct liballoc_major*)liballoc_alloc( st );

	if ( maj == NULL ) 
	{
		l_warningCount += 1;
		debugf( "liballoc: WARNING: liballoc_alloc( %i ) return NULL\n", st );
		return NULL;	// uh oh, we ran out of memory.
	}
		
	maj->prev 	= NULL;
	maj->next 	= NULL;
	maj->pages 	= st;
	maj->size 	= st * l_pageSize;
	maj->usage 	= sizeof(struct liballoc_major);
	maj->first 	= NULL;

	l_allocated += maj->size;

	//printf( "liballoc: Resource allocated %x of %i pages (%i bytes) for %i size.\n", maj, st, maj->size, size );

	//printf( "liballoc: Total memory usage = %i KB\n",  (int)((l_allocated / (1024))) );

		
	return maj;
}

void *kmalloc(size_t req_size)
{
	int startedBet = 0;
	unsigned long long bestSize = 0;
	void *p = NULL;
	uintptr_t diff;
	struct liballoc_major *maj;
	struct liballoc_minor *min;
	struct liballoc_minor *new_min;
	unsigned long size = req_size;

	// For alignment, we adjust size so there's enough space to align.
	if ( ALIGNMENT > 1 )
	{
		size += ALIGNMENT + ALIGN_INFO;
	}

	// So, ideally, we really want an alignment of 0 or 1 in order
	// to save space.
	
	liballoc_lock();

	if ( size == 0 )
	{
		l_warningCount += 1;
		liballoc_unlock();
		return kmalloc(1);
	}
	

	if ( l_memRoot == NULL )
	{
		// This is the first time we are being used.
		l_memRoot = allocate_new_page( size );
		if ( l_memRoot == NULL )
		{
		  liballoc_unlock();
		  return NULL;
		}
	}

	// Now we need to bounce through every major and find enough space....

	maj = l_memRoot;
	startedBet = 0;
	
	// Start at the best bet....
	if ( l_bestBet != NULL )
	{
		bestSize = l_bestBet->size - l_bestBet->usage;

		if ( bestSize > (size + sizeof(struct liballoc_minor)))
		{
			maj = l_bestBet;
			startedBet = 1;
		}
	}
	
	while ( maj != NULL )
	{
		diff  = maj->size - maj->usage;	
		// free memory in the block

		if ( bestSize < diff )
		{
			// Hmm.. this one has more memory then our bestBet. Remember!
			l_bestBet = maj;
			bestSize = diff;
		}
		
		// CASE 1:  There is not enough space in this major block.
		if ( diff < (size + sizeof( struct liballoc_minor )) )
		{
			// Another major block next to this one?
			if ( maj->next != NULL ) 
			{
				maj = maj->next;		// Hop to that one.
				continue;
			}

			if ( startedBet == 1 )		// If we started at the best bet,
			{							// let's start all over again.
				maj = l_memRoot;
				startedBet = 0;
				continue;
			}

			// Create a new major block next to this one and...
			maj->next = allocate_new_page( size );	// next one will be okay.
			if ( maj->next == NULL ) break;			// no more memory.
			maj->next->prev = maj;
			maj = maj->next;

			// .. fall through to CASE 2 ..
		}

		// CASE 2: It's a brand new block.
		if ( maj->first == NULL )
		{
			maj->first = (struct liballoc_minor*)((uintptr_t)maj + sizeof(struct liballoc_major) );

			
			maj->first->magic 		= LIBALLOC_MAGIC;
			maj->first->prev 		= NULL;
			maj->first->next 		= NULL;
			maj->first->block 		= maj;
			maj->first->size 		= size;
			maj->first->req_size 	= req_size;
			maj->usage 	+= size + sizeof( struct liballoc_minor );

			l_inuse += size;
						
			p = (void*)((uintptr_t)(maj->first) + sizeof( struct liballoc_minor ));

			ALIGN( p );
			
			liballoc_unlock();		// release the lock
			return p;
		}

		// CASE 3: Block in use and enough space at the start of the block.
		diff =  (uintptr_t)(maj->first);
		diff -= (uintptr_t)maj;
		diff -= sizeof(struct liballoc_major);

		if ( diff >= (size + sizeof(struct liballoc_minor)) )
		{
			// Yes, space in front. Squeeze in.
			maj->first->prev = (struct liballoc_minor*)((uintptr_t)maj + sizeof(struct liballoc_major) );
			maj->first->prev->next = maj->first;
			maj->first = maj->first->prev;
				
			maj->first->magic 	= LIBALLOC_MAGIC;
			maj->first->prev 	= NULL;
			maj->first->block 	= maj;
			maj->first->size 	= size;
			maj->first->req_size 	= req_size;
			maj->usage 			+= size + sizeof( struct liballoc_minor );

			l_inuse += size;

			p = (void*)((uintptr_t)(maj->first) + sizeof( struct liballoc_minor ));
			ALIGN( p );

			liballoc_unlock();		// release the lock
			return p;
		}
		
		// CASE 4: There is enough space in this block. But is it contiguous?
		min = maj->first;
		
		// Looping within the block now...
		while ( min != NULL )
		{
			// CASE 4.1: End of minors in a block. Space from last and end?
			if ( min->next == NULL )
			{
				// the rest of this block is free...  is it big enough?
				diff = (uintptr_t)(maj) + maj->size;
				diff -= (uintptr_t)min;
				diff -= sizeof( struct liballoc_minor );
				diff -= min->size; 
				// minus already existing usage..

				if ( diff >= (size + sizeof( struct liballoc_minor )) )
				{
					// yay....
					min->next = (struct liballoc_minor*)((uintptr_t)min + sizeof( struct liballoc_minor ) + min->size);
					min->next->prev = min;
					min = min->next;
					min->next = NULL;
					min->magic = LIBALLOC_MAGIC;
					min->block = maj;
					min->size = size;
					min->req_size = req_size;
					maj->usage += size + sizeof( struct liballoc_minor );

					l_inuse += size;
					
					p = (void*)((uintptr_t)min + sizeof( struct liballoc_minor ));
					ALIGN( p );

					liballoc_unlock();		// release the lock
					return p;
				}
			}

			// CASE 4.2: Is there space between two minors?
			if ( min->next != NULL )
			{
				// is the difference between here and next big enough?
				diff  = (uintptr_t)(min->next);
				diff -= (uintptr_t)min;
				diff -= sizeof( struct liballoc_minor );
				diff -= min->size;
				// minus our existing usage.

				if ( diff >= (size + sizeof( struct liballoc_minor )) )
				{
					// yay......
					new_min = (struct liballoc_minor*)((uintptr_t)min + sizeof( struct liballoc_minor ) + min->size);

					new_min->magic = LIBALLOC_MAGIC;
					new_min->next = min->next;
					new_min->prev = min;
					new_min->size = size;
					new_min->req_size = req_size;
					new_min->block = maj;
					min->next->prev = new_min;
					min->next = new_min;
					maj->usage += size + sizeof( struct liballoc_minor );
					
					l_inuse += size;
					
					p = (void*)((uintptr_t)new_min + sizeof( struct liballoc_minor ));
					ALIGN( p );
					
					liballoc_unlock();		// release the lock
					return p;
				}
			}	// min->next != NULL

			min = min->next;
		} // while min != NULL ...

		// CASE 5: Block full! Ensure next block and loop.
		if ( maj->next == NULL ) 
		{
			#ifdef DEBUG
			printf( "CASE 5: block full\n");
			FLUSH();
			#endif

			if ( startedBet == 1 )
			{
				maj = l_memRoot;
				startedBet = 0;
				continue;
			}
				
			// we've run out. we need more...
			maj->next = allocate_new_page( size );		// next one guaranteed to be okay
			if ( maj->next == NULL ) break;			//  uh oh,  no more memory.....
			maj->next->prev = maj;

		}

		maj = maj->next;
	} // while (maj != NULL)
	
	liballoc_unlock();		// release the lock

	return NULL;
}

void kfree(void *ptr)
{
	struct liballoc_minor *min;
	struct liballoc_major *maj;

	if ( ptr == NULL ) 
	{
		l_warningCount += 1;
		return;
	}

	UNALIGN( ptr );

	liballoc_lock();		// lockit

	min = (struct liballoc_minor*)((uintptr_t)ptr - sizeof( struct liballoc_minor ));
	
	if ( min->magic != LIBALLOC_MAGIC ) 
	{
		l_errorCount += 1;

		// Check for overrun errors. For all bytes of LIBALLOC_MAGIC 
		if ( 
			((min->magic & 0xFFFFFF) == (LIBALLOC_MAGIC & 0xFFFFFF)) || 
			((min->magic & 0xFFFF) == (LIBALLOC_MAGIC & 0xFFFF)) || 
			((min->magic & 0xFF) == (LIBALLOC_MAGIC & 0xFF)) 
		   )
		{
			l_possibleOverruns += 1;
		}
						
		/*				
		if ( min->magic == LIBALLOC_DEAD )
		{
			#if defined DEBUG || defined INFO
			printf( "liballoc: ERROR: multiple PREFIX(free)() attempt on %x from %x.\n", 
									ptr,
									__builtin_return_address(0) );
			FLUSH();
			#endif
		}
		else
		{
			#if defined DEBUG || defined INFO
			printf( "liballoc: ERROR: Bad PREFIX(free)( %x ) called from %x\n",
								ptr,
								__builtin_return_address(0) );
			FLUSH();
			#endif
		}
		*/

		// being lied to...
		liballoc_unlock();		// release the lock
		return;
	}


	maj = min->block;

	l_inuse -= min->size;

	maj->usage -= (min->size + sizeof( struct liballoc_minor ));
	min->magic  = LIBALLOC_DEAD;		// No mojo.

	if ( min->next != NULL ) min->next->prev = min->prev;
	if ( min->prev != NULL ) min->prev->next = min->next;

	if ( min->prev == NULL ) maj->first = min->next;	
						// Might empty the block. This was the first
						// minor.

	// We need to clean up after the majors now....

	if ( maj->first == NULL )	// Block completely unused.
	{
		if ( l_memRoot == maj ) l_memRoot = maj->next;
		if ( l_bestBet == maj ) l_bestBet = NULL;
		if ( maj->prev != NULL ) maj->prev->next = maj->next;
		if ( maj->next != NULL ) maj->next->prev = maj->prev;
		l_allocated -= maj->size;

		liballoc_free( maj, maj->pages );
	}
	else
	{
		if ( l_bestBet != NULL )
		{
			int bestSize = l_bestBet->size  - l_bestBet->usage;
			int majSize = maj->size - maj->usage;

			if ( majSize > bestSize ) l_bestBet = maj;
		}

	}
	
	liballoc_unlock();		// release the lock
}

void* kcalloc(size_t nobj, size_t size)
{
	   int real_size;
	   void *p;

	   real_size = nobj * size;
	   
	   p = kmalloc( real_size );

	   liballoc_memset( p, 0, real_size );

	   return p;
}

void*   krealloc(void *p, size_t size)
{
	void *ptr;
	struct liballoc_minor *min;
	unsigned int real_size;
	
	// Honour the case of size == 0 => free old and return NULL
	if ( size == 0 )
	{
		kfree( p );
		return NULL;
	}

	// In the case of a NULL pointer, return a simple malloc.
	if ( p == NULL ) return kmalloc( size );

	// Unalign the pointer if required.
	ptr = p;
	UNALIGN(ptr);

	liballoc_lock();		// lockit

	min = (struct liballoc_minor*)((uintptr_t)ptr - sizeof( struct liballoc_minor ));

	// Ensure it is a valid structure.
	if ( min->magic != LIBALLOC_MAGIC ) 
	{
		l_errorCount += 1;

		// Check for overrun errors. For all bytes of LIBALLOC_MAGIC 
		if ( 
			((min->magic & 0xFFFFFF) == (LIBALLOC_MAGIC & 0xFFFFFF)) || 
			((min->magic & 0xFFFF) == (LIBALLOC_MAGIC & 0xFFFF)) || 
			((min->magic & 0xFF) == (LIBALLOC_MAGIC & 0xFF)) 
			)
		{
			l_possibleOverruns += 1;
		}
						
		/*		
		if ( min->magic == LIBALLOC_DEAD )
		{
			#if defined DEBUG || defined INFO
			printf( "liballoc: ERROR: multiple PREFIX(free)() attempt on %x from %x.\n", 
									ptr,
									__builtin_return_address(0) );
			FLUSH();
			#endif
		}
		else
		{
			#if defined DEBUG || defined INFO
			printf( "liballoc: ERROR: Bad PREFIX(free)( %x ) called from %x\n",
								ptr,
								__builtin_return_address(0) );
			FLUSH();
			#endif
		}
		*/
		
		// being lied to...
		liballoc_unlock();		// release the lock
		return NULL;
	}	
	
	// Definitely a memory block.
	
	real_size = min->req_size;

	if ( real_size >= size ) 
	{
		min->req_size = size;
		liballoc_unlock();
		return p;
	}

	liballoc_unlock();

	// If we got here then we're reallocating to a block bigger than us.
	ptr = kmalloc( size );					// We need to allocate new memory
	liballoc_memcpy( ptr, p, real_size );
	kfree( p );

	return ptr;
}

void * __attribute__((weak)) memset(void * dest, int c, size_t n)
{
    unsigned char *s = dest;
    size_t k;

    /* Fill head and tail with minimal branching. Each
     * conditional ensures that all the subsequently used
     * offsets are well-defined and in the dest region. */

    if (!n) return dest;
    s[0] = s[n-1] = c;
    if (n <= 2) return dest;
    s[1] = s[n-2] = c;
    s[2] = s[n-3] = c;
    if (n <= 6) return dest;
    s[3] = s[n-4] = c;
    if (n <= 8) return dest;

    /* Advance pointer to align it at a 4-byte boundary,
     * and truncate n to a multiple of 4. The previous code
     * already took care of any head/tail that get cut off
     * by the alignment. */

    k = -(uintptr_t)s & 3;
    s += k;
    n -= k;
    n &= -4;
    n /= 4;

    uint32_t *ws = (uint32_t *)s;
    uint32_t wc = c & 0xFF;
    wc |= ((wc << 8) | (wc << 16) | (wc << 24));

    /* Pure C fallback with no aliasing violations. */
    for (; n; n--, ws++) *ws = wc;

    return dest;
}

/** This function is supposed to lock the memory data structures. It
 * could be as simple as disabling interrupts or acquiring a spinlock.
 * It's up to you to decide. 
 *
 * \return 0 if the lock was acquired successfully. Anything else is
 * failure.
 */

bool liballoc_is_locked = false;

int liballoc_lock( void ) {
	if( liballoc_is_locked ) {
		return 1;
	}

	liballoc_is_locked = true;

	return 0;
}


/** This function unlocks what was previously locked by the liballoc_lock
 * function.  If it disabled interrupts, it enables interrupts. If it
 * had acquiried a spinlock, it releases the spinlock. etc.
 *
 * \return 0 if the lock was successfully released.
 */
int liballoc_unlock( void ) {
    if( liballoc_is_locked ) {
		liballoc_is_locked = false;
		return 0;
	}

	return 1;
}

/** This is the hook into the local system which allocates pages. It
 * accepts an integer parameter which is the number of pages
 * required.  The page size was set up in the liballoc_init function.
 *
 * \return NULL if the pages were not allocated.
 * \return A pointer to the allocated memory.
 */

void * liballoc_alloc( size_t n ) {
	return (void *)page_allocate( n );
}

/** This frees previously allocated memory. The void* parameter passed
 * to the function is the exact same value returned from a previous
 * liballoc_alloc call.
 *
 * The integer value is the number of pages to free.
 *
 * \return 0 if the memory was successfully freed.
 */
int liballoc_free( void* m, size_t s ) {
	if( m ) { ; } //kill compiler warning

	if( s ) { ; } //kill compiler warning

	return 0;
};

