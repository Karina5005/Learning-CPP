#include <assert.h>
#include <string.h>
#include "str.h"
#include "test_str.h"

void test_strlen() {
	char t1[100] = "good";
	assert(my_strlen(t1) == strlen(t1));
	
	char t2[100] = "";
	assert(my_strlen(t2) == strlen(t2));

	char t3[100] = "00";
	assert(my_strlen(t3) == strlen(t3));

	char t4[100] = "gOoD";
	assert(my_strlen(t4) == strlen(t4));

	char t5[100] = "t0e7s0t8";
	assert(my_strlen(t5) == strlen(t5));
}

void test_strcpy() {
	char t1_1[100] = "";
	char t1_2[100] = "good";
	assert(my_strcpy(t1_1, t1_2) == strcpy(t1_1, t1_2));

	char t2_1[100] = "notgood";
	char t2_2[100] = "good";
	assert(my_strcpy(t2_1, t2_2) == strcpy(t2_1, t2_2));

	char t3_1[100] = "notgood";
	char t3_2[100] = "";
	assert(my_strcpy(t3_1, t3_2) == strcpy(t3_1, t3_2));

	char t4_1[100] = "00";
	char t4_2[100] = "good";
	assert(my_strcpy(t4_1, t4_2) == strcpy(t4_1, t4_2));

	char t5_1[100] = "good";
	char t5_2[100]= "g00d";
	assert(my_strcpy(t5_1, t5_2) == strcpy(t5_1, t5_2));
}

void test_strcmp() {
	char t1_1[100] = "";
	char t1_2[100] = "good";
	assert(my_strcmp(t1_1, t1_2) < 0);

	char t2_1[100] = "notgood";
	char t2_2[100] = "good";
	assert(my_strcmp(t2_1, t2_2) > 0);

	char t3_1[100] = "notgood";
	char t3_2[100] = "";
	assert(my_strcmp(t3_1, t3_2) > 0);

	char t4_1[100] = "00";
	char t4_2[100] = "good";
	assert(my_strcmp(t4_1, t4_2) < 0);

	char t5_1[100] = "good";
	char t5_2[100] = "good";
	assert(my_strcmp(t5_1, t5_2) == 0);
}

void test_strcat() {
	char t1_1[100] = "";
	char t1_2[100] = "good";
	assert(my_strcat(t1_1, t1_2) == strcat(t1_1, t1_2));

	char t2_1[100]= "notgood";
	char t2_2[100] = "good";
	assert(my_strcat(t2_1, t2_2) == strcat(t2_1, t2_2));

	char t3_1[100] = "notgood";
	char t3_2[100] = "";
	assert(my_strcat(t3_1, t3_2) == strcat(t3_1, t3_2));

	char t4_1[100] = "00";
	char t4_2[100] = "good";
	assert(my_strcat(t4_1, t4_2) == strcat(t4_1, t4_2));

	char t5_1[100] = "good";
	char t5_2[100] = "g00d";
	assert(my_strcat(t5_1, t5_2) == strcat(t5_1, t5_2));
}
