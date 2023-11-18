CC=gcc
CFLAGS=-Wall -Werror -Wextra

SRC=./
OUT_PATH=../build/Quest_

FORMAT=clang-format -
CHECK=cppcheck --enable=all --suppress=missingIncludeSystem

all: print_module documentation_module bst_create_test bst_insert_test bst_traverse_test

rebuild: clean all

clean:
	rm -rf *.o *.a *.gch $(OUT_PATH)*

print_module: print_module.h
	$(CC) $(CFLAGS) -D PRINT_MODULE main_module_entry_point.c print_module.c -o $(OUT_PATH)1

documentation_module: print_module.h documentation_module.h
	$(CC) $(CFLAGS) -D DOCUMENTATION_MODULE main_module_entry_point.c documentation_module.c -o $(OUT_PATH)2

bst_create_test: bst.h
	$(CC) $(CFLAGS) bst_create_test.c bst.c -o $(OUT_PATH)3

bst_insert_test: bst.h
	$(CC) $(CFLAGS) bst_insert_test.c bst.c -o $(OUT_PATH)4

bst_traverse_test: bst.h
	$(CC) $(CFLAGS) bst_traverse_test.c bst.c -o $(OUT_PATH)5





format:
	$(FORMAT)i $(SRC)*.c
	$(FORMAT)i $(SRC)*.h

check:
	$(CHECK) $(SRC)*.c
	$(CHECK) $(SRC)*.h





all_sanitize: print_module_sanitize documentation_module_sanitize bst_create_test_sanitize bst_insert_test_sanitize bst_traverse_test_sanitize

print_module_sanitize: print_module.h
	$(CC) $(CFLAGS) -D PRINT_MODULE main_module_entry_point.c print_module.c -fsanitize=address -o $(OUT_PATH)1_sanitized

documentation_module_sanitize: print_module.h documentation_module.h
	$(CC) $(CFLAGS) -D DOCUMENTATION_MODULE main_module_entry_point.c documentation_module.c -o $(OUT_PATH)2_sanitized

bst_create_test_sanitize: bst.h
	$(CC) $(CFLAGS) bst_create_test.c bst.c -o $(OUT_PATH)3_sanitized

bst_insert_test_sanitize: bst.h
	$(CC) $(CFLAGS) bst_insert_test.c bst.c -o $(OUT_PATH)4_sanitized

bst_traverse_test_sanitize: bst.h
	$(CC) $(CFLAGS) bst_traverse_test.c bst.c -o $(OUT_PATH)5_sanitized