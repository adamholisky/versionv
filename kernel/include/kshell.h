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

#ifdef __cplusplus
}
#endif
#endif