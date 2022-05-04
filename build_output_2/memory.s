	.file	"memory.c"
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 0 "/usr/local/osdev/versions/v" "kernel/c/memory.c"
	.section	.rodata
.LC0:
	.string	"System"
.LC1:
	.string	"Kernel"
.LC2:
	.string	"Intel8254"
.LC3:
	.string	"Memory"
.LC4:
	.string	"PCI"
.LC5:
	.string	"Interrupt"
.LC6:
	.string	"Paging"
.LC7:
	.string	"ELF"
	.data
	.align 32
	.type	sys_text, @object
	.size	sys_text, 32
sys_text:
	.long	.LC0
	.long	.LC1
	.long	.LC2
	.long	.LC3
	.long	.LC4
	.long	.LC5
	.long	.LC6
	.long	.LC7
	.section	.rodata
.LC8:
	.string	"0000"
.LC9:
	.string	"0001"
.LC10:
	.string	"0010"
.LC11:
	.string	"0011"
.LC12:
	.string	"0100"
.LC13:
	.string	"0101"
.LC14:
	.string	"0110"
.LC15:
	.string	"0111"
.LC16:
	.string	"1000"
.LC17:
	.string	"1001"
.LC18:
	.string	"1010"
.LC19:
	.string	"1011"
.LC20:
	.string	"1100"
.LC21:
	.string	"1101"
.LC22:
	.string	"1110"
.LC23:
	.string	"1111"
	.data
	.align 32
	.type	bit_array, @object
	.size	bit_array, 64
bit_array:
	.long	.LC8
	.long	.LC9
	.long	.LC10
	.long	.LC11
	.long	.LC12
	.long	.LC13
	.long	.LC14
	.long	.LC15
	.long	.LC16
	.long	.LC17
	.long	.LC18
	.long	.LC19
	.long	.LC20
	.long	.LC21
	.long	.LC22
	.long	.LC23
	.section	.rodata
.LC24:
	.string	"VersionV"
	.data
	.align 4
	.type	vv_magic_word, @object
	.size	vv_magic_word, 4
vv_magic_word:
	.long	.LC24
	.globl	physical_memory_base
	.align 4
	.type	physical_memory_base, @object
	.size	physical_memory_base, 4
physical_memory_base:
	.long	-1
	.globl	phsyical_memory_top
	.align 4
	.type	phsyical_memory_top, @object
	.size	phsyical_memory_top, 4
phsyical_memory_top:
	.long	-1
	.globl	kernel_virtual_memory_base
	.align 4
	.type	kernel_virtual_memory_base, @object
	.size	kernel_virtual_memory_base, 4
kernel_virtual_memory_base:
	.long	-805306368
	.globl	kernel_virtual_memory_top
	.align 4
	.type	kernel_virtual_memory_top, @object
	.size	kernel_virtual_memory_top, 4
kernel_virtual_memory_top:
	.long	-805306368
	.globl	second_page_table
	.section	.bss
	.align 4096
	.type	second_page_table, @object
	.size	second_page_table, 4096
second_page_table:
	.zero	4096
	.globl	graphics_page_table
	.align 4096
	.type	graphics_page_table, @object
	.size	graphics_page_table, 4096
graphics_page_table:
	.zero	4096
	.globl	another_page_table
	.align 4096
	.type	another_page_table, @object
	.size	another_page_table, 4096
another_page_table:
	.zero	4096
	.globl	process_pd
	.align 4096
	.type	process_pd, @object
	.size	process_pd, 4096
process_pd:
	.zero	4096
	.globl	process_pt
	.align 4096
	.type	process_pt, @object
	.size	process_pt, 4096
process_pt:
	.zero	4096
	.section	.rodata
.LC25:
	.string	"[\033[0;34;49m%s:%d\033[0;00;00m] "
.LC26:
	.string	"Enter\n"
.LC27:
	.string	"paging_level_active"
.LC28:
	.string	"Paging level: %d\n"
.LC29:
	.string	"Page Size: 0x%08X\n"
	.align 4
.LC30:
	.string	"Start Addr: %x %x | Length: %x %x | Size: %x | Type: %d\n"
.LC31:
	.string	"alloc start: %08X\n"
.LC32:
	.string	"alloc start mod: %08X\n"
.LC33:
	.string	"alloc addition: %08X\n"
	.align 4
.LC34:
	.string	"Usable memory detected:    0x%08X\n"
	.align 4
.LC35:
	.string	"Physical memory base:      0x%08X\n"
	.align 4
.LC36:
	.string	"Virtual memory base:       0x%08X\n"
	.align 4
.LC37:
	.string	"Memory allocatable:        0x%08X\n"
.LC38:
	.string	"%X --> %x\n"
.LC39:
	.string	"00   uint32_t: %08X\n"
.LC40:
	.string	"pmem uint32_t: %08X\n"
.LC41:
	.string	"0x0 and pmem are not equal!\n"
.LC42:
	.string	"Exit\n"
	.text
	.globl	memory_initalize
	.type	memory_initalize, @function
memory_initalize:
.LFB8:
	.file 1 "kernel/c/memory.c"
	.loc 1 35 31
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$76, %esp
	.cfi_offset 7, -12
	.cfi_offset 6, -16
	.cfi_offset 3, -20
	.loc 1 36 2
	subl	$12, %esp
	pushl	$1
	call	set_debug_output
	addl	$16, %esp
	.loc 1 36 4
	subl	$4, %esp
	pushl	$36
	pushl	$__FUNCTION__.2
	pushl	$.LC25
	call	printf_
	addl	$16, %esp
	.loc 1 36 71
	subl	$12, %esp
	pushl	$.LC26
	call	printf_
	addl	$16, %esp
	.loc 1 36 93
	subl	$12, %esp
	pushl	$0
	call	set_debug_output
	addl	$16, %esp
	.loc 1 40 22
	movb	$2, paging_level_active
	.loc 1 42 11
	movl	$0, -36(%ebp)
	.loc 1 43 11
	movl	$0, -28(%ebp)
	.loc 1 44 25
	movl	$_kernel_end, %eax
	.loc 1 44 11
	addl	$1073741824, %eax
	movl	%eax, -40(%ebp)
	.loc 1 46 26
	call	get_multiboot_header
	movl	%eax, -44(%ebp)
	.loc 1 48 2
	subl	$4, %esp
	pushl	$1024
	pushl	$0
	pushl	$another_page_table
	call	memset
	addl	$16, %esp
	.loc 1 49 2
	subl	$4, %esp
	pushl	$1024
	pushl	$0
	pushl	$graphics_page_table
	call	memset
	addl	$16, %esp
	.loc 1 51 2
	subl	$12, %esp
	pushl	$51
	pushl	$__FUNCTION__.2
	pushl	$paging_level_active
	pushl	$.LC27
	pushl	$1
	call	klog_variable_func
	addl	$32, %esp
	.loc 1 52 2
	subl	$12, %esp
	pushl	$1
	call	set_debug_output
	addl	$16, %esp
	.loc 1 52 4
	subl	$4, %esp
	pushl	$52
	pushl	$__FUNCTION__.2
	pushl	$.LC25
	call	printf_
	addl	$16, %esp
	.loc 1 52 71
	movzbl	paging_level_active, %eax
	movzbl	%al, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$.LC28
	call	printf_
	addl	$16, %esp
	.loc 1 52 125
	subl	$12, %esp
	pushl	$0
	call	set_debug_output
	addl	$16, %esp
	.loc 1 53 2
	subl	$12, %esp
	pushl	$1
	call	set_debug_output
	addl	$16, %esp
	.loc 1 53 4
	subl	$4, %esp
	pushl	$53
	pushl	$__FUNCTION__.2
	pushl	$.LC25
	call	printf_
	addl	$16, %esp
	.loc 1 53 71
	subl	$8, %esp
	pushl	$2097152
	pushl	$.LC29
	call	printf_
	addl	$16, %esp
	.loc 1 53 117
	subl	$12, %esp
	pushl	$0
	call	set_debug_output
	addl	$16, %esp
.LBB2:
	.loc 1 56 11
	movl	$0, -32(%ebp)
	.loc 1 56 2
	jmp	.L2
.L5:
.LBB3:
	.loc 1 57 68
	movl	-44(%ebp), %eax
	movl	48(%eax), %edx
	.loc 1 57 80
	movl	-32(%ebp), %eax
	addl	%edx, %eax
	.loc 1 57 33
	movl	%eax, -72(%ebp)
	.loc 1 59 14
	movl	-72(%ebp), %eax
	movl	20(%eax), %eax
	.loc 1 59 11
	cmpl	$1, %eax
	jne	.L3
	.loc 1 61 10
	movl	-72(%ebp), %eax
	movl	8(%eax), %eax
	.loc 1 61 6
	testl	%eax, %eax
	jne	.L3
	.loc 1 63 22
	movl	-72(%ebp), %eax
	movl	12(%eax), %eax
	.loc 1 63 7
	cmpl	%eax, -28(%ebp)
	jnb	.L4
	.loc 1 64 16
	movl	-72(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, -36(%ebp)
	.loc 1 65 15
	movl	-72(%ebp), %eax
	movl	12(%eax), %eax
	movl	%eax, -28(%ebp)
.L4:
	.loc 1 68 5
	subl	$12, %esp
	pushl	$1
	call	set_debug_output
	addl	$16, %esp
	.loc 1 68 7
	subl	$4, %esp
	pushl	$68
	pushl	$__FUNCTION__.2
	pushl	$.LC25
	call	printf_
	addl	$16, %esp
	.loc 1 68 74
	movl	-72(%ebp), %eax
	movl	20(%eax), %ebx
	movl	-72(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -84(%ebp)
	movl	-72(%ebp), %eax
	movl	12(%eax), %ecx
	movl	%ecx, -88(%ebp)
	movl	-72(%ebp), %eax
	movl	16(%eax), %ecx
	movl	-72(%ebp), %eax
	movl	4(%eax), %edx
	movl	-72(%ebp), %eax
	movl	8(%eax), %eax
	subl	$4, %esp
	pushl	%ebx
	pushl	-84(%ebp)
	pushl	-88(%ebp)
	pushl	%ecx
	pushl	%edx
	pushl	%eax
	pushl	$.LC30
	call	printf_
	addl	$32, %esp
	.loc 1 68 222
	subl	$12, %esp
	pushl	$0
	call	set_debug_output
	addl	$16, %esp
.L3:
.LBE3:
	.loc 1 56 46 discriminator 2
	movl	-32(%ebp), %eax
	addl	$24, %eax
	.loc 1 56 42 discriminator 2
	movl	%eax, -32(%ebp)
.L2:
	.loc 1 56 25 discriminator 1
	movl	-44(%ebp), %eax
	movl	44(%eax), %edx
	.loc 1 56 20 discriminator 1
	movl	-32(%ebp), %eax
	cmpl	%eax, %edx
	ja	.L5
.LBE2:
	.loc 1 78 3
	subl	$12, %esp
	pushl	$1
	call	set_debug_output
	addl	$16, %esp
	.loc 1 78 5
	subl	$4, %esp
	pushl	$78
	pushl	$__FUNCTION__.2
	pushl	$.LC25
	call	printf_
	addl	$16, %esp
	.loc 1 78 72
	subl	$8, %esp
	pushl	-40(%ebp)
	pushl	$.LC31
	call	printf_
	addl	$16, %esp
	.loc 1 78 119
	subl	$12, %esp
	pushl	$0
	call	set_debug_output
	addl	$16, %esp
	.loc 1 79 3
	subl	$12, %esp
	pushl	$1
	call	set_debug_output
	addl	$16, %esp
	.loc 1 79 5
	subl	$4, %esp
	pushl	$79
	pushl	$__FUNCTION__.2
	pushl	$.LC25
	call	printf_
	addl	$16, %esp
	.loc 1 79 72
	movl	-40(%ebp), %eax
	andl	$2097151, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$.LC32
	call	printf_
	addl	$16, %esp
	.loc 1 79 134
	subl	$12, %esp
	pushl	$0
	call	set_debug_output
	addl	$16, %esp
	.loc 1 80 3
	subl	$12, %esp
	pushl	$1
	call	set_debug_output
	addl	$16, %esp
	.loc 1 80 5
	subl	$4, %esp
	pushl	$80
	pushl	$__FUNCTION__.2
	pushl	$.LC25
	call	printf_
	addl	$16, %esp
	.loc 1 80 131
	movl	-40(%ebp), %eax
	andl	$2097151, %eax
	movl	%eax, %edx
	.loc 1 80 72
	movl	$2097152, %eax
	subl	%edx, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$.LC33
	call	printf_
	addl	$16, %esp
	.loc 1 80 146
	subl	$12, %esp
	pushl	$0
	call	set_debug_output
	addl	$16, %esp
	.loc 1 81 40
	movl	-40(%ebp), %eax
	andl	$-2097152, %eax
	.loc 1 81 15
	addl	$2097152, %eax
	movl	%eax, -40(%ebp)
	.loc 1 84 24
	movl	-40(%ebp), %eax
	.loc 1 84 22
	movl	%eax, phsyical_memory_top
	.loc 1 85 25
	movl	-40(%ebp), %eax
	.loc 1 85 23
	movl	%eax, physical_memory_base
	.loc 1 87 2
	subl	$12, %esp
	pushl	$1
	call	set_debug_output
	addl	$16, %esp
	.loc 1 87 4
	subl	$4, %esp
	pushl	$87
	pushl	$__FUNCTION__.2
	pushl	$.LC25
	call	printf_
	addl	$16, %esp
	.loc 1 87 122
	movl	-44(%ebp), %eax
	movl	8(%eax), %eax
	.loc 1 87 71
	sall	$10, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$.LC34
	call	printf_
	addl	$16, %esp
	.loc 1 87 144
	subl	$12, %esp
	pushl	$0
	call	set_debug_output
	addl	$16, %esp
	.loc 1 88 2
	subl	$12, %esp
	pushl	$1
	call	set_debug_output
	addl	$16, %esp
	.loc 1 88 4
	subl	$4, %esp
	pushl	$88
	pushl	$__FUNCTION__.2
	pushl	$.LC25
	call	printf_
	addl	$16, %esp
	.loc 1 88 71
	movl	physical_memory_base, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$.LC35
	call	printf_
	addl	$16, %esp
	.loc 1 88 143
	subl	$12, %esp
	pushl	$0
	call	set_debug_output
	addl	$16, %esp
	.loc 1 89 2
	subl	$12, %esp
	pushl	$1
	call	set_debug_output
	addl	$16, %esp
	.loc 1 89 4
	subl	$4, %esp
	pushl	$89
	pushl	$__FUNCTION__.2
	pushl	$.LC25
	call	printf_
	addl	$16, %esp
	.loc 1 89 71
	movl	kernel_virtual_memory_base, %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$.LC36
	call	printf_
	addl	$16, %esp
	.loc 1 89 149
	subl	$12, %esp
	pushl	$0
	call	set_debug_output
	addl	$16, %esp
	.loc 1 90 2
	subl	$12, %esp
	pushl	$1
	call	set_debug_output
	addl	$16, %esp
	.loc 1 90 4
	subl	$4, %esp
	pushl	$90
	pushl	$__FUNCTION__.2
	pushl	$.LC25
	call	printf_
	addl	$16, %esp
	.loc 1 90 71
	subl	$8, %esp
	pushl	-28(%ebp)
	pushl	$.LC37
	call	printf_
	addl	$16, %esp
	.loc 1 90 131
	subl	$12, %esp
	pushl	$0
	call	set_debug_output
	addl	$16, %esp
	.loc 1 92 2
	subl	$12, %esp
	pushl	$5
	call	page_allocate
	addl	$16, %esp
	.loc 1 122 33
	subl	$12, %esp
	pushl	$2097152
	call	kmalloc
	addl	$16, %esp
	movl	%eax, -48(%ebp)
	.loc 1 123 35
	movl	-48(%ebp), %eax
	.loc 1 123 80
	addl	$2097088, %eax
	.loc 1 123 24
	movl	%eax, -48(%ebp)
	.loc 1 125 2
	subl	$4, %esp
	pushl	$1024
	pushl	$0
	pushl	$process_pt
	call	memset
	addl	$16, %esp
	.loc 1 130 14
	movl	$paging_pdpt, -52(%ebp)
	.loc 1 131 14
	movl	$process_pt, -56(%ebp)
	.loc 1 132 12
	movl	-48(%ebp), %eax
	movl	%eax, %ecx
	movl	%eax, %ebx
	sarl	$31, %ebx
	.loc 1 132 46
	movl	physical_memory_base, %eax
	cltd
	.loc 1 132 44
	addl	%ecx, %eax
	adcl	%ebx, %edx
	.loc 1 132 91
	addl	$805306499, %eax
	adcl	$-1, %edx
	.loc 1 132 8
	movl	-56(%ebp), %ecx
	movl	%eax, (%ecx)
	movl	%edx, 4(%ecx)
	.loc 1 140 11
	movl	$process_pt, %eax
	cltd
	.loc 1 140 47
	addl	$1073741825, %eax
	adcl	$-1, %edx
	.loc 1 140 8
	movl	-52(%ebp), %ecx
	movl	%eax, (%ecx)
	movl	%edx, 4(%ecx)
	.loc 1 141 31
	movl	-52(%ebp), %eax
	movl	4(%eax), %edx
	movl	(%eax), %eax
	.loc 1 141 29
	movl	%eax, %ebx
	andb	$-1, %bh
	movl	%ebx, -80(%ebp)
	movl	%edx, %eax
	andl	$0, %eax
	movl	%eax, -76(%ebp)
	.loc 1 141 8
	movl	-52(%ebp), %eax
	movl	-80(%ebp), %ecx
	movl	-76(%ebp), %ebx
	movl	%ecx, (%eax)
	movl	%ebx, 4(%eax)
	.loc 1 142 31
	movl	-56(%ebp), %eax
	movl	4(%eax), %edx
	movl	(%eax), %eax
	.loc 1 142 29
	movl	%eax, %ebx
	andb	$-1, %bh
	movl	%ebx, %esi
	movl	%edx, %eax
	andl	$0, %eax
	movl	%eax, %edi
	.loc 1 142 8
	movl	-56(%ebp), %eax
	movl	%esi, (%eax)
	movl	%edi, 4(%eax)
	.loc 1 148 2
	movl	-56(%ebp), %eax
/APP
/  148 "kernel/c/memory.c" 1
	invlpg (%eax)
/  0 "" 2
	.loc 1 149 2
/NO_APP
	call	asm_refresh_cr3
	.loc 1 151 13
	movl	-48(%ebp), %eax
	movl	%eax, -60(%ebp)
	.loc 1 152 9
	movl	-60(%ebp), %eax
	addl	$4, %eax
	.loc 1 152 14
	movl	$1638, (%eax)
	.loc 1 154 2
	subl	$12, %esp
	pushl	$1
	call	set_debug_output
	addl	$16, %esp
	.loc 1 154 4
	subl	$4, %esp
	pushl	$154
	pushl	$__FUNCTION__.2
	pushl	$.LC25
	call	printf_
	addl	$16, %esp
	.loc 1 154 115
	movl	-60(%ebp), %eax
	addl	$4, %eax
	.loc 1 154 72
	movl	(%eax), %eax
	movl	-60(%ebp), %edx
	addl	$4, %edx
	subl	$4, %esp
	pushl	%eax
	pushl	%edx
	pushl	$.LC38
	call	printf_
	addl	$16, %esp
	.loc 1 154 124
	subl	$12, %esp
	pushl	$0
	call	set_debug_output
	addl	$16, %esp
	.loc 1 156 9
	movl	$0, -64(%ebp)
	.loc 1 157 13
	movl	-64(%ebp), %eax
	movl	%eax, -68(%ebp)
	.loc 1 158 13
	movl	-68(%ebp), %eax
	addl	$8, %eax
	.loc 1 158 18
	movl	$-1162167622, (%eax)
	.loc 1 160 2
	subl	$12, %esp
	pushl	$1
	call	set_debug_output
	addl	$16, %esp
	.loc 1 160 4
	subl	$4, %esp
	pushl	$160
	pushl	$__FUNCTION__.2
	pushl	$.LC25
	call	printf_
	addl	$16, %esp
	.loc 1 160 117
	movl	-68(%ebp), %eax
	addl	$4, %eax
	.loc 1 160 72
	movl	(%eax), %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$.LC39
	call	printf_
	addl	$16, %esp
	.loc 1 160 125
	subl	$12, %esp
	pushl	$0
	call	set_debug_output
	addl	$16, %esp
	.loc 1 161 2
	subl	$12, %esp
	pushl	$1
	call	set_debug_output
	addl	$16, %esp
	.loc 1 161 4
	subl	$4, %esp
	pushl	$161
	pushl	$__FUNCTION__.2
	pushl	$.LC25
	call	printf_
	addl	$16, %esp
	.loc 1 161 113
	movl	-60(%ebp), %eax
	addl	$4, %eax
	.loc 1 161 72
	movl	(%eax), %eax
	subl	$8, %esp
	pushl	%eax
	pushl	$.LC40
	call	printf_
	addl	$16, %esp
	.loc 1 161 121
	subl	$12, %esp
	pushl	$0
	call	set_debug_output
	addl	$16, %esp
	.loc 1 163 17
	movl	-68(%ebp), %eax
	addl	$4, %eax
	.loc 1 163 6
	movl	(%eax), %edx
	.loc 1 163 32
	movl	-60(%ebp), %eax
	addl	$4, %eax
	.loc 1 163 25
	movl	(%eax), %eax
	.loc 1 163 4
	cmpl	%eax, %edx
	je	.L6
	.loc 1 164 3
	subl	$12, %esp
	pushl	$.LC41
	call	kpanic
	addl	$16, %esp
.L6:
	.loc 1 167 2
	subl	$12, %esp
	pushl	$1
	call	set_debug_output
	addl	$16, %esp
	.loc 1 167 4
	subl	$4, %esp
	pushl	$167
	pushl	$__FUNCTION__.2
	pushl	$.LC25
	call	printf_
	addl	$16, %esp
	.loc 1 167 72
	subl	$12, %esp
	pushl	$.LC42
	call	printf_
	addl	$16, %esp
	.loc 1 167 93
	subl	$12, %esp
	pushl	$0
	call	set_debug_output
	addl	$16, %esp
	.loc 1 168 1
	nop
	leal	-12(%ebp), %esp
	popl	%ebx
	.cfi_restore 3
	popl	%esi
	.cfi_restore 6
	popl	%edi
	.cfi_restore 7
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE8:
	.size	memory_initalize, .-memory_initalize
	.globl	get_physical_memory_base
	.type	get_physical_memory_base, @function
get_physical_memory_base:
.LFB9:
	.loc 1 175 45
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	.loc 1 176 9
	movl	physical_memory_base, %eax
	.loc 1 177 1
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE9:
	.size	get_physical_memory_base, .-get_physical_memory_base
	.globl	get_physical_addr_from_virt
	.type	get_physical_addr_from_virt, @function
get_physical_addr_from_virt:
.LFB10:
	.loc 1 179 59
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	.loc 1 180 22
	movl	physical_memory_base, %eax
	movl	%eax, %edx
	.loc 1 180 55
	movl	8(%ebp), %eax
	.loc 1 180 53
	addl	%edx, %eax
	.loc 1 180 70
	addl	$805306368, %eax
	.loc 1 181 1
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE10:
	.size	get_physical_addr_from_virt, .-get_physical_addr_from_virt
	.globl	set_task_pde
	.type	set_task_pde, @function
set_task_pde:
.LFB11:
	.loc 1 188 49
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	.loc 1 195 2
	subl	$4, %esp
	pushl	$4096
	pushl	8(%ebp)
	pushl	$process_pt
	call	memcpy
	addl	$16, %esp
	.loc 1 203 2
	call	asm_refresh_cr3
	.loc 1 222 1
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE11:
	.size	set_task_pde, .-set_task_pde
	.section	.rodata
	.align 4
.LC43:
	.string	"Error: page is null. i = %d, j - %d\n"
	.align 4
.LC44:
	.string	"pd[%d].page[%03d] present, virt 0x%08X --> phys mem: 0x%08X\n"
	.text
	.globl	dump_active_pt
	.type	dump_active_pt, @function
dump_active_pt:
.LFB12:
	.loc 1 224 29
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%edi
	pushl	%esi
	subl	$64, %esp
	.cfi_offset 7, -12
	.cfi_offset 6, -16
	.loc 1 226 13
	movl	$paging_pdpt, -12(%ebp)
.LBB4:
	.loc 1 231 11
	movl	$0, -16(%ebp)
	.loc 1 231 2
	jmp	.L13
.L19:
	.loc 1 234 7
	movl	-12(%ebp), %eax
	movl	4(%eax), %edx
	movl	(%eax), %eax
	.loc 1 234 12
	movl	%eax, %ecx
	andl	$1, %ecx
	movl	%ecx, %esi
	movl	%edx, %eax
	andl	$0, %eax
	movl	%eax, %edi
	.loc 1 234 5
	movl	%esi, %eax
	xorb	$0, %ah
	movl	%eax, -64(%ebp)
	movl	%edi, %eax
	xorb	$0, %ah
	movl	%eax, -60(%ebp)
	movl	-64(%ebp), %edx
	movl	-60(%ebp), %ecx
	movl	%ecx, %eax
	orl	%edx, %eax
	testl	%eax, %eax
	je	.L14
.LBB5:
	.loc 1 238 20
	movl	-12(%ebp), %eax
	movl	4(%eax), %edx
	movl	(%eax), %eax
	.loc 1 238 25
	movl	%eax, %ecx
	andl	$-4096, %ecx
	movl	%ecx, -48(%ebp)
	movl	%edx, %eax
	andl	$1048575, %eax
	movl	%eax, -44(%ebp)
	.loc 1 238 14
	movl	-48(%ebp), %eax
	movl	-44(%ebp), %edx
	addl	$-1073741824, %eax
	adcl	$0, %edx
	movl	%eax, -32(%ebp)
	movl	%edx, -28(%ebp)
	.loc 1 247 22
	movl	-32(%ebp), %eax
	.loc 1 247 15
	movl	%eax, -20(%ebp)
.LBB6:
	.loc 1 253 13
	movl	$0, -24(%ebp)
	.loc 1 253 4
	jmp	.L15
.L18:
.LBB7:
	.loc 1 254 7
	cmpl	$0, -20(%ebp)
	jne	.L16
	.loc 1 255 6
	subl	$12, %esp
	pushl	$1
	call	set_debug_output
	addl	$16, %esp
	.loc 1 255 8
	subl	$4, %esp
	pushl	$255
	pushl	$__FUNCTION__.1
	pushl	$.LC25
	call	printf_
	addl	$16, %esp
	.loc 1 255 76
	subl	$4, %esp
	pushl	-24(%ebp)
	pushl	-16(%ebp)
	pushl	$.LC43
	call	printf_
	addl	$16, %esp
	.loc 1 255 134
	subl	$12, %esp
	pushl	$0
	call	set_debug_output
	addl	$16, %esp
.L16:
	.loc 1 259 25
	movl	-20(%ebp), %eax
	movl	4(%eax), %edx
	movl	(%eax), %eax
	.loc 1 259 14
	movl	%eax, %ecx
	andl	$-1048576, %ecx
	movl	%ecx, -40(%ebp)
	movl	%edx, %eax
	andl	$1048575, %eax
	movl	%eax, -36(%ebp)
	.loc 1 264 9
	movl	-20(%ebp), %eax
	movl	4(%eax), %edx
	movl	(%eax), %eax
	.loc 1 264 15
	movl	%eax, %ecx
	andl	$1, %ecx
	movl	%ecx, -56(%ebp)
	movl	%edx, %eax
	andl	$0, %eax
	movl	%eax, -52(%ebp)
	.loc 1 264 7
	movl	-56(%ebp), %eax
	movl	-52(%ebp), %edx
	movl	%eax, %ecx
	xorb	$0, %ch
	movl	%ecx, -72(%ebp)
	movl	%edx, %eax
	xorb	$0, %ah
	movl	%eax, -68(%ebp)
	movl	-72(%ebp), %edx
	movl	-68(%ebp), %ecx
	movl	%ecx, %eax
	orl	%edx, %eax
	testl	%eax, %eax
	je	.L17
	.loc 1 265 6
	subl	$12, %esp
	pushl	$1
	call	set_debug_output
	addl	$16, %esp
	.loc 1 265 8
	subl	$4, %esp
	pushl	$265
	pushl	$__FUNCTION__.1
	pushl	$.LC25
	call	printf_
	addl	$16, %esp
	.loc 1 265 173
	movl	-16(%ebp), %eax
	sall	$9, %eax
	movl	%eax, %edx
	movl	-24(%ebp), %eax
	addl	%edx, %eax
	.loc 1 265 76
	sall	$21, %eax
	subl	$8, %esp
	pushl	-36(%ebp)
	pushl	-40(%ebp)
	pushl	%eax
	pushl	-24(%ebp)
	pushl	-16(%ebp)
	pushl	$.LC44
	call	printf_
	addl	$32, %esp
	.loc 1 265 204
	subl	$12, %esp
	pushl	$0
	call	set_debug_output
	addl	$16, %esp
.L17:
.LBE7:
	.loc 1 253 30 discriminator 2
	addl	$1, -24(%ebp)
	.loc 1 253 38 discriminator 2
	addl	$8, -20(%ebp)
.L15:
	.loc 1 253 22 discriminator 1
	cmpl	$511, -24(%ebp)
	jle	.L18
.L14:
.LBE6:
.LBE5:
	.loc 1 231 26 discriminator 2
	addl	$1, -16(%ebp)
	.loc 1 231 33 discriminator 2
	addl	$8, -12(%ebp)
.L13:
	.loc 1 231 20 discriminator 1
	cmpl	$3, -16(%ebp)
	jle	.L19
.LBE4:
	.loc 1 272 1
	nop
	nop
	leal	-8(%ebp), %esp
	popl	%esi
	.cfi_restore 6
	popl	%edi
	.cfi_restore 7
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE12:
	.size	dump_active_pt, .-dump_active_pt
	.globl	page_map
	.type	page_map, @function
page_map:
.LFB13:
	.loc 1 281 65
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%esi
	pushl	%ebx
	subl	$32, %esp
	.cfi_offset 6, -12
	.cfi_offset 3, -16
	.loc 1 282 11
	movl	$0, -12(%ebp)
	.loc 1 286 24
	movl	8(%ebp), %ecx
	.loc 1 286 11
	shrl	$30, %ecx
	movl	%ecx, -16(%ebp)
	.loc 1 287 23
	movl	8(%ebp), %ecx
	.loc 1 287 57
	movl	-16(%ebp), %ebx
	sall	$30, %ebx
	.loc 1 287 43
	subl	%ebx, %ecx
	.loc 1 287 11
	shrl	$21, %ecx
	movl	%ecx, -20(%ebp)
	.loc 1 288 51
	movl	-16(%ebp), %ecx
	sall	$3, %ecx
	.loc 1 288 12
	addl	$paging_pdpt, %ecx
	movl	%ecx, -24(%ebp)
	.loc 1 289 45
	movl	-20(%ebp), %ecx
	sall	$3, %ecx
	.loc 1 289 12
	addl	$paging_pd, %ecx
	movl	%ecx, -28(%ebp)
	.loc 1 297 14
	movl	12(%ebp), %ecx
	.loc 1 297 34
	orb	$-125, %cl
	movl	$0, %ebx
	.loc 1 297 12
	movl	-28(%ebp), %esi
	movl	%ecx, (%esi)
	movl	%ebx, 4(%esi)
	.loc 1 298 35
	movl	-28(%ebp), %ecx
	movl	4(%ecx), %ebx
	movl	(%ecx), %ecx
	.loc 1 298 33
	movl	%ecx, %esi
	andl	$-1, %esi
	movl	%esi, %eax
	andl	$0, %ebx
	movl	%ebx, %edx
	.loc 1 298 12
	movl	-28(%ebp), %ecx
	movl	%eax, (%ecx)
	movl	%edx, 4(%ecx)
	.loc 1 312 2
	movl	-28(%ebp), %eax
/APP
/  312 "kernel/c/memory.c" 1
	invlpg (%eax)
/  0 "" 2
	.loc 1 313 2
/NO_APP
	call	asm_refresh_cr3
	.loc 1 406 9
	movl	8(%ebp), %eax
	.loc 1 407 1
	addl	$32, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%esi
	.cfi_restore 6
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE13:
	.size	page_map, .-page_map
	.globl	page_allocate
	.type	page_allocate, @function
page_allocate:
.LFB14:
	.loc 1 409 42
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	.loc 1 410 13
	movl	kernel_virtual_memory_top, %eax
	movl	%eax, -16(%ebp)
.LBB8:
	.loc 1 412 16
	movl	$0, -12(%ebp)
	.loc 1 412 2
	jmp	.L23
.L24:
	.loc 1 413 3 discriminator 3
	movl	phsyical_memory_top, %edx
	movl	kernel_virtual_memory_top, %eax
	subl	$8, %esp
	pushl	%edx
	pushl	%eax
	call	page_map
	addl	$16, %esp
	.loc 1 414 44 discriminator 3
	movl	kernel_virtual_memory_top, %eax
	.loc 1 414 80 discriminator 3
	addl	$2097152, %eax
	.loc 1 414 29 discriminator 3
	movl	%eax, kernel_virtual_memory_top
	.loc 1 415 38 discriminator 3
	movl	phsyical_memory_top, %eax
	.loc 1 415 68 discriminator 3
	addl	$2097152, %eax
	.loc 1 415 23 discriminator 3
	movl	%eax, phsyical_memory_top
	.loc 1 412 33 discriminator 3
	addl	$1, -12(%ebp)
.L23:
	.loc 1 412 25 discriminator 1
	movl	-12(%ebp), %eax
	cmpl	8(%ebp), %eax
	jb	.L24
.LBE8:
	.loc 1 424 9
	movl	-16(%ebp), %eax
	.loc 1 425 1
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE14:
	.size	page_allocate, .-page_allocate
	.section	.rodata
.LC45:
	.string	"kmalloc(0x256) into p2\n"
.LC46:
	.string	"kmalloc(0x512) into p3\n"
.LC47:
	.string	"kmalloc(0x11000) into p4\n"
.LC48:
	.string	"kmalloc(0x11000) into p5\n"
	.text
	.globl	memory_test
	.type	memory_test, @function
memory_test:
.LFB15:
	.loc 1 429 26
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	.loc 1 430 2
	subl	$12, %esp
	pushl	$1
	call	set_debug_output
	addl	$16, %esp
	.loc 1 430 4
	subl	$4, %esp
	pushl	$430
	pushl	$__FUNCTION__.0
	pushl	$.LC25
	call	printf_
	addl	$16, %esp
	.loc 1 430 72
	subl	$12, %esp
	pushl	$.LC26
	call	printf_
	addl	$16, %esp
	.loc 1 430 94
	subl	$12, %esp
	pushl	$0
	call	set_debug_output
	addl	$16, %esp
	.loc 1 446 7
	subl	$12, %esp
	pushl	$598
	call	kmalloc
	addl	$16, %esp
	movl	%eax, -12(%ebp)
	.loc 1 447 2
	subl	$12, %esp
	pushl	$1
	call	set_debug_output
	addl	$16, %esp
	.loc 1 447 4
	subl	$4, %esp
	pushl	$447
	pushl	$__FUNCTION__.0
	pushl	$.LC25
	call	printf_
	addl	$16, %esp
	.loc 1 447 72
	subl	$12, %esp
	pushl	$.LC45
	call	printf_
	addl	$16, %esp
	.loc 1 447 111
	subl	$12, %esp
	pushl	$0
	call	set_debug_output
	addl	$16, %esp
	.loc 1 450 2
	subl	$12, %esp
	pushl	$1
	call	set_debug_output
	addl	$16, %esp
	.loc 1 450 4
	subl	$4, %esp
	pushl	$450
	pushl	$__FUNCTION__.0
	pushl	$.LC25
	call	printf_
	addl	$16, %esp
	.loc 1 450 72
	subl	$12, %esp
	pushl	$.LC46
	call	printf_
	addl	$16, %esp
	.loc 1 450 111
	subl	$12, %esp
	pushl	$0
	call	set_debug_output
	addl	$16, %esp
	.loc 1 451 7
	subl	$12, %esp
	pushl	$1298
	call	kmalloc
	addl	$16, %esp
	movl	%eax, -16(%ebp)
	.loc 1 454 2
	subl	$12, %esp
	pushl	$1
	call	set_debug_output
	addl	$16, %esp
	.loc 1 454 4
	subl	$4, %esp
	pushl	$454
	pushl	$__FUNCTION__.0
	pushl	$.LC25
	call	printf_
	addl	$16, %esp
	.loc 1 454 72
	subl	$12, %esp
	pushl	$.LC47
	call	printf_
	addl	$16, %esp
	.loc 1 454 113
	subl	$12, %esp
	pushl	$0
	call	set_debug_output
	addl	$16, %esp
	.loc 1 455 7
	subl	$12, %esp
	pushl	$69632
	call	kmalloc
	addl	$16, %esp
	movl	%eax, -20(%ebp)
	.loc 1 458 2
	subl	$12, %esp
	pushl	$1
	call	set_debug_output
	addl	$16, %esp
	.loc 1 458 4
	subl	$4, %esp
	pushl	$458
	pushl	$__FUNCTION__.0
	pushl	$.LC25
	call	printf_
	addl	$16, %esp
	.loc 1 458 72
	subl	$12, %esp
	pushl	$.LC48
	call	printf_
	addl	$16, %esp
	.loc 1 458 113
	subl	$12, %esp
	pushl	$0
	call	set_debug_output
	addl	$16, %esp
	.loc 1 459 7
	subl	$12, %esp
	pushl	$69632
	call	kmalloc
	addl	$16, %esp
	movl	%eax, -24(%ebp)
	.loc 1 464 2
	call	liballoc_dump
	.loc 1 466 2
	subl	$12, %esp
	pushl	$1
	call	set_debug_output
	addl	$16, %esp
	.loc 1 466 4
	subl	$4, %esp
	pushl	$466
	pushl	$__FUNCTION__.0
	pushl	$.LC25
	call	printf_
	addl	$16, %esp
	.loc 1 466 72
	subl	$12, %esp
	pushl	$.LC42
	call	printf_
	addl	$16, %esp
	.loc 1 466 93
	subl	$12, %esp
	pushl	$0
	call	set_debug_output
	addl	$16, %esp
	.loc 1 467 1
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE15:
	.size	memory_test, .-memory_test
	.section	.rodata
	.align 4
	.type	__FUNCTION__.2, @object
	.size	__FUNCTION__.2, 17
__FUNCTION__.2:
	.string	"memory_initalize"
	.align 4
	.type	__FUNCTION__.1, @object
	.size	__FUNCTION__.1, 15
__FUNCTION__.1:
	.string	"dump_active_pt"
	.align 4
	.type	__FUNCTION__.0, @object
	.size	__FUNCTION__.0, 12
__FUNCTION__.0:
	.string	"memory_test"
	.weak	memset
	.text
.Letext0:
	.file 2 "/usr/local/osdev/versions/v/libcvv/include/_types/_size_t.h"
	.file 3 "/usr/local/osdev/versions/v/libcvv/include/_types/_uint32_t.h"
	.file 4 "/usr/local/osdev/versions/v/libcvv/include/_types/_uint64_t.h"
	.file 5 "/usr/local/osdev/versions/v/libcvv/include/_types/_uint8_t.h"
	.file 6 "/usr/local/osdev/versions/v/kernel/include/memory.h"
	.file 7 "/usr/local/osdev/versions/v/kernel/include/debug.h"
	.file 8 "/usr/local/osdev/versions/v/kernel/include/multiboot.h"
	.file 9 "/usr/local/osdev/versions/v/kernel/include/globals.h"
	.file 10 "/usr/local/osdev/versions/v/kernel/include/kmalloc.h"
	.file 11 "/usr/local/osdev/versions/v/libcvv/include/string.h"
	.file 12 "/usr/local/osdev/versions/v/libcvv/include/printf.h"
	.file 13 "/usr/local/osdev/versions/v/kernel/include/terminal.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0xa54
	.value	0x5
	.byte	0x1
	.byte	0x4
	.long	.Ldebug_abbrev0
	.uleb128 0x22
	.long	.LASF145
	.byte	0x1d
	.long	.LASF0
	.long	.LASF1
	.long	.Ltext0
	.long	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.long	.LASF2
	.uleb128 0x3
	.long	.LASF9
	.byte	0x2
	.byte	0x4
	.byte	0x17
	.long	0x39
	.uleb128 0x4
	.byte	0x4
	.byte	0x7
	.long	.LASF3
	.uleb128 0x4
	.byte	0xc
	.byte	0x4
	.long	.LASF4
	.uleb128 0x4
	.byte	0x2
	.byte	0x5
	.long	.LASF5
	.uleb128 0x23
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x4
	.byte	0x8
	.byte	0x5
	.long	.LASF6
	.uleb128 0x4
	.byte	0x1
	.byte	0x6
	.long	.LASF7
	.uleb128 0x4
	.byte	0x2
	.byte	0x7
	.long	.LASF8
	.uleb128 0x3
	.long	.LASF10
	.byte	0x3
	.byte	0x4
	.byte	0x16
	.long	0x76
	.uleb128 0x4
	.byte	0x4
	.byte	0x7
	.long	.LASF11
	.uleb128 0x3
	.long	.LASF12
	.byte	0x4
	.byte	0x4
	.byte	0x1c
	.long	0x89
	.uleb128 0x4
	.byte	0x8
	.byte	0x7
	.long	.LASF13
	.uleb128 0x3
	.long	.LASF14
	.byte	0x5
	.byte	0x4
	.byte	0x17
	.long	0x9c
	.uleb128 0x4
	.byte	0x1
	.byte	0x8
	.long	.LASF15
	.uleb128 0x11
	.long	.LASF96
	.byte	0x9
	.byte	0x5
	.byte	0x10
	.long	0x90
	.uleb128 0x4
	.byte	0x1
	.byte	0x6
	.long	.LASF16
	.uleb128 0xe
	.long	0xaf
	.uleb128 0x15
	.byte	0x4
	.byte	0x6
	.byte	0x37
	.byte	0x9
	.long	0x147
	.uleb128 0x6
	.long	.LASF17
	.byte	0x38
	.byte	0xa
	.long	0x90
	.byte	0x1
	.byte	0
	.uleb128 0x24
	.string	"rw"
	.byte	0x6
	.byte	0x39
	.byte	0xa
	.long	0x90
	.byte	0x1
	.byte	0x1
	.uleb128 0x6
	.long	.LASF18
	.byte	0x3a
	.byte	0xa
	.long	0x90
	.byte	0x1
	.byte	0x2
	.uleb128 0x6
	.long	.LASF19
	.byte	0x3b
	.byte	0xa
	.long	0x90
	.byte	0x1
	.byte	0x3
	.uleb128 0x6
	.long	.LASF20
	.byte	0x3c
	.byte	0xa
	.long	0x90
	.byte	0x1
	.byte	0x4
	.uleb128 0x6
	.long	.LASF21
	.byte	0x3d
	.byte	0xa
	.long	0x90
	.byte	0x1
	.byte	0x5
	.uleb128 0x6
	.long	.LASF22
	.byte	0x3e
	.byte	0xa
	.long	0x90
	.byte	0x1
	.byte	0x6
	.uleb128 0x6
	.long	.LASF23
	.byte	0x3f
	.byte	0xa
	.long	0x90
	.byte	0x1
	.byte	0x7
	.uleb128 0x6
	.long	.LASF24
	.byte	0x40
	.byte	0xa
	.long	0x90
	.byte	0x3
	.byte	0x8
	.uleb128 0x6
	.long	.LASF25
	.byte	0x41
	.byte	0xb
	.long	0x6a
	.byte	0x14
	.byte	0xb
	.byte	0
	.uleb128 0x3
	.long	.LASF26
	.byte	0x6
	.byte	0x42
	.byte	0x3
	.long	0xbb
	.uleb128 0x8
	.long	0x6a
	.uleb128 0x25
	.byte	0x4
	.uleb128 0x19
	.long	0x158
	.uleb128 0x8
	.long	0x147
	.uleb128 0x26
	.string	"sys"
	.byte	0x7
	.byte	0x4
	.long	0x76
	.byte	0x7
	.byte	0x12
	.byte	0x6
	.long	0x1a7
	.uleb128 0x9
	.long	.LASF27
	.byte	0
	.uleb128 0x9
	.long	.LASF28
	.byte	0x1
	.uleb128 0x9
	.long	.LASF29
	.byte	0x2
	.uleb128 0x9
	.long	.LASF30
	.byte	0x3
	.uleb128 0x9
	.long	.LASF31
	.byte	0x4
	.uleb128 0x9
	.long	.LASF32
	.byte	0x5
	.uleb128 0x9
	.long	.LASF33
	.byte	0x6
	.uleb128 0x9
	.long	.LASF34
	.byte	0x7
	.byte	0
	.uleb128 0xa
	.long	0x1b7
	.long	0x1b7
	.uleb128 0xd
	.long	0x39
	.byte	0x7
	.byte	0
	.uleb128 0x8
	.long	0xb6
	.uleb128 0x5
	.long	.LASF35
	.byte	0x7
	.byte	0x1d
	.byte	0x15
	.long	0x1a7
	.uleb128 0x5
	.byte	0x3
	.long	sys_text
	.uleb128 0xa
	.long	0x1b7
	.long	0x1de
	.uleb128 0xd
	.long	0x39
	.byte	0xf
	.byte	0
	.uleb128 0x5
	.long	.LASF36
	.byte	0x7
	.byte	0x28
	.byte	0x15
	.long	0x1ce
	.uleb128 0x5
	.byte	0x3
	.long	bit_array
	.uleb128 0x8
	.long	0xaf
	.uleb128 0x3
	.long	.LASF37
	.byte	0x8
	.byte	0x5e
	.byte	0x17
	.long	0x9c
	.uleb128 0x3
	.long	.LASF38
	.byte	0x8
	.byte	0x5f
	.byte	0x18
	.long	0x63
	.uleb128 0x3
	.long	.LASF39
	.byte	0x8
	.byte	0x60
	.byte	0x16
	.long	0x76
	.uleb128 0x3
	.long	.LASF40
	.byte	0x8
	.byte	0x61
	.byte	0x1c
	.long	0x89
	.uleb128 0x12
	.long	.LASF46
	.byte	0x10
	.byte	0x7d
	.long	0x261
	.uleb128 0x1
	.long	.LASF41
	.byte	0x7f
	.byte	0x16
	.long	0x20d
	.byte	0
	.uleb128 0x1
	.long	.LASF42
	.byte	0x80
	.byte	0x16
	.long	0x20d
	.byte	0x4
	.uleb128 0x1
	.long	.LASF43
	.byte	0x81
	.byte	0x16
	.long	0x20d
	.byte	0x8
	.uleb128 0x1
	.long	.LASF44
	.byte	0x82
	.byte	0x16
	.long	0x20d
	.byte	0xc
	.byte	0
	.uleb128 0x3
	.long	.LASF45
	.byte	0x8
	.byte	0x84
	.byte	0x2c
	.long	0x225
	.uleb128 0x12
	.long	.LASF47
	.byte	0x10
	.byte	0x87
	.long	0x2a9
	.uleb128 0x1a
	.string	"num"
	.byte	0x89
	.byte	0x16
	.long	0x20d
	.byte	0
	.uleb128 0x1
	.long	.LASF48
	.byte	0x8a
	.byte	0x16
	.long	0x20d
	.byte	0x4
	.uleb128 0x1
	.long	.LASF43
	.byte	0x8b
	.byte	0x16
	.long	0x20d
	.byte	0x8
	.uleb128 0x1
	.long	.LASF49
	.byte	0x8c
	.byte	0x16
	.long	0x20d
	.byte	0xc
	.byte	0
	.uleb128 0x3
	.long	.LASF50
	.byte	0x8
	.byte	0x8e
	.byte	0x33
	.long	0x26d
	.uleb128 0x1b
	.byte	0x10
	.byte	0xa3
	.long	0x2d3
	.uleb128 0x1c
	.long	.LASF51
	.byte	0xa5
	.byte	0x23
	.long	0x261
	.uleb128 0x1c
	.long	.LASF52
	.byte	0xa6
	.byte	0x2a
	.long	0x2a9
	.byte	0
	.uleb128 0x15
	.byte	0x8
	.byte	0x8
	.byte	0xcd
	.byte	0x5
	.long	0x2f5
	.uleb128 0x1
	.long	.LASF53
	.byte	0xcf
	.byte	0x1a
	.long	0x20d
	.byte	0
	.uleb128 0x1
	.long	.LASF54
	.byte	0xd0
	.byte	0x1a
	.long	0x201
	.byte	0x4
	.byte	0
	.uleb128 0x15
	.byte	0x6
	.byte	0x8
	.byte	0xd2
	.byte	0x5
	.long	0x347
	.uleb128 0x1
	.long	.LASF55
	.byte	0xd4
	.byte	0x19
	.long	0x1f5
	.byte	0
	.uleb128 0x1
	.long	.LASF56
	.byte	0xd5
	.byte	0x19
	.long	0x1f5
	.byte	0x1
	.uleb128 0x1
	.long	.LASF57
	.byte	0xd6
	.byte	0x19
	.long	0x1f5
	.byte	0x2
	.uleb128 0x1
	.long	.LASF58
	.byte	0xd7
	.byte	0x19
	.long	0x1f5
	.byte	0x3
	.uleb128 0x1
	.long	.LASF59
	.byte	0xd8
	.byte	0x19
	.long	0x1f5
	.byte	0x4
	.uleb128 0x1
	.long	.LASF60
	.byte	0xd9
	.byte	0x19
	.long	0x1f5
	.byte	0x5
	.byte	0
	.uleb128 0x1b
	.byte	0x8
	.byte	0xcb
	.long	0x359
	.uleb128 0x1d
	.long	0x2d3
	.uleb128 0x1d
	.long	0x2f5
	.byte	0
	.uleb128 0x12
	.long	.LASF61
	.byte	0x78
	.byte	0x90
	.long	0x4ad
	.uleb128 0x1
	.long	.LASF62
	.byte	0x93
	.byte	0x16
	.long	0x20d
	.byte	0
	.uleb128 0x1
	.long	.LASF63
	.byte	0x96
	.byte	0x16
	.long	0x20d
	.byte	0x4
	.uleb128 0x1
	.long	.LASF64
	.byte	0x97
	.byte	0x16
	.long	0x20d
	.byte	0x8
	.uleb128 0x1
	.long	.LASF65
	.byte	0x9a
	.byte	0x16
	.long	0x20d
	.byte	0xc
	.uleb128 0x1
	.long	.LASF66
	.byte	0x9d
	.byte	0x16
	.long	0x20d
	.byte	0x10
	.uleb128 0x1
	.long	.LASF67
	.byte	0xa0
	.byte	0x16
	.long	0x20d
	.byte	0x14
	.uleb128 0x1
	.long	.LASF68
	.byte	0xa1
	.byte	0x16
	.long	0x20d
	.byte	0x18
	.uleb128 0x1a
	.string	"u"
	.byte	0xa7
	.byte	0x5
	.long	0x2b5
	.byte	0x1c
	.uleb128 0x1
	.long	.LASF69
	.byte	0xaa
	.byte	0x16
	.long	0x20d
	.byte	0x2c
	.uleb128 0x1
	.long	.LASF70
	.byte	0xab
	.byte	0x16
	.long	0x20d
	.byte	0x30
	.uleb128 0x1
	.long	.LASF71
	.byte	0xae
	.byte	0x16
	.long	0x20d
	.byte	0x34
	.uleb128 0x1
	.long	.LASF72
	.byte	0xaf
	.byte	0x16
	.long	0x20d
	.byte	0x38
	.uleb128 0x1
	.long	.LASF73
	.byte	0xb2
	.byte	0x16
	.long	0x20d
	.byte	0x3c
	.uleb128 0x1
	.long	.LASF74
	.byte	0xb5
	.byte	0x16
	.long	0x20d
	.byte	0x40
	.uleb128 0x1
	.long	.LASF75
	.byte	0xb8
	.byte	0x16
	.long	0x20d
	.byte	0x44
	.uleb128 0x1
	.long	.LASF76
	.byte	0xbb
	.byte	0x16
	.long	0x20d
	.byte	0x48
	.uleb128 0x1
	.long	.LASF77
	.byte	0xbc
	.byte	0x16
	.long	0x20d
	.byte	0x4c
	.uleb128 0x1
	.long	.LASF78
	.byte	0xbd
	.byte	0x16
	.long	0x201
	.byte	0x50
	.uleb128 0x1
	.long	.LASF79
	.byte	0xbe
	.byte	0x16
	.long	0x201
	.byte	0x52
	.uleb128 0x1
	.long	.LASF80
	.byte	0xbf
	.byte	0x16
	.long	0x201
	.byte	0x54
	.uleb128 0x1
	.long	.LASF81
	.byte	0xc0
	.byte	0x16
	.long	0x201
	.byte	0x56
	.uleb128 0x1
	.long	.LASF82
	.byte	0xc2
	.byte	0x16
	.long	0x219
	.byte	0x58
	.uleb128 0x1
	.long	.LASF83
	.byte	0xc3
	.byte	0x16
	.long	0x20d
	.byte	0x60
	.uleb128 0x1
	.long	.LASF84
	.byte	0xc4
	.byte	0x16
	.long	0x20d
	.byte	0x64
	.uleb128 0x1
	.long	.LASF85
	.byte	0xc5
	.byte	0x16
	.long	0x20d
	.byte	0x68
	.uleb128 0x1
	.long	.LASF86
	.byte	0xc6
	.byte	0x15
	.long	0x1f5
	.byte	0x6c
	.uleb128 0x1
	.long	.LASF87
	.byte	0xca
	.byte	0x15
	.long	0x1f5
	.byte	0x6d
	.uleb128 0x27
	.long	0x347
	.byte	0x70
	.byte	0
	.uleb128 0x3
	.long	.LASF88
	.byte	0x8
	.byte	0xdd
	.byte	0x1f
	.long	0x359
	.uleb128 0x12
	.long	.LASF89
	.byte	0x18
	.byte	0xe6
	.long	0x50d
	.uleb128 0x1
	.long	.LASF48
	.byte	0xe8
	.byte	0x16
	.long	0x20d
	.byte	0
	.uleb128 0x1
	.long	.LASF90
	.byte	0xe9
	.byte	0x16
	.long	0x20d
	.byte	0x4
	.uleb128 0x1
	.long	.LASF91
	.byte	0xea
	.byte	0x16
	.long	0x20d
	.byte	0x8
	.uleb128 0x1
	.long	.LASF92
	.byte	0xeb
	.byte	0x16
	.long	0x20d
	.byte	0xc
	.uleb128 0x1
	.long	.LASF93
	.byte	0xec
	.byte	0x16
	.long	0x20d
	.byte	0x10
	.uleb128 0x1
	.long	.LASF94
	.byte	0xf4
	.byte	0x16
	.long	0x20d
	.byte	0x14
	.byte	0
	.uleb128 0x3
	.long	.LASF95
	.byte	0x8
	.byte	0xf6
	.byte	0x25
	.long	0x4b9
	.uleb128 0x11
	.long	.LASF97
	.byte	0x1
	.byte	0x8
	.byte	0x11
	.long	0x6a
	.uleb128 0x11
	.long	.LASF98
	.byte	0x1
	.byte	0xb
	.byte	0x1f
	.long	0x15f
	.uleb128 0x11
	.long	.LASF99
	.byte	0x1
	.byte	0xc
	.byte	0x1f
	.long	0x15f
	.uleb128 0x5
	.long	.LASF100
	.byte	0x1
	.byte	0xe
	.byte	0x15
	.long	0x1b7
	.uleb128 0x5
	.byte	0x3
	.long	vv_magic_word
	.uleb128 0x13
	.long	.LASF101
	.byte	0xf
	.long	0x153
	.uleb128 0x5
	.byte	0x3
	.long	physical_memory_base
	.uleb128 0x13
	.long	.LASF102
	.byte	0x10
	.long	0x153
	.uleb128 0x5
	.byte	0x3
	.long	phsyical_memory_top
	.uleb128 0x13
	.long	.LASF103
	.byte	0x11
	.long	0x153
	.uleb128 0x5
	.byte	0x3
	.long	kernel_virtual_memory_base
	.uleb128 0x13
	.long	.LASF104
	.byte	0x12
	.long	0x153
	.uleb128 0x5
	.byte	0x3
	.long	kernel_virtual_memory_top
	.uleb128 0xa
	.long	0x147
	.long	0x5a0
	.uleb128 0x28
	.long	0x39
	.value	0x3ff
	.byte	0
	.uleb128 0xf
	.long	.LASF105
	.byte	0x14
	.long	0x58f
	.uleb128 0x5
	.byte	0x3
	.long	second_page_table
	.uleb128 0xf
	.long	.LASF106
	.byte	0x15
	.long	0x58f
	.uleb128 0x5
	.byte	0x3
	.long	graphics_page_table
	.uleb128 0xf
	.long	.LASF107
	.byte	0x16
	.long	0x58f
	.uleb128 0x5
	.byte	0x3
	.long	another_page_table
	.uleb128 0xf
	.long	.LASF108
	.byte	0x18
	.long	0x58f
	.uleb128 0x5
	.byte	0x3
	.long	process_pd
	.uleb128 0xf
	.long	.LASF109
	.byte	0x19
	.long	0x58f
	.uleb128 0x5
	.byte	0x3
	.long	process_pt
	.uleb128 0x1e
	.long	.LASF110
	.byte	0xa
	.byte	0x2f
	.byte	0x6
	.uleb128 0x14
	.long	.LASF112
	.byte	0xb
	.byte	0x3e
	.byte	0x7
	.long	0x158
	.long	0x618
	.uleb128 0x2
	.long	0x15a
	.uleb128 0x2
	.long	0x61d
	.uleb128 0x2
	.long	0x2d
	.byte	0
	.uleb128 0x8
	.long	0x622
	.uleb128 0x19
	.long	0x618
	.uleb128 0x29
	.uleb128 0x16
	.long	.LASF114
	.byte	0x7
	.byte	0x54
	.long	0x635
	.uleb128 0x2
	.long	0x1f0
	.uleb128 0x1f
	.byte	0
	.uleb128 0x1e
	.long	.LASF111
	.byte	0x1
	.byte	0x9
	.byte	0xd
	.uleb128 0x14
	.long	.LASF113
	.byte	0xa
	.byte	0x28
	.byte	0x7
	.long	0x158
	.long	0x653
	.uleb128 0x2
	.long	0x2d
	.byte	0
	.uleb128 0x16
	.long	.LASF115
	.byte	0x7
	.byte	0x5b
	.long	0x678
	.uleb128 0x2
	.long	0x6a
	.uleb128 0x2
	.long	0x1f0
	.uleb128 0x2
	.long	0x158
	.uleb128 0x2
	.long	0x1f0
	.uleb128 0x2
	.long	0x6a
	.byte	0
	.uleb128 0x14
	.long	.LASF116
	.byte	0xa
	.byte	0x2e
	.byte	0x1e
	.long	0x158
	.long	0x698
	.uleb128 0x2
	.long	0x158
	.uleb128 0x2
	.long	0x4e
	.uleb128 0x2
	.long	0x2d
	.byte	0
	.uleb128 0x2a
	.long	.LASF146
	.byte	0x8
	.value	0x117
	.byte	0x14
	.long	0x6a5
	.uleb128 0x8
	.long	0x4ad
	.uleb128 0x14
	.long	.LASF117
	.byte	0xc
	.byte	0x3d
	.byte	0x5
	.long	0x4e
	.long	0x6c1
	.uleb128 0x2
	.long	0x1b7
	.uleb128 0x1f
	.byte	0
	.uleb128 0x16
	.long	.LASF118
	.byte	0xd
	.byte	0x18
	.long	0x6d2
	.uleb128 0x2
	.long	0x6d2
	.byte	0
	.uleb128 0x4
	.byte	0x1
	.byte	0x2
	.long	.LASF119
	.uleb128 0x2b
	.long	.LASF130
	.byte	0x1
	.value	0x1ad
	.byte	0x6
	.long	.LFB15
	.long	.LFE15-.LFB15
	.uleb128 0x1
	.byte	0x9c
	.long	0x738
	.uleb128 0x17
	.long	.LASF132
	.long	0x748
	.uleb128 0x5
	.byte	0x3
	.long	__FUNCTION__.0
	.uleb128 0x10
	.string	"p2"
	.value	0x1b0
	.byte	0x9
	.long	0x158
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x10
	.string	"p3"
	.value	0x1b1
	.byte	0x9
	.long	0x158
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x10
	.string	"p4"
	.value	0x1b2
	.byte	0x9
	.long	0x158
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x10
	.string	"p5"
	.value	0x1b3
	.byte	0x9
	.long	0x158
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0xa
	.long	0xb6
	.long	0x748
	.uleb128 0xd
	.long	0x39
	.byte	0xb
	.byte	0
	.uleb128 0xe
	.long	0x738
	.uleb128 0x20
	.long	.LASF121
	.value	0x199
	.long	0x153
	.long	.LFB14
	.long	.LFE14-.LFB14
	.uleb128 0x1
	.byte	0x9c
	.long	0x79d
	.uleb128 0x2c
	.string	"num"
	.byte	0x1
	.value	0x199
	.byte	0x24
	.long	0x6a
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0xb
	.long	.LASF120
	.value	0x19a
	.byte	0xd
	.long	0x153
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0xc
	.long	.LBB8
	.long	.LBE8-.LBB8
	.uleb128 0x10
	.string	"i"
	.value	0x19c
	.byte	0x10
	.long	0x6a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.byte	0
	.uleb128 0x20
	.long	.LASF122
	.value	0x119
	.long	0x153
	.long	.LFB13
	.long	.LFE13-.LFB13
	.uleb128 0x1
	.byte	0x9c
	.long	0x825
	.uleb128 0x21
	.long	.LASF123
	.byte	0x20
	.long	0x153
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x21
	.long	.LASF124
	.byte	0x35
	.long	0x153
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0xb
	.long	.LASF125
	.value	0x11a
	.byte	0xb
	.long	0x6a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0xb
	.long	.LASF126
	.value	0x11e
	.byte	0xb
	.long	0x6a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0xb
	.long	.LASF127
	.value	0x11f
	.byte	0xb
	.long	0x6a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0xb
	.long	.LASF128
	.value	0x120
	.byte	0xc
	.long	0x825
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0xb
	.long	.LASF129
	.value	0x121
	.byte	0xc
	.long	0x825
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x2d
	.long	.LASF132
	.long	0x83a
	.byte	0
	.uleb128 0x8
	.long	0x7d
	.uleb128 0xa
	.long	0xb6
	.long	0x83a
	.uleb128 0xd
	.long	0x39
	.byte	0x8
	.byte	0
	.uleb128 0xe
	.long	0x82a
	.uleb128 0x18
	.long	.LASF131
	.byte	0xe0
	.long	.LFB12
	.long	.LFE12-.LFB12
	.uleb128 0x1
	.byte	0x9c
	.long	0x8dc
	.uleb128 0x7
	.string	"pde"
	.byte	0xe2
	.byte	0xd
	.long	0x825
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x17
	.long	.LASF132
	.long	0x8ec
	.uleb128 0x5
	.byte	0x3
	.long	__FUNCTION__.1
	.uleb128 0xc
	.long	.LBB4
	.long	.LBE4-.LBB4
	.uleb128 0x7
	.string	"i"
	.byte	0xe7
	.byte	0xb
	.long	0x4e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0xc
	.long	.LBB5
	.long	.LBE5-.LBB5
	.uleb128 0x7
	.string	"pt"
	.byte	0xee
	.byte	0xe
	.long	0x7d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x5
	.long	.LASF133
	.byte	0x1
	.byte	0xf7
	.byte	0xf
	.long	0x825
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0xc
	.long	.LBB6
	.long	.LBE6-.LBB6
	.uleb128 0x7
	.string	"j"
	.byte	0xfd
	.byte	0xd
	.long	0x4e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0xc
	.long	.LBB7
	.long	.LBE7-.LBB7
	.uleb128 0xb
	.long	.LASF25
	.value	0x103
	.byte	0xe
	.long	0x7d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0xa
	.long	0xb6
	.long	0x8ec
	.uleb128 0xd
	.long	0x39
	.byte	0xe
	.byte	0
	.uleb128 0xe
	.long	0x8dc
	.uleb128 0x18
	.long	.LASF134
	.byte	0xbc
	.long	.LFB11
	.long	.LFE11-.LFB11
	.uleb128 0x1
	.byte	0x9c
	.long	0x915
	.uleb128 0x2e
	.string	"pte"
	.byte	0x1
	.byte	0xbc
	.byte	0x2b
	.long	0x15f
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.byte	0
	.uleb128 0x2f
	.long	.LASF135
	.byte	0x1
	.byte	0xb3
	.byte	0xc
	.long	0x153
	.long	.LFB10
	.long	.LFE10-.LFB10
	.uleb128 0x1
	.byte	0x9c
	.long	0x93f
	.uleb128 0x30
	.long	.LASF136
	.byte	0x1
	.byte	0xb3
	.byte	0x34
	.long	0x153
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.byte	0
	.uleb128 0x31
	.long	.LASF147
	.byte	0x1
	.byte	0xaf
	.byte	0xc
	.long	0x153
	.long	.LFB9
	.long	.LFE9-.LFB9
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x18
	.long	.LASF137
	.byte	0x23
	.long	.LFB8
	.long	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.long	0xa3d
	.uleb128 0x17
	.long	.LASF132
	.long	0xa4d
	.uleb128 0x5
	.byte	0x3
	.long	__FUNCTION__.2
	.uleb128 0x5
	.long	.LASF138
	.byte	0x1
	.byte	0x2a
	.byte	0xb
	.long	0x6a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x5
	.long	.LASF139
	.byte	0x1
	.byte	0x2b
	.byte	0xb
	.long	0x6a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x5
	.long	.LASF140
	.byte	0x1
	.byte	0x2c
	.byte	0xb
	.long	0x6a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x7
	.string	"mbh"
	.byte	0x2e
	.byte	0x14
	.long	0x6a5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -52
	.uleb128 0x5
	.long	.LASF141
	.byte	0x1
	.byte	0x7a
	.byte	0x9
	.long	0x158
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x7
	.string	"pde"
	.byte	0x82
	.byte	0xe
	.long	0x825
	.uleb128 0x2
	.byte	0x91
	.sleb128 -60
	.uleb128 0x7
	.string	"pte"
	.byte	0x83
	.byte	0xe
	.long	0x825
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x5
	.long	.LASF142
	.byte	0x1
	.byte	0x97
	.byte	0xd
	.long	0x153
	.uleb128 0x3
	.byte	0x91
	.sleb128 -68
	.uleb128 0x5
	.long	.LASF143
	.byte	0x1
	.byte	0x9c
	.byte	0x9
	.long	0x158
	.uleb128 0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x5
	.long	.LASF144
	.byte	0x1
	.byte	0x9d
	.byte	0xd
	.long	0x153
	.uleb128 0x3
	.byte	0x91
	.sleb128 -76
	.uleb128 0xc
	.long	.LBB2
	.long	.LBE2-.LBB2
	.uleb128 0x7
	.string	"i"
	.byte	0x38
	.byte	0xb
	.long	0x4e
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0xc
	.long	.LBB3
	.long	.LBE3-.LBB3
	.uleb128 0x7
	.string	"mm"
	.byte	0x39
	.byte	0x21
	.long	0xa52
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0xa
	.long	0xb6
	.long	0xa4d
	.uleb128 0xd
	.long	0x39
	.byte	0x10
	.byte	0
	.uleb128 0xe
	.long	0xa3d
	.uleb128 0x8
	.long	0x50d
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 8
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 6
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0xd
	.uleb128 0xb
	.uleb128 0x6b
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 22
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x88
	.uleb128 0x21
	.sleb128 4096
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 8
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 8
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 12
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 6
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 6
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x37
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 8
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x17
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 8
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 3
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 8
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0xd
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 12
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0x21
	.sleb128 281
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x1f
	.uleb128 0x1b
	.uleb128 0x1f
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0xd
	.uleb128 0xb
	.uleb128 0x6b
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x25
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x26
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x27
	.uleb128 0xd
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x28
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x29
	.uleb128 0x26
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x2a
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x2b
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2c
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x2d
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x2e
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x2f
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7a
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x30
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x31
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7a
	.uleb128 0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.long	0x1c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x4
	.byte	0
	.value	0
	.value	0
	.long	.Ltext0
	.long	.Letext0-.Ltext0
	.long	0
	.long	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF93:
	.string	"len_high"
.LASF120:
	.string	"return_pointer"
.LASF126:
	.string	"pdpt_index"
.LASF23:
	.string	"ignored"
.LASF79:
	.string	"vbe_interface_seg"
.LASF132:
	.string	"__FUNCTION__"
.LASF62:
	.string	"flags"
.LASF123:
	.string	"virt_addr"
.LASF49:
	.string	"shndx"
.LASF11:
	.string	"unsigned int"
.LASF101:
	.string	"physical_memory_base"
.LASF104:
	.string	"kernel_virtual_memory_top"
.LASF97:
	.string	"_kernel_end"
.LASF46:
	.string	"multiboot_aout_symbol_table"
.LASF29:
	.string	"sys_intel8254"
.LASF19:
	.string	"write_through"
.LASF40:
	.string	"multiboot_uint64_t"
.LASF102:
	.string	"phsyical_memory_top"
.LASF66:
	.string	"cmdline"
.LASF67:
	.string	"mods_count"
.LASF131:
	.string	"dump_active_pt"
.LASF88:
	.string	"multiboot_info_t"
.LASF18:
	.string	"privilege"
.LASF36:
	.string	"bit_array"
.LASF35:
	.string	"sys_text"
.LASF42:
	.string	"strsize"
.LASF142:
	.string	"pmem"
.LASF68:
	.string	"mods_addr"
.LASF65:
	.string	"boot_device"
.LASF10:
	.string	"uint32_t"
.LASF138:
	.string	"mem_start"
.LASF134:
	.string	"set_task_pde"
.LASF83:
	.string	"framebuffer_pitch"
.LASF13:
	.string	"long long unsigned int"
.LASF81:
	.string	"vbe_interface_len"
.LASF90:
	.string	"addr_low"
.LASF20:
	.string	"cache_disabled"
.LASF124:
	.string	"phys_addr"
.LASF100:
	.string	"vv_magic_word"
.LASF64:
	.string	"mem_upper"
.LASF76:
	.string	"vbe_control_info"
.LASF106:
	.string	"graphics_page_table"
.LASF53:
	.string	"framebuffer_palette_addr"
.LASF9:
	.string	"size_t"
.LASF125:
	.string	"pt_addr_physical"
.LASF139:
	.string	"mem_size"
.LASF61:
	.string	"multiboot_info"
.LASF21:
	.string	"accessed"
.LASF119:
	.string	"_Bool"
.LASF56:
	.string	"framebuffer_red_mask_size"
.LASF33:
	.string	"sys_paging"
.LASF75:
	.string	"apm_table"
.LASF115:
	.string	"klog_variable_func"
.LASF91:
	.string	"addr_high"
.LASF58:
	.string	"framebuffer_green_mask_size"
.LASF16:
	.string	"char"
.LASF51:
	.string	"aout_sym"
.LASF144:
	.string	"zerozero"
.LASF69:
	.string	"mmap_length"
.LASF141:
	.string	"process_address_space"
.LASF14:
	.string	"uint8_t"
.LASF17:
	.string	"present"
.LASF98:
	.string	"paging_pdpt"
.LASF145:
	.string	"GNU C17 11.2.0 -mtune=generic -march=pentiumpro -g -O0 -ffreestanding -fno-omit-frame-pointer"
.LASF121:
	.string	"page_allocate"
.LASF77:
	.string	"vbe_mode_info"
.LASF27:
	.string	"sys_system"
.LASF6:
	.string	"long long int"
.LASF71:
	.string	"drives_length"
.LASF80:
	.string	"vbe_interface_off"
.LASF128:
	.string	"pdpt_uint"
.LASF133:
	.string	"page"
.LASF108:
	.string	"process_pd"
.LASF109:
	.string	"process_pt"
.LASF116:
	.string	"memset"
.LASF143:
	.string	"zero_addr_space"
.LASF84:
	.string	"framebuffer_width"
.LASF39:
	.string	"multiboot_uint32_t"
.LASF47:
	.string	"multiboot_elf_section_header_table"
.LASF48:
	.string	"size"
.LASF140:
	.string	"alloc_start"
.LASF45:
	.string	"multiboot_aout_symbol_table_t"
.LASF111:
	.string	"asm_refresh_cr3"
.LASF117:
	.string	"printf_"
.LASF137:
	.string	"memory_initalize"
.LASF78:
	.string	"vbe_mode"
.LASF37:
	.string	"multiboot_uint8_t"
.LASF92:
	.string	"len_low"
.LASF72:
	.string	"drives_addr"
.LASF28:
	.string	"sys_kernel"
.LASF74:
	.string	"boot_loader_name"
.LASF31:
	.string	"sys_pci"
.LASF4:
	.string	"long double"
.LASF63:
	.string	"mem_lower"
.LASF96:
	.string	"paging_level_active"
.LASF99:
	.string	"paging_pd"
.LASF127:
	.string	"pd_index"
.LASF73:
	.string	"config_table"
.LASF5:
	.string	"short int"
.LASF147:
	.string	"get_physical_memory_base"
.LASF2:
	.string	"long int"
.LASF24:
	.string	"available"
.LASF12:
	.string	"uint64_t"
.LASF55:
	.string	"framebuffer_red_field_position"
.LASF95:
	.string	"multiboot_memory_map_t"
.LASF103:
	.string	"kernel_virtual_memory_base"
.LASF118:
	.string	"set_debug_output"
.LASF114:
	.string	"kpanic"
.LASF59:
	.string	"framebuffer_blue_field_position"
.LASF136:
	.string	"virt"
.LASF130:
	.string	"memory_test"
.LASF3:
	.string	"long unsigned int"
.LASF25:
	.string	"address"
.LASF41:
	.string	"tabsize"
.LASF52:
	.string	"elf_sec"
.LASF82:
	.string	"framebuffer_addr"
.LASF85:
	.string	"framebuffer_height"
.LASF94:
	.string	"type"
.LASF15:
	.string	"unsigned char"
.LASF113:
	.string	"kmalloc"
.LASF89:
	.string	"multiboot_mmap_entry"
.LASF34:
	.string	"sys_elf"
.LASF146:
	.string	"get_multiboot_header"
.LASF43:
	.string	"addr"
.LASF110:
	.string	"liballoc_dump"
.LASF87:
	.string	"framebuffer_type"
.LASF129:
	.string	"pd_uint"
.LASF107:
	.string	"another_page_table"
.LASF57:
	.string	"framebuffer_green_field_position"
.LASF86:
	.string	"framebuffer_bpp"
.LASF122:
	.string	"page_map"
.LASF7:
	.string	"signed char"
.LASF8:
	.string	"short unsigned int"
.LASF112:
	.string	"memcpy"
.LASF50:
	.string	"multiboot_elf_section_header_table_t"
.LASF44:
	.string	"reserved"
.LASF70:
	.string	"mmap_addr"
.LASF135:
	.string	"get_physical_addr_from_virt"
.LASF30:
	.string	"sys_memory"
.LASF54:
	.string	"framebuffer_palette_num_colors"
.LASF26:
	.string	"page_directory_entry"
.LASF22:
	.string	"page_size"
.LASF38:
	.string	"multiboot_uint16_t"
.LASF60:
	.string	"framebuffer_blue_mask_size"
.LASF105:
	.string	"second_page_table"
.LASF32:
	.string	"sys_interrupt"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/usr/local/osdev/versions/v"
.LASF0:
	.string	"kernel/c/memory.c"
	.ident	"GCC: (GNU) 11.2.0"
