#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "mergesort.h"

int comparator_char(const void* a, const void* b) {
	return *((char*)a) - *((char*)b);
}

int comparator_int(const void* a, const void* b) {
	return *((int*)a) - *((int*)b);
}

int comparator_str(const void* a, const void* b) {
	char* c = *(char**)a;
	char* d = *(char**)b;
	return strcmp((char*)c, (char*)d);
}

int main(int argc, char **argv) {
	if (strcmp(argv[1], "char") == 0) {
		if ((argc - 2) <= 0) return 0;
		char* array = malloc(sizeof(char) * (argc - 2));
		assert(array != NULL);
		for (int i = 0; i < argc - 2; i++) {
			array[i] = argv[i + 2][0];
		}
		mergesort(array, (argc - 2), sizeof(char), &comparator_char);
		for (int i = 0; i < argc - 2; i++) {
			printf("%c ", array[i]);
		}
		free(array);
	} else if (strcmp(argv[1], "int") == 0) {
		if ((argc - 2) <= 0) return 0;
		int* array = malloc(sizeof(int) * (argc - 2));
		assert(array != NULL);
		for (int i = 0; i < argc - 2; i++) {
			array[i] = atoi(argv[i + 2]);
		}
		mergesort(array, (argc - 2), sizeof(int), &comparator_int);
		for (int i = 0; i < argc - 2; i++) {
			printf("%d ", array[i]);
		}
		free(array);
	} else if (strcmp(argv[1], "str") == 0) {
		if ((argc - 2) <= 0) return 0;
		char** array = malloc(sizeof(char*) * (argc - 2));
		assert(array != NULL);
		for (int i = 0; i < argc - 2; i++) {
			array[i] = malloc(sizeof(char) * (strlen(argv[i + 2]) + 1));
			assert(array[i] != NULL);
			strcpy(array[i], argv[i + 2]);
		}
		mergesort(array, (argc - 2), sizeof(char*), &comparator_str);
		for (int i = 0; i < argc - 2; i++) {
			printf("%s ", array[i]);
			free(array[i]);
		}
		free(array);
	}
	return 0;
}
