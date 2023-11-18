CC=gcc
CFLAGS=-Wall -Werror -Wextra

all: graph

rebuild: clean all

clean:
	rm -rf *.o *.a ../build/graph*

graph:
	$(CC) $(CFLAGS) graph.c data_init.c data_structs.c data_process.c data_plot.c -o ../build/graph

format:
	clang-format -i *.c
	clang-format -i *.h

check:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c
	cppcheck --enable=all --suppress=missingIncludeSystem *.h





graph_sanitized_address:
	$(CC) $(CFLAGS) -fsanitize=address -g graph.c data_init.c data_structs.c data_process.c data_plot.c -o ../build/graph_sanitized

graph_sanitized_undefined:
	$(CC) $(CFLAGS) -fsanitize=undefined -g graph.c data_init.c data_structs.c data_process.c data_plot.c -o ../build/graph_sanitized

