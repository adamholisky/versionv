#ifndef KSHELL_INCLUDED
#define KSHELL_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

void kshell_get_line( void );
void kshell_process_line( void );
void kshell_run( void );
void kshell_shutdown( void );

void kshell_test_fork( void );
void kshell_divide_by_zero( void );
void kshell_test_devices( void );
void test_syscall( void );
void kshell_test_loaded_file( void );
void kshell_ps( void );
void kshell_afs_test( void );

#ifdef __cplusplus
}
#endif
#endif