# This is a makefile for compiling your whole project.

# Directories
BUILD_DIR = build
SRC_DIR = c
HEADER_DIR = header
MAIN_SRC = main.c

# Compiler and flags
CC = gcc
CFLAGS = -g -Wall -I$(HEADER_DIR)

# Find all source files
SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/adt/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
TARGET = $(BUILD_DIR)/main
MAIN_OBJ = $(BUILD_DIR)/main.o

# This is default target that is used to compile the project.
all: $(TARGET)
	@echo "Build complete!"

# Rule to compile main.c
$(MAIN_OBJ): $(MAIN_SRC) $(wildcard $(HEADER_DIR)/*.h)
	@mkdir -p $(BUILD_DIR)
	@echo "Compiling main.c..."
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile each C file in src/c/ to an object file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER_DIR)/%.h
	@mkdir -p $(BUILD_DIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Special rule for C files that might not have a matching header
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@echo "Compiling $< (no header)..."
	$(CC) $(CFLAGS) -c $< -o $@

# This target is used to link the object files and create the executable.
$(TARGET): $(MAIN_OBJ) $(OBJS)
	@echo "Linking object files..."
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(BUILD_DIR)
	rm -f *.o
	rm -f *.out
	rm -f *.exe
	rm -f *.a
	rm -f *.so
	rm -f *.dll
	rm -f *.dSYM
	rm -f *.pdb
	rm -f *.ilk
	rm -f *.idb
	rm -f *.lib
	rm -f *.exp
.PHONY: all clean