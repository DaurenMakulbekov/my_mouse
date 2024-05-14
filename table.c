#include <stdio.h>
#include "my_mouse.h"
#include <unistd.h>
#include <stdlib.h>


void my_read(int fd, char* array) {
	int sz = read(fd, array, 511);
	array[sz] = '\0';
}

void create_table(Table* table, char* line, char* col) {
	table->line = my_atoi(line);
	table->col = my_atoi(col);
	table->array = (char**)malloc((table->line + 1) * sizeof(char*));

	for (int i = 0; i < table->line + 1; i++) {
		table->array[i] = (char*)malloc((table->col + 1) * sizeof(char));
	}

	//printf("Table created\n");
}

Array* create_array() {
	Array* array = (Array*)malloc(sizeof(Array));
	array->array = (char*)malloc(512 * sizeof(char));
	array->line = (char*)malloc(10 * sizeof(char));
	array->col = (char*)malloc(10 * sizeof(char));

	//printf("Array created\n");

	return array;
}

void print_table(Table* table) {
	for (int i = 0; i < table->line + 1; i++) {
		printf("%s\n", table->array[i]);
	}
}

void get_line(char* array, char* line, int* index) {
	int index_1 = 0;

	while (array[*index] >= '0' && array[*index] <= '9') {
		line[index_1] = array[*index];
		(*index) ++;
		index_1 ++;
	}
	line[index_1] = '\0';
}

void get_col(char* array, char* col, int* index) {
	int index_1 = 0;
	
	while (array[*index] >= '0' && array[*index] <= '9') {
		col[index_1] = array[*index];
		(*index) ++;
		index_1 ++;
	}
	col[index_1] = '\0';
}

void get_parameters(Table* table, char* array, char* line, char* col) {
	int index = 0;

	while (array[index] != '\n') {
		get_line(array, line, &index);
		index ++;
		get_col(array, col, &index);
		table->full = array[index];
		index ++;
		table->empty = array[index];
		index ++;
		table->path = array[index];
		index ++;
		table->enter = array[index];
		index ++;
		table->exit = array[index];
		index ++;
	}
}

void get_entry(Table* table, char* ptr, int* entry) {
	int index = 0;

	while (ptr[index] != '\0') {
		if (ptr[index] == table->enter) {
			*entry = index;
			break;
		}
		index ++;
	}
}

void get_exit(Table* table, char* ptr, int* exit) {
	int index = 0;

	while (ptr[index] != '\0') {
		if (ptr[index] == table->exit) {
			*exit = index;
			break;
		}
		index ++;
	}
}

int my_strcpy_char(Table* table, char* table_array, int line, char* array, int index, int index_1, int* count) {
	int ptr = 0;

	if (line == 0) {
		table_array[index_1] = array[index];
	}
	else if (array[index] == table->full || array[index] == table->empty) {
		table_array[index_1] = array[index];
	}
	else if ((array[index] == table->enter || array[index] == table->exit)) {
		table_array[index_1] = array[index];
		(*count) ++;
		if (*count > 2) {
			ptr = 1;
		}
	}
	else if (array[index] != table->full || array[index] != table->empty || array[index] != table->enter || array[index] != table->exit) {
		ptr = 1;
	}

	return ptr;
}

void check_col_size(Table* table, char* array, int line, int index_1, int* ptr) { 
	if (index_1 > table->col) {
		*ptr = 1;
	}
	else if (line > 0 && (array[0] != '\0' || array[0] != '\n') && index_1 < table->col) {
		*ptr = 1;
	}
}

int my_strcpy_line(int fd, Table* table, char* table_array, int line, char* array, int* index, int* count) {
	int index_1 = 0;
	int ptr = 0;

	while (array[*index] != '\n') {
		if (array[*index] == '\0') {
			my_read(fd, array);
			*index = 0;
			if (array[0] == '\0' || array[0] == '\n') {
				break;
			}
		}
		ptr = my_strcpy_char(table, table_array, line, array, *index, index_1, count);
		if (ptr == 1) {
			break;
		}
		(*index) ++;
		index_1 ++;
	}
	table_array[index_1] = '\0';
	check_col_size(table, array, line, index_1, &ptr);

	return ptr;
}

int fill_table_array(int fd, Table* table, char* array) {
	int index = 0;
	int line = 0;
	int ptr = 0;
	int count = 0;

	while (line < table->line + 1) {
		ptr = my_strcpy_line(fd, table, table->array[line], line, array, &index, &count);
		if (ptr == 1) {
			break;
		}
		index ++;
		line ++;
	}
	if (array[index] != '\0' && array[index] != '\n') {
		ptr = 1;
	}

	return ptr;
}

void free_array(Array* array) {
	free(array->array);
	free(array->line);
	free(array->col);
	free(array);
	
	//printf("Array freed\n");
}

void free_table(Table* table) {
	for (int i = 0; i < table->line + 1; i++) {
		free(table->array[i]);
	}
	free(table->array);
	free(table);

	//printf("Table freed\n");
}
