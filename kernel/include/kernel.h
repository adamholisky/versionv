#ifndef KERNELHEADER_INCLUDED
#define KERNELHEADER_INCLUDED

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "bootstrap.h"
#include <string.h>
#include "terminal.h"
#include <printf.h>
#include "serial.h"
#include "memory.h"
#include "kmalloc.h"
#include "task.h"
#include "modules.h"
#include "debug.h"

void kernel_main( );

#endif