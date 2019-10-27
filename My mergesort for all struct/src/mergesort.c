#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "mergesort.h"

static void my_memcpy(char* dest, const char* arr, size_t elements, size_t size_element) {
	for (unsigned int i = 0; i < size_element*elements; i++) {
		*((char*)(dest + i)) = *((char*)(arr + i));
	}
}

void mergesort(void *array, size_t elements, size_t element_size, int (*comparator)(const void*, const void*)) {
	if (elements == 1) return;

	unsigned int size_half_elements1 = element_size * (elements / 2);
	unsigned int size_half_elements2 = element_size * (elements - elements / 2);

	void* left = malloc(size_half_elements1);
	assert(left != NULL);
	void* right = malloc(size_half_elements2);
	assert(right != NULL);

	my_memcpy(left, ((char*)array), elements / 2, element_size);
	my_memcpy(right, ((char*)array + size_half_elements1), (elements - elements / 2), element_size);

	mergesort(left, elements / 2, element_size, comparator);
	mergesort(right, elements - elements / 2, element_size, comparator);

	unsigned int i = 0;
	unsigned int j = 0;
	while(i < size_half_elements1  || j < size_half_elements2) {
		if ((i < size_half_elements1) && (j < size_half_elements2)) {
			if (comparator((char*)left + i, (char*)right + j) >= 0) {
				my_memcpy(array + i + j, right + j, 1, element_size);
				j += element_size;
			} else {
				my_memcpy(array + i + j, left + i, 1, element_size);
				i += element_size;
			}
		} else if (i < size_half_elements1 ) {
			my_memcpy(array + i + j, left + i, 1, element_size);
			i += element_size;
		} else {
			my_memcpy(array + i + j, right + j, 1, element_size);
			j += element_size;
		}
			
	}
	free(left);
	free(right);
}


