CC = gcc

all: afs

run: all 
	./afs

afs: afs.c
	$(CC) $< -g -o afs

clean:
	rm afs