CC=gcc
CFLAGS=-Wall -Werror -Wextra
OUTPATH=../build/Quest_

all: state_sort state_search clear_state

rebuild: clean all

clean:
	rm -rf *.o *.a $(OUTPATH)*

format:
	clang-format -i *.c
	clang-format -i *.h

check:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c
	cppcheck --enable=all --suppress=missingIncludeSystem *.h




state_sort:
	$(CC) $(CFLAGS) state_sort.c -o $(OUTPATH)1

state_search:
	$(CC) $(CFLAGS) state_search.c -o $(OUTPATH)2

clear_state:
	$(CC) $(CFLAGS) clear_state.c -o $(OUTPATH)3