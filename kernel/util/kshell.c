#include <kernel.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <serial.h>
#include <keyboard.h>
#include <debug.h>
#include <kmalloc.h>
#include <kapps.h>
#include <task.h>
#include <kshell.h>
#include <syscall.h>
#include <afs.h>

char line[256];
char jail_env[256];
char wd[256];
char* dir_bin;
char* dir_usr_bin;
int line_pos;

void kshell_ps( void );
void kshell_test_loaded_file( void );

void kshell_get_line( void ) {
	char c = ' ';
	bool process_keypress = true;

	memset( line, 0, 256 );
	line_pos = 0;

	while( process_keypress ) {
		if( c = keyboard_get_char() ) {
			if( c != 13 ) {
				printf( "%c", c );
			}
		}

		if( c == '\n' || c == 13 ) {
			printf( "\n" );
			process_keypress = false;
		} else {
			line[line_pos] = c;
			line_pos++;

			if( line_pos == 256 ) {
				process_keypress = false;
			}
		}
	}
	
}

void kshell_process_line( void ) {
	bool check_file_cmd = true;
	char path[256];
	char args[4][100];
	char *c = line;
	bool keep_processing = true;
	int i = 0;
	int j = 0;

	memset( path, 0, 256 );
	memset( args, 0, 4 * 100 );

	do {
		if( *c != ' ' ) {
			args[i][j] = *c; 
			j++;
		} else {
			i++;
			j = 0;

			if( i > 3 ) {
				keep_processing = false;
			}
		}

		c++;
	} while( keep_processing );
	
	/* 
	for( i = 0; i < 4; i++ ) {
		debugf( "args[%d] = \"%s\"\n", i, args[i] );
	} 
	*/

	if( strcmp( args[0], "1" ) == 0 ) {
		kshell_test_fork();
	}

	if( strcmp( args[0], "q" ) == 0 ) {
		kshell_shutdown();
	}

	if( strcmp( args[0], "ps" ) == 0 ) {
		//kshell_ps();
		kexec( "ps",(uint32_t *)kshell_ps, NULL );
	}

	/* if( strcmp( args[0], "ls" ) == 0 ) {
		ls();

		check_file_cmd = false;
	}

	if( strcmp( args[0], "cd" ) == 0 ) {
		cd( args[1] );

		check_file_cmd = false;
	}

	if( check_file_cmd ) {
		strcpy( path, line );
		strcat( path, ".vvs" );

		if( file_exists( wd, path ) ) {
			strcpy( path, wd );
		} else if( file_exists( dir_bin, path ) ) {
			strcpy( path, dir_bin );
		} else if( file_exists( dir_usr_bin, path  ) ) {
			strcpy( path, dir_usr_bin );
		} else {
			printf( "%s not found.\n", line );
			path[0] = 0;
		}

		if( path[0] != 0 ) {
			strcat( path, line );
			strcat( path, ".vvs" );

			load_and_run( path, line );
		}
	} */
}

void kshell_run( void ) {
	kexec( "test_loaded_file", (uint32_t *)kshell_test_loaded_file, NULL );
	kexec( "ps", (uint32_t *)kshell_ps, NULL );

	uint32_t binaddr = kdebug_get_symbol_addr( "_binary_afs_img_start" );
	kdebug_peek_at( binaddr );

	afs_disply_diagnostic_data( (uint8_t *)binaddr );

	printf( "Shutting down gracefully.\n" );
	kshell_shutdown();

	while( true ) {
		printf( "\x1b[0;31;49mVersionV\x1b[0;0;0m:\x1b[0;32;49m%s\x1b[0;0;0m> ", wd );

		kshell_get_line();

		kshell_process_line();

		sched_yield();
	}
}

void kshell_shutdown( void ) {
	debugf( "\nGoodbye, Dave.\n" );
	outportb( 0xF4, 0x00 );
}

void kshell_ps( void ) {
	debugf( "Process Info\n" );

	task *t = get_tasks();

	debugf( "ID   S         Type        EIP           Name\n" );

	for( int i = 0; i < TASK_MAX; i++ ) {
		if( t[i].id != TASK_ID_INVALID ) {
			x86_context *context = (x86_context *)t[i].context_at_interrupt;
			uint32_t eip = context->eip;
			debugf( "%d    %s  %s    0x%08X    %s\n", i, task_status_to_string( t[i].status ), task_type_to_string( t[i].type ), eip, t[i].name );
			//kdebug_peek_at( context );
		}
	}

	task_exit();
}

void kshell_test_fork( void  ) {
	int pid = kfork();

	if( pid == 0 ) {
		printf( "Parent task.\n" );
	} else {
		printf( "Child task: %d\n", pid );
	}
}

void kshell_test_loaded_file( void ) {
	log_entry_enter();

	

	uint32_t *mem = page_map( 0xE0000000, 0xE0000000 );

	kdebug_peek_at( mem );

	task_exit();
	log_entry_exit();
}