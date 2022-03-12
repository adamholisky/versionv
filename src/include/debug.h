#if !defined(DEBUG_INCLUDED)
#define DEBUG_INCLUDED

#include "printf.h"
#include "serial.h"
#include "terminal.h"

#define KDEBUG_MAX_SYMBOLS 1024
#define STACKFRAME_MAX 25

enum level {
    level_info,
    level_warn,
    level_error,
    level_panic
};

enum sys {
    sys_system,
    sys_kernel,
    sys_intel8254,
    sys_memory,
    sys_pci,
    sys_interrupt,
    sys_paging,
    sys_elf
};

static const char * sys_text[] = {
    [sys_system] = "System",
    [sys_kernel] = "Kernel",
    [sys_intel8254] = "Intel8254",
    [sys_memory] = "Memory",
    [sys_pci] = "PCI",
    [sys_interrupt] = "Interrupt",
    [sys_paging] = "Paging",
    [sys_elf] = "ELF"
};

static const char * bit_array[16] = {
    [ 0] = "0000", [ 1] = "0001", [ 2] = "0010", [ 3] = "0011",
    [ 4] = "0100", [ 5] = "0101", [ 6] = "0110", [ 7] = "0111",
    [ 8] = "1000", [ 9] = "1001", [10] = "1010", [11] = "1011",
    [12] = "1100", [13] = "1101", [14] = "1110", [15] = "1111",
};

typedef struct {
	char * 		name;
	uint32_t	addr;
	uint32_t	size;
} kdebug_symbol;

typedef struct {
    uint32_t    start;
    uint32_t    stop;
    uint32_t    length;
} profile_information;

typedef struct {
    struct stackframe * ebp;
    uint32_t eip;
} stackframe;

void kdebug_add_symbol( char * name, uint32_t addr, uint32_t size );
kdebug_symbol * kdebug_get_symbol( char * name );
kdebug_symbol * kdebug_get_symbol_array( void );
uint32_t kdebug_get_symbol_addr( char * name );
char * kdebug_get_function_at( uint32_t addr );
char * kdebug_peek_at( uint32_t addr );
char peek_char( char c );
void profile_test( void );
void profile_test_run( uint32_t num_of_nops );
profile_information * get_profile_information( void );
void profile_stop( void );
void profile_start( void );
void k_log( uint32_t system_id, uint32_t level, char * message, ... );
char * strcat( char * dest, char * src );
char * strstr( register char * string, char * substring );
void debugf_stack_trace( void );
void stack_trace_test_func_a( void );
void stack_trace_test_func_b( void );
void stack_trace_test_func_c( void );
void stack_trace_test_func_d( void );

#define debug_out_on() set_debug_output( true )
#define debug_out_off() set_debug_output( false )
#define klog( ... ) debug_out_on(); printf( "[\x1b[0;34;49m%s:%d\x1b[0;00;00m] ", __FUNCTION__, __LINE__ ); printf( __VA_ARGS__ ); debug_out_off()
#define debugf( ... ) debug_out_on(); printf( __VA_ARGS__ ); debug_out_off()
#define log_entry_enter() klog( "Enter\n" )
#define log_entry_exit() klog( "Exit\n" );

#define dbA() debugf( "A" )
#define dbB() debugf( "B" )
#define dbC() debugf( "C" )
#define dbD() debugf( "D" )
#define dbE() debugf( "E" )
#define db1() debugf( "1" )
#define db2() debugf( "2" )
#define db3() debugf( "3" )
#define db4() debugf( "4" )
#define db5() debugf( "5" )

#define debugf_bit_array( x ) debugf( "flags: %s %s %s %s %s %s %s %s -- 0x%08X\n", \
        bit_array[ 0xF & (x >> 28) ], \
        bit_array[ 0xF & (x >> 24) ], \
        bit_array[ 0xF & (x >> 20) ], \
        bit_array[ 0xF & (x >> 16) ], \
        bit_array[ 0xF & (x >> 12) ],\
        bit_array[ 0xF & (x >> 8) ], \
        bit_array[ 0xF & (x >> 4) ], \
        bit_array[ 0xF & x ], \
        x ); \
        debugf( "       31   27   23   19   15   11   7    3\n" )

#endif