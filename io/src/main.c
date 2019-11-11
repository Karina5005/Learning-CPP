#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "point_list.h"
#include "clist.h"

#define SECOND_BYTE 256
#define THIRD_BYTE 256 * 256
#define STRING_NUMBER_SIZE 100


static void savetext(intrusive_list* list, char* file_out) {
	FILE *my_file_out = fopen(file_out, "wb");
			if (my_file_out == NULL) {
				printf("file not found\n");
				return;
			} else {
				save_all_points_text(list, my_file_out);
				fclose(my_file_out);
			}
}

static void savebin(intrusive_list* list, char* file_out) {
	FILE *my_file_out = fopen(file_out, "wb");
			if (my_file_out == NULL) {
				printf("file not found\n");
				return;
			} else {
				save_all_points_bin(list, my_file_out);
				fclose(my_file_out);
			}
}

static void add_one(intrusive_node* node, void* data) {
	node = node;
	*(int*)data = *(int*)data + 1;	
}

static int count(intrusive_list* list) {
	int len = 0;
	apply(list, &add_one, &len);
	return len;
}

int main(int argc, char **argv) {
	argc = argc;
	intrusive_list list;
    	intrusive_list* l = &list;
    	init_list(l);

	if (strcmp(argv[1], "loadtext") == 0) {
		FILE *my_file_in = fopen (argv[2], "rb");
		if (my_file_in == NULL) {
			printf("file not found\n");
			return 1;
		} else {
			char arr[STRING_NUMBER_SIZE];
			int x, y;
			while (fgets (arr, STRING_NUMBER_SIZE, my_file_in) != NULL) {
				sscanf(arr, "%d %d\n", &x, &y);
				add_point(l, x, y);
			}
			fclose(my_file_in);
		}
	} else {
		FILE *my_file_in = fopen (argv[2], "rb");
		if (my_file_in == NULL) {
			printf("file not found\n");
			return 1;
		} else {
			unsigned char x[3], y[3];
			fread(x, sizeof(x), 1, my_file_in);
			fread(y, sizeof(y), 1, my_file_in);
			while (!feof(my_file_in)) {
				int addx = (unsigned int)x[0] + (unsigned int)x[1] * SECOND_BYTE + (unsigned int)x[2] * THIRD_BYTE;
				int addy = (unsigned int)y[0] + (unsigned int)y[1] * SECOND_BYTE + (unsigned int)y[2] * THIRD_BYTE;
				add_point(l, addx, addy);
				fread(x, sizeof(x), 1, my_file_in);
				fread(y, sizeof(y), 1, my_file_in);
			}
			fclose(my_file_in);
		}
	}

	if (strcmp(argv[3], "savetext") == 0) {
		savetext(l, argv[4]);
	} 
	if (strcmp(argv[3], "savebin") == 0) {
		savebin(l, argv[4]);
	} 
	if (strcmp(argv[3], "print") == 0) {	
		show_all_points(l, argv[4]);	
	} 
	if (strcmp(argv[3], "count") == 0) {	
		int size = count(l);
		printf("%d\n", size);
	}

	remove_all_points(l);
	return 0;
}
