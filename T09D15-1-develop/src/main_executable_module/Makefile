CC=gcc
CFLAGS=-Wall -Werror -Wextra

all: rebuild build_with_macro build_with_static build_with_dynamic

rebuild: main_executable_module.o data_io.o data_process.o decision.o data_stat.o
	$(CC) $(CFLAGS) main_executable_module.o data_io.o data_process.o decision.o data_stat.o -o ../../build/Quest_3 -lm

build_with_macro: main_executable_module_macro.o data_process.o decision.o data_stat.o
	$(CC) $(CFLAGS) main_executable_module_macro.o data_process.o decision.o data_stat.o -o ../../build/Quest_4 -lm

build_with_static: main_executable_module.o data_io.o data_process.o decision.o data_stat.a
	$(CC) $(CFLAGS) main_executable_module.o data_io.o data_process.o decision.o -o ../../build/Quest_5 data_stat.a -lm

build_with_dynamic: main_executable_module.o data_io.o data_process.so decision.o data_stat.o
	$(CC) $(CFLAGS) main_executable_module.o data_io.o data_process.so decision.o data_stat.o -o ../../build/Quest_6 -lm

main_executable_module.o: main_executable_module.c
	$(CC) $(CFLAGS) -c main_executable_module.c

main_executable_module_macro.o: main_executable_module.c
	$(CC) $(CFLAGS) -c -D TYPE=double main_executable_module.c -o main_executable_module_macro.o

data_io.o: ../data_libs/data_io.c ../data_libs/data_io.h
	$(CC) $(CFLAGS) -c ../data_libs/data_io.c

data_process.o: ../data_module/data_process.c ../data_module/data_process.h
	$(CC) $(CFLAGS) -c ../data_module/data_process.c

decision.o: ../yet_another_decision_module/decision.c ../yet_another_decision_module/decision.h
	$(CC) $(CFLAGS) -c ../yet_another_decision_module/decision.c

data_stat.o: ../data_libs/data_stat.c ../data_libs/data_stat.h
	$(CC) $(CFLAGS) -c ../data_libs/data_stat.c

data_stat.a: data_stat.o
	ar rcs data_stat.a data_stat.o

data_process.so: data_process.o data_stat.o
	$(CC) $(CFLAGS) -shared data_process.o data_stat.o -o data_process.so
	cp ./data_process.so ../../build/data_process.so

libs: data_stat.a

clean:
	rm -rf all *.o *.a *.so *.gch ../../build/Quest_* ../../build/*.so