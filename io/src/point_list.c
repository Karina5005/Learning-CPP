#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "point_list.h"
 
#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))
#define FIRST_BYTE 256
#define SECOND_BYTE (256 * 256)) / 256
#define THIRD_BYTE (256*256*256)) / (256 * 256)

point_node *get_point(intrusive_node *node) {
	return container_of(node, point_node, node);
}

int match_point(intrusive_node *node, int x, int y) {
	point_node *pnode = get_point(node);
	return pnode->x == x && pnode->y == y;
}

void delete_point(intrusive_node *node) {
	remove_node(node);
	free(get_point(node));
}

void print_point(intrusive_node *node, void* str_out) {
	point_node *pnode = get_point(node);
	printf(str_out, pnode->x, pnode->y);
}

void save_point_text(intrusive_node *node, void* str_out) {
	point_node *pnode = get_point(node);
	fprintf(str_out, "%d %d\n", pnode->x, pnode->y);
}

void save_point_bin(intrusive_node *node, void* str_out) {
	point_node *pnode = get_point(node);
	unsigned char x[3] = {pnode->x % FIRST_BYTE, (pnode->x % SECOND_BYTE, (pnode->x % THIRD_BYTE};
	fwrite(x, sizeof(x), 1, str_out);
	unsigned char y[3] = {pnode->y % FIRST_BYTE, (pnode->y % SECOND_BYTE, (pnode->y % THIRD_BYTE};
	fwrite(y, sizeof(y), 1, str_out);
}

void remove_point(intrusive_list *list, int x, int y) {
	intrusive_node *head = &list->head;
	intrusive_node *node = head->next;

	while (node != head) {
		intrusive_node *next = node->next;

		if (match_point(node, x, y))
			delete_point(node);

		node = next;
    }
}

void add_point(intrusive_list *list, int x, int y) {
	point_node *pnode = malloc(sizeof(point_node));
	pnode->x = x;
	pnode->y = y;

	add_node(list, &pnode->node);
}

void show_all_points(intrusive_list *list, void* str_out) {
	apply(list, print_point, str_out);

	printf("\n");
}

void save_all_points_text(intrusive_list *list, void* str_out) {
	apply(list, save_point_text, str_out);
}

void save_all_points_bin(intrusive_list *list, void* str_out) {
	apply(list, save_point_bin, str_out);
}

void remove_all_points(intrusive_list *list) {
	while (list->head.next != &list->head)
		delete_point(list->head.next);
}

