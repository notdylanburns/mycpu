CC := gcc
PYTHON := python

ROOT_DIR := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

INC_DIR := $(ROOT_DIR)/inc
SRC_DIR := $(ROOT_DIR)/src
OBJ_DIR := $(ROOT_DIR)/obj
BIN_DIR := /usr/local/bin
LIB_DIR := /usr/lib

MICROCODE_FILE := $(dir $(ROOT_DIR))Microcode.csv

SRC_EXCLUDE :=

CFLAGS := -Wall -I$(INC_DIR) #-ggdb3
LDFLAGS := 

SRCS := $(SRC_DIR)/matrix.c $(filter-out $(SRC_EXCLUDE), $(wildcard $(SRC_DIR)/*.c))
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

MAIN := $(ROOT_DIR)/d16asm.c

LIB_TARGET = libd16.so
TARGET := d16asm

all: build
build: $(TARGET)
$(TARGET): $(LIB_DIR)/$(LIB_TARGET)
	$(CC) -ld16 $(CFLAGS) -o $(TARGET) $(MAIN)

lib-install: $(LIB_DIR)/$(LIB_TARGET)
$(LIB_DIR)/$(LIB_TARGET): $(LIB_TARGET)
	cp $< $@

lib: $(LIB_TARGET)
$(LIB_TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(CFLAGS) -shared -o $@ $^

objects: $(OBJS)
$(SRC_DIR)/matrix.c: $(MICROCODE_FILE)
	$(PYTHON) $(ROOT_DIR)/gen_ocm.py $(MICROCODE_FILE) > $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(OBJ_DIR)
	$(CC) $(LDFLAGS) $(CFLAGS) -fPIC -o $@ -c $<

$(OBJ_DIR):
	mkdir $@

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(ROOT_DIR)/test
	rm -f $(ROOT_DIR)/valgrind-out.txt
	rm -f $(ROOT_DIR)/$(LIB_TARGET)

remove: clean
	rm -f $(TARGET)

install: $(BIN_DIR)/$(TARGET)
$(BIN_DIR)/$(TARGET): $(TARGET)
	cp $< $@

FORCE: ;

.PHONY: all