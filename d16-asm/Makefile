CC := gcc
PYTHON := python

ROOT_DIR := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

INC_DIR := $(ROOT_DIR)/inc
SRC_DIR := $(ROOT_DIR)/src
OBJ_DIR := $(ROOT_DIR)/obj

MICROCODE_FILE := $(dir $(ROOT_DIR))Microcode.csv

SRC_EXCLUDE :=

CFLAGS := -Wall -I$(INC_DIR) -ggdb3
LDFLAGS := 

SRCS := $(SRC_DIR)/matrix.c $(filter-out $(SRC_EXCLUDE), $(wildcard $(SRC_DIR)/*.c))
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS)) 
TARGET := d16asm

all: build
build: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $(TARGET) $^

objects: $(OBJS)
$(SRC_DIR)/matrix.c: $(MICROCODE_FILE)
	$(PYTHON) $(ROOT_DIR)/gen_ocm.py $(MICROCODE_FILE) > $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ 

$(OBJ_DIR):
	mkdir $@

clean:
	rm -rf $(OBJ_DIR)

remove: clean
	rm -f $(TARGET)

.PHONY: all