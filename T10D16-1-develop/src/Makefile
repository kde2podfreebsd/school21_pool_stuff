CC=gcc
CFLAGS=-Wall -Werror -Wextra
OUT_PATH=../build/Quest_

all: strlen_tests strcmp_tests strcpy_tests strcat_tests strchr_tests strstr_tests strtok_tests text_processor

rebuild: clean all

strlen_tests: s21_string.c s21_string.h s21_string_test.c
	$(CC) $(CFLAGS) -D STRLEN s21_string_test.c s21_string.c -o $(OUT_PATH)1

strcmp_tests: s21_string.c s21_string.h s21_string_test.c
	$(CC) $(CFLAGS) -D STRCMP s21_string_test.c s21_string.c -o $(OUT_PATH)2

strcpy_tests: s21_string.c s21_string.h s21_string_test.c
	$(CC) $(CFLAGS) -D STRCPY s21_string_test.c s21_string.c -o $(OUT_PATH)3

strcat_tests: s21_string.c s21_string.h s21_string_test.c
	$(CC) $(CFLAGS) -D STRCAT s21_string_test.c s21_string.c -o $(OUT_PATH)4

strchr_tests: s21_string.c s21_string.h s21_string_test.c
	$(CC) $(CFLAGS) -D STRCHR s21_string_test.c s21_string.c -o $(OUT_PATH)5

strstr_tests: s21_string.c s21_string.h s21_string_test.c
	$(CC) $(CFLAGS) -D STRSTR s21_string_test.c s21_string.c -o $(OUT_PATH)6

strtok_tests: s21_string.c s21_string.h s21_string_test.c
	$(CC) $(CFLAGS) -D STRTOK s21_string_test.c s21_string.c -o $(OUT_PATH)7

text_processor: text_processor.c s21_string.c s21_string.h
	$(CC) $(CFLAGS) text_processor.c s21_string.c -o $(OUT_PATH)8

clean:
	rm -rf all *.o *.a *.so *.gch $(OUT_PATH)* *.out