typedef struct Table {
	int line;
	int col;
	char** array;
	char full;
	char empty;
	char path;
	char enter;
	char exit;
} Table;

typedef struct Array {
	char* array;
	char* line;
	char* col;
} Array;

/* table.c */
void my_read(int fd, char* array);
void create_table(Table* table, char* line, char* col);
Array* create_array();
void print_table(Table* table);
void get_line(char* array, char* line, int* index);
void get_col(char* array, char* col, int* index);
void get_parameters(Table* table, char* array, char* line, char* col);
void get_entry(Table* table, char* ptr, int* entry);
void get_exit(Table* table, char* ptr, int* exit);
int my_strcpy_char(Table* table, char* table_array, int line, char* array, int index, int index_1, int* count);
void check_col_size(Table* table, char* array, int line, int index_1, int* ptr);
int my_strcpy_line(int fd, Table* table, char* table_array, int line, char* array, int* index, int* count);
int fill_table_array(int fd, Table* table, char* array);
void free_array(Array* array);
void free_table(Table* table);

/* functions.c */
int my_strlen(char* ptr);
void get_array_int(char* ptr, int* array);
int get_int(int* array_int, int length);
int my_atoi(char* ptr);

/* equal */
void fill_line_equal(Table* table, int* index, int* entry, int* count);

/* left */
int find_line_left_1(Table* table, int index, int index_1);
void find_line_left(Table* table, int* index, int index_1, int* hight, int* index_col, int* line);
int find_way_left(Table* table, int* index, int* hight, int* index_col);
void check_way_left(Table* table, int* index, int* entry, int* hight, int* index_col, int* count);
void fill_line_left_1(Table* table, int* index, int* entry, int* hight, int* index_col, int* count);
void check_hight(Table* table, int* index, int index_1, int* hight, int* index_col);
void fill_line_left(Table* table, int* index, int* entry, int* exit, int* count);

/* right */
int find_line_right_1(Table* table, int index, int index_1);
void find_line_right(Table* table, int* index, int index_1, int* hight, int* index_col, int* line);
int find_way_right(Table* table, int* index, int* hight, int* index_col);
void check_way_right(Table* table, int* index, int* entry, int* hight, int* index_col, int* count);
void fill_line_right_1(Table* table, int* index, int* entry, int* hight, int* index_col, int* count);
void fill_line_right(Table* table, int* index, int* entry, int* exit, int* count);

/* functions for left, equal, right */
void find_hight_1(Table* table, int* index, int index_1, int* hight);
void find_hight(Table* table, int* index, int index_1, int* hight, int* index_col);
int find_way_1(Table* table, int hight, int index_1);
int find_way_1_1_1(Table* table, int index, int index_1);
int find_way_1_1(Table* table, int index, int index_1, int hight);
int find_way_2(Table* table, int index, int index_1);
int find_way_2_2_2(Table* table, int index, int index_1);
int find_way_2_2(Table* table, int index, int index_1, int hight);
void fill_line_1(Table* table, int* index, int* entry, int* index_1, int* count);
void fill_line_2(Table* table, int* index, int* entry, int* index_1, int* count);
