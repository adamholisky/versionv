#if !defined(AFS_INCLUDED)
#define AFS_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>

	/*
		Drive Byte          Data
		------------------------------------------------------------
		0                   afs_drive
		[index 0]           afs_block_directory for /
		[index ]


	*/

#define AFS_VERSION_1 1

#define AFS_BLOCK_TYPE_UNKNOWN 0
#define AFS_BLOCK_TYPE_FILE 1
#define AFS_BLOCK_TYPE_DIRECTORY 2

typedef struct {
	uint32_t	start;			// starting byte of the item
	uint32_t	name_index;		// string table index
} afs_index;

typedef struct {
	char		string[5000][50];
	uint32_t	next_free;		// next free string table name
} afs_string_table;

typedef struct {	
	uint32_t 	version;		// version of the drive struct
	uint32_t 	size;			// overall size of the drive, in bytes
	uint32_t	name_index;		// string table index
	uint32_t	root_directory;	// starting byte of the dir struct for root

	uint32_t	next_free;		// next free byte
	afs_index 	index[256];		// root drive
	uint32_t	next_index;		// new index free
} afs_drive;

typedef struct {
	uint8_t 	type;			// Type, always AFS_BLOCK_TYPE_FILE
	uint32_t 	size;			// size of the file
	uint32_t	name_index;		// string table index
} afs_file;

typedef struct {
	uint8_t 	type;			// Type, always AFS_BLOCK_TYPE_DIRECTORY
    uint32_t	name_index;		// string table index
	afs_index	index[256];		// Block index for things in this directory
	uint32_t	next_index;		// next index free
} afs_block_directory;

typedef struct {
	vv_file *	fd[128];
	char		working_directory[128];
	afs_drive *	drive;
	afs_block_directory * root_dir;
	afs_string_table * string_table;
} vv_file_internal;

typedef struct {
	uint32_t	fd;
	uint8_t		*base;
	uint32_t	size;
	uint32_t	position;
	bool		dirty;

} vv_file;

#define FILE_VV vv_file


#ifdef __cplusplus
}
#endif

#endif