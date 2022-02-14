SOURCES := $(wildcard *.s)
OBJECTS := $(patsubst %.s, ../../build/%.o, $(SOURCES))

all: $(OBJECTS)

../../build/%.o : %.s
	$(ASM) $(AFLAGS) $< -g -o $@