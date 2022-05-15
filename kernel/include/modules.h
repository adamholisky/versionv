#if !defined(MODULES_INCLUDED)
#define MODULES_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef void (*module_init_func)( void );
typedef void (*module_exit_func)( void );
typedef void (*module_main_func)( int argc, char *argv[] );

class Module {
	private:
		uint32_t	task_id;
		uint32_t	elf_object_start_addr;
		uint32_t	elf_object_size;
		
		char		name[25];

		module_init_func init;
		module_exit_func exit;
		module_main_func main;
	public:
		void load( uint32_t *module_start );
		void call_init( void );
		void call_exit( void );
		void call_main( void );
};

#ifdef __cplusplus
}
#endif

#endif