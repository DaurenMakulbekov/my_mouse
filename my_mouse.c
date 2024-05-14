#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "my_mouse.h"


void parse_table_array(Table* table, int* count) {
	int index = 1, entry = 0, exit = 0;
	get_entry(table, table->array[index], &entry);
	get_exit(table, table->array[table->line], &exit);

	while (index < table->line) {
		if (index > 1 && entry < exit) {
			fill_line_left(table, &index, &entry, &exit, count);
		}
		else if (index > 1 && entry == exit) {
			fill_line_equal(table, &index, &entry, count);
		}
		else if (index > 1 && entry > exit) {
			fill_line_right(table, &index, &entry, &exit, count);
		}
		index ++;
	}
}

int check_table_array(Table* table, char** array, int index) {
	int index_col = 0;
	int ptr = 1;

	while (array[index][index_col] != '\0') {
		if (array[index][index_col] == table->enter && array[index + 1][index_col] == table->path) {
			ptr = 0;
		}
		else if (array[index][index_col] == table->path && array[index + 1][index_col] == table->exit) {
			ptr = 0;
		}
		else if (array[index][index_col] == table->path && array[index + 1][index_col] == table->path){
			ptr = 0;
		}
		if (ptr == 0) {
			break;
		}
		index_col ++;
	}
	
	return ptr;
}

int check_table(Table* table) {
	int index = 1;
	int ptr = 0;

	while (index < table->line) {
		ptr = check_table_array(table, table->array, index);
		if (ptr == 1) {
			break;
		}
		index ++;
	}

	return ptr;
}

int fill_table(int fd, Table* table, char* array) {
	int ptr = fill_table_array(fd, table, array);
	
	if (ptr == 0) {
		int count = 0;
		parse_table_array(table, &count);
		ptr = check_table(table);

		if (ptr == 0) {
			print_table(table);
			printf("%d STEPS!\n", count);
			return 0;
		}
		else {
			return 1;
		}
	}
	else {
		return 1;
	}
}

int my_mouse(int fd) {
	Array* array = create_array();
	Table* table = (Table*)malloc(sizeof(Table));
	my_read(fd, array->array);
	get_parameters(table, array->array, array->line, array->col);
	create_table(table, array->line, array->col);

	int ptr = fill_table(fd, table, array->array);
	free_array(array);
	free_table(table);

	if (ptr == 0) {
		return 0;
	}
	else {
		return 1;
	}
}

int main(int argc, char** argv) {
	if (argc == 1) {
		return 0;
	}
	else {
		int fd = open(argv[1], O_RDONLY);
		if (fd == -1) {
			printf("No such file\n");
			return 1;
		}
		else {
			int ptr = my_mouse(fd);
       		close(fd);
			if (ptr == 0) {
				return 0;
			}
			else {
				write(2, "MAP ERROR\n", 10);
				return 1;
			}
		}
	}
}
