#include <stdio.h>
#include <stdlib.h>


int my_strlen(char* ptr) {
	int index = 0;

	while (ptr[index] != '\0') {
		index ++;
	}
	
	return index;
}

void get_array_int(char* ptr, int* array) {
	int number[10] = {0, 1, 2, 3, 4, 5, 6, 7 ,8 ,9};
	int index = 0;
	int count = 0;
	int index_ptr = 0;

	while (ptr[index_ptr] != '\0') {
		count = 0;
		for (int i = 48; i < 58; i++) {
			if (ptr[index_ptr] == i) {
				array[index] = number[count];
				index += 1;
				break;
			}
			count += 1;
		}
		index_ptr ++;
	}
}

int get_int(int* array_int, int length) {
	int array_numbers[10] = {1, 10, 100, 1000};
    int index_1 = length - 1;
    int number = 0;
	int index = 0;

	while (index < length) {
		number += array_int[index] * array_numbers[index_1];
		index += 1;
		index_1 -= 1;
	}

    return number;
}

int my_atoi(char* ptr) {
    int* array_int = NULL;
    int length = my_strlen(ptr);
	array_int = (int*)malloc(length * sizeof(int));
	get_array_int(ptr, array_int);

	int number = 0;
    if (ptr[0] == '-') {
        length -= 1;
    }
    number = get_int(array_int, length);
    if (ptr[0] == '-') {
        number = -number;
    }

	free(array_int);

	return number;
}
