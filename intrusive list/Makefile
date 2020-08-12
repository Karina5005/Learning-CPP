.PHONY: all clean

CFLAGS = -Wall -Wextra -Werror -g -I include

all:lab_03

clean:
	rm -rf obj lab_03

obj:
	mkdir obj

obj/clist.o: src/clist.c include/clist.h |obj
	gcc $(CFLAGS) -c src/clist.c -o obj/clist.o

obj/main.o: src/main.c include/clist.h |obj
	gcc $(CFLAGS) -c src/main.c -o obj/main.o

lab_03: obj/clist.o obj/main.o
	gcc obj/clist.o obj/main.o -o lab_03
