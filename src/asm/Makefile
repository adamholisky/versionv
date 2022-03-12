SOURCES := $(wildcard *.s)
SOURCES2 := $(wildcard *.S)
OBJECTS := $(patsubst %.s, ../../build/%.o, $(SOURCES))
OBJECTS2 := $(patsubst %.S, ../../build/%.o, $(SOURCES2))

all: $(OBJECTS) $(OBJECTS2)

../../build/%.o : %.s
	$(ASM) $(AFLAGS) $< -g -o $@

../../build/%.o : %.S
	$(ASM) $(AFLAGS) $< -g -o $@