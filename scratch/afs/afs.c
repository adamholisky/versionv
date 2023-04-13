#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "afs.h"
#include <sys/stat.h>

/* FILE_VV * afs_fopen( const char * filename, const char * mode );
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

} */

/* bool afs_exists( const char * filename ) {
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
} */

#define afsfile "/usr/local/osdev/versions/v/afs.img"

bool afs_format( uint8_t *buff, uint32_t size );
uint32_t afs_add_name_to_string_table( char * name );
bool afs_add_file( uint8_t *drive_buff, afs_block_directory *dir, uint8_t *file_buff, uint32_t size, char * name );
bool afs_cp( char *name, char *name_new, uint8_t *drive_buff, afs_block_directory *dir );


uint32_t afs_get_file_location( vv_file_internal *fs, const char *filename );
uint32_t afs_get_file_location_in_dir( vv_file_internal *fs, afs_block_directory *d, const char *filename );
uint32_t afs_add_string(vv_file_internal *fs, char *name);
void afs_ls(vv_file_internal *fs, char *path);
afs_file *afs_get_file(vv_file_internal *fs, const char *filename);
vv_file * afs_fopen( vv_file_internal *fs, const char * filename, const char * mode );
uint32_t afs_exists( vv_file_internal *fs, const char * filename );
uint32_t afs_fread( vv_file_internal *fs, void *ptr, uint32_t size, uint32_t nmemb, vv_file *fp );
void afs_disply_diagnostic_data( uint8_t * buff );
void dump_afs_file( vv_file_internal *fs, afs_file *f );
uint32_t afs_exists_in_dir( vv_file_internal *fs, afs_block_directory *d, char *name );


uint32_t drive_size_in_bytes = 1024 * 1024 * 2;
char str_test[] = "Hello, world!";

afs_drive * a_drive;
afs_string_table * a_st;
afs_block_directory *a_dir;

vv_file_internal file_system;

int main( void ) {
	uint8_t * buff = malloc( drive_size_in_bytes );

	FILE *fp = fopen( afsfile, "r+" );

	afs_format( buff, drive_size_in_bytes );

	afs_add_file( buff, a_dir, str_test, strlen( str_test ), "testing.txt" );
	afs_cp( "hi", "log.txt", buff, a_dir );

	size_t written = fwrite( buff, drive_size_in_bytes, 1, fp );

	printf( "ast->nf %d\n", a_st->next_free );
	printf( "Written: %d\n", written );

	for( int i = 0; i < a_drive->next_free; i++ ) {
		if( *(buff + i) != 0 ) {
			//printf( "%X: %02X\n", i,  *(buff + i) );
		}
	}

	printf( "\n" );

	fclose( fp );

	file_system.drive = buff;
	file_system.root_dir = a_dir;
	file_system.string_table = a_st;
	file_system.next_fd = 0;

	//afs_disply_diagnostic_data( file_system.drive );

	vv_file *f = afs_fopen( &file_system, "testing.txt", "r" );

	if( f == NULL ) {
		printf( "fopen returned null\n" );
	}
	
	char *file_buff = malloc( f->size + 1);
	memset( file_buff, 0, f->size + 1);
	
	uint32_t num_read = afs_fread( &file_system, file_buff, f->size, 1, f );

	printf( "num_read: %d\n", num_read );
	printf( "data read: \"%s\"\n", file_buff );

	afs_ls( &file_system, "usr::bin" );

	return 0;
}	

bool afs_format( uint8_t *buff, uint32_t size ) {
	a_drive = (afs_drive *)buff;

	a_drive->version = AFS_VERSION_1;
	a_drive->size = size;
	a_drive->name_index = 0;
	a_drive->next_free = sizeof( afs_drive );

	a_st = (afs_string_table *)(buff + a_drive->next_free );
	a_drive->next_free = a_drive->next_free + sizeof( afs_string_table );
	strcpy( a_st->string[0], "AFS Drive 1" );
	a_st->next_free++;

	a_dir = (afs_block_directory *)(buff + a_drive->next_free );
	a_drive->root_directory = a_drive->next_free;
	a_dir->type = AFS_BLOCK_TYPE_DIRECTORY;
	a_dir->name_index = 0;
	a_dir->next_index = 0;
	memset( a_dir->index, 0, sizeof( afs_index ) * 256 );
	a_drive->next_free = a_drive->next_free + sizeof( afs_block_directory );
}

/**
 * @brief Adds a given file to the given directory
 * 
 * @param drive_buff Pointer to the buffer containing the drive
 * @param dir Pointer to the directory to put the file in
 * @param file_buff Pointer to the buffer containing the file
 * @param size Size of the file
 * @param name Name of the file
 * 
 * @return true File adding was successful
 * @return false File adding failed
 */
bool afs_add_file( uint8_t *drive_buff, afs_block_directory *dir, uint8_t *file_buff, uint32_t size, char * name ) {
	afs_file * f = (afs_file *)(drive_buff + a_drive->next_free);
	f->name_index = afs_add_name_to_string_table( name );
	f->block_size = size + 1024;
	f->file_size = size;
	f->type = AFS_BLOCK_TYPE_FILE;

	dir->index[ dir->next_index ].start = a_drive->next_free;
	dir->index[ dir->next_index ].name_index = f->name_index;
	dir->next_index++;

	a_drive->next_free = a_drive->next_free + sizeof( afs_file );
	
	memcpy( (drive_buff + a_drive->next_free), file_buff, size );

	a_drive->next_free = a_drive->next_free + f->file_size;

	return true;
}

/**
 * @brief Copy a file into the given directory
 * 
 * @param name_old File name (including path) of the file to copy into the structure
 * @param name_new New file name to use
 * @param drive_buff Pointer to the buffer containing the dirve
 * @param dir Pointer to the directory to add the file to
 * 
 * @return true Copying the file was successful
 * @return false Copying the file failed
 */
bool afs_cp( char *name_old, char *name_new, uint8_t *drive_buff, afs_block_directory *dir ) {
	FILE *fp = fopen( name_old, "r" );

	struct stat sta;
	stat( name_old, &sta );
	uint32_t file_size = sta.st_size;

	printf( "size: %d\n", file_size );

	uint8_t * buff = malloc( file_size );

	uint32_t read_size = fread( buff, file_size, 1, fp );
	printf( "read_size: %d\n", read_size );

	afs_add_file( drive_buff, a_dir, buff, file_size, name_new );

	fclose( fp );
}

/**
 * @brief Add name to the string table
 * 
 * @param name Text string to add
 * 
 * @return uint32_t Index that the name was added at
 */
uint32_t afs_add_name_to_string_table( char * name ) {
	strcpy( a_st->string[ a_st->next_free ], name );
	a_st->next_free++;

	return a_st->next_free - 1;
}


/**************************************************************/
/*                                                            */
/*                                                            */
/* SYNC EVERYTHING BELOW THIS COMMENT BLOCK WITH KERNEL       */
/*                                                            */
/*                                                            */
/**************************************************************/

/**
 * @brief Opens a file, returning FP
 * 
 * @param fs Filesystem object
 * @param filename Name of the file
 * @param mode Mode (libc like): r, w, r+
 * 
 * @return vv_file* Pointer to the file struct
 */
vv_file * afs_fopen( vv_file_internal *fs, const char * filename, const char * mode ) {
	afs_file *f = afs_get_file( fs, filename );
	vv_file *fp;

	// Bail if not found
	if( f == NULL ) {
		return NULL;
	}

	// Use the next available fp
	if( fs->next_fd == MAX_FD - 1 ) {
		return NULL;
	}

	fp = &fs->fd[fs->next_fd];
	fp->fd = fs->next_fd;
	fp->base = (uint8_t *)(f);
	fp->base = fp->base + sizeof(afs_file);
	fp->size = f->file_size;
	fp->position = 0;
	fp->dirty = false;
	fp->name = fs->string_table->string[ f->name_index ];

	//dump_afs_file( fs, f );

	fs->next_fd++;

	return fp;
}

/**
 * @brief Reads data from the given stream
 * 
 * @param fs pointer to the file system object
 * @param ptr pointer to buffer to put read data into
 * @param size number of bytes of each element to read
 * @param nmemb number of elements
 * @param fp pointer to the file pointer object
 * 
 * @return uint32_t number of members read
 */
uint32_t afs_fread( vv_file_internal *fs, void *ptr, uint32_t size, uint32_t nmemb, vv_file *fp ) {
	uint32_t num_read = 0;

	for( int i = 0; i < nmemb; i++ ) {
		if( fp->position + size > fp->size ) {
			i = nmemb + 1;
		}

		memcpy( (ptr + (size * i)), ((uint8_t *)fp->base + fp->position), size );

		fp->position = fp->position + size;
		num_read++;
	}
	
	return num_read;
}

/**
 * @brief Tests if the file exists
 * 
 * @param fs Filesystem object
 * @param filename Name of the file
 * @return bool true if the file exists, otherwise false
 */
uint32_t afs_exists( vv_file_internal *fs, const char * filename ) {
	return afs_get_file( fs, filename ) ? true : false;
}

/**
 * @brief Tests if the file exists
 * 
 * @param fs Filesystem object
 * @param filename Name of the file
 * @return uint32_t byte location of the file's afs_file if found, otherwise 0
 */
uint32_t afs_get_file_location( vv_file_internal *fs, const char *filename ) {
	afs_block_directory *d = fs->root_dir;
	uint32_t loc = 0;

	for( int i = 0; i < d->next_index; i++ ) {
		if( strcmp( fs->string_table->string[ d->index[i].name_index ], filename ) == 0 ) {
			loc = d->index[i].start;
			i = 1000000;
		}
	}

	return loc;
}

/**
 * @brief Returns bytes of file in the given dir
 * 
 * @param fs Filesystem object
 * @param dir Directory object
 * @param filename Name of the file
 * @return uint32_t byte location of the file's afs_file if found, otherwise 0
 */
uint32_t afs_get_file_location_in_dir( vv_file_internal *fs, afs_block_directory *d, const char *filename ) {
	uint32_t loc = 0;

	for( int i = 0; i < d->next_index; i++ ) {
		if( strcmp( fs->string_table->string[ d->index[i].name_index ], filename ) == 0 ) {
			loc = d->index[i].start;
			i = 1000000;
		}
	}

	return loc;
}

/**
 * @brief Returns an afs_file object for the given filename
 * 
 * @param fs Pointer to the filesystem object
 * @param filename Name of the file to retrieve
 * @return afs_file* Pointer to the given file struct
 */
afs_file* afs_get_file( vv_file_internal *fs, const char *filename ) {
	afs_file *file = NULL;
	uint32_t loc;

	loc = afs_get_file_location( fs, filename );

	if( loc == 0 ) {
		return NULL;
	}

	file = (afs_file *)( (uint8_t *)fs->drive + loc );

	return file;
}

/**
 * @brief Dump drive diagnostic data
 * 
 * @param buff Pointer to the buffer containing the drive
 */
void afs_disply_diagnostic_data( uint8_t * buff ) {

	// First dump the drive info

	afs_drive * drive = (afs_drive *)buff;

	printf( "drive.version: %d\n", drive->version );
	printf( "drive.size: %d\n", drive->size );
	printf( "drive.name_index: %d\n", drive->name_index );
	printf( "drive.root_directory: %d\n", drive->root_directory );
	printf( "drive.next_free: %d\n", drive->next_free );
	printf( "\n" );

	// Dump string index

	afs_string_table *st = (afs_string_table *)(buff + sizeof(afs_drive));

	for( int i = 0; i < st->next_free; i++ ) {
		printf( "string_table[%d] = \"%s\"\n", i, st->string[i] );
	}
	printf( "\n" );

	// Dump dir struct

	afs_block_directory * d = (afs_block_directory *)(buff + drive->root_directory);

	printf( "dir.next_index = %d\n", d->next_index );
	printf( "dir.name_index = %d\n", d->name_index );
	
	for( int i = 0; i < d->next_index; i++ ) {
		printf( "dir.index[%d].start = %d\n", i, d->index[i].start );
		printf( "dir.index[%d].name_index = \"%s\"\n", i, st->string[d->index[i].name_index] );
	}
	printf( "\n" );

	// Dump file stucts

	for( int i = 0; i < d->next_index; i++ ) {
		afs_file *f = (afs_file *)(buff + d->index[i].start );

		printf( "f.block_size: %d\n", f->block_size );
		printf( "f.file_size: %d\n", f->file_size );
		printf( "f.name_index = \"%s\"\n", st->string[f->name_index]);
		printf( "\n" );

		printf( "%s\n\n", (char *)((char *)f + sizeof( afs_file )) );
	}
}

void dump_afs_file( vv_file_internal *fs, afs_file *f ) {
	afs_string_table *st = fs->string_table;

	printf( "f.block_size: %d\n", f->block_size );
	printf( "f.file_size: %d\n", f->file_size );
	printf( "f.name_index = \"%s\"\n", st->string[f->name_index]);
	printf( "\n" );

	printf( "%s\n\n", (char *)((char *)f + sizeof( afs_file )) );
}

/**
 * @brief Add name to the string table
 * 
 * @param name Text string to add
 * 
 * @return uint32_t Index that the name was added at
 */
uint32_t afs_add_string( vv_file_internal *fs, char * name ) {
	strcpy( fs->string_table->string[ fs->string_table->next_free ], name );
	fs->string_table->next_free++;

	return fs->string_table->next_free - 1;
}

void afs_ls( vv_file_internal *fs, char *path ) {
	afs_block_directory *dir_to_list = fs->root_dir;

	printf( "ls output:\n" );

	for( int i = 0; i < dir_to_list->next_index; i++ ) {
		printf( "%s\t", fs->string_table->string[ dir_to_list->index[i].name_index ] );
	}

	printf( "\n" );
}

bool afs_mkdir( vv_file_internal *fs, afs_block_directory *d, char *name ) {
	d->index[ d->next_index ].start = fs->drive->next_free;
	d->index[ d->next_index ].name_index = afs_add_string( fs, name );
}

afs_generic_block* afs_get_generic_block( vv_file_internal *fs, char *filename ) {
	char full_filename[256];
	int i = 0;
	char item_name[256];
	afs_block_directory *d = fs->root_dir;
	bool keep_going = true;
	bool found = false;

	memset( full_filename, 0, 256 );

	// If first char isn't /, then it's a relative path
		// pre-pend with working dir
	
	if( filename[0] != '/' ) {
		strcpy( full_filename, fs.working_directory );
		
		int wd_len = strlen( fs.working_directory );

		if( full_filename[wd_len] != '/' ) {
			full_filename[wd_len] = '/';
			full_filename[wd_len + 1] = 0;
		}

		strcat( full_filename, filename );
	}

	// If first char is /, then it's an absolute path
		// iterate over each /
		// result is final iteration
	
	while( full_filename[i] != 0 && keep_going ) {
		memset( item_name, 0, 256 );

		// Copy the current element into item_name
		for( int x = 0; x < 256; x++, i++ ) {
			item_name[x] = full_filename[i];

			if( full_filename[i] == '/' ) {
				x = 256;
				i++;
			}

			if( full_filename[i] == 0 ) {
				x = 256;
			}
		}

		// Test if item_name exists
		if( afs_exists_in_dir( d, item_name ) != 0 ) {
			keep_going = false;
			found = false;
		} else {
			found = true;
		}
	}


}

uint32_t afs_exists_in_dir( vv_file_internal *fs, afs_block_directory *d, char *name ) {
	uint32_t result = 0;

	for( int i = 0; i < d->next_index; i++ ) {
		if( strcmp( fs->string_table->string[ d->index[i].name_index ], name ) == 0 ) {
			result = d->index[i].start;
		}
	}

	return result;
}