#include <kernel.h>
#include <ahci.h>
#include <afs.h>
#include <fs.h>

vv_file_internal file_system;
afs_drive main_drive;
afs_block_directory root_dir;
afs_string_table string_table;

#define KDEBUG_FS_INIT
/**
 * @brief Initalize the filesystem
 * 
 */
void fs_initalize( void ) {
	strcpy( file_system.working_directory, "/" );
	file_system.drive = &main_drive;
	file_system.root_dir = &root_dir;
	file_system.string_table = &string_table;

	// Initalize the main drive block
	if( ! ahci_read_at_byte_offset( 0, sizeof(afs_drive), file_system.drive ) ) {
		printf( "FS: Drive block read failed.\n" );
		return;
	}

	#ifdef KDEBUG_FS_INIT
	printf( "drive.version: %d\n", file_system.drive->version );
	printf( "drive.size: %08X\n", file_system.drive->size );
	printf( "drive.name_index: %d\n", file_system.drive->name_index );
	printf( "drive.root_directory: %04X\n", file_system.drive->root_directory );
	printf( "drive.next_free: %04X\n", file_system.drive->next_free );
	printf( "\n" );
	#endif

	// Load the string table
	if( ! ahci_read_at_byte_offset( sizeof(afs_drive), sizeof(afs_string_table), file_system.string_table ) ) {
		printf( "FS: String table read failed.\n" );
		return;
	}

	#ifdef KDEBUG_FS_INIT
	for( int i = 0; i < file_system.string_table->next_free; i++ ) {
		printf( "string_table[%d] = \"%s\" @ 0x%08X\n", i, file_system.string_table->string[i], file_system.string_table->string[i]);
	}
	printf( "\n" );
	#endif

	// Load the root directory block info
	if( ! ahci_read_at_byte_offset( file_system.drive->root_directory, sizeof( afs_block_directory), file_system.root_dir ) ) {
		printf( "FS: Root drive read failed.\n" );
		return;
	}

	#ifdef KDEBUG_FS_INIT
	printf( "dir.next_index = %d\n", file_system.root_dir->next_index );
	printf( "dir.name_index = %d\n", file_system.root_dir->name_index );
	
	for( int i = 0; i < file_system.root_dir->next_index; i++ ) {
		printf( "dir.index[%d].start = 0x%X\n", i, file_system.root_dir->index[i].start );
		printf( "dir.index[%d].name_index = %d\n", i, file_system.root_dir->index[i].name_index );
		char * s = file_system.string_table->string[file_system.root_dir->index[i].name_index];
		printf( "dir.index[%d].name  = \"%s\"\n", i, s );
	}
	printf( "\n" );
	#endif
}

void primative_ls( char *path ) {
	afs_ls( &file_system, path );
}