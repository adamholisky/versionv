#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "afs.h"

#define afsfile "/usr/local/osdev/versions/v/afs.img"

bool afs_format( FILE *fp, uint32_t size );
FILE_VV * afs_fopen( const char * filename, const char * mode );
int afs_fclose( FILE_VV *fp );

bool afs_exists( const char * filename );
char * afs_ls( const char * directory, char * list );

int afs_fgetc( FILE_VV * fp );
char * afs_fgets( char *buf, int n, FILE_VV *fp );
size_t afs_fread(void *ptr, size_t size_of_elements, size_t number_of_elements, FILE_VV *a_file);

int afs_fputc( int c, FILE_VV *fp );
int afs_fputs( const char *s, FILE_VV *fp );              
size_t afs_fwrite(const void *ptr, size_t size_of_elements, size_t number_of_elements, FILE_VV *a_file);

FILE_VV * afs_fopen( const char * filename, const char * mode ) {

}

int afs_fclose( FILE_VV *fp ) {

}

char * afs_ls( const char * directory, char * list ) {

}

bool afs_exists( const char * filename ) {
	char full_filename[512];
	char list_of_dir[256];
	char item_name[256];
	char current_dir[256];

	afs_index ** current_index = filesys.drive;

	char *list = (char *)list_of_dir;
	int i = 0;

	// If first char isn't /, then it's a relative path
		// pre-pend with working dir
	
	if( filename[0] != '/' ) {
		strcpy( full_filename, filesys.working_directory );
		
		int wd_len = strlen( filesys.working_directory );

		if( full_filename[wd_len] != '/' ) {
			full_filename[wd_len] = '/';
			full_filename[wd_len + 1] = 0;
		}

		strcat( full_filename, filename );

		if( full_filename[wd_len] != '/' ) {
			full_filename[wd_len] = '/';
			full_filename[wd_len + 1] = 0;
		}
	}

	// If first char is /, then it's an absolute path
		// iterate over each /
		// result is final iteration
	
	while( full_filename[i] != 0 ) {
		memset( item_name, 0, 256 );

		// Copy the current element into item_name
		for( int x = 0; x < 256; x++, i++ ) {
			item_name[x] = full_filename[i];

			if( full_filename == '/' ) {
				x = 256;
				i++;
			}

			if( full_filename == 0 ) {
				x = 256;
			}
		}

		// Test if item_name exists
		
	}
	
	
	
	strcpy( current_dir, filesys.working_directory );
	list_of_dir = afs_ls( current_dir, list_of_dir );
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


vv_file_internal filesys;

uint32_t drive_size_in_bytes = 1024 * 1024 * 256;

int main( void ) {
	// Setup the file system internals
	strcpy( filesys.working_directory, "/" );

	FILE *fp = fopen( afsfile, "r+" );

	//afs_format( fp, 1024 * 1024 * 2 );

	fclose( fp );

	return 0;
}

afs_block_directory * afs_get_directory_block_from_path( char * path ) {
	afs_block_directory * d;

	char full_filename[512];
	char list_of_dir[256];
	char item_name[256];
	char current_dir[256];


	afs_index ** current_index = filesys.root_dir->index;

	char *list = (char *)list_of_dir;
	int i = 1;

	if( path == NULL ) {
		d = filesys.root_dir;
	} elseif( strcmp( path, "/" ) == 0 ) {
		d = filesys.root_dir;
	} else {
		// If first char isn't /, then it's a relative path
		// pre-pend with working dir
	
		if( path[0] != '/' ) {
			strcpy( full_filename, filesys.working_directory );
			
			int wd_len = strlen( filesys.working_directory );

			if( full_filename[wd_len] != '/' ) {
				full_filename[wd_len] = '/';
				full_filename[wd_len + 1] = 0;
			}

			strcat( full_filename, filename );

			if( full_filename[wd_len] != '/' ) {
				full_filename[wd_len] = '/';
				full_filename[wd_len + 1] = 0;
			}
		}

		// Now parse the full path

		while( full_filename[i] != 0 ) {
			bool keep_going = false;

			memset( item_name, 0, 256 );

			// Copy the current element into item_name
			for( int x = 0; x < 256; x++, i++ ) {
				item_name[x] = full_filename[i];

				if( full_filename == '/' ) {
					x = 256;
					i++;
				}

				if( full_filename == 0 ) {
					x = 256;
				}
			}

			// does the item exist?
			for( int x = 0; x < 256; x++ ) {
				if( strcmp(filesys.string_table->string[current_index[x].name_index], item_name) == 0 ) {
					// It exists
					x = 256;
					keep_going = false;
				} else {
					keep_going = true;
				}
				
			}

			// if it exists AND we're at the end, then set result
			if( keep_going == true && full_filename[i] == 0 ) {
				d = 
			} else {
				// Item in the path wasn't found, bail
				full_filename[i] = 0;
			}
		}
	}

	

	// If first char is /, then it's an absolute path
		// iterate over each /
		// result is final iteration
	
	

		// Test if item_name exists
		
	}

	return d;
}

bool afs_mkdir( char * path, char * name ) {
	afs_block_directory * d = afs_get_directory_block_from_path( path );
}

bool afs_format( FILE *fp, uint32_t size ) {
	uint8_t * buff = malloc( size );
	afs_drive * a_drive = (afs_drive *)buff;

	a_drive->version = AFS_VERSION_1;
	a_drive->size = size;
	a_drive->name_index = 0;
	a_drive->next_free = sizeof( afs_drive );
	memset( a_drive->index, 0, sizeof( afs_index ) * 256 );
	a_drive->next_index = 0;

	afs_string_table * a_st = (afs_string_table *)(buff + a_drive->next_free );
	a_drive->next_free = a_drive->next_free + sizeof( afs_string_table );
	strcpy( a_st->string[0], "AFS Drive 1" );
	a_st->next_free++;

	// Setup first directory, bin
	afs_block_directory * d = (afs_block_directory *)(buff + a_drive->next_free );
	d->type = AFS_BLOCK_TYPE_DIRECTORY;
	d->name_index = 1;
	strcpy( a_st->string[ a_st->next_free ], "bin" );

	a_drive->index[ a_drive->next_index ].start = a_drive->next_free;
	a_drive->index[ a_drive->next_index ].name_index = a_st->next_free;
	a_drive->next_free = a_drive->next_free + sizeof( afs_block_directory );

	a_drive->next_index++;
	a_st->next_free++;

	// Setup first file, test.txt
	afs_file * f = (afs_file *)(buff + a_drive->next_free);
	f->name_index = 2;
	f->size = 1024 * 100;
	f->type = AFS_BLOCK_TYPE_FILE;

	strcpy( a_st->string[ a_st->next_free ], "test.txt" );
	a_st->next_free++;

	a_drive->next_free = a_drive->next_free + sizeof( afs_file );
	
	printf( "next_free: %X\n", a_drive->next_free );

	strcpy( (buff + a_drive->next_free ), "This is a test text file." );

	a_drive->next_free = a_drive->next_free +  1024 * 100;

	size_t written = fwrite( buff, size, 1, fp );

	printf( "Written: %d\n", written );

	for( int i = 0; i < a_drive->next_free; i++ ) {
		if( *(buff + i) != 0 ) {
			printf( "%X: %02X\n", i,  *(buff + i) );
		}
	}

	printf( "\n" );
}