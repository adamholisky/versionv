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
#include <device.h>
#include <terminal.h>
#include <ahci.h>
#include <fs.h>

char line[256];
char jail_env[256];
char wd[256];
char* dir_bin;
char* dir_usr_bin;
int line_pos;

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
	char *argv_builder[4];
	char *c = line;
	bool keep_processing = true;
	int num_args = 0;

	memset( path, 0, 256 );
	memset( args, 0, 4 * 100 );

	int i = 0;
	int j = 0;

	do {
		if( *c != ' ' && *c != 0 ) {
			args[i][j] = *c; 
			j++;
		} else {
			if( j != 0 ) {
				num_args++;
			}

			args[i][j] = 0;
			i++;
			j = 0;

			if( i > 3 ) {
				keep_processing = false;
			}
		}

		c++;
	} while( keep_processing );

	klog( "num_args = %d\n", num_args );
	
	
	for( int z = 0; z < 4; z++ ) {
		debugf( "args[%d] = \"%s\"\n", z, args[z] );
		argv_builder[z] = args[z];
	} 
	

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

	if( strcmp( args[0], "cat" ) == 0 ) {
		kshell_cat( num_args, argv_builder );
	}

	if( strcmp( args[0], "ls" ) == 0 ) {
		primative_ls( args[1] );
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

#define KDEBUG_CAT
void kshell_cat( int argc, char *argv[] ) {
	bool show_help = false;

	if( argc < 2 ) {
		show_help = true;	
	} else if( strcmp( argv[1], "--help" ) == 0 ) {
		show_help = true;
	}

	if( show_help ) {
		printf( "cat: cat <pathname>\n" );
	}

	#ifdef KDEBUG_CAT
	klog( "cating \"%s\"\n", argv[1] );
	#endif

	int FD = open( argv[1], 0 );
	
	char *buff = malloc( 2048 );
	memset( buff, 0, 2048 );

	int size = get_file_size(FD);
	int bytes_read = read( FD, buff, size );

	#ifdef KDEBUG_CAT
	klog( "bytes read: %d\n", bytes_read );
	#endif

	printf( "%s\n", buff );

	free( buff );
}

void kshell_fake_cli( char *cmd ) {
	printf( "\x1b[0;31;49mVersionV\x1b[0;0;0m:\x1b[0;32;49m%s\x1b[0;0;0m> %s\n" , wd, cmd );
}

void kshell_automate( char *cmd_line ) {
	memset( line, 0, 256 );
	strcpy( line, cmd_line );

	kshell_fake_cli( cmd_line );
	kshell_process_line();
}

void kshell_run( void ) {
	kshell_fake_cli( "ps_to_log" );
	kexec( "ps", (uint32_t *)kshell_ps, NULL );

	kshell_automate( "ls" );
	kshell_automate( "ls /bin" );
	kshell_automate( "cat /bin/do_a_thing" );
	kshell_automate( "cat bin/do_a_thing" );

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

	uint32_t *mem = page_map( (uint32_t *)0xE0000000, (uint32_t *)0xE0000000 );

	kdebug_peek_at( (uint32_t)mem );

	task_exit();
	log_entry_exit();
}

void test_syscall( void ) {
	char *mem = malloc( 6 );
	memset( mem, 0, 6 );

	uint32_t count = read( -2, mem, 5 );

	printf( "Syscall result:\nmem: \"%s\"\ncount: %d\n", mem, count );
}

void kshell_test_devices( void ) {
	device *term = get_device_by_file( "/dev/tty0" );

	//term->write( "A", 1 );

	//printf( "\n" );

	term->write( "Hello, terminal!\n", strlen( "Hello, terminal!\n" ) );

	task_exit();
}

void kshell_divide_by_zero( void ) {
	asm volatile( 
		"movl 0, %eax \n\t"
		"movl 0, %ecx \n\t"
		"div %ecx \n\t"
	);
}

/**
 * @brief Test that AFS drive and root directory are sane
 * 
 */
void kshell_afs_test_alpha( void ) {
	afs_drive *drive = malloc( sizeof(afs_drive) );
	afs_string_table *st = malloc( sizeof(afs_string_table) );
	afs_block_directory *root_dir = malloc( sizeof(afs_block_directory) );
	afs_file *f = malloc( sizeof(afs_file) );

	if( ahci_read_at_byte_offset( 0, sizeof(afs_drive), drive) ) {
		printf( "drive.version: %d\n", drive->version );
		printf( "drive.size: %08X\n", drive->size );
		printf( "drive.name_index: %d\n", drive->name_index );
		printf( "drive.root_directory: %04X\n", drive->root_directory );
		printf( "drive.next_free: %04X\n", drive->next_free );
		printf( "\n\n" );

		if( ahci_read_at_byte_offset( sizeof(afs_drive), sizeof( afs_string_table), st ) ) {
			for( int i = 0; i < st->next_free; i++ ) {
				printf( "string_table[%d] = \"%s\" @ 0x%08X\n", i, st->string[i], st->string[i]);
			}
			printf( "\n" );

			if( ahci_read_at_byte_offset( drive->root_directory, sizeof( afs_block_directory), root_dir ) ) {
				printf( "dir.next_index = %d\n", root_dir->next_index );
				printf( "dir.name_index = %d\n", root_dir->name_index );
				
				for( int i = 0; i < root_dir->next_index; i++ ) {
					printf( "dir.index[%d].start = 0x%X\n", i, root_dir->index[i].start );
					printf( "dir.index[%d].name_index = %d\n", i, root_dir->index[i].name_index );
					char * s = st->string[root_dir->index[i].name_index];
					printf( "dir.index[%d].name  = \"%s\"\n", i, s );
				}
				printf( "\n" );

				for( int i = 0; i < root_dir->next_index; i++ ) {
					memset( f, 0, sizeof( afs_file ) );
					klog( "file table %d\n", i );
					if( ahci_read_at_byte_offset( root_dir->index[i].start, sizeof( afs_file ), f ) ) {

						printf( "f.block_size: %d\n", f->block_size );
						printf( "f.file_size: %d\n", f->file_size );
						printf( "f.name_index = \"%s\"\n", st->string[f->name_index]);
						printf( "\n" );

						//printf( "%s\n\n", (char *)((char *)f + sizeof( afs_file )) );
					} else {
						printf( "file info read failed" );
					}
				}
			} else {
				printf( "dir read failed" );
			}

		} else {
			printf( "string table read failed\n" );
		}
	} else {
		printf( "drive read failed\n" );
	}

	printf( "file system tests done.\n" );
	do_immediate_shutdown();

	task_exit();
}