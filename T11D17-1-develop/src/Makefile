CC=gcc
CFLAGS=-Wall -Werror -Wextra
OUT_PATH=../build/Quest_
SRC=./

FORMAT=clang-format -i
CHECK=cppcheck --enable=all --suppress=missingIncludeSystem

all: door_struct list_test stack_test

door_struct: dmanager_module.o
	$(CC) $(CFLAGS) dmanager_module.o -o $(OUT_PATH)1

list_test: list.o list_test.c
	$(CC) $(CFLAGS) -D LIST_ADD_REMOVE_TEST list.o list_test.c -o $(OUT_PATH)2

stack_test: stack.o stack_test.c
	$(CC) $(CFLAGS) -D STACK_TEST stack.o stack_test.c -o $(OUT_PATH)3

rebuild: clean all

clean:
	rm -rf *.a *.o *.gch $(OUT_PATH)*





dmanager_module.o: dmanager_module.c door_struct.h
	$(CC) $(CFLAGS) -c dmanager_module.c

list.o: list.c list.h door_struct.h
	$(CC) $(CFLAGS) -c list.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c





format:
	$(FORMAT) $(SRC)*.c
	$(FORMAT) $(SRC)*.h

check:
	$(CHECK) $(SRC)*.c
	$(CHECK) $(SRC)*.h





all_sanitize: door_struct_sanitize list_test_sanitize stack_test_sanitize

door_struct_sanitize: dmanager_module.o
	$(CC) $(CFLAGS) dmanager_module.o -fsanitize=address -o $(OUT_PATH)1_sanitized

list_test_sanitize: list.o list_test.c
	$(CC) $(CFLAGS) -D LIST_ADD_REMOVE_TEST -fsanitize=address list_test.c list.o -o $(OUT_PATH)2_sanitized

stack_test_sanitize: stack.o stack_test.c
	$(CC) $(CFLAGS) -D STACK_TEST -fsanitize=address stack.o stack_test.c -o $(OUT_PATH)3_sanitized