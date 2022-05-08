#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <kernel_symbols.h>

void KernelSymbols::add( char * name, uint32_t addr, uint32_t size ) {
	kernel_symbols[ kernel_symbol_top ].name = name;
	kernel_symbols[ kernel_symbol_top ].addr = addr;
	kernel_symbols[ kernel_symbol_top ].size = size;
	kernel_symbol_top++;
}

KernelSymbol * KernelSymbols::get_symbol_array( void ) {
	return this->kernel_symbols;
}

char * KernelSymbols::get_function_at( uint32_t addr ) {
	char * ret_val = (char *)KernelSymbols::kdebug_symbol_cannot_find;

	for( int i = 0; i<DEBUG_SYMBOLS_MAX; i++ ) {
		if( this->kernel_symbols[i].size == 0 ) continue; 

		if( addr >= this->kernel_symbols[i].addr ) {
			if( addr < ( this->kernel_symbols[i].addr + this->kernel_symbols[i].size) ) {
				ret_val = this->kernel_symbols[i].name;
			}
		}
	}

	return ret_val;
}

KernelSymbol * KernelSymbols::get_symbol( char * name ) {
	KernelSymbol * ret = NULL;

	for( int i = 0; i < this->kernel_symbol_top; i++ ) {
		//klog( "%d", i );
		if( this->kernel_symbols[i].name[0] == 0 ) continue;

		if( strcmp( this->kernel_symbols[i].name, name ) == 0 ) {
			ret = this->kernel_symbols + i;
		}
	}

	return ret;
}

uint32_t KernelSymbols::get_total_symbols( void ) {
	return this->kernel_symbol_top;
}

uint32_t KernelSymbols::get_symbol_addr( char * name ) {
	uint32_t ret = 0;

	KernelSymbol * sym = this->get_symbol( name );

	if( sym != NULL ) {
		ret = sym->addr;
	}

	return ret;
}