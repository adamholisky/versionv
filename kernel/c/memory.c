#include "kernel.h"
#include "multiboot.h"

//#define kdebug_memory_pages 1

extern page_directory_entry * boot_page_directory;
extern page_directory_entry * boot_page_table;
extern uint32_t _kernel_end;
extern void asm_refresh_cr3( void );
extern void asm_invalidate_page( void * p );

static const char * vv_magic_word = "VersionV";
uint32_t * physical_memory_base = (uint32_t *)0xFFFFFFFF;
uint32_t * phsyical_memory_top = (uint32_t *)0xFFFFFFFF;
uint32_t * kernel_virtual_memory_base = (uint32_t *)KERNEL_VIRT_HEAP_BASE;
uint32_t * kernel_virtual_memory_top = (uint32_t *)KERNEL_VIRT_HEAP_BASE;

page_directory_entry second_page_table[1024] __attribute__ ((aligned (4096)));
page_directory_entry another_page_table[1024] __attribute__ ((aligned (4096)));

page_directory_entry process_pd[1024] __attribute__ ((aligned (4096)));
page_directory_entry process_pt[1024] __attribute__ ((aligned (4096)));

//#define kdebug_memory
//#define kdebug_memory_pages

/**
 * @brief Initalize basic memory
 * 
 */

void memory_initalize( void ) {
	log_entry_enter();

	uint32_t mem_start = 0;
	uint32_t mem_size = 0;
	uint32_t alloc_start = (uint32_t)&_kernel_end - KERNEL_VIRT_LOAD_BASE;

	multiboot_info_t *mbh = get_multiboot_header();

	memset( (void *)another_page_table, 0, 1024 );

	klog( "Page Size: 0x%08X\n", page_size_in_bytes );
	

	for( int i = 0; i < mbh->mmap_length; i = i + sizeof(multiboot_memory_map_t)) {
        multiboot_memory_map_t* mm = (multiboot_memory_map_t*) (mbh->mmap_addr + i);
 
        if(mm->type == MULTIBOOT_MEMORY_AVAILABLE) {
			// This corrects for the weird last entry in the mmap saying we have an extra 1G?
			if( mm->addr_high == 0 ) {
				// For now let's just use the largest continual space, which works in QEMU
				if( mem_size < mm->len_low ) {
					mem_start = mm->addr_low; // 32 bit only
					mem_size = mm->len_low; // 32 bit only
				}
				
				klog("Start Addr: %x %x | Length: %x %x | Size: %x | Type: %d\n", mm->addr_high, mm->addr_low, mm->len_high, mm->len_low, mm->size, mm->type);
			}
        }
    }

	// Calculate the alloc start so it ends up on a 4k boundry
	//alloc_start = (alloc_start % 0x1000) + alloc_start;

	phsyical_memory_top = (uint32_t *)alloc_start;
	physical_memory_base = (uint32_t *)alloc_start;

	klog( "Usable memory detected:    0x%08X\n", mbh->mem_upper * 1024 );
	klog( "Physical memory base:      0x%08X\n", physical_memory_base );
	klog( "Virtual memory base:       0x%08X\n", kernel_virtual_memory_base );
	klog( "Memory allocatable:        0x%08X\n", mem_size );

	page_allocate( 1 );

	#ifdef kdebug_memory

	memory_test();

	#endif

	#ifdef kdebug_memory_pages

	page_directory_entry * kernel_page = (page_directory_entry *)(&boot_page_directory + 768);

	debugf( "----\n" );
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
	debugf( "----\n" );

	#endif

	void * process_address_space = kmalloc( 0x1000 );
	process_address_space = (void *)((uint32_t)process_address_space + 0x1000 - 0x0040);

	page_directory_entry * pde = (page_directory_entry *)&boot_page_directory;
	page_directory_entry * pte = (page_directory_entry *)&process_pt;

	#ifdef kdebug_memory_pages
	klog( "process_pt paddr:  0x%08X\n", ((uint32_t)process_pt - KERNEL_VIRT_LOAD_BASE) );
	klog( "process paddr sp:  0x%08X\n", (uint32_t)physical_memory_base + (uint32_t)process_address_space - KERNEL_VIRT_HEAP_BASE );
	klog( "process paddr>>11: 0x%08X\n", ((uint32_t)physical_memory_base + (uint32_t)process_address_space - KERNEL_VIRT_HEAP_BASE)>>11 );
	#endif

	pte->present = 1;
	pte->rw = 1;
	pte->address = ((uint32_t)physical_memory_base + (uint32_t)process_address_space - KERNEL_VIRT_HEAP_BASE)>>11;

	#ifdef kdebug_memory_pages
	klog( "pte->address: 0x%08X\n", pte->address<<11 );
	#endif

	pde->present = 1;
	pde->rw = 1;
	pde->address = ((uint32_t)process_pt - KERNEL_VIRT_LOAD_BASE) >> 11;

	//asm volatile("invlpg (%0)" ::"r" (pte) : "memory");
	asm_refresh_cr3();

	uint32_t * pmem = (uint32_t *)process_address_space;
	*(pmem + 1) = 0x0666;

	void * zero_addr_space = 0x00000000;
	uint32_t * zerozero = (uint32_t *)zero_addr_space;

	//#ifdef kdebug_memory_pages
	klog( "00   uint32_t: %08X\n", *(zerozero + 1) );
	klog( "pmem uint32_t: %08X\n", *(pmem + 1) );
	//#endif
	
	//dump_active_pt();

	log_entry_exit();
}

/**
 * @brief Get the physical memory base
 * 
 * @return uint32_t* Pointer to the physical memory base
 */
uint32_t * get_physical_memory_base( void ) {
	return physical_memory_base;
}

uint32_t * get_physical_addr_from_virt( uint32_t * virt ) {
	return (uint32_t *)((uint32_t)physical_memory_base + (uint32_t)virt - KERNEL_VIRT_HEAP_BASE);
}

/**
 * @brief Set the process PDE object
 * 
 * @param pte Pointer to the dage_directory_entry to copy into the main process PTE
 */
void set_task_pde( page_directory_entry * pte ) {
	page_directory_entry * pde = (page_directory_entry *)&boot_page_directory;

/* 	pde->present = 1;
	pde->rw = 1;
	pde->address = ((uint32_t)process_pt - KERNEL_VIRT_LOAD_BASE) >> 11;
 */
	memcpy( &process_pt, pte, sizeof( page_directory_entry ) * 1024 );

	// debugf( "pte: 0x%08X\n", (uint32_t)pte );
	// debugf( "pde->addr: 0x%08X\n", pde->address << 11 );
	// debugf( "pte->addr: 0x%08X\n", pte->address << 11 );

	page_directory_entry * pt = (page_directory_entry *)((pde[0].address << 11) + KERNEL_VIRT_LOAD_BASE);

	asm_refresh_cr3();

	//asm_invalidate_page( (pt[0].address << 11) );
	//asm_invalidate_page( &process_pt );

	/*
	kdebug_peek_at( 0 );

	klog( "Dumping active pages:\n" );
	dump_active_pt();
	klog( "End of active pages.\n" );
	
	klog( "pt[0].address: 0x%08X\n", pt[0].address );
	klog( "pt[0].address << 11: 0x%08X\n", (pt[0].address << 11) );
	klog( "pt[0].address << 11 + KVHB + PMB: 0x%08X\n", (pt[0].address << 11) + KERNEL_VIRT_HEAP_BASE - (uint32_t)get_physical_memory_base() );

	uint32_t *ad = (pt[0].address << 11) + KERNEL_VIRT_HEAP_BASE - (uint32_t)get_physical_memory_base();
	kdebug_peek_at( ad );
	*/
}

void dump_active_pt( void ) {
	page_directory_entry * pde = (page_directory_entry *)&boot_page_directory;

	for( int i = 0; i < 1024; i++ ) {
		if( pde[i].present == 1 ) {
			page_directory_entry *pt = (page_directory_entry *)((pde[i].address << 11) + KERNEL_VIRT_LOAD_BASE);

			for( int j = 0; j < 1024; j++ ) {
				if( pt[j].present == 1 ) {
					klog( "pd[%d]->pt[%d] is present pointing to phys mem: 0x%08X\n", i, j, (pt[j].address << 11) );
				} else {
					klog( "pd[%d]->pt[%d] is not present.\n", i, j );
				}
			}
		}
	}
}

/**
 * @brief Map the virtual address to the physical address
 * 
 * @param virt_addr 
 * @param phys_addr 
 * @return uint32_t* Returns the virtual address
 */
uint32_t * page_map( uint32_t *virt_addr, uint32_t *phys_addr ) {
	uint32_t pt_addr_physical = ((uint32_t)second_page_table) - KERNEL_VIRT_LOAD_BASE;
	uint32_t pd_index = 0;
	uint32_t pt_index = 0;
	page_directory_entry * pd;
	page_directory_entry * pt;

	// Find entry in BPD
	pd_index = (uint32_t)virt_addr >> 22;
	pt_index = ((uint32_t)virt_addr >> 12) & 0x03FF;

	// for now cheese it, allow the page fault test
	if( (uint32_t)virt_addr > 0xFF000000 ) {
		pt_addr_physical = (uint32_t)another_page_table - KERNEL_VIRT_LOAD_BASE;
		pt = (page_directory_entry *)(another_page_table + pt_index);
	} else {
		pt = (page_directory_entry *)(second_page_table + pt_index);
	}

	// Set the page directory entry up correctly
	pd = (page_directory_entry *)(&boot_page_directory + pd_index);

	if( pd->present == 1 ) {
		pt->present = 1;
		pt->rw = 1;
		pt->address = (uint32_t)phys_addr >> 11;
	} else {
		pd->present = 1;
		pd->rw = 1;
		pd->address = pt_addr_physical >> 11;

		pt->present = 1;
		pt->rw = 1;
		pt->address = (uint32_t)phys_addr >> 11;
	}

	#ifdef kdebug_memory_pages_more

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

	//k_log( sys_memory, level_info, "%d page(s) allocated at 0x%08X", num, return_pointer );

	return return_pointer;
}

#define memtest_dump( v ) klog( #v " mem dump: 0x%04X %04X",( ( uint32_t )( v ) >> 16 ), ( uint32_t )( v )&0xFFFF)

void memory_test( void ) {
	log_entry_enter();

	void * p2;
	void * p3;
	void * p4;
	void * p5;

	//memtest_dump( kernel_virtual_memory_top );

	/*
	void * p;
	p = liballoc_alloc( 4096 );
	printf( "liballoc_alloc( 4096 ) page into p\n" );
	memtest_dump( p );
	*/
	
	p2 = kmalloc( 0x256 );
	klog( "kmalloc(0x256) into p2" );
	//memtest_dump( p2 );

	klog( "kmalloc(0x512) into p3" );
	p3 = kmalloc( 0x512 );
	//memtest_dump( p3 );

	klog( "kmalloc(0x11000) into p4" );
	p4 = kmalloc( 0x11000 );
	//memtest_dump( p4 );

	klog( "kmalloc(0x11000) into p5" );
	p5 = kmalloc( 0x11000 );
	//memtest_dump( p5 );

	//memtest_dump( kernel_virtual_memory_top );
	
	liballoc_dump();

	log_entry_exit();
}
