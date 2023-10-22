CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra -lm
SRC_DIR = src
BUILD_DIR = build

out = 

ifndef out
$(error Please specify the target file: make out=filename)
endif

all: $(BUILD_DIR)/$(out)
	$(BUILD_DIR)/$(out)

$(BUILD_DIR)/%: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(BUILD_DIR)/*

.PHONY: all clean
