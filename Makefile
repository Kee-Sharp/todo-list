CFLAGS=-std=c99 -Wall -pedantic -Wextra -Werror -O2 -Wstrict-prototypes -Wold-style-definition -g
OBJECTS=todo.o todo_data.o todo_helpers.o
todo: $(OBJECTS)
	gcc $(CFLAGS) -o todo $(OBJECTS)
todo.o todo_data.o todo_helpers.o: todo.h
todo.o: useful_strings.h