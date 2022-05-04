.DEFAULT_GOAL := all

#Support variables
ROOT_DIR = $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
BUILD_LOG = $(ROOT_DIR)/build.log
SHELL :=/bin/bash -O globstar
SOURCES_C = $(shell ls kernel/**/*.c)
SOURCES_ASM = $(shell ls kernel/**/*.s)
SOURCES_ASMS = $(shell ls kernel/**/*.S)
OBJECTS_C = $(patsubst %.c, build/%.o, $(shell ls kernel/**/*.c | xargs -n 1 basename))
OBJECTS_ASM = $(patsubst %.s, build/%.o, $(shell ls kernel/**/*.s | xargs -n 1 basename))
OBJECTS_ASMS = $(patsubst %.S, build/%.o, $(shell ls kernel/**/*.S | xargs -n 1 basename))
OBJECTS_APPS = $(patsubst %.c, test_apps/build_objout/%.bin, $(shell ls test_apps/*.c | xargs -n 1 basename))
APPS := $(wildcard test_apps/*.c)


#Compile programs and flags
CC = /usr/local/osdev/bin/i686-elf-gcc
DEFINES = -DPAGING_PAE \
		  -DGRAPHICS_ON \
		  -DBITS_32 \
		  #-DDF_COM4_ONLY
CFLAGS = $(DEFINES) -ffreestanding -fno-omit-frame-pointer -O0 -nostdlib -static-libgcc -lgcc -g -I$(ROOT_DIR)/kernel/include -I$(ROOT_DIR)/libvv/include -I$(ROOT_DIR)/libcvv/include -save-temps -dumpdir $(ROOT_DIR)/build_output_2/ -fdump-earlydebug
ASM = /usr/local/osdev/bin/i686-elf-as
AFLAGS = $(CFLAGS) -I$(ROOT_DIR)/kernel/include -I$(ROOT_DIR)/libvv/include -I$(ROOT_DIR)/libcvv/include

#Support program and flags
OBJDUMP = /usr/local/osdev/bin/i686-elf-objdump
QEMU = qemu-system-i386 
QEMU_COMMON = 	-drive format=raw,if=ide,file=$(ROOT_DIR)/vv_hd.img \
				-device isa-debug-exit,iobase=0xf4,iosize=0x04 \
				-nic user,ipv6=off,model=e1000,mac=52:54:98:76:54:32 \
				-m 4G \
				-serial tcp:192.168.0.100:10100,nodelay=on,reconnect=1 \
				-serial stdio \
				-serial null \
				-serial file:$(ROOT_DIR)/serial_out.txt \
				-no-reboot
QEMU_DISPLAY_NONE =	-display none
QEMU_DISPLAY_NORMAL = -vga std
QEMU_DEBUG_COMMON = -S -gdb tcp::5894 
QEMU_DEBUG_LOGGING = -D $(ROOT_DIR)/qemu_debug_log.txt -d int,cpu_reset 

export

all: install

build/versionv.bin: build_test_apps $(SOURCES_C) $(SOURCES_ASM) $(SOURCES_ASMS) $(OBJECTS_C) $(OBJECTS_ASM) $(OBJECTS_ASMS) $(APPS)
	$(CC) -T kernel/build_support/linker.ld -o build/versionv.bin $(CFLAGS) libcvv/vvlibc.o $(OBJECTS_C) $(OBJECTS_ASM) $(OBJECTS_ASMS) $(OBJECTS_APPS)
	objdump -x -D -S build/versionv.bin > objdump.txt
	readelf -a build/versionv.bin > elfdump.txt
	@>&2 printf "[Build] Done\n"

build/%.o: kernel/*/%.c
	@>&2 printf "[Build] $<\n"
	$(eval OBJNAME := $(shell basename $@))
	$(CC) $(CFLAGS) -c $< -o build/$(OBJNAME) >> $(BUILD_LOG)

build/%.o: kernel/*/%.s
	@>&2 printf "[Build] $<\n"
	$(eval OBJNAME := $(shell basename $@))
	$(ASM) -c $< -o build/$(OBJNAME) >> $(BUILD_LOG)

build/%.o: kernel/*/%.S
	@>&2 printf "[Build] $<\n"
	$(eval OBJNAME := $(shell basename $@))
	$(CC) $(AFLAGS) -c $< -o build/$(OBJNAME) >> $(BUILD_LOG)

build_test_apps:
	@>&2 echo [Build] Test apps
	make -C test_apps >> $(BUILD_LOG) 

install:
	@make install_stage2 >> $(BUILD_LOG)
	@>&2 printf "[Install] Done\n"

install_stage2: build/versionv.bin
	@>&2 echo [Install] Installing to vv_hd.img
	mount hd_mount_dir >> $(BUILD_LOG)
	cp build/versionv.bin -f hd_mount_dir/boot/versionv.bin >> $(BUILD_LOG)
	umount hd_mount_dir >> $(BUILD_LOG)

run: install
	$(QEMU) $(QEMU_COMMON) $(QEMU_DISPLAY_NORMAL)

run_debug: install
	$(QEMU) $(QEMU_COMMON) $(QEMU_DISPLAY_NORMAL) $(QEMU_DEBUG_COMMON)

run_ng: install
	$(QEMU) $(QEMU_COMMON) $(QEMU_DISPLAY_NONE) && echo "Exit Code: $$?" || echo "Exit Code: $$?"

run_ng_debug: install
	$(QEMU) $(QEMU_COMMON) $(QEMU_DISPLAY_NONE) $(QEMU_DEBUG_COMMON)

clean:
	@rm -rf build.log
	@rm -rf build/*.o >> $(BUILD_LOG)
	@rm -rf build/*.bin >> $(BUILD_LOG)
	@rm -rf objdump.txt >> $(BUILD_LOG)
	@rm -rf versionv.iso >> $(BUILD_LOG)
	@make -C test_apps clean >> $(BUILD_LOG)
	@>&2 echo [Clean] Done
