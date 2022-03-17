# VersionV

Physical Memory Map
	0000 0000 -> 000F FFFF		Reserved for bios/etc; maps to 0xC000 0000 -> 0xC00F FFFF in kernel space
	0010 0000 -> 00?? ????		Kernel loaded; maps to 0xC010 0000 in kernel space
	**** **** -> **** ****  <-  _kernel_end symbol (aligned 4k bound); must not be greater than 0x1000 0000 (256mb)
	XXXX XXXX -> FFFF FFFF  <-  Free

Kernel Virtual Memory Map
	0000 0000 -> 9FFF FFFF		Maps to loaded process
	A000 0000 -> BFFF FFFF		Maps to loaded process (old kernel heap)
	C000 0000 -> CFFF FFFF		Kernel code + binary + stack area + bios reserved
	D000 0000 -> FFFF FFFF		Kernel heap


Process Virtual Memory Map
	0000 0000 -> 3FFF FFFF		Code + binary + stack area
	4000 0000 -> BFFF FFFF		Heap
	C000 0000 -> FFFF FFFF		Kernel reserved

Paging
	page_allocate( )
		Allocates a continual block of virtual memory that is num pages long for process_id
		Input:
			process_id
			num
		Output:
			pointer to beinning of allocated virtual memory page
	page_free()
		??
	page_get_directory( )
		Returns the page directory structure for the current process
	
