#include <stdlib.h>
#include "clist.h"

void init_list(struct intrusive_list* list) {
	list->head.next = &list->head;
	list->head.prev = &list->head;
}

void add_node(struct intrusive_list *list, struct intrusive_node *new_node) {
	new_node->next = list->head.next;	
	list->head.next = new_node;
	new_node->prev = &list->head;
	new_node->next->prev = new_node;
}

void remove_node(struct intrusive_node *del_node) {
	del_node->next->prev = del_node->prev;
	del_node->prev->next = del_node->next;
}

int get_length(struct intrusive_list *list) {
	int size = 0;
	struct intrusive_node *last = list->head.next;
	while (last != &list->head) {
		size++;
		last = last->next;
	}
	return size;
}
