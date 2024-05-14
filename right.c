#include <stdio.h>
#include "my_mouse.h"


int find_line_right_1(Table* table, int index, int index_1) {
	int line = 0;

	while (table->array[index][index_1] != table->full) {
		line ++;
		index_1 --;
	}

	return line;
}

void find_line_right(Table* table, int* index, int index_2, int* hight, int* index_col, int* line) {
	int index_1 = *index;
	int line_1 = 0;

	while (table->array[index_1][index_2] != table->full) {
		if (table->array[index_1][index_2] == table->exit) {
			break;
		}
		line_1 = find_line_right_1(table, index_1, index_2);
		if (*line <= line_1 || *hight == index_1) {
			*line = line_1;
			*hight = index_1;
			*index_col = index_2;
		}
		index_1 ++;
	}
}

int find_way_right(Table* table, int* index, int* hight, int* index_col) {
	int index_1 = *index_col;
	int ptr = 0;
	int hight_1 = 0;

	while (table->array[*index][index_1] != table->full) {
		find_hight_1(table, index, index_1, &hight_1);
		ptr = find_way_2_2(table, *index, index_1, hight_1);
		if (ptr == 0 && hight_1 != (*index) + 1) {
			*hight = hight_1;
			*index_col = index_1;
			break;
		}
		index_1 ++;
	}

	return ptr;
}

void check_way_right(Table* table, int* index, int* entry, int* hight, int* index_col, int* count) {
	if (find_way_right(table, index, hight, index_col) == 0) {
		fill_line_2(table, index, entry, index_col, count);
	}
	else if (find_way_left(table, index, hight, index_col) == 0) {
		fill_line_1(table, index, entry, index_col, count);
	}
}

void fill_line_right_1(Table* table, int* index, int* entry, int* hight, int* index_col, int* count) {
	check_way_right(table, index, entry, hight, index_col, count);

	while (*entry >= *index_col) {
		if (table->array[*index][*entry] == table->empty) {
			table->array[*index][*entry] = table->path;
			(*count) ++;
		}
		if (*entry == *index_col) {
			break;
		}
		(*entry) --;
	}
}

void fill_line_right(Table* table, int* index, int* entry, int* exit, int* count) {
	int hight = 0;
	int index_col = 0;
	int index_1 = *entry;
	int line = 0;

	while (table->array[*index][index_1] != table->full && index_1 > *exit) {
		find_hight(table, index, index_1, &hight, &index_col);
		if (table->line - hight < index_1 - *exit && hight != table->line) {
			find_line_right(table, index, index_1, &hight, &index_col, &line);
		}
		index_1 --;
		if (index_1 == *exit) {
			check_hight(table, index, index_1, &hight, &index_col);
		}
	}
	fill_line_right_1(table, index, entry, &hight, &index_col, count);
}
