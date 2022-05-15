#ifndef KERNELHEADER_INCLUDED
#define KERNELHEADER_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <globals.h>
#include "bootstrap.h"
#include <string.h>
#include "terminal.h"
#include <printf.h>
#include "serial.h"
#include "memory.h"
#include "kmalloc.h"
#include "task.h"
#include "modules_bootstrap.h"
#include "debug.h"

void kernel_main( );

#ifdef __cplusplus
}
#endif

#endif