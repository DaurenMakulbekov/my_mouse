#include <stdio.h>
#include "my_mouse.h"


void fill_line_equal(Table* table, int* index, int* entry, int* count) {
	int hight = 0;
	int index_col = 0;
	int hight_1 = 0;
	find_hight(table, index, *entry, &hight_1, &index_col);

	if (find_way_left(table, index, &hight, &index_col) == 0) {
		fill_line_1(table, index, entry, &index_col, count);
	}
	else if (find_way_right(table, index, &hight, &index_col) == 0) {
		fill_line_2(table, index, entry, &index_col, count);
	}
	else if (table->array[*index][*entry] == table->empty) {
		table->array[*index][*entry] = table->path;
		(*count) ++;
	}
}
