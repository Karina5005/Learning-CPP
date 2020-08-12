#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "clist.h"

#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

struct point {
  int x, y;
  struct intrusive_node node;
};

void add_point(struct intrusive_list *list, int x, int y) {
	struct point *new_point = malloc(sizeof(struct point));
	new_point->node.next = new_point->node.prev = NULL;
	new_point->x = x;
	new_point->y = y;
	add_node(list, (struct intrusive_node*)(&new_point->node));
}

void remove_point(struct intrusive_list *list, int x, int y) { 
	struct intrusive_node *last = list->head.next;
	while (last != &list->head) {
		struct point *now = container_of(last, struct point, node);
		if (now->x == x && now->y == y) {
			last = last->prev;
			remove_node(last->next);
			free(now);
		}
		last = last->next;
	}
}

void show_all_points(struct intrusive_list *list) {
	struct intrusive_node *last = list->head.next;
	while (last != &list->head) {
		struct point *now = container_of(last, struct point, node);
		printf("(%d %d) ", now->x, now->y);
		last = last->next;
	}
	printf("\n");
}

void remove_all_points(struct intrusive_list *list) {
	struct intrusive_node *last = list->head.next;
	while (last != &list->head) {
		struct point *now = container_of(last, struct point, node);
		last = last->next;
		remove_node(last->prev);
		free(now);
	}
}

int main() {
	struct intrusive_list list;
	init_list(&list);
  	char command[100];
	int x, y;
	while (1) {
		fgets(command, 100, stdin);
		if (sscanf(command, "add %d %d\n", &x, &y)) {
			add_point(&list, x, y);
		} else if (sscanf(command, "rm %d %d", &x, &y)) {
			remove_point(&list, x, y);
		} else if (strcmp(command, "rma\n") == 0) {
			remove_all_points(&list);
		} else if (strcmp(command, "print\n") == 0) {
			show_all_points(&list);
		} else if (strcmp(command, "len\n") == 0) {
			int ans = get_length(&list);
			printf("%d\n", ans);
		} else if (strcmp(command, "exit\n") == 0) {
			break;
		} else {
			printf("Unknown command\n");
		}
	}
	remove_all_points(&list);
	return 0;
}
