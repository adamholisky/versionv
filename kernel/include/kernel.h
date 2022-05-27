#ifndef KERNELHEADER_INCLUDED
#define KERNELHEADER_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <globals.h>
#include <printf.h>
#include <debug.h>
#include <kmalloc.h>
#include <string.h>
#include <memory.h>
#include <bootstrap.h>

typedef uint8_t byte;
typedef uint16_t word;

/* void *operator new(size_t size);
void *operator new[](size_t size);
void operator delete(void *p);
void operator delete[](void *p); */

#ifdef __cplusplus
}
#endif

#endif