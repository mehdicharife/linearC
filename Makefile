
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

CGREEN_TEST_FILES := $(filter-out Makefile, $(shell grep -lr "Ensure")) 
CGREEN_TEST_OBJ_PATHS = $(patsubst $(TESTS_DIR)/%.c, $(TESTS_DIR)/obj/%.o, $(CGREEN_TEST_FILES))
CGREEN_TEST_MAIN_SRC = tests/cgreen_main.c
CGREEN_TEST_MAIN_BIN = tests/bin/cgreen_main
CGREEN_TEST_MAIN_OBJ = tests/obj/cgreen_main.o


TEST_FILES = $(wildcard $(TESTS_DIR)/*.c)
TEST_BINS = $(patsubst $(TESTS_DIR)/%.c, $(TESTS_DIR)/bin/%, $(TEST_FILES))
TESTS_EXECS := $(filter-out $(CGREEN_TEST_BINS), $(TEST_BINS))

LIB_DIR = lib
LIB_FILE = $(LIB_DIR)/lib.a




all: $(LIB_FILE)

$(LIB_FILE): $(OBJ_DIR) $(OBJ_FILES_PATHS) $(LIB_DIR)

$(OBJ_DIR): 
	@mkdir $@

$(LIB_DIR):
	@mkdir $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c 
	@test -d $(@D) || mkdir -pm 775 $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@


test-build : $(LIB_FILE) $(TESTS_DIR) $(TESTS_DIR)/bin $(TEST_BINS)

test : $(LIB_FILE) $(TESTS_DIR) $(TESTS_DIR)/bin  $(TESTS_DIR)/obj $(TEST_BINS) $(CGREEN_TEST_MAIN_BIN)
	@for test in $(TESTS_EXECS) ;  do ./$$test --verbose ; done

$(TESTS_DIR) : 
	@mkdir $@

$(TESTS_DIR)/bin : 
	@mkdir $@

$(TESTS_DIR)/obj :
	@mkdir $@


$(TESTS_DIR)/bin/% : $(TESTS_DIR)/%.c 
	@if grep -q "criterion" $<; then \
		$(CC) $(CFLAGS) $< $(OBJ_FILES_PATHS) -o $@ -lcriterion -lm ; \
	fi

$(TESTS_DIR)/obj/%.o : $(TESTS_DIR)/%.c 
	@if grep -q "cgreen" $<; then \
		$(CC) -c -o $@ $< $(CFLAGS) ; \
	fi

$(CGREEN_TEST_MAIN_OBJ) : 
	@$(CC) -c -o $(CGREEN_TEST_MAIN_OBJ) $(CGREEN_TEST_MAIN_SRC) $(CFLAGS)

$(CGREEN_TEST_MAIN_BIN) : $(CGREEN_TEST_OBJ_PATHS) $(CGREEN_TEST_MAIN_OBJ)
	@$(CC) $(OBJ_FILES_PATHS) $(CGREEN_TEST_OBJ_PATHS) $(CGREEN_TEST_MAIN_OBJ) -lm -lcgreen -o  $@




clean:
	@$(RM) -r $(OBJ_DIR) $(LIB_DIR) $(TESTS_DIR)/bin $(TESTS_DIR)/obj
	@find -name "*.o" -type f -delete






make-test:
	@echo "$(CGREEN_TEST_FILES)"
