#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vshell.h>
#include <serial.h>
#include <keyboard.h>
#include <debug.h>
#include <kmalloc.h>
#include <ftp.h>
#include <kernel.h>

#define SERIAL_CONSOLE_ACTIVE true

void VShell::init( FTP *f ) {
	this->ftp = f;
	ftp->cwd( "/usr/local/osdev/versions/v/os_root/" );

	strcpy( jail_env, "/usr/local/osdev/versions/v/os_root/" );
}

void VShell::ls( void ) {
	ftp->nlst();
	debugf( "%s\n", ftp->data_buffer );
}

void VShell::run( void ) {
	ls();

	cd( "/home/vv" );
	cd( "adam" );
	cd( "what" );

	debugf( "VersionV:%s>", wd );

	while( false ) {
		if( SERIAL_CONSOLE_ACTIVE ) {
			debugf( "VersionV:%s>", wd );
		} else {
			printf( "VersionV:%s>", wd );
		}

		get_line();

		if( SERIAL_CONSOLE_ACTIVE ) {
			debugf( "\n" );
		} else {
			printf( "\n" );
		}

		process_line();
	}
}

void VShell::get_line( void ) {
	char c = ' ';
	bool process_keypress = true;

	memset( line, 0, 256 );
	line_pos = 0;

	while( process_keypress ) {
		if( SERIAL_CONSOLE_ACTIVE ) {
			if( serial_buffer_is_ready() ) {
				c = serial_buffer_get_char();

				debugf( "%c", c );
			}
		} else {
			if( c = keyboard_get_char() ) {
				printf( "%c", c );
			}
		}

		if( c == '\n' ) {
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

void VShell::process_line( void ) {
	if( strcmp( line, "c" ) == 0 ) {
		cd( "/home/vv" );
		cd( "adam" );
		cd( "etwhat" );
	}

	if( strcmp( line, "q" ) == 0 ) {
		shutdown();
	}

	if( strcmp( line, "ls" ) == 0 ) {
		ls();
	}
}

void VShell::shutdown( void ) {
	debugf( "\nGoodbye, Dave.\n" );
	outportb( 0xF4, 0x00 );
}

bool VShell::cd( char *path ) {
	char p[256];
	char p_no_jail[256];
	char* token;
	bool absolute = false;
	int front_adjustment = 0;

	debugf( "cd %s\n", path );

	// Apply jailing env to our local path root
	strcpy( p, jail_env );

	// Handle relative vs absolute path
	// TODO: Look into this more, seems too easy
	if( path[0] == '/' ) {
		absolute = true;
		front_adjustment = 1;
		strcpy( p_no_jail, "/" );
		//strcat( p, (path + 1) ); // ignore the first /
		//strcat( p, "/" );
	} else {
		strcat( p, wd );
		strcpy( p_no_jail, wd );
		//strcat( p, path );
		//strcat( p, path );
	}

	debugf( "Full path for this CD: \"%s%s\"\n", p, (path + front_adjustment) );

	token = strtok( path, "/" );

	while( token != NULL ) {
		//debugf( "t: \"%s\"\n", token );
		
		//does token exist?
		bool exist = file_exists( p, token );
		if( exist ) {
			//debugf( "%s exists!\n", token );
			strcat( p, token );
			strcat( p, "/" );

			strcat( p_no_jail, token );
			strcat( p_no_jail, "/" );
		} else {
			debugf( "cd: %s: no such file name or directory.\n", path );
			return false;
		}
		
		token = strtok( NULL, "/" );
	}

	ftp->cwd( p );

	strcpy( wd, p_no_jail );

	debugf( "Successfully CD'd into %s!\n", wd );

	return true;
}

char* VShell::get_jailed_path( void ) {
	return "/";
}

/**
 * @brief Test if the file exists
 * 
 * @param path Path to the directory to check if file exists in. MUST BE VALID.
 * @param file Name of the file to check, case sensitive
 * @return true The file exists
 * @return false The file doesn't exist
 */
bool VShell::file_exists( char *path, char *file ) {
	char list_of_dir[256];
	char item_name[256];
	char current_dir[256];

	char *list = (char *)list_of_dir;
	int i = 0;
	
	strcpy( current_dir, ftp->pwd() );
	ftp->cwd( path );
	ftp->nlst();
	strcpy( list_of_dir, ftp->data_buffer );

	memset( item_name, 0, 256 );

	// Parse through the entire buffer
	while( *list != 0 ) {
		// Get each line
		while( *list != '\n' ) {
			item_name[i]= *list;
			i++;
			list++;

			// Terminating char at end of each file name is 0xD?
			if( item_name[i - 1] == 13 ) {
				item_name[i - 1] = 0;
			}
		}

		//Does the item exist?
		if( strcmp( file, item_name ) == 0 ) {
			ftp->cwd( current_dir );
			return true;
		} else {
			//debugf( "\"%s\" doesn't exist.\n", item_name );
		}

		list++;
		memset( item_name, 0, 256 );
		i = 0;
	}

	ftp->cwd( current_dir );
	return false;
}
