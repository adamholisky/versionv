# 0 "kernel/c/memory.c"
# 1 "/usr/local/osdev/versions/v//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "kernel/c/memory.c"
# 1 "/usr/local/osdev/versions/v/kernel/include/kernel.h" 1



# 1 "/usr/local/osdev/lib/gcc/i686-elf/11.2.0/include/stdbool.h" 1 3 4
# 5 "/usr/local/osdev/versions/v/kernel/include/kernel.h" 2
# 1 "/usr/local/osdev/versions/v/libcvv/include/stddef.h" 1



# 1 "/usr/local/osdev/versions/v/libcvv/include/_types/_ptrdiff_t.h" 1



typedef long ptrdiff_t;
# 5 "/usr/local/osdev/versions/v/libcvv/include/stddef.h" 2
# 1 "/usr/local/osdev/versions/v/libcvv/include/_types/_size_t.h" 1



typedef unsigned long size_t;

typedef long ssize_t;
# 6 "/usr/local/osdev/versions/v/libcvv/include/stddef.h" 2

#pragma mark - NULL -
# 18 "/usr/local/osdev/versions/v/libcvv/include/stddef.h"
#pragma mark - offsetof -
# 30 "/usr/local/osdev/versions/v/libcvv/include/stddef.h"
#pragma mark - max_align_t -





typedef long double max_align_t;
# 6 "/usr/local/osdev/versions/v/kernel/include/kernel.h" 2
# 1 "/usr/local/osdev/versions/v/libcvv/include/stdint.h" 1
# 9 "/usr/local/osdev/versions/v/libcvv/include/stdint.h"
# 1 "/usr/local/osdev/versions/v/libcvv/include/limits.h" 1




# 1 "/usr/local/osdev/versions/v/libcvv/include/_limits.h" 1
# 6 "/usr/local/osdev/versions/v/libcvv/include/limits.h" 2
# 10 "/usr/local/osdev/versions/v/libcvv/include/stdint.h" 2
# 20 "/usr/local/osdev/versions/v/libcvv/include/stdint.h"
# 1 "/usr/local/osdev/versions/v/libcvv/include/_types/_int16_t.h" 1



typedef short int16_t;
# 21 "/usr/local/osdev/versions/v/libcvv/include/stdint.h" 2
# 1 "/usr/local/osdev/versions/v/libcvv/include/_types/_int32_t.h" 1



typedef int int32_t;
# 22 "/usr/local/osdev/versions/v/libcvv/include/stdint.h" 2
# 1 "/usr/local/osdev/versions/v/libcvv/include/_types/_int64_t.h" 1



typedef long long int64_t;
# 23 "/usr/local/osdev/versions/v/libcvv/include/stdint.h" 2
# 1 "/usr/local/osdev/versions/v/libcvv/include/_types/_int8_t.h" 1



typedef signed char int8_t;
# 24 "/usr/local/osdev/versions/v/libcvv/include/stdint.h" 2
# 1 "/usr/local/osdev/versions/v/libcvv/include/_types/_uint16_t.h" 1



typedef unsigned short uint16_t;
# 25 "/usr/local/osdev/versions/v/libcvv/include/stdint.h" 2
# 1 "/usr/local/osdev/versions/v/libcvv/include/_types/_uint32_t.h" 1



typedef unsigned int uint32_t;
# 26 "/usr/local/osdev/versions/v/libcvv/include/stdint.h" 2
# 1 "/usr/local/osdev/versions/v/libcvv/include/_types/_uint64_t.h" 1



typedef unsigned long long uint64_t;
# 27 "/usr/local/osdev/versions/v/libcvv/include/stdint.h" 2
# 1 "/usr/local/osdev/versions/v/libcvv/include/_types/_uint8_t.h" 1



typedef unsigned char uint8_t;
# 28 "/usr/local/osdev/versions/v/libcvv/include/stdint.h" 2



typedef int8_t int_least8_t;


typedef int16_t int_least16_t;


typedef int32_t int_least32_t;


typedef int64_t int_least64_t;


typedef uint8_t uint_least8_t;


typedef uint16_t uint_least16_t;


typedef uint32_t uint_least32_t;


typedef uint64_t uint_least64_t;



typedef int8_t int_fast8_t;


typedef int32_t int_fast16_t;


typedef int32_t int_fast32_t;


typedef int64_t int_fast64_t;


typedef uint8_t uint_fast8_t;


typedef uint32_t uint_fast16_t;


typedef uint32_t uint_fast32_t;


typedef uint64_t uint_fast64_t;


# 1 "/usr/local/osdev/versions/v/libcvv/include/_types/_intptr_t.h" 1



typedef long intptr_t;
# 81 "/usr/local/osdev/versions/v/libcvv/include/stdint.h" 2
# 1 "/usr/local/osdev/versions/v/libcvv/include/_types/_uintptr_t.h" 1



typedef unsigned long uintptr_t;
# 82 "/usr/local/osdev/versions/v/libcvv/include/stdint.h" 2


# 1 "/usr/local/osdev/versions/v/libcvv/include/_types/_intmax_t.h" 1



typedef long long int intmax_t;
# 85 "/usr/local/osdev/versions/v/libcvv/include/stdint.h" 2
# 1 "/usr/local/osdev/versions/v/libcvv/include/_types/_uintmax_t.h" 1



typedef long long unsigned int uintmax_t;
# 86 "/usr/local/osdev/versions/v/libcvv/include/stdint.h" 2
# 7 "/usr/local/osdev/versions/v/kernel/include/kernel.h" 2
# 1 "/usr/local/osdev/versions/v/kernel/include/globals.h" 1




extern uint8_t paging_level_active;
# 8 "/usr/local/osdev/versions/v/kernel/include/kernel.h" 2
# 1 "/usr/local/osdev/versions/v/kernel/include/bootstrap.h" 1
# 9 "/usr/local/osdev/versions/v/kernel/include/bootstrap.h"
uint64_t __udivmoddi4(uint64_t num, uint64_t den, uint64_t *rem_p);

unsigned long hex2int(char *a, unsigned int len);
# 29 "/usr/local/osdev/versions/v/kernel/include/bootstrap.h"
static inline void outportb( uint32_t port, uint8_t value ) {
    __asm__ __volatile__ ("outb %%al,%%dx"::"d" (port), "a" (value));
}


static inline void outportw( uint32_t port, uint32_t value ) {
    __asm__ __volatile__ ("outw %%ax,%%dx"::"d" (port), "a" (value));
}


static inline uint8_t inportb( uint32_t port ) {
    uint8_t value;
    __asm__ __volatile__ ("inb %w1,%b0" : "=a"(value) : "d"(port));
    return value;
}

static inline uint8_t inportw( uint32_t port ) {
    uint8_t value;
    __asm__ __volatile__ ("inw %%dx,%%ax" : "=a"(value) : "d"(port));
    return value;
}

static inline void out_port_long( uint16_t port, uint32_t value) {
    __asm__ __volatile__ ( "outl %%eax, %%dx" : : "d" (port), "a" (value) );
}

static inline uint32_t in_port_long( uint16_t port ) {
    uint32_t value;
    __asm__ __volatile__ ("inl %%dx, %%eax" : "=a"(value) : "dN"(port));
    return value;
}
# 9 "/usr/local/osdev/versions/v/kernel/include/kernel.h" 2
# 1 "/usr/local/osdev/versions/v/libcvv/include/string.h" 1
# 11 "/usr/local/osdev/versions/v/libcvv/include/string.h"
#pragma mark - memory -
# 29 "/usr/local/osdev/versions/v/libcvv/include/string.h"
int memcmp(const void* s1, const void* s2, size_t n);
# 45 "/usr/local/osdev/versions/v/libcvv/include/string.h"
void* memset(void* dest, int c, size_t n);
# 62 "/usr/local/osdev/versions/v/libcvv/include/string.h"
void* memcpy(void* __restrict dest, const void* __restrict src, size_t n);
# 78 "/usr/local/osdev/versions/v/libcvv/include/string.h"
void* memmove(void* dest, const void* src, size_t n);
# 94 "/usr/local/osdev/versions/v/libcvv/include/string.h"
void* memchr(const void* s, int c, size_t n);
# 111 "/usr/local/osdev/versions/v/libcvv/include/string.h"
void* memmem(const void* l, size_t l_len, const void* s, size_t s_len);

#pragma mark - string -
# 127 "/usr/local/osdev/versions/v/libcvv/include/string.h"
size_t strlen(const char* str);
# 144 "/usr/local/osdev/versions/v/libcvv/include/string.h"
size_t strnlen(const char* str, size_t maxlen);
# 164 "/usr/local/osdev/versions/v/libcvv/include/string.h"
char* strcpy(char* __restrict dst, const char* __restrict src);
# 187 "/usr/local/osdev/versions/v/libcvv/include/string.h"
char* strncpy(char* __restrict dst, const char* __restrict src, size_t maxlen);
# 204 "/usr/local/osdev/versions/v/libcvv/include/string.h"
char* strstr(const char* string, const char* substring);
# 222 "/usr/local/osdev/versions/v/libcvv/include/string.h"
char* strnstr(const char* s, const char* find, size_t slen);
# 237 "/usr/local/osdev/versions/v/libcvv/include/string.h"
int strcmp(const char* s1, const char* s2);
# 255 "/usr/local/osdev/versions/v/libcvv/include/string.h"
int strncmp(const char* s1, const char* s2, size_t n);
# 267 "/usr/local/osdev/versions/v/libcvv/include/string.h"
char* strdup(const char* str);
# 280 "/usr/local/osdev/versions/v/libcvv/include/string.h"
char* strndup(const char* str, size_t n);
# 296 "/usr/local/osdev/versions/v/libcvv/include/string.h"
char* strchr(const char* s, int c);
# 312 "/usr/local/osdev/versions/v/libcvv/include/string.h"
char* strrchr(const char* s, int c);
# 332 "/usr/local/osdev/versions/v/libcvv/include/string.h"
char* strcat(char* __restrict dst, const char* __restrict src);
# 355 "/usr/local/osdev/versions/v/libcvv/include/string.h"
char* strncat(char* __restrict dst, const char* __restrict src, size_t maxlen);
# 375 "/usr/local/osdev/versions/v/libcvv/include/string.h"
char* strtok(char* s, const char* delim);


size_t strxfrm(char* __restrict, const char* __restrict, size_t);
size_t strcspn(const char*, const char*);
size_t strspn(const char*, const char*);
char* strpbrk(const char*, const char*);
int strcoll(const char*, const char*);
char* strerror(int);
int strerror_r(int, char*, size_t);
# 10 "/usr/local/osdev/versions/v/kernel/include/kernel.h" 2
# 1 "/usr/local/osdev/versions/v/kernel/include/terminal.h" 1


# 1 "/usr/local/osdev/versions/v/kernel/include/vga.h" 1



enum vga_color
{
 VGA_COLOR_BLACK = 0,
 VGA_COLOR_BLUE = 1,
 VGA_COLOR_GREEN = 2,
 VGA_COLOR_CYAN = 3,
 VGA_COLOR_RED = 4,
 VGA_COLOR_MAGENTA = 5,
 VGA_COLOR_BROWN = 6,
 VGA_COLOR_LIGHT_GREY = 7,
 VGA_COLOR_DARK_GREY = 8,
 VGA_COLOR_LIGHT_BLUE = 9,
 VGA_COLOR_LIGHT_GREEN = 10,
 VGA_COLOR_LIGHT_CYAN = 11,
 VGA_COLOR_LIGHT_RED = 12,
 VGA_COLOR_LIGHT_MAGENTA = 13,
 VGA_COLOR_LIGHT_BROWN = 14,
 VGA_COLOR_WHITE = 15,
};


typedef struct {
   char VbeSignature[4];
   uint16_t VbeVersion;
   uint16_t OemStringPtr[2];
   uint8_t Capabilities[4];
   uint16_t VideoModePtr[2];
   uint16_t TotalMemory;
} vesa_info_block;


typedef struct {
 uint16_t attributes;
 uint8_t window_a;
 uint8_t window_b;
 uint16_t granularity;
 uint16_t window_size;
 uint16_t segment_a;
 uint16_t segment_b;
 uint32_t win_func_ptr;
 uint16_t pitch;
 uint16_t width;
 uint16_t height;
 uint8_t w_char;
 uint8_t y_char;
 uint8_t planes;
 uint8_t bpp;
 uint8_t banks;
 uint8_t memory_model;
 uint8_t bank_size;
 uint8_t image_pages;
 uint8_t reserved0;

 uint8_t red_mask;
 uint8_t red_position;
 uint8_t green_mask;
 uint8_t green_position;
 uint8_t blue_mask;
 uint8_t blue_position;
 uint8_t reserved_mask;
 uint8_t reserved_position;
 uint8_t direct_color_attributes;

 uint32_t framebuffer;
 uint32_t off_screen_mem_off;
 uint16_t off_screen_mem_size;
 uint8_t reserved1[206];
} vesa_mode_info;
# 85 "/usr/local/osdev/versions/v/kernel/include/vga.h"
typedef struct {
 uint32_t x;
 uint32_t y;
} point;

typedef struct {
 uint32_t x;
 uint32_t y;
 uint32_t w;
 uint32_t h;
} rect;

typedef struct {
 uint8_t * fbuffer;
 uint8_t * buffer;
 uint32_t pitch;
 uint32_t width;
 uint32_t height;
 uint32_t bpp;
 uint32_t pixel_width;

 uint32_t char_width;
 uint32_t char_height;

 uint32_t fg_color;
 uint32_t bg_color;
} vga_information;

void vga_initalize( void );
void fillrect( uint8_t * buffer, uint32_t color, unsigned int x, unsigned int y, unsigned int w, unsigned int h);
void put_pixel( unsigned int x, unsigned int y, int color );
void putpixel( uint8_t * buffer, unsigned int x, unsigned int y, int color);
void draw_string( char * string, unsigned int x, unsigned int y, unsigned int fg_color, unsigned int bg_color );
void draw_rect( rect r, unsigned int color );
void move_rect( rect dest, rect src );
void moverect( uint8_t *buff, rect dest, rect src );
void vga_move_line( unsigned int dest_y, unsigned int src_y );
void vga_put_char( unsigned char c, unsigned int x, unsigned int y );
void draw_char( uint8_t * buffer, unsigned int x, unsigned int y, uint32_t fg, uint32_t bg, unsigned int font_char );
void vga_draw_screen( void );
vga_information * vga_get_info( void );

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
{
 return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
 return (uint16_t) uc | (uint16_t) color << 8;
}
# 4 "/usr/local/osdev/versions/v/kernel/include/terminal.h" 2
# 1 "/usr/local/osdev/versions/v/libcvv/include/printf.h" 1
# 35 "/usr/local/osdev/versions/v/libcvv/include/printf.h"
# 1 "/usr/local/osdev/lib/gcc/i686-elf/11.2.0/include/stdarg.h" 1 3 4
# 40 "/usr/local/osdev/lib/gcc/i686-elf/11.2.0/include/stdarg.h" 3 4

# 40 "/usr/local/osdev/lib/gcc/i686-elf/11.2.0/include/stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 99 "/usr/local/osdev/lib/gcc/i686-elf/11.2.0/include/stdarg.h" 3 4
typedef __gnuc_va_list va_list;
# 36 "/usr/local/osdev/versions/v/libcvv/include/printf.h" 2
# 49 "/usr/local/osdev/versions/v/libcvv/include/printf.h"

# 49 "/usr/local/osdev/versions/v/libcvv/include/printf.h"
void _putchar(char character);
# 61 "/usr/local/osdev/versions/v/libcvv/include/printf.h"
int printf_(const char* format, ...);
# 72 "/usr/local/osdev/versions/v/libcvv/include/printf.h"
int sprintf_(char* buffer, const char* format, ...);
# 87 "/usr/local/osdev/versions/v/libcvv/include/printf.h"
int snprintf_(char* buffer, size_t count, const char* format, ...);
int vsnprintf_(char* buffer, size_t count, const char* format, va_list va);
# 98 "/usr/local/osdev/versions/v/libcvv/include/printf.h"
int vprintf_(const char* format, va_list va);
# 109 "/usr/local/osdev/versions/v/libcvv/include/printf.h"
int fctprintf(void (*out)(char character, void* arg), void* arg, const char* format, ...);
# 5 "/usr/local/osdev/versions/v/kernel/include/terminal.h" 2




typedef struct {
    uint32_t current_row;
    uint32_t current_column;
    uint32_t foreground_color;
    uint32_t background_color;
} term;

void term_initalize( void );
void term_print_color( void );
void term_set_color( uint32_t foreground, uint32_t background );
void term_put_char( char c );
void term_put_char_at( char c, unsigned char color, unsigned int x, unsigned int y );
void term_clear_last_char( void );
void term_put_string( const char* data, size_t size );
void term_write_string( const char* data );
void set_debug_output( 
# 24 "/usr/local/osdev/versions/v/kernel/include/terminal.h" 3 4
                      _Bool 
# 24 "/usr/local/osdev/versions/v/kernel/include/terminal.h"
                           d );
void write_serial(char a);
void write_to_serial_port( char c );

void console_init( char * name, unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int bg_color, unsigned int fg_color );
void console_draw( void );
void console_put_char_at( char c, unsigned int x, unsigned int y );
void console_put_char( char c );
void console_move_row( unsigned int dest, unsigned int src );
void console_scroll_forever_test( void );
# 11 "/usr/local/osdev/versions/v/kernel/include/kernel.h" 2

# 1 "/usr/local/osdev/versions/v/kernel/include/serial.h" 1
# 17 "/usr/local/osdev/versions/v/kernel/include/serial.h"
void initalize_serial( void );
void serial_enable_interrupts( void );
void serial_setup_port( uint32_t port );
void serial_set_default_port( uint32_t port );
void serial_write_port( char c, uint32_t port );
char serial_read_port( uint32_t port );

# 23 "/usr/local/osdev/versions/v/kernel/include/serial.h" 3 4
_Bool 
# 23 "/usr/local/osdev/versions/v/kernel/include/serial.h"
    serial_buffer_is_ready( void );
char serial_buffer_get_char( void );
void set_data_ready_callback( void *f );
void set_data_buffer( char *buff );
void set_data_is_being_read( 
# 27 "/usr/local/osdev/versions/v/kernel/include/serial.h" 3 4
                            _Bool 
# 27 "/usr/local/osdev/versions/v/kernel/include/serial.h"
                                 b );
# 13 "/usr/local/osdev/versions/v/kernel/include/kernel.h" 2
# 1 "/usr/local/osdev/versions/v/kernel/include/memory.h" 1
# 55 "/usr/local/osdev/versions/v/kernel/include/memory.h"
typedef struct {
 uint8_t present : 1;
 uint8_t rw : 1;
 uint8_t privilege : 1;
 uint8_t write_through : 1;
 uint8_t cache_disabled : 1;
 uint8_t accessed : 1;
 uint8_t page_size : 1;
 uint8_t ignored : 1;
 uint8_t available : 3;
 uint32_t address : 20;
} page_directory_entry;

void memory_initalize( void );
uint32_t * page_map( uint32_t *virt_addr, uint32_t *phys_addr );
uint32_t * page_allocate( uint32_t num );
void set_task_pde( page_directory_entry * pte );
uint32_t * get_physical_memory_base( void );
void dump_active_pt( void );
uint32_t * get_physical_addr_from_virt( uint32_t * virt );
# 14 "/usr/local/osdev/versions/v/kernel/include/kernel.h" 2
# 1 "/usr/local/osdev/versions/v/kernel/include/kmalloc.h" 1
# 11 "/usr/local/osdev/versions/v/kernel/include/kmalloc.h"
int liballoc_lock();







int liballoc_unlock();
# 28 "/usr/local/osdev/versions/v/kernel/include/kmalloc.h"
void* liballoc_alloc(size_t);
# 38 "/usr/local/osdev/versions/v/kernel/include/kmalloc.h"
int liballoc_free(void*,size_t);

void *kmalloc(size_t);
void *krealloc(void *, size_t);
void *kcalloc(size_t, size_t);
void kfree(void *);

void memory_test( void );
void * __attribute__((weak)) memset(void * dest, int c, size_t n);
void liballoc_dump( void );
# 15 "/usr/local/osdev/versions/v/kernel/include/kernel.h" 2
# 1 "/usr/local/osdev/versions/v/kernel/include/task.h" 1




# 1 "/usr/local/osdev/versions/v/kernel/include/interrupts.h" 1
# 67 "/usr/local/osdev/versions/v/kernel/include/interrupts.h"
typedef struct {
 uint16_t low_offset;
 uint16_t selector;
 uint16_t settings;
 uint16_t high_offset;
} __attribute__ ((packed)) x86_interrupt;

typedef struct {
     uint16_t limit;
     x86_interrupt *base;
} __attribute__ ((packed)) idtr;

typedef struct {
 uint16_t gs;
 uint16_t gs_padding;
 uint16_t fs;
 uint16_t fs_padding;
 uint16_t es;
 uint16_t es_padding;
 uint16_t ds;
 uint16_t ds_padding;

 uint32_t edi;
 uint32_t esi;
 uint32_t ebp;
 uint32_t esp;
 uint32_t ebx;
 uint32_t edx;
 uint32_t ecx;
 uint32_t eax;

 uint32_t _esp;

 uint32_t err;
 uint32_t eip;
 uint16_t cs;
 uint16_t cs_padding;
 uint32_t eflags;
 uint32_t useresp;
 uint32_t ss;
} x86_context;

union x86flags {
 uint32_t all_flags;

 struct {
  uint32_t cf:1;
  uint32_t must_be_1:1;
  uint32_t pf:1;
  uint32_t must_be_0_1:1;
  uint32_t af:1;
  uint32_t must_be_0_2:1;
  uint32_t zf:1;
  uint32_t sf:1;
  uint32_t tf:1;
  uint32_t ifen:1;
  uint32_t df:1;
  uint32_t of:1;
  uint32_t iopl:2;
  uint32_t nt:1;
  uint32_t must_be_0_3:1;
  uint32_t rf:1;
  uint32_t vm:1;
  uint32_t ac:1;
  uint32_t vif:1;
  uint32_t vip:1;
  uint32_t id:1;
  uint32_t must_be_0_4:2;
  uint32_t must_be_0_5:4;
 } eflags_bits;
};

typedef struct {
 uint32_t present:1;
 uint32_t write:1;
 uint32_t user:1;
 uint32_t reserved_write:1;
 uint32_t instruction_fetch:1;
 uint32_t protection_key:1;
 uint32_t shadow_stack:1;
 uint32_t reserved:8;
 uint32_t sgx:1;
 uint32_t reserved2:15;
} __attribute__ ((packed)) page_fault_err;

extern void interrupt_0( void );
extern void interrupt_1( void );
extern void interrupt_2( void );
extern void interrupt_3( void );
extern void interrupt_4( void );
extern void interrupt_5( void );
extern void interrupt_6( void );
extern void interrupt_7( void );
extern void interrupt_8( void );
extern void interrupt_9( void );
extern void interrupt_10( void );
extern void interrupt_11( void );
extern void interrupt_12( void );
extern void interrupt_13( void );
extern void interrupt_14( void );
extern void interrupt_16( void );
extern void interrupt_17( void );
extern void interrupt_18( void );
extern void interrupt_19( void );
extern void interrupt_0x20( void );
extern void interrupt_0x21( void );
extern void interrupt_0x22( void );
extern void interrupt_0x23( void );
extern void interrupt_0x24( void );
extern void interrupt_0x25( void );
extern void interrupt_0x26( void );
extern void interrupt_0x27( void );
extern void interrupt_0x28( void );
extern void interrupt_0x29( void );
extern void interrupt_0x2A( void );
extern void interrupt_0x2B( void );
extern void interrupt_0x2C( void );
extern void interrupt_0x2D( void );
extern void interrupt_0x2E( void );
extern void interrupt_0x2F( void );
extern void interrupt_0x30( void );
extern void interrupt_0x31( void );
extern void interrupt_0x32( void );
extern void interrupt_0x99( void );

void interrupts_initalize( void );
void interrupt_default_handler( unsigned long interrupt_num, unsigned long route_code, x86_context ** _stack );
void load_idtr( void );
void add_interrupt( int number, void (*handler)(), uint32_t dpl );
void load_exceptions();
void remap_pic( int pic1, int pic2 );
void interrupt_mask_irq( uint8_t irq );
void interrupt_unmask_irq( uint8_t irq );
uint32_t get_timer_counter( void );
void replace_stack_on_int_exit( x86_context * stack );
void page_fault_test( void );
extern uint32_t get_cr3( void );
void serial_interrupt_read_from_com2( void );
void serial_interrupt_read_from_com1( void );
# 6 "/usr/local/osdev/versions/v/kernel/include/task.h" 2

# 1 "/usr/local/osdev/versions/v/kernel/include/elf.h" 1
# 51 "/usr/local/osdev/versions/v/kernel/include/elf.h"
typedef struct {
    unsigned char e_ident[16];
    uint16_t e_type;
    uint16_t e_machine;
    uint32_t e_version;
    uint32_t e_entry;
    uint32_t e_phoff;
    uint32_t e_shoff;
    uint32_t e_flags;
    uint16_t e_ehsize;
    uint16_t e_phentsize;
    uint16_t e_phnum;
    uint16_t e_shentsize;
    uint16_t e_shnum;
    uint16_t e_shstrndx;
} Elf32_Ehdr;

typedef struct {
    uint32_t p_type;
    uint32_t p_offset;
    uint32_t p_vaddr;
    uint32_t p_paddr;
    uint32_t p_filesz;
    uint32_t p_memsz;
    uint32_t p_flags;
    uint32_t p_align;
} Elf32_Phdr;

typedef struct {
  uint32_t sh_name;
  uint32_t sh_type;
  uint32_t sh_flags;
  uint32_t sh_addr;
  uint32_t sh_offset;
  uint32_t sh_size;
  uint32_t sh_link;
  uint32_t sh_info;
  uint32_t sh_addralign;
  uint32_t sh_entsize;
} Elf32_Shdr;

typedef struct {
  uint32_t st_name;
  uint32_t st_value;
  uint32_t st_size;
  unsigned char st_info;
  unsigned char st_other;
  uint16_t st_shndx;
} Elf32_Sym;

typedef struct {
    uint32_t r_offset;
    uint32_t r_info;
} Elf32_Rel;

typedef struct {
    uint32_t r_offset;
    uint32_t r_info;
    int32_t r_addend;
} Elf32_Rela;

void elf_initalize( uint32_t kmain );
Elf32_Shdr* elf_find_rel_plt(uint32_t* mem, Elf32_Ehdr* elf_header);
Elf32_Shdr* elf_find_got_plt(uint32_t* mem, Elf32_Ehdr* elf_header);
char* elf_get_section_name(uint32_t* mem, Elf32_Ehdr* elf_header, uint32_t sec_num);
void elf_load_program_headers(Elf32_Ehdr* elf_header, uint8_t* process_space, uint8_t* data);
char* elf_get_sym_name_from_index(uint32_t* mem, Elf32_Ehdr* elf_header, uint32_t index);
uint16_t elf_get_sym_shndx_from_index(uint32_t* mem, Elf32_Ehdr* elf_header, uint32_t index);
Elf32_Shdr * elf_find_sym_strtab(uint32_t* mem, Elf32_Ehdr* elf_header);
Elf32_Shdr * elf_find_dynstr_tab(uint32_t* mem, Elf32_Ehdr* elf_header);
uint16_t elf_get_sym_value_from_index(uint32_t* mem, Elf32_Ehdr* elf_header, uint32_t index);
Elf32_Shdr * elf_find_symtab(uint32_t* mem, Elf32_Ehdr* elf_header);
# 8 "/usr/local/osdev/versions/v/kernel/include/task.h" 2
# 28 "/usr/local/osdev/versions/v/kernel/include/task.h"
typedef struct {
 int32_t id;
 int32_t type;
 char name[25];

 int32_t status;

 x86_context context;
 uint32_t * context_at_interrupt;

 uint32_t * stack;
 uint32_t stack_eip;
 int32_t num_syms;
  Elf32_Sym * sym_table;
 uint8_t * str_table;
 uint8_t * raw_data;
 void * code_start_phys;
 void * data_start_phys;
 void * code_start_virt;
 void * data_start_virt;
 void * virt_heap_top;
 void * stack_base;
 void * entry;

 page_directory_entry * code_page_table;
 page_directory_entry * data_page_table;

 uint32_t start_time;
 uint32_t total_share_time;
 uint32_t share_time_start;
} task;



void task_initalize( void );
int32_t task_add( task *t );
task * switch_next_task( void );
task * get_current_task( void );
int32_t get_current_task_id( void );
void task_set_name( int32_t task_id, char * n );
void task_set_active( int32_t task_id );
void task_set_inactive( int32_t task_id );
void task_set_modhack( int32_t task_id );
task * get_tasks( void );
void task_initalize_and_run( int32_t task_id );
char * task_type_to_string( int32_t type );
char * task_status_to_string( int32_t status );
void task_exit( void );
void task_end_from_wrapper( void );
void set_next_active_task( int32_t task_id );
void set_current_task_id( int32_t task_id );
# 16 "/usr/local/osdev/versions/v/kernel/include/kernel.h" 2
# 1 "/usr/local/osdev/versions/v/kernel/include/modules.h" 1





typedef struct {
 uint32_t task_id;
 uint32_t elf_object_start_addr;
 uint32_t elf_object_size;

 char name[25];

 void *entry;
} kmodule;

void modules_initalize( void );
void load_module( kmodule *mod );
uint32_t load_module_elf_image( uint32_t *raw_data_start );
void run_module_by_name( char * name );
# 17 "/usr/local/osdev/versions/v/kernel/include/kernel.h" 2
# 1 "/usr/local/osdev/versions/v/kernel/include/debug.h" 1





# 1 "/usr/local/osdev/versions/v/kernel/include/terminal.h" 1
# 7 "/usr/local/osdev/versions/v/kernel/include/debug.h" 2




enum level {
    level_info,
    level_warn,
    level_error,
    level_panic
};

enum sys {
    sys_system,
    sys_kernel,
    sys_intel8254,
    sys_memory,
    sys_pci,
    sys_interrupt,
    sys_paging,
    sys_elf
};

static const char * sys_text[] = {
    [sys_system] = "System",
    [sys_kernel] = "Kernel",
    [sys_intel8254] = "Intel8254",
    [sys_memory] = "Memory",
    [sys_pci] = "PCI",
    [sys_interrupt] = "Interrupt",
    [sys_paging] = "Paging",
    [sys_elf] = "ELF"
};

static const char * bit_array[16] = {
    [ 0] = "0000", [ 1] = "0001", [ 2] = "0010", [ 3] = "0011",
    [ 4] = "0100", [ 5] = "0101", [ 6] = "0110", [ 7] = "0111",
    [ 8] = "1000", [ 9] = "1001", [10] = "1010", [11] = "1011",
    [12] = "1100", [13] = "1101", [14] = "1110", [15] = "1111",
};





typedef struct {
 char * name;
 uint32_t addr;
 uint32_t size;
} kdebug_symbol;

typedef struct {
    uint32_t start;
    uint32_t stop;
    uint32_t length;
} profile_information;

typedef struct {
    struct stackframe * ebp;
    uint32_t eip;
} stackframe;

void kdebug_initalize( void );
void kdebug_add_symbol( char * name, uint32_t addr, uint32_t size );
uint32_t kdebug_get_total_symbols( void );
kdebug_symbol * kdebug_get_symbol( char * name );
kdebug_symbol * kdebug_get_symbol_array( void );
uint32_t kdebug_get_symbol_addr( char * name );
char * kdebug_get_function_at( uint32_t addr );
char * kdebug_peek_at( uint32_t addr );
uint32_t reverse_uint32( uint32_t x );
char peek_char( char c );
void profile_test( void );
void profile_test_run( uint32_t num_of_nops );
profile_information * get_profile_information( void );
void profile_stop( void );
void profile_start( void );
void k_log( uint32_t system_id, uint32_t level, char * message, ... );
void kpanic( char * message, ... );
void debugf_stack_trace( void );
void stack_trace_test_func_a( void );
void stack_trace_test_func_b( void );
void stack_trace_test_func_c( void );
void stack_trace_test_func_d( void );
void klog_func( char * func, uint32_t line, char * message, ... );
void klog_variable_func( uint32_t type, char * name, void * var, char * func, uint32_t line );
# 18 "/usr/local/osdev/versions/v/kernel/include/kernel.h" 2

void kernel_main( );
# 2 "kernel/c/memory.c" 2
# 1 "/usr/local/osdev/versions/v/kernel/include/multiboot.h" 1
# 94 "/usr/local/osdev/versions/v/kernel/include/multiboot.h"
typedef unsigned char multiboot_uint8_t;
typedef unsigned short multiboot_uint16_t;
typedef unsigned int multiboot_uint32_t;
typedef unsigned long long multiboot_uint64_t;

struct multiboot_header
{

  multiboot_uint32_t magic;


  multiboot_uint32_t flags;


  multiboot_uint32_t checksum;


  multiboot_uint32_t header_addr;
  multiboot_uint32_t load_addr;
  multiboot_uint32_t load_end_addr;
  multiboot_uint32_t bss_end_addr;
  multiboot_uint32_t entry_addr;


  multiboot_uint32_t mode_type;
  multiboot_uint32_t width;
  multiboot_uint32_t height;
  multiboot_uint32_t depth;
};


struct multiboot_aout_symbol_table
{
  multiboot_uint32_t tabsize;
  multiboot_uint32_t strsize;
  multiboot_uint32_t addr;
  multiboot_uint32_t reserved;
};
typedef struct multiboot_aout_symbol_table multiboot_aout_symbol_table_t;


struct multiboot_elf_section_header_table
{
  multiboot_uint32_t num;
  multiboot_uint32_t size;
  multiboot_uint32_t addr;
  multiboot_uint32_t shndx;
};
typedef struct multiboot_elf_section_header_table multiboot_elf_section_header_table_t;

struct multiboot_info
{

  multiboot_uint32_t flags;


  multiboot_uint32_t mem_lower;
  multiboot_uint32_t mem_upper;


  multiboot_uint32_t boot_device;


  multiboot_uint32_t cmdline;


  multiboot_uint32_t mods_count;
  multiboot_uint32_t mods_addr;

  union
  {
    multiboot_aout_symbol_table_t aout_sym;
    multiboot_elf_section_header_table_t elf_sec;
  } u;


  multiboot_uint32_t mmap_length;
  multiboot_uint32_t mmap_addr;


  multiboot_uint32_t drives_length;
  multiboot_uint32_t drives_addr;


  multiboot_uint32_t config_table;


  multiboot_uint32_t boot_loader_name;


  multiboot_uint32_t apm_table;


  multiboot_uint32_t vbe_control_info;
  multiboot_uint32_t vbe_mode_info;
  multiboot_uint16_t vbe_mode;
  multiboot_uint16_t vbe_interface_seg;
  multiboot_uint16_t vbe_interface_off;
  multiboot_uint16_t vbe_interface_len;

  multiboot_uint64_t framebuffer_addr;
  multiboot_uint32_t framebuffer_pitch;
  multiboot_uint32_t framebuffer_width;
  multiboot_uint32_t framebuffer_height;
  multiboot_uint8_t framebuffer_bpp;



  multiboot_uint8_t framebuffer_type;
  union
  {
    struct
    {
      multiboot_uint32_t framebuffer_palette_addr;
      multiboot_uint16_t framebuffer_palette_num_colors;
    };
    struct
    {
      multiboot_uint8_t framebuffer_red_field_position;
      multiboot_uint8_t framebuffer_red_mask_size;
      multiboot_uint8_t framebuffer_green_field_position;
      multiboot_uint8_t framebuffer_green_mask_size;
      multiboot_uint8_t framebuffer_blue_field_position;
      multiboot_uint8_t framebuffer_blue_mask_size;
    };
  };
};
typedef struct multiboot_info multiboot_info_t;

struct multiboot_color
{
  multiboot_uint8_t red;
  multiboot_uint8_t green;
  multiboot_uint8_t blue;
};

struct multiboot_mmap_entry
{
  multiboot_uint32_t size;
  multiboot_uint32_t addr_low;
  multiboot_uint32_t addr_high;
  multiboot_uint32_t len_low;
  multiboot_uint32_t len_high;







  multiboot_uint32_t type;
} __attribute__((packed));
typedef struct multiboot_mmap_entry multiboot_memory_map_t;

struct multiboot_mod_list
{

  multiboot_uint32_t mod_start;
  multiboot_uint32_t mod_end;


  multiboot_uint32_t cmdline;


  multiboot_uint32_t pad;
};
typedef struct multiboot_mod_list multiboot_module_t;


struct multiboot_apm_info
{
  multiboot_uint16_t version;
  multiboot_uint16_t cseg;
  multiboot_uint32_t offset;
  multiboot_uint16_t cseg_16;
  multiboot_uint16_t dseg;
  multiboot_uint16_t flags;
  multiboot_uint16_t cseg_len;
  multiboot_uint16_t cseg_16_len;
  multiboot_uint16_t dseg_len;
};



void multiboot_initalize( unsigned long _mb_magic, multiboot_info_t *mbh );
multiboot_info_t * get_multiboot_header( void );
void multiboot_echo_to_serial( void );
# 3 "kernel/c/memory.c" 2



extern page_directory_entry * boot_page_directory;
extern page_directory_entry * boot_page_table;
extern uint32_t _kernel_end;
extern void asm_refresh_cr3( void );
extern void asm_invalidate_page( void * p );
extern page_directory_entry * paging_pdpt;
extern page_directory_entry * paging_pd;

static const char * vv_magic_word = "VersionV";
uint32_t * physical_memory_base = (uint32_t *)0xFFFFFFFF;
uint32_t * phsyical_memory_top = (uint32_t *)0xFFFFFFFF;
uint32_t * kernel_virtual_memory_base = (uint32_t *)0xD0000000;
uint32_t * kernel_virtual_memory_top = (uint32_t *)0xD0000000;

page_directory_entry second_page_table[1024] __attribute__ ((aligned (4096)));
page_directory_entry graphics_page_table[1024] __attribute__ ((aligned (4096)));
page_directory_entry another_page_table[1024] __attribute__ ((aligned (4096)));

page_directory_entry process_pd[1024] __attribute__ ((aligned (4096)));
page_directory_entry process_pt[1024] __attribute__ ((aligned (4096)));
# 35 "kernel/c/memory.c"
void memory_initalize( void ) {
 set_debug_output( 
# 36 "kernel/c/memory.c" 3 4
1 
# 36 "kernel/c/memory.c"
); printf_( "[\x1b[0;34;49m%s:%d\x1b[0;00;00m] ", __FUNCTION__, 36 ); printf_( "Enter\n" ); set_debug_output( 
# 36 "kernel/c/memory.c" 3 4
0 
# 36 "kernel/c/memory.c"
);



 paging_level_active = 2;

 uint32_t mem_start = 0;
 uint32_t mem_size = 0;
 uint32_t alloc_start = (uint32_t)&_kernel_end - 0xC0000000;

 multiboot_info_t *mbh = get_multiboot_header();

 memset( (void *)another_page_table, 0, 1024 );
 memset( (void *)graphics_page_table, 0, 1024 );

 klog_variable_func( 1, "paging_level_active" "", &paging_level_active, __FUNCTION__, 51 );
 set_debug_output( 
# 52 "kernel/c/memory.c" 3 4
1 
# 52 "kernel/c/memory.c"
); printf_( "[\x1b[0;34;49m%s:%d\x1b[0;00;00m] ", __FUNCTION__, 52 ); printf_( "Paging level: %d\n", paging_level_active ); set_debug_output( 
# 52 "kernel/c/memory.c" 3 4
0 
# 52 "kernel/c/memory.c"
);
 set_debug_output( 
# 53 "kernel/c/memory.c" 3 4
1 
# 53 "kernel/c/memory.c"
); printf_( "[\x1b[0;34;49m%s:%d\x1b[0;00;00m] ", __FUNCTION__, 53 ); printf_( "Page Size: 0x%08X\n", 0x00200000 ); set_debug_output( 
# 53 "kernel/c/memory.c" 3 4
0 
# 53 "kernel/c/memory.c"
);


 for( int i = 0; i < mbh->mmap_length; i = i + sizeof(multiboot_memory_map_t)) {
        multiboot_memory_map_t* mm = (multiboot_memory_map_t*) (mbh->mmap_addr + i);

        if(mm->type == 1) {

   if( mm->addr_high == 0 ) {

    if( mem_size < mm->len_low ) {
     mem_start = mm->addr_low;
     mem_size = mm->len_low;
    }

    set_debug_output( 
# 68 "kernel/c/memory.c" 3 4
   1 
# 68 "kernel/c/memory.c"
   ); printf_( "[\x1b[0;34;49m%s:%d\x1b[0;00;00m] ", __FUNCTION__, 68 ); printf_( "Start Addr: %x %x | Length: %x %x | Size: %x | Type: %d\n", mm->addr_high, mm->addr_low, mm->len_high, mm->len_low, mm->size, mm->type ); set_debug_output( 
# 68 "kernel/c/memory.c" 3 4
   0 
# 68 "kernel/c/memory.c"
   );
   }
        }
    }






  set_debug_output( 
# 78 "kernel/c/memory.c" 3 4
 1 
# 78 "kernel/c/memory.c"
 ); printf_( "[\x1b[0;34;49m%s:%d\x1b[0;00;00m] ", __FUNCTION__, 78 ); printf_( "alloc start: %08X\n", alloc_start ); set_debug_output( 
# 78 "kernel/c/memory.c" 3 4
 0 
# 78 "kernel/c/memory.c"
 );
  set_debug_output( 
# 79 "kernel/c/memory.c" 3 4
 1 
# 79 "kernel/c/memory.c"
 ); printf_( "[\x1b[0;34;49m%s:%d\x1b[0;00;00m] ", __FUNCTION__, 79 ); printf_( "alloc start mod: %08X\n", alloc_start % 0x200000 ); set_debug_output( 
# 79 "kernel/c/memory.c" 3 4
 0 
# 79 "kernel/c/memory.c"
 );
  set_debug_output( 
# 80 "kernel/c/memory.c" 3 4
 1 
# 80 "kernel/c/memory.c"
 ); printf_( "[\x1b[0;34;49m%s:%d\x1b[0;00;00m] ", __FUNCTION__, 80 ); printf_( "alloc addition: %08X\n", 0x200000 - (alloc_start % 0x200000) ); set_debug_output( 
# 80 "kernel/c/memory.c" 3 4
 0 
# 80 "kernel/c/memory.c"
 );
  alloc_start = alloc_start + 0x200000 - (alloc_start % 0x200000);


 phsyical_memory_top = (uint32_t *)alloc_start;
 physical_memory_base = (uint32_t *)alloc_start;

 set_debug_output( 
# 87 "kernel/c/memory.c" 3 4
1 
# 87 "kernel/c/memory.c"
); printf_( "[\x1b[0;34;49m%s:%d\x1b[0;00;00m] ", __FUNCTION__, 87 ); printf_( "Usable memory detected:    0x%08X\n", mbh->mem_upper * 1024 ); set_debug_output( 
# 87 "kernel/c/memory.c" 3 4
0 
# 87 "kernel/c/memory.c"
);
 set_debug_output( 
# 88 "kernel/c/memory.c" 3 4
1 
# 88 "kernel/c/memory.c"
); printf_( "[\x1b[0;34;49m%s:%d\x1b[0;00;00m] ", __FUNCTION__, 88 ); printf_( "Physical memory base:      0x%08X\n", physical_memory_base ); set_debug_output( 
# 88 "kernel/c/memory.c" 3 4
0 
# 88 "kernel/c/memory.c"
);
 set_debug_output( 
# 89 "kernel/c/memory.c" 3 4
1 
# 89 "kernel/c/memory.c"
); printf_( "[\x1b[0;34;49m%s:%d\x1b[0;00;00m] ", __FUNCTION__, 89 ); printf_( "Virtual memory base:       0x%08X\n", kernel_virtual_memory_base ); set_debug_output( 
# 89 "kernel/c/memory.c" 3 4
0 
# 89 "kernel/c/memory.c"
);
 set_debug_output( 
# 90 "kernel/c/memory.c" 3 4
1 
# 90 "kernel/c/memory.c"
); printf_( "[\x1b[0;34;49m%s:%d\x1b[0;00;00m] ", __FUNCTION__, 90 ); printf_( "Memory allocatable:        0x%08X\n", mem_size ); set_debug_output( 
# 90 "kernel/c/memory.c" 3 4
0 
# 90 "kernel/c/memory.c"
);

 page_allocate( 5 );
# 122 "kernel/c/memory.c"
 void * process_address_space = kmalloc( 0x00200000 );
 process_address_space = (void *)((uint32_t)process_address_space + 0x00200000 - 0x0040);

 memset( &process_pt, 0, 1024 );


# 127 "kernel/c/memory.c"
#pragma GCC diagnostic push
# 127 "kernel/c/memory.c"


# 128 "kernel/c/memory.c"
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
# 128 "kernel/c/memory.c"


  uint64_t * pde = (uint64_t *)&paging_pdpt;
  uint64_t * pte = (uint64_t *)&process_pt;
  *pte = (((uint64_t)process_address_space + (uint64_t)physical_memory_base) - 0xD0000000 + 0x83);







  *pde = ((uint64_t)&process_pt - 0xC0000000) + 0x1;
  *pde = 0x00000000FFFFFFFF & *pde;
  *pte = 0x00000000FFFFFFFF & *pte;




# 146 "kernel/c/memory.c"
#pragma GCC diagnostic pop
# 146 "kernel/c/memory.c"


 asm volatile("invlpg (%0)" ::"r" (pte) : "memory");
 asm_refresh_cr3();

 uint32_t * pmem = (uint32_t *)process_address_space;
 *(pmem + 1) = 0x0666;

 set_debug_output( 
# 154 "kernel/c/memory.c" 3 4
1 
# 154 "kernel/c/memory.c"
); printf_( "[\x1b[0;34;49m%s:%d\x1b[0;00;00m] ", __FUNCTION__, 154 ); printf_( "%X --> %x\n", (pmem + 1), *(pmem + 1 ) ); set_debug_output( 
# 154 "kernel/c/memory.c" 3 4
0 
# 154 "kernel/c/memory.c"
);

 void * zero_addr_space = 0x00000000;
 uint32_t * zerozero = (uint32_t *)zero_addr_space;
 *(zerozero + 2) = 0xBABABABA;

 set_debug_output( 
# 160 "kernel/c/memory.c" 3 4
1 
# 160 "kernel/c/memory.c"
); printf_( "[\x1b[0;34;49m%s:%d\x1b[0;00;00m] ", __FUNCTION__, 160 ); printf_( "00   uint32_t: %08X\n", *(zerozero + 1) ); set_debug_output( 
# 160 "kernel/c/memory.c" 3 4
0 
# 160 "kernel/c/memory.c"
);
 set_debug_output( 
# 161 "kernel/c/memory.c" 3 4
1 
# 161 "kernel/c/memory.c"
); printf_( "[\x1b[0;34;49m%s:%d\x1b[0;00;00m] ", __FUNCTION__, 161 ); printf_( "pmem uint32_t: %08X\n", *(pmem + 1) ); set_debug_output( 
# 161 "kernel/c/memory.c" 3 4
0 
# 161 "kernel/c/memory.c"
);

 if( *(zerozero + 1) != *(pmem + 1) ) {
  kpanic( "0x0 and pmem are not equal!\n" );
 }

 set_debug_output( 
# 167 "kernel/c/memory.c" 3 4
1 
# 167 "kernel/c/memory.c"
); printf_( "[\x1b[0;34;49m%s:%d\x1b[0;00;00m] ", __FUNCTION__, 167 ); printf_( "Exit\n" ); set_debug_output( 
# 167 "kernel/c/memory.c" 3 4
0 
# 167 "kernel/c/memory.c"
);;
}






uint32_t * get_physical_memory_base( void ) {
 return physical_memory_base;
}

uint32_t * get_physical_addr_from_virt( uint32_t * virt ) {
 return (uint32_t *)((uint32_t)physical_memory_base + (uint32_t)virt - 0xD0000000);
}






void set_task_pde( page_directory_entry * pte ) {






 memcpy( &process_pt, pte, sizeof( page_directory_entry ) * 1024 );







 asm_refresh_cr3();
# 222 "kernel/c/memory.c"
}

void dump_active_pt( void ) {

 uint64_t * pde = (uint64_t *)&paging_pdpt;




 for( int i = 0; i < 4; i++, pde++ ) {


  if( *pde & 1<<0 == 1 ) {



    uint64_t pt = (*pde & 0x000FFFFFFFFFF000) + 0xC0000000;





  
# 244 "kernel/c/memory.c"
#pragma GCC diagnostic push
# 244 "kernel/c/memory.c"
  
  
# 245 "kernel/c/memory.c"
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
# 245 "kernel/c/memory.c"
  

    uint64_t *page = (uint64_t *)pt;



  
# 251 "kernel/c/memory.c"
#pragma GCC diagnostic pop
# 251 "kernel/c/memory.c"
  

   for( int j = 0; j < 512; j++, page++ ) {
    if( page == ((void*)0) ) {
     set_debug_output( 
# 255 "kernel/c/memory.c" 3 4
    1 
# 255 "kernel/c/memory.c"
    ); printf_( "[\x1b[0;34;49m%s:%d\x1b[0;00;00m] ", __FUNCTION__, 255 ); printf_( "Error: page is null. i = %d, j - %d\n", i, j ); set_debug_output( 
# 255 "kernel/c/memory.c" 3 4
    0 
# 255 "kernel/c/memory.c"
    );
    }


    uint64_t address = (*page & 0x000FFFFFFFF00000);




    if( *page & 1<<0 == 1 ) {
     set_debug_output( 
# 265 "kernel/c/memory.c" 3 4
    1 
# 265 "kernel/c/memory.c"
    ); printf_( "[\x1b[0;34;49m%s:%d\x1b[0;00;00m] ", __FUNCTION__, 265 ); printf_( "pd[%d].page[%03d] present, virt 0x%08X --> phys mem: 0x%08X\n", i, j, (i * 0x40000000) + (j * 0x00200000), address ); set_debug_output( 
# 265 "kernel/c/memory.c" 3 4
    0 
# 265 "kernel/c/memory.c"
    );
    } else {

    }
   }
  }
 }
}
# 281 "kernel/c/memory.c"
uint32_t * page_map( uint32_t *virt_addr, uint32_t *phys_addr ) {
 uint32_t pt_addr_physical = 0;



 uint32_t pdpt_index = (uint32_t)virt_addr / 0x40000000;
 uint32_t pd_index = ((uint32_t)virt_addr - (pdpt_index * 0x40000000)) / 0x00200000;
 uint64_t *pdpt_uint = ((uint64_t *)&paging_pdpt) + pdpt_index;
 uint64_t *pd_uint = (uint64_t *)&paging_pd + pd_index;



 if( *pdpt_uint & 1<<0 == 0 ) {
  set_debug_output( 
# 294 "kernel/c/memory.c" 3 4
 1 
# 294 "kernel/c/memory.c"
 ); printf_( "[\x1b[0;34;49m%s:%d\x1b[0;00;00m] ", __FUNCTION__, 294 ); printf_( "pdpt is not present.\n" ); set_debug_output( 
# 294 "kernel/c/memory.c" 3 4
 0 
# 294 "kernel/c/memory.c"
 );
  *pdpt_uint | 1<<0;
 } else {
  *pd_uint = (uint32_t)phys_addr | 0x83;
  *pd_uint = 0x00000000FFFFFFFF & *pd_uint;
 }
# 312 "kernel/c/memory.c"
 asm volatile("invlpg (%0)" ::"r" (pd_uint) : "memory");
 asm_refresh_cr3();
# 406 "kernel/c/memory.c"
 return virt_addr;
}

uint32_t * page_allocate( uint32_t num ) {
 uint32_t * return_pointer = kernel_virtual_memory_top;

 for( uint32_t i = 0; i < num; i++ ) {
  page_map( kernel_virtual_memory_top, phsyical_memory_top );
  kernel_virtual_memory_top = (uint32_t *)((uint32_t)kernel_virtual_memory_top + 0x00200000);
  phsyical_memory_top = (uint32_t *)((uint32_t)phsyical_memory_top + 0x00200000);




 }



 return return_pointer;
}



void memory_test( void ) {
 set_debug_output( 
# 430 "kernel/c/memory.c" 3 4
1 
# 430 "kernel/c/memory.c"
); printf_( "[\x1b[0;34;49m%s:%d\x1b[0;00;00m] ", __FUNCTION__, 430 ); printf_( "Enter\n" ); set_debug_output( 
# 430 "kernel/c/memory.c" 3 4
0 
# 430 "kernel/c/memory.c"
);

 void * p2;
 void * p3;
 void * p4;
 void * p5;
# 446 "kernel/c/memory.c"
 p2 = kmalloc( 0x256 );
 set_debug_output( 
# 447 "kernel/c/memory.c" 3 4
1 
# 447 "kernel/c/memory.c"
); printf_( "[\x1b[0;34;49m%s:%d\x1b[0;00;00m] ", __FUNCTION__, 447 ); printf_( "kmalloc(0x256) into p2\n" ); set_debug_output( 
# 447 "kernel/c/memory.c" 3 4
0 
# 447 "kernel/c/memory.c"
);


 set_debug_output( 
# 450 "kernel/c/memory.c" 3 4
1 
# 450 "kernel/c/memory.c"
); printf_( "[\x1b[0;34;49m%s:%d\x1b[0;00;00m] ", __FUNCTION__, 450 ); printf_( "kmalloc(0x512) into p3\n" ); set_debug_output( 
# 450 "kernel/c/memory.c" 3 4
0 
# 450 "kernel/c/memory.c"
);
 p3 = kmalloc( 0x512 );


 set_debug_output( 
# 454 "kernel/c/memory.c" 3 4
1 
# 454 "kernel/c/memory.c"
); printf_( "[\x1b[0;34;49m%s:%d\x1b[0;00;00m] ", __FUNCTION__, 454 ); printf_( "kmalloc(0x11000) into p4\n" ); set_debug_output( 
# 454 "kernel/c/memory.c" 3 4
0 
# 454 "kernel/c/memory.c"
);
 p4 = kmalloc( 0x11000 );


 set_debug_output( 
# 458 "kernel/c/memory.c" 3 4
1 
# 458 "kernel/c/memory.c"
); printf_( "[\x1b[0;34;49m%s:%d\x1b[0;00;00m] ", __FUNCTION__, 458 ); printf_( "kmalloc(0x11000) into p5\n" ); set_debug_output( 
# 458 "kernel/c/memory.c" 3 4
0 
# 458 "kernel/c/memory.c"
);
 p5 = kmalloc( 0x11000 );




 liballoc_dump();

 set_debug_output( 
# 466 "kernel/c/memory.c" 3 4
1 
# 466 "kernel/c/memory.c"
); printf_( "[\x1b[0;34;49m%s:%d\x1b[0;00;00m] ", __FUNCTION__, 466 ); printf_( "Exit\n" ); set_debug_output( 
# 466 "kernel/c/memory.c" 3 4
0 
# 466 "kernel/c/memory.c"
);;
}
