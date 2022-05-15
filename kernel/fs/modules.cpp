#include <stdlib.h>
#include <stdio.h>
#include <kmalloc.h>
#include <elf.h>
#include <task.h>
#include <debug.h>
#include <modules.h>

#define kdebug_module 

void Module::call_init( void ) {
	this->init();
}

void Module::call_exit( void ) {
	this->exit();
}

void Module::call_main( void ) {
	this->main( 0, NULL );
}

void Module::load( uint32_t *raw_data_start ) {
	task *module_task = (task *)kmalloc( sizeof( task ) );
	uint32_t *VIRT_HEAP_BASE = reinterpret_cast<uint32_t *>(KERNEL_VIRT_HEAP_BASE);
	

	module_task->code_start_virt = page_allocate( 1 );
	uint32_t *code_start_uint32 = reinterpret_cast<uint32_t *>(module_task->code_start_virt);

	module_task->code_start_phys = reinterpret_cast<void *>(code_start_uint32 - VIRT_HEAP_BASE + get_physical_memory_base());

	module_task->stack = page_allocate( 1 );
	module_task->data_start_virt = page_allocate( 1 );
	uint32_t *data_start_uint32 = reinterpret_cast<uint32_t *>(module_task->data_start_virt);

	module_task->data_start_phys =reinterpret_cast<void *>(data_start_uint32 - VIRT_HEAP_BASE + get_physical_memory_base());

	#ifdef kdebug_module
	klog( "code_start_virt: 0x%08X\n", module_task->code_start_virt );
	klog( "code_start_phys: 0x%08X\n", module_task->code_start_phys );
	#endif

	// Parse raw data to identify secrtions to load, and to copy them into memory
	uint8_t *process_space = reinterpret_cast<uint8_t *>(code_start_uint32);
	Elf32_Ehdr *elf_header = (Elf32_Ehdr *)raw_data_start;

	#ifdef kdebug_module
	klog( "proccess_space: 0x%08X\n", process_space);
	klog( "elf_header: 0x%08X\n", elf_header);
	#endif

	Elf32_Shdr* rel_plt = elf_find_rel_plt((uint32_t*)raw_data_start, elf_header);
    if (rel_plt != NULL) {
        uint32_t* data = (uint32_t*)((uint8_t*)raw_data_start + rel_plt->sh_offset);

		#ifdef kdebug_module
		debugf( "raw data start: %X\n", raw_data_start );
		debugf( "rel_plt:sh_offset %X\n", rel_plt->sh_offset);
		debugf("data %X %x\n", data, *data );
        debugf(".rel.plt out:\n");
        for (int j = 0; j < (rel_plt->sh_size/4); j++) {
            debugf("%08X\t", (uint32_t) * (data + j));
        }
        debugf("\n\n");
		#endif
    }
    else {
        klog("Could not find .rel.plt section\n");
    }

    elf_load_program_headers(elf_header, (uint8_t *)process_space, (uint8_t *)raw_data_start);

	/* I have no idea why I did this or what 0x1288 means...
	#ifdef kdebug_process_loader
	for (int k = 0x1288; k < 0x12a0; k = k + 4) {
        debugf("0x%03X: %02X %02X %02X %02X\n", k, (uint8_t) * ((uint8_t*)process_space + k), (uint8_t) * ((uint8_t*)process_space + k + 1), (uint8_t) * ((uint8_t*)process_space + k + 2), (uint8_t) * ((uint8_t*)process_space + k + 3));
    }
	#endif 
	*/

	Elf32_Shdr* got_plt = elf_find_got_plt((uint32_t*)raw_data_start, elf_header);
    if (got_plt != NULL) {
        uint32_t* data = (uint32_t*)(process_space + got_plt->sh_addr);

		#ifdef kdebug_module
        debugf(".got.plt out:\n");
        for (int j = 0; j < (got_plt->sh_size/4); j++) {
            debugf("%08X\t", (uint32_t) * (data + j));
        }
        debugf("\n\n");
		#endif
    }
    else {
        klog("Could not find .got.plt section\n");
    }

	module_task->entry = (void *)elf_header->e_entry;
	
	//debugf( "entry: 0x%08X\n", module_task->entry);
	
    if (rel_plt == NULL) {
		klog( "rel_pplt is null\n");
    }

    if (got_plt == NULL) {
       klog( "got_plt is null\n");
    }

	// Loop through the rel_plt and updating the corresponding GOT entry
	for(int rel_num = 0; rel_num < (rel_plt->sh_size/4)/2; rel_num++) {
		Elf32_Rel *elf_rel = (Elf32_Rel*)((uint8_t*)raw_data_start + rel_plt->sh_offset + (rel_num * sizeof(Elf32_Rel)));

		if( elf_get_sym_shndx_from_index((uint32_t*)raw_data_start, elf_header, ELF32_R_SYM(elf_rel->r_info)) == 0 ) {
			uint32_t *got_entry = (uint32_t*)(process_space + elf_rel->r_offset);
			*got_entry = (uint32_t)kdebug_get_symbol_addr( elf_get_sym_name_from_index((uint32_t*)raw_data_start, elf_header, ELF32_R_SYM(elf_rel->r_info)) );

			#ifdef kdebug_module
			klog( "rel sym: 0x%08X, %d, %d, %X, %s\n", elf_rel->r_offset, ELF32_R_TYPE(elf_rel->r_info), ELF32_R_SYM(elf_rel->r_info),  elf_get_sym_shndx_from_index((uint32_t*)raw_data_start, elf_header, ELF32_R_SYM(elf_rel->r_info)), elf_get_sym_name_from_index((uint32_t*)raw_data_start, elf_header, ELF32_R_SYM(elf_rel->r_info)) );
			#endif
		} else {
			// Link main -- I think I'm doing something wrong by having to do this, maybe not handling got right?
			uint32_t *got_entry = (uint32_t*)(process_space + elf_rel->r_offset);

			*got_entry = (uint32_t)elf_get_sym_value_from_index((uint32_t*)raw_data_start, elf_header, ELF32_R_SYM(elf_rel->r_info));
		}
		
		//#ifdef kdebug_process_loader
		
		//#endif
	}

	#ifdef kdebug_module
	uint32_t* data2 = (uint32_t*)((uint32_t)process_space + got_plt->sh_addr);
	debugf(".got.plt out:\n");
	for (int x = 0; x < (got_plt->sh_size/4); x++) {
		debugf("%08X\t", (uint32_t) * (data2 + x));
	}
	debugf("\n\n");
	

	debugf( "    module_task entry:      0x%08X\n", module_task->entry);
	debugf( "    module_task code virt:  0x%08X\n", module_task->code_start_virt );
	debugf( "    module_task stack virt: 0x%08X\n", module_task->stack );
	#endif

	Elf32_Shdr * strtab_shdr = elf_find_sym_strtab( (uint32_t*)raw_data_start, elf_header );
	Elf32_Shdr * elf_sym_shdr = elf_find_symtab( raw_data_start, elf_header); 


	module_task->raw_data = (uint8_t *)raw_data_start;
	module_task->sym_table = (Elf32_Sym*)((uint8_t*)raw_data_start + elf_sym_shdr->sh_offset);
	module_task->str_table = (uint8_t *)raw_data_start + strtab_shdr->sh_offset;
	module_task->num_syms = elf_sym_shdr->sh_size / sizeof( Elf32_Sym );

	module_task->context.eip = (uint32_t)module_task->entry;

	module_task->type = TASK_TYPE_MODULE;

	uint32_t task_id = task_add( module_task );
	task_set_modhack( task_id );

	this->task_id = task_id;
}