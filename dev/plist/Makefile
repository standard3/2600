SRC_DIR  := src
OBJ_DIR  := build\obj
BIN_DIR  := bin
INC_DIR  := includes
LIB_DIR  := lib
EXE_NAME := plist.exe

EXE := $(BIN_DIR)/$(EXE_NAME)
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

RMDIR := rd /s /q

CC       := gcc
CPPFLAGS := -I$(INC_DIR) -MMD -MP
CFLAGS   := -Wall #-Werror # -Wpedantic
LDFLAGS  := -L$(LIB_DIR)
LDLIBS   := -lm -lpsapi -lkernel32 -static $(patsubst $(LIB_DIR)\lib*.a, -l$(LIB_DIR)\*, $(wildcard $(LIB_DIR)/lib*.a))

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	if not exist "$@" mkdir $@

clean:
	@if exist $(BIN_DIR) $(RMDIR) $(BIN_DIR)
	@if exist $(OBJ_DIR) $(RMDIR) $(OBJ_DIR)

-include $(OBJ:.o=.d)

run:
	$(EXE)
