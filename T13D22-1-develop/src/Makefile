CC=gcc
CFLAGS=-Wall -Werror -Wextra
OUTPATH=../build/

all: cipher logging_cipher

rebuild: clean all

clean:
	rm -rf *.o *.a $(OUTPATH)cipher*

format:
	clang-format -i *.c
	clang-format -i *.h

check:
	clang-format -n *.c
	clang-format -n *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c
	cppcheck --enable=all --suppress=missingIncludeSystem *.h
	



cipher:
	$(CC) $(CFLAGS) cipher.c logger.c -o $(OUTPATH)cipher

logging_cipher:
	$(CC) $(CFLAGS) -D LOG cipher.c logger.c -o $(OUTPATH)logging_cipher




all_sanitized: cipher_sanitized_address cipher_sanitized_undefined

cipher_sanitized_address:
	$(CC) $(CFLAGS) cipher.c -fsanitize=address -o $(OUTPATH)cipher_sanitized_address

cipher_sanitized_undefined:
	$(CC) $(CFLAGS) cipher.c -fsanitize=undefined -o $(OUTPATH)cipher_sanitized_undefined


# cifer Ceasar encoded with shift +3