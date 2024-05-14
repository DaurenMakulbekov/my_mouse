CC=gcc
CFLAGS=-Wall -Wextra -Werror
TARGET=my_mouse

all:
	$(CC) ${CFLAGS} my_mouse.c table.c functions.c equal.c left.c right.c functions_for_left_equal_right.c -o ${TARGET}

clean:
	rm -f my_mouse

fclean: clean
