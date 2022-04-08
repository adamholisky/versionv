.DEFAULT_GOAL := all

#Support variables
ROOT_DIR = $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
BUILD_LOG = $(ROOT_DIR)/build.log
SHELL :=/bin/bash -O globstar
SOURCES_CPP = $(shell ls cpp/**/*.cpp)
OBJECTS_C = $(patsubst %.cpp, build/%.o, $(shell ls cpp/**/*.cpp | xargs -n 1 basename))

#Compile programs and flags
CC = /usr/bin/g++
DEFINES = -DGRAPHICS_OFF 
CFLAGS = $(DEFINES) -O0 -g -I$(ROOT_DIR)/../kernel/include 
#Support program and flags
OBJDUMP = /usr/local/osdev/bin/i686-elf-objdump

export

all: install

build/vvscript: $(OBJECTS_C)
	$(CC) -o build/vvscript $(CFLAGS) $(OBJECTS_C) 
	objdump -x -d build/vvscript > objdump.txt
	readelf -a build/vvscript > elfdump.txt
	@>&2 printf "[Build] Done\n"

build/%.o: ./cpp/%.cpp
	@>&2 printf "[Build] $<\n"
	$(eval OBJNAME := $(shell basename $@))
	$(CC) $(CFLAGS) -c $< -o build/$(OBJNAME) >> $(BUILD_LOG)

install:
	@>&2 printf "[Build] Staring...\n"
	@make install_stage2 >> $(BUILD_LOG)
	@>&2 printf "[Install] Done\n"

install_stage2: build/vvscript
	@>&2 printf "[Build] Ending...\n"

run: install
	$(ROOT_DIR)/build/vvscript

run_debug: install
	$(ROOT_DIR)/build/vvscript

clean:
	@rm -rf build.log
	@rm -rf build/*.o >> $(BUILD_LOG)
	@rm -rf objdump.txt >> $(BUILD_LOG)
	@rm -rf build/vvscript >> $(BUILD_LOG)
	@>&2 echo [Clean] Done
