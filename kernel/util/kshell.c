#include <kernel.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <serial.h>
#include <keyboard.h>
#include <debug.h>
#include <kmalloc.h>

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

	if( strcmp( args[0], "q" ) == 0 ) {
		kshell_shutdown();
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
	while( true ) {
		printf( "\x1b[0;31;49mVersionV\x1b[0;0;0m:\x1b[0;32;49m%s\x1b[0;0;0m> ", wd );

		kshell_get_line();

		kshell_process_line();
	}
}

void kshell_shutdown( void ) {
	debugf( "\nGoodbye, Dave.\n" );
	outportb( 0xF4, 0x00 );
}
