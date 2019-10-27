.PHONY: all clean

CFLAGS = -Wall -Wextra -Werror -g -I include

all:lab_03

clean:
	rm -rf obj lab_04

obj:
	mkdir obj

obj/mergesort.o: src/mergesort.c include/mergesort.h |obj
	gcc $(CFLAGS) -c src/mergesort.c -o obj/mergesort.o

obj/main.o: src/main.c include/mergesort.h |obj
	gcc $(CFLAGS) -c src/main.c -o obj/main.o

lab_03: obj/mergesort.o obj/main.o
	gcc obj/mergesort.o obj/main.o -o lab_04
