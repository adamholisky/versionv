# VersionV

VersionV is a hobbist operating system that's being built with the goals of undertanding OS and low-level components better, and building basic applications on top of that understanding.

The key word above is that this is a **hobbiest** project, and contains **NO** code or ideas from my day job.

#### Goal 1: Implement major components of an OS

|Goal|Status|Comments|
|---|---|---|
|Paging|🟡|Paging w/hookups to processes and heap management|
|File system|🔴|Filesystem R/W|
|Module & Exec|🟡|Module loading and exec; ELF|
|CPL|🔴|Ring 0/3 execution|
|Abstractions|🔴|Device abstraction layer|
|Interrupts|🟡|Interrupt and exception handling|
|Dev interfaces|🟠|Debugging via DWARF and GDB interfaces|
|IPC|🔴|Basic signals and events|

#### Goal 2: Interface with hardware to better understand how it works
|Goal|Status|Comments|
|---|---|---|
|Basic I/O|🟡|Basic I/O (serial, terminal/ANSI, keyboard, mouse, etc...)|
|PCI|🟠|Bus management, device interactions|
|SATA|🔴|Basic r/w on drives|
|Ethernet|🔴|Send/recv via TCP/IP stack, run a simple webserver|
|USB|🔴|Get a 3rd party device working|
|VGA|🔴|Maybe some graphics interfaces|

### Legend
🟢 Goal achieved! Good enough for what I set out to do.

🔵 Basics working, maybe a few things finalized

🟡 This isn't an embarassment

🟠 I understand things, maybe? Probably not.

🔴 Not started

## Memory Maps

### Physical Memory Map
|Start|End|Notes|
|---|---|---|
|0000 0000|000F FFFF|Reserved for bios/etc; maps to 0xC000 0000|0xC00F FFFF in kernel space|
|0010 0000|00?? ????|Kernel loaded; maps to 0xC010 0000 in kernel |
|**** ****|**** ****|_kernel_end symbol (aligned 4k bound); must not be greater than 0x1000 0000 (256mb)|
|XXXX XXXX|FFFF FFFF|Free|

### Kernel Virtual Memory Map
|start|End|Notes|
|---|---|---|
|0000 0000|9FFF FFFF|Maps to loaded process|
|A000 0000|BFFF FFFF|Maps to loaded process (old kernel heap)|
|C000 0000|CFFF FFFF|Kernel code + binary + stack area + bios reserved|
|D000 0000|FFFF FFFF|Kernel heap|

### Process Virtual Memory Map
|Start|End|Notes|
|---|---|---|
|0000 0000|3FFF FFFF|Code + binary + stack area|
|4000 0000|BFFF FFFF|Heap|
|C000 0000|FFFF FFFF|Kernel reserved|

## Paging

* page_allocate( )
	* Allocates a continual block of virtual memory that is num pages long for process_id
* page_free()
	* ??
* page_get_directory( )
	* Returns the page directory structure for the current process
	
