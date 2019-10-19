#include <stddef.h>
#include "str.h"

size_t my_strlen(const char *s) {
	size_t n = 0;
	for (; *s != '\0'; ++s) {
		++n;
	}
	return n;
}

char *my_strcpy(char *dest, const char *src) {
	char *ans = dest;
	while (*src != '\0') {
		*dest = *src;
		++dest;
		++src;
	}
	*dest = '\0';
	return ans;	
}

int my_strcmp(const char * s1, const char * s2) {
	while (*s1 != '\0' && *s2 != '\0') {
		if(*s1 != *s2) {
			return ((int)(*s1 - *s2));
		}
		++s1;
		++s2;
	}

	if(*s1 == '\0' && *s2 == '\0') {
	return 0;
	}
	else if (*s1 != '\0') {
		return 1;
	} else {
		return -1;
	}
}

char *my_strcat(char *s1, const char *s2) {
	char *dest = s1 + my_strlen(s1);
	while (*s2 != '\0') {
		*dest = *s2;
		dest++;
		s2++;
	}
	*dest = '\0';
	return s1;	
}
