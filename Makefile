CC=gcc
PRJ_NAME=lin_algebra
DBG_FLAGS=-Wall -Wextra -pedantic -O0 -g
RLS_FLAGS=-Wall -Wextra -O2
DBG_DIR=debug
RLS_DIR=release
SRC_FLS=./**/*.c
MEM_CHK=valgrind --leak-check=full

clean:
		@rm -rf $(DBG_DIR) $(RLS_DIR)

memleak-chk: build-dbg
		@$(MEM_CHK) ./$(DBG_DIR)/$(PRJ_NAME)

build-all: build-dbg build-rls

build-dbg: clean
		@mkdir $(DBG_DIR)
		@$(CC) $(DBG_FLAGS) $(SRC_FLS) -o $(DBG_DIR)/$(PRJ_NAME)

build-rls: clean
		@mkdir $(RLS_DIR)
		@$(CC) $(RLS_FLAGS) $(SRC_FLS) -o $(RLS_DIR)/$(PRJ_NAME)

run-dbg: build-dbg
		@./$(DBG_DIR)/$(PRJ_NAME)

run-rls: build-rls
		@./$(RLS_DIR)/$(PRJ_NAME)