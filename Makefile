
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

CC = gcc
CFLAGS = -g -Wall -Wno-unused-parameter

SRC_DIR = src
SRC_SUB_DIRS = $(call rwildcard,$(SRC_DIR)/,*/)
SRC_FILES_PATHS = $(call rwildcard,$(SRC_DIR)/,*.c)
SRC_FILES_NAMES = $(foreach file_path,$(SRC_FILES_PATHS),$(shell basename $(file_path)))

INCLUDE_DIR = include
INCLUDE_FILES = $(wildcard $(INCLUDE_DIR)/*.h)

OBJ_DIR = obj
OBJ_FILES = $(patsubst %.c, %.o, $(SRC_FILES_NAMES))
OBJ_FILES_PATHS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES_PATHS))

TESTS_DIR = tests
TEST_FILES = $(wildcard $(TESTS_DIR)/*.c)
TESTS_BINS = $(patsubst $(TESTS_DIR)/%.c, $(TESTS_DIR)/bin/%, $(TEST_FILES))

LIB_DIR = lib
LIB_FILE = $(LIB_DIR)/lib.a



all: $(LIB_FILE)

$(LIB_FILE): $(OBJ_DIR) $(OBJ_FILES_PATHS) $(LIB_DIR)

$(OBJ_DIR): 
	mkdir $@

$(LIB_DIR):
	mkdir $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c 
	@test -d $(@D) || mkdir -pm 775 $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@


test : $(LIB_FILE) $(TESTS_DIR) $(TESTS_DIR)/bin  $(TESTS_BINS)
	for test in $(TESTS_BINS) ; do ./$$test --verbose ; done

$(TESTS_DIR) : 
	mkdir $@

$(TESTS_DIR)/bin : 
	mkdir $@

$(TESTS_DIR)/bin/% : $(TESTS_DIR)/%.c
	@$(CC) $(CFLAGS) $< $(OBJ_FILES_PATHS) -o $@ -lcriterion -lm



clean:
	$(RM) -r $(OBJ_DIR) $(LIB_DIR) $(TESTS_DIR)/bin
	find -name "*.o" -type f -delete
