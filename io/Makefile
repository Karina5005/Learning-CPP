.PHONY: all clean 

CFLAGS = -Wall -Wextra -g -I include -Werror

all:lab_05

clean:
	rm -rf obj lab_05

obj:
	mkdir obj

obj/clist.o: src/clist.c include/clist.h |obj
	gcc $(CFLAGS) -c src/clist.c -o obj/clist.o

obj/point_list.o: src/point_list.c include/point_list.h include/clist.h |obj
	gcc $(CFLAGS) -c src/point_list.c -o obj/point_list.o

obj/main.o: src/main.c include/clist.h include/point_list.h |obj
	gcc $(CFLAGS) -c src/main.c -o obj/main.o

lab_05: obj/clist.o obj/main.o obj/point_list.o
	gcc obj/clist.o obj/point_list.o obj/main.o -o lab_05
