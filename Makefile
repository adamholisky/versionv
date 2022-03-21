.DEFAULT_GOAL := all

#Support variables
ROOT_DIR = $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
BUILD_LOG = $(ROOT_DIR)/build.log
SHELL :=/bin/bash -O globstar
SOURCES_C = $(shell ls kernel/**/*.c)
SOURCES_ASM = $(shell ls kernel/**/*.s)
OBJECTS_C = $(patsubst %.c, build/%.o, $(shell ls kernel/**/*.c | xargs -n 1 basename))
OBJECTS_ASM = $(patsubst %.s, build/%.o, $(shell ls kernel/**/*.s | xargs -n 1 basename))
APPS := $(wildcard test_apps/build_objout/*.bin)

#Compile programs and flags
CC = /usr/local/osdev/bin/i686-elf-gcc
CFLAGS = -ffreestanding -fno-omit-frame-pointer -O2 -nostdlib -static-libgcc -lgcc -g -I$(ROOT_DIR)/kernel/include -I$(ROOT_DIR)/libvv/include -I$(ROOT_DIR)/vvlibc/include $(C_OPTS) 
ASM = /usr/local/osdev/bin/i686-elf-as
AFLAGS = $(C_OPTS) -I$(ROOT_DIR)/kernel/include

#Support program and flags
OBJDUMP = /usr/local/osdev/bin/i686-elf-objdump
QEMU = qemu-system-i386 
QEMU_COMMON = 	-drive format=raw,if=ide,file=$(ROOT_DIR)/vv_hd.img \
				-device isa-debug-exit,iobase=0xf4,iosize=0x04 \
				-nic user,ipv6=off,model=e1000,mac=52:54:98:76:54:32 \
				-m 4G
QEMU_DISPLAY_NONE =	-serial file:$(ROOT_DIR)/serial_out.txt \
					-serial stdio \
					-display none
QEMU_DISPLAY_NORMAL = -serial file:$(ROOT_DIR)/serial_out.txt \
					  -serial stdio
QEMU_DEBUG_COMMON = -S -gdb tcp::5894

export

all: install

build/versionv.bin: $(SOURCES_C) $(SOURCES_ASM) $(OBJECTS_C) $(OBJECTS_ASM) $(APPS)
	$(CC) -T kernel/build_support/linker.ld -o build/versionv.bin $(CFLAGS) vvlibc/vvlibc.o $(OBJECTS_C) $(OBJECTS_ASM) $(APPS)
	objdump -x -d build/versionv.bin > objdump.txt
	readelf -a build/versionv.bin > elfdump.txt

build/%.o: kernel/*/%.c
	$(eval OBJNAME := $(shell basename $@))
	$(CC) $(CFLAGS) -c $< -o build/$(OBJNAME)

build/%.o: kernel/*/%.s
	$(eval OBJNAME := $(shell basename $@))
	$(ASM) $(AFLAGS) -c $< -o build/$(OBJNAME)

build_test_apps:
	make -C test_apps genasm
	make -C test_apps all

install: build/versionv.bin
	mount hd_mount_dir
	cp build/versionv.bin -f hd_mount_dir/boot/versionv.bin >> $(BUILD_LOG)
	umount hd_mount_dir

run: install
	$(QEMU) $(QEMU_COMMON) $(QEMU_DISPLAY_NORMAL)

run_debug: install
	$(QEMU) $(QEMU_COMMON) $(QEMU_DISPLAY_NORMAL) $(QEMU_DEBUG_COMMON)

run_ng: install
	$(QEMU) $(QEMU_COMMON) $(QEMU_DISPLAY_NONE) && echo "Exit Code: $$?" || echo "Exit Code: $$?"

run_ng_debug: install
	$(QEMU) $(QEMU_COMMON) $(QEMU_DISPLAY_NONE) $(QEMU_DEBUG_COMMON)

clean:
	rm -rf build.log
	rm -rf build/*.o
	rm -rf build/*.bin 
	rm -rf objdump.txt
	rm -rf versionv.iso
	make -C test_apps clean
