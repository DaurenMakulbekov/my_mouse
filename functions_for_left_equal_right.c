#include "my_mouse.h"


void find_hight_1(Table* table, int* index, int index_2, int* hight) {
	int index_1 = *index;

	while (table->array[index_1][index_2] != table->full) {
		if (table->array[index_1][index_2] == table->exit) {
			break;
		}
		index_1 ++;
	}

	*hight = index_1;
}

void find_hight(Table* table, int* index, int index_2, int* hight, int* index_col) {
	int index_1 = *index;

	while (table->array[index_1][index_2] != table->full) {
		if (table->array[index_1][index_2] == table->exit) {
			break;
		}
		index_1 ++;
	}

	if (index_1 > *hight) {
		*hight = index_1;
		*index_col = index_2;
	}
}

int find_way_1(Table* table, int hight, int index_1) {
	int number = 1;
	
	while (table->array[hight - 1][index_1] != table->full) {
		if (table->array[hight][index_1] == table->exit || hight == table->line) {
			number = 0;
			break;
		}
		else if (table->array[hight - 1][index_1] == table->empty && table->array[hight][index_1] == table->empty && table->array[hight + 1][index_1] == table->empty) {
			number = 0;
			break;
		}
		index_1 ++;
	}

	return number;
}

int find_way_1_1_1(Table* table, int index, int index_1) {
	int number = 1;
	int hight_1 = 0;
	
	while (table->array[index][index_1] != table->full) {
		find_hight_1(table, &index, index_1, &hight_1);
		number = find_way_1(table, hight_1, index_1);
		if (number == 0) {
			break;
		}
		index_1 --;
	}

	return number;
}

int find_way_1_1(Table* table, int index, int index_1, int hight) {
	int number = 1;
	index ++;

	while (index != hight) {
		number = find_way_1_1_1(table, index, index_1);
		if (number == 0) {
			break;
		}
		index ++;
	}
	
	return number;
}

int find_way_2(Table* table, int index, int index_1) {
	int number = 1;
	
	while (table->array[index - 1][index_1] != table->full) {
		if (table->array[index][index_1] == table->exit || index == table->line) {
			number = 0;
			break;
		}
		else if (table->array[index - 1][index_1] == table->empty && table->array[index][index_1] == table->empty && table->array[index + 1][index_1] == table->empty) {
			number = 0;
			break;
		}
		index_1 --;
	}

	return number;
}

int find_way_2_2_2(Table* table, int index, int index_1) {
	int number = 1;
	int hight_1 = 0;

	while (table->array[index][index_1] != table->full) {
		find_hight_1(table, &index, index_1, &hight_1);
		number = find_way_2(table, hight_1, index_1);
		if (number == 0) {
			break;
		}
		index_1 ++;
	}

	return number;
}

int find_way_2_2(Table* table, int index, int index_1, int hight) {
	int number = 1;
	index ++;

	while (index != hight) {
		number = find_way_2_2_2(table, index, index_1);
		if (number == 0) {
			break;
		}
		index ++;
	}
	
	return number;
}

void fill_line_1(Table* table, int* index, int* entry, int* index_col, int* count) {
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

void fill_line_2(Table* table, int* index, int* entry, int* index_col, int* count) {
	while (*entry <= *index_col) {
		if (table->array[*index][*entry] == table->empty) {
			table->array[*index][*entry] = table->path;
			(*count) ++;
		}
		if (*entry == *index_col) {
			break;
		}
		(*entry) ++;
	}
}
