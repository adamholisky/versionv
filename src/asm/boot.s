.set MAGIC,    0x1BADB002 

.section .multiboot
.align 4
	.long MAGIC				/* mb magic key */
	.long 0x7				/* Flags: align, mem, video */
	.long -(MAGIC + 0x7)	/* Checksum */

	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	
	.long 1
	.long 80
	.long 25
	.long 0

.section .versionv_magic, "aw"
	.asciz "VersionV"
	.byte 0x01
	.byte 0x02 
	.byte 0x03
	.byte 0x04

.section .bootstrap_stack, "aw", @nobits
	.align 16
	stack_bottom:
	.skip 16384
	stack_top:

.section .bss, "aw", @nobits 
	.align 4096
	.global boot_page_directory
	boot_page_directory:
	.skip 4096
	.global boot_page_table
	boot_page_table:
	.skip 4096

.section .data
.global GDTR
.global GDT
GDTR:
	.word	GDT_END - GDT - 1
	.long	GDT
GDT:
NULL_SELECTOR:  	# 0x0
	.long 0x0
	.long 0x0
CODE_SELECTOR:		# 0x08
	.word 0xFFFF
	.word 0x0
	.byte 0x0
	.byte 0x9A
	.byte 0xCF
	.byte 0x0
DATA_SELECTOR:		# 0x10
	.word 0xFFF
	.word 0x0
	.byte 0x0
	.byte 0x92
	.byte 0xCF
	.byte 0x0
CODE_USER:			# 0x18
	.word 0xFFFF
	.word 0x0
	.byte 0x0
	.byte 0xFA
	.byte 0xCF
	.byte 0x0
DATA_USER:			# 0x20
	.word 0xFFFF
	.word 0x0
	.byte 0x0
	.byte 0xF2
	.byte 0xCF
	.byte 0x0
TSS:				# 0x28
	.long 0x0
	.long 0x0
GDT_END:
	
.section .text
.global _asm_kernel_start
.type _asm_kernel_start, @function
_asm_kernel_start:
	movl $(boot_page_table - 0xC0000000), %edi		/* EDI gets the physical page table  address */
	movl $0, %esi									/* 0 == first address mapped */
	movl $1024, %ecx								/* Map our pages */

stage1:	
	cmpl $0, %ecx
	dec %ecx

stage2:
	movl %esi, %edx									/* Load physical address into EDX */
	orl  $0x003, %edx								/* Make the kernel's phsyical mem present and writeable */
	movl %edx, (%edi)								/* Move table entry to address pointed to in edi */
	addl $4096, %esi								/* Increment esi (physical address) by 4k */
	addl $4, %edi									/* Increment the table entry by 1 (1 entry == 32 bits == 4 bytes) */
	loop stage1
 
stage3:
	/* Setup physical 0 and 0xC0000000 to be present, writable so when we load CR3 we don't error out */
	movl $(boot_page_table - 0xC0000000 + 0x003), boot_page_directory - 0xC0000000
	movl $(boot_page_table - 0xC0000000 + 0x003), boot_page_directory - 0xC0000000 + 768 * 4

	movl $(boot_page_directory - 0xC0000000), %ecx	/* Correct for linker 0xC0000000 offset */
	movl %ecx, %cr3

	movl %cr0, %ecx
	orl  $0x80010000, %ecx							/* Enable w/4kb paging */
	movl %ecx, %cr0


	lea  stage4, %ecx
	jmp  *%ecx										/* BSG: "Jump" */

stage4:
	lgdt GDTR
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %ss
	mov %ax, %es
	mov %ax, %fs 
	mov %ax, %gs

	jmp $0x08, $stage5

stage5:
	movl $0, boot_page_directory					/* Remove entry 0, since it's mapped now. Refresh cr3 */
	movl %cr3, %ecx
	movl %ecx, %cr3

	mov  $(stack_top), %esp							/* Setup the stack */

	addl $0xC0000000, %ebx
	push %ebx										/* Multiboot header pointer */
	push %eax										/* Magic number */

	xor %ebp, %ebp									/* NULL Stack for tracing purposes */

	call kernel_main

.global asm_refresh_cr3
asm_refresh_cr3:
	movl %cr3, %ecx
	movl %ecx, %cr3
	ret

.size _asm_kernel_start, . - _asm_kernel_start
