ROOT_DIR := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

ASM := $(ROOT_DIR)/../d16asm
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

SRC_DIR := $(ROOT_DIR)/src
BIN_DIR := $(ROOT_DIR)/bin

SRCS := $(wildcard $(SRC_DIR)/*.S)
BINS := $(patsubst $(SRC_DIR)/%.S, $(BIN_DIR)/%.bin, $(SRCS)) 

all: $(BIN_DIR) $(BINS)
$(BIN_DIR)/%.bin: $(SRC_DIR)/%.S
	valgrind $(VALGRIND_FLAGS) $(ASM) $< $@

$(BIN_DIR):
	mkdir -p $@

.PHONY: all