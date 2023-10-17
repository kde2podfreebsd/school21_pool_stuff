CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra -lm
SRC_DIR = src
BUILD_DIR = build
CPPLINT = cpplint
out = 

ifndef out
$(error Please specify the target file: make out=filename)
endif

target = $(BUILD_DIR)/$(out)

all: $(target)
	$(target)

$(BUILD_DIR)/%: $(SRC_DIR)/%.c
	# $(CPPLINT) $<
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(BUILD_DIR)/*
	rm -f $(BUILD_DIR)/$(out)

.PHONY: all clean
