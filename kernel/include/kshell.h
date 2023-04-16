#ifndef KSHELL_INCLUDED
#define KSHELL_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#define kshell_fake_cli(x) printf( "\x1b[0;31;49mVersionV\x1b[0;0;0m:\x1b[0;32;49m%s\x1b[0;0;0m> "x"\n" , wd );

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
void kshell_afs_test_alpha( void );

#ifdef __cplusplus
}
#endif
#endif