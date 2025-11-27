# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude

# Raylib & system libs (Windows + MSYS2)
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

# Directories
SRC_DIR = src
BUILD_DIR = build

# Source files and output
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
TARGET = $(BUILD_DIR)/game.exe

# Default target
all: $(TARGET)

# Link all objects
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LIBS)

# Compile each .cpp to .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build
clean:
	rm -rf $(BUILD_DIR)/*
