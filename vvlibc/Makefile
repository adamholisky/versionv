.DEFAULT_GOAL := all

#Support variables
ROOT_DIR = $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
BUILD_LOG = $(ROOT_DIR)/build.log
SOURCES_C = $(shell ls src/**/*.c)
#SOURCES_ASM = $(shell ls src/**/*.s)
OBJECTS = $(patsubst %.c, build/%.o, $(shell ls src/**/*.c | xargs -n 1 basename))

#Compile programs and flags
CC = /usr/local/osdev/bin/i686-elf-gcc
CFLAGS = -ffreestanding -fno-omit-frame-pointer -O2 -nostdlib -static-libgcc -lgcc -g -I$(ROOT_DIR)/include $(C_OPTS) 
LD = /usr/local/osdev/bin/i686-elf-ld
ASM = /usr/local/osdev/bin/i686-elf-as
ALAGS = $(C_OPTS) -I$(ROOT_DIR)/src/include

#Support program and flags
OBJDUMP = /usr/local/osdev/bin/i686-elf-objdump

export

all: build/vvlibc.o

build/vvlibc.o: $(OBJECTS)
	@echo $(SOURCES_C)

	$(LD) -g -I$(ROOT_DIR)/include -nostdlib -r $(OBJECTS) -o vvlibc.o
	objdump -x -d vvlibc.o > vvlibc_objdump.txt

build/%.o: src/*/%.c
	$(eval OBJNAME := $(shell basename $@))
	$(CC) $(CFLAGS) -c $< -o build/$(OBJNAME)


install: build/vvlibc.o
  	#cp build/versionv.bin -f hd_mount_dir/boot/versionv.bin >> $(BUILD_LOG)

clean:
	rm -rf vvlibc.o
	rm -rf build.log
	rm -rf build/*.o
	rm -rf build/*.bin 
	rm -rf vvlibc_objdump.txt

# TODO:  objcopy --input binary --output elf32-i386 --binary i386 magic.txt magic_txt.o