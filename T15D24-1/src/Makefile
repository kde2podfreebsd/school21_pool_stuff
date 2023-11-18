CC = gcc
FLAGS = -Wall -Werror -Wextra

all: build_db

clang:
	clang-format -i *.c
	clang-format -i *.h

build_db:
	$(CC) $(FLAGS) -fPIC modules_db.c MODULES.c STATUS_EVENTS.c LEVELS.c shared.c -o ../build/build_db

