# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude $(shell pkg-config --cflags opencv4)
LDFLAGS := $(shell pkg-config --libs opencv4)

# Directories
SRC_DIR := src
OBJ_DIR := build
BIN := navigate

# Source files (exclude list)
EXCLUDE_SRCS := $(SRC_DIR)/demo_node.cpp
SRCS := $(filter-out $(EXCLUDE_SRCS), $(wildcard $(SRC_DIR)/*.cpp))
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Default target
all: $(BIN)

# Link executable
$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compile source files into objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create build directory if not exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(BIN)

# Rebuild everything
rebuild: clean all

.PHONY: all clean rebuild
