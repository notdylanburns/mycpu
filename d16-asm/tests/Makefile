ROOT_DIR := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

ASM := $(ROOT_DIR)/../d16asm

SRC_DIR := $(ROOT_DIR)/src
BIN_DIR := $(ROOT_DIR)/bin

SRCS := $(wildcard $(SRC_DIR)/*.S)
BINS := $(patsubst $(SRC_DIR)/%.S, $(BIN_DIR)/%.bin, $(SRCS)) 

all: $(BINS)
$(BIN_DIR)/%.bin: $(SRC_DIR)/%.S
	$(ASM) $< $@

.PHONY: all