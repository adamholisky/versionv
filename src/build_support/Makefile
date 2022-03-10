OBJECTS := $(wildcard ../../build/*.o)
APPS := $(wildcard ../test_apps/build_objout/*.bin)

all:
	$(CC) -T linker.ld -o ../../build/versionv.bin $(CFLAGS) ../../../vvlibc/vvlibc.o $(OBJECTS) $(APPS)