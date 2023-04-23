#include <kernel.h>
#include <syscall.h>
#include <afs.h>
#include <fs.h>

#define KDEBUG_READ
uint32_t read( int fd, void * buff, uint32_t size ) {
	syscall_args	args;

	#ifdef KDEBUG_READ
	klog( "calling syscall read with fd = %d, buff = 0x%08X, size = %d\n", fd, buff, size );
	#endif

	args.arg_1 = fd;
	args.arg_2 = (uint32_t)buff;
	args.arg_3 = size;

	return syscall( SYSCALL_READ, 3, &args );
}

uint32_t syscall_read( int _fd, void * buff, uint32_t size ) {
	uint32_t num_read = 0;
	vv_file_internal *fs = get_fs_internal();
	vv_file *fp;

	if( _fd == -2 ) {
		strcpy( buff, "VFive" );

		num_read = 651;
	}

	fp = &fs->fd[_fd];

	#ifdef KDEBUG_READ
	printf( "syscall_read size: %d\n", size );
	printf( "buff addr: 0x%08X\n", buff );
	#endif

	num_read = afs_read( fs, buff, size, fp );
	
	#ifdef KDEBUG_READ
	klog( "syscall_read bytes: %d\n", num_read );
	#endif
	
	return num_read;
}
