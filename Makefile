.DEFAULT_GOAL := all

#Support variables
ROOT_DIR = $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
BUILD_LOG = $(ROOT_DIR)/build.log

#Compile programs and flags
CC = /usr/local/osdev/bin/i686-elf-gcc
CFLAGS = -ffreestanding -fno-omit-frame-pointer -O2 -nostdlib -static-libgcc -lgcc -g -I$(ROOT_DIR)/src/include -I$(ROOT_DIR)/src/libvv/include $(C_OPTS) 
ASM = /usr/local/osdev/bin/i686-elf-as
ALAGS = $(C_OPTS) -I$(ROOT_DIR)/src/include

#Support program and flags
OBJDUMP = /usr/local/osdev/bin/i686-elf-objdump
QEMU = qemu-system-i386 
QEMU_COMMON = 	-drive format=raw,if=ide,file=$(ROOT_DIR)/vv_hd.img \
				-device isa-debug-exit,iobase=0xf4,iosize=0x04 \
				-nic user,ipv6=off,model=e1000,mac=52:54:98:76:54:32 \
				-m 4G
QEMU_DISPLAY_NONE =	-serial stdio \
					-serial file:$(ROOT_DIR)/serial_out.txt \
					-display none
QEMU_DISPLAY_NORMAL = -serial file:$(ROOT_DIR)/serial_out.txt
QEMU_DEBUG_COMMON = -S -gdb tcp::5894

export

all: install
	rm build/versionv.bin

build/versionv.bin:
	$(MAKE) -C src
	objdump -x -d build/versionv.bin > objdump.txt
	readelf -a build/versionv.bin > elfdump.txt

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

# TODO:  objcopy --input binary --output elf32-i386 --binary i386 magic.txt magic_txt.o