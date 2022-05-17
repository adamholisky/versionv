#ifndef VSHELL_INCLUDED
#define VSHELL_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <ftp.h>

class VShell {
	private:
		char line[256];
		char jail_env[256];
		char wd[256];
		int line_pos;
		FTP *ftp;

		void get_line( void );
		void process_line( void );
		void ls( void );
		void shutdown( void );
	public:
		void init( FTP *f );
		void run( void );
		char *get_jailed_path( void );
		bool cd( char *path );
		bool file_exists( char *path, char *file );
};

#ifdef __cplusplus
}
#endif
#endif