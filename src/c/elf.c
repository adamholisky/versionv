#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "elf.h"
#include "printf.h"
#include "multiboot.h"
#include "debug.h"
#include "terminal.h"

void elf_initalize( uint32_t kmain ) {
	elf32_section_header *section_headers;
	elf32_sym *symbol_table;
	uint32_t symtable_num_entries = 0;
	int i = 0;
	uint32_t name_addr = 0;
	int string_index = 0;
	int symtable_index = 0;

	multiboot_info_t *multiboot_header = get_multiboot_header();

/* 	debugf( "elf_sec.num:           0x%08X\n", multiboot_header->u.elf_sec.num );
    debugf( "elf_sec.size:          0x%08X\n", multiboot_header->u.elf_sec.size );
    debugf( "elf_sec.addr:          0x%08X\n", multiboot_header->u.elf_sec.addr );
    debugf( "elf_sec.shndx:         0x%08X\n", multiboot_header->u.elf_sec.shndx ); */

	section_headers = (elf32_section_header *)(multiboot_header->u.elf_sec.addr);
/* 	debugf( "section_headers: 0x%08X\n", &section_headers[1] ); */

	for( i = 0; i < multiboot_header->u.elf_sec.num; i++ ) {
		if( section_headers[i].sh_type == SHT_STRTAB ) {
			string_index = i;
/* 			debugf( "String table index: %d\n", i );
 */			i = 99999;
		}
	}

	for( i = 0; i < multiboot_header->u.elf_sec.num; i++ ) {
		if( section_headers[i].sh_type == SHT_SYMTAB ) {
			symtable_index = i;
			symtable_num_entries = section_headers[symtable_index].sh_size / sizeof(elf32_sym);
/* 			debugf( "Symbol table index: %d\n", i );
			debugf( "Symbol table address: 0x%08X\n", section_headers[symtable_index].sh_addr );
			debugf( "table size: %d\n", section_headers[symtable_index].sh_size );
			debugf( "entry size: %d\n", sizeof( elf32_sym ) );
			debugf( "num entries: %d\n", symtable_num_entries ); */
			i = 99999;
		}
	}

	name_addr = section_headers[string_index].sh_addr + 0xC0000000;
	symbol_table = (elf32_sym *)(section_headers[symtable_index].sh_addr + 0xC0000000 );

/* 	debugf( "name addr: 0x%08X\n", name_addr );
	debugf( "symtable addr: 0x%08X\n", symbol_table );
 */

/* 	for( i = 0; i < multiboot_header->u.elf_sec.num; i++ ) {
		debugf( "[%d / %x] found type: %x     %d\n", i, i, section_headers[i].sh_type, section_headers[i].sh_type );
		if( section_headers[i].sh_type == 0 ) { continue; }
		//debugf( "name index: %d \n", section_headers[i].sh_name );
		//debugf( "name: %s\n", (char *)(name_addr + section_headers[i].sh_name ));
		debugf( "    addr:       %x\n", section_headers[i].sh_addr );
		debugf( "    soff:       %x\n", section_headers[i].sh_offset );
		debugf( "    shlink:     %x\n", section_headers[i].sh_link );
	} */

	for( i = 1; i < symtable_num_entries - 1; i++ ) {
		if( ELF32_ST_TYPE( symbol_table[i].st_info ) == STT_FUNC ) {
			/* debugf( "[%d] found value: 0x%08X\n", i, &symbol_table[i]);
			debugf( "    0x%08X    0x%X    0x%X\n", symbol_table[i].st_value, symbol_table[i].st_size, ELF32_ST_TYPE( symbol_table[i].st_info ) );
			debugf( "    %s\n", (char *)(name_addr + symbol_table[i].st_name) );
 */
			kdebug_add_symbol( (char *)(name_addr + symbol_table[i].st_name), symbol_table[i].st_value, symbol_table[i].st_size );
		}
	}

	k_log( sys_elf, level_info, "0x%08X is in function: %s", kmain + 0x10, kdebug_get_function_at( kmain + 0x10 ));
}