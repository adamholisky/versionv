.DEFAULT_GOAL := all

#Support variables
ROOT_DIR = $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
BUILD_LOG = $(ROOT_DIR)/build.log

#Compile programs and flags
CC = gcc
CFLAGS = -fno-omit-frame-pointer -O2 -static-libgcc -lgcc -g -I$(ROOT_DIR)/include -I$(ROOT_DIR)/build_support $(C_OPTS) 
ASM = /usr/local/osdev/bin/i686-elf-as
ALAGS = $(C_OPTS) -I$(ROOT_DIR)/include -I$(ROOT_DIR)/build_support

#Support program and flags
OBJDUMP = /usr/local/osdev/bin/i686-elf-objdump

export

all: vv_lib_test

vv_lib_test:
	$(MAKE) -C src >> $(BUILD_LOG)
	$(MAKE) -C build_support >> $(BUILD_LOG)
	@objdump -x -d vv_lib_test > objdump.txt

run: vv_lib_test
	@echo "Runing vv_lib_test...\n--------------------------\n"
	@$(ROOT_DIR)/vv_lib_test

clean:
	rm -rf build.log
	rm -rf build/*.o 
	rm -rf objdump.txt
	rm -rf vv_lib_test

# TODO:  objcopy --input binary --output elf32-i386 --binary i386 magic.txt magic_txt.o