TARGET    = gvec.a
TESTER    = test

SRC_DIR   = src
OBJ_DIR   = obj
INC_DIR   = inc
TST_DIR   = tests

BIN_SRC_FILES = $(shell find $(SRC_DIR) -type f -name '*.c')
BIN_OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(BIN_SRC_FILES))
BIN_INC_FILES = $(wildcard $(INC_DIR)/*.h)

TST_SRC_FILES = $(wildcard $(TST_DIR)/*.c)
TST_OBJ_FILES = $(patsubst %.c, $(OBJ_DIR)/%.o, $(TST_SRC_FILES))

CFLAGS    = -std=c11 -Wall -Wextra -Werror #-pedantic
IFLAGS    = -I $(INC_DIR)
TFLAGS    = -lcriterion $(TARGET)

all: $(TARGET) $(TESTER)

$(TARGET): $(BIN_OBJ_FILES)
	@printf "ARCHIVE\t%s\n" $@
	@ar rcs $@ $^

$(BIN_OBJ_FILES): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(BIN_INC_FILES)
	@printf "CC\t%s\n" $@
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(IFLAGS) -c -o $@ $<

$(TESTER): $(TST_OBJ_FILES) $(TARGET)
	@printf "LINK\t%s\n" $@
	@$(CC) $(CFLAGS) $(TFLAGS) -o $@ $^

$(TST_OBJ_FILES): $(OBJ_DIR)/$(TST_DIR)/%.o : $(TST_DIR)/%.c $(BIN_INC_FILES)
	@printf "CC\t%s\n" $@
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(IFLAGS) -c -o $@ $<

clean:
	@rm -rf $(OBJ_DIR) $(TARGET) $(TESTER)

re: clean all

.PHONY: all clean re
