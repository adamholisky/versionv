#if !defined(ELF_INCLUDED)
#define ELF_INCLUDED
#include <stdint.h>

typedef struct {
  uint32_t	sh_name;
  uint32_t	sh_type;
  uint32_t	sh_flags;
  uint32_t	sh_addr;
  uint32_t	sh_offset;
  uint32_t	sh_size;
  uint32_t	sh_link;
  uint32_t	sh_info;
  uint32_t	sh_addralign;
  uint32_t	sh_entsize;
} elf32_section_header;

typedef struct {
  uint32_t	st_name;
  uint32_t	st_value;
  uint32_t	st_size;
  unsigned char	st_info;
  unsigned char	st_other;
  uint16_t	st_shndx;
} elf32_sym;

#define SHT_NULL 0
#define SHT_PROGBITS 1
#define SHT_SYMTAB 2
#define SHT_STRTAB 3

#define STT_NOTYPE 0
#define STT_OBJECT 1
#define STT_FUNC   2

#define ELF32_ST_BIND(INFO)	((INFO) >> 4)
#define ELF32_ST_TYPE(INFO)	((INFO) & 0x0F)

void elf_initalize( uint32_t kmain );

#endif