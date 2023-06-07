
# # Compiler
# CXX := g++

# # Compiler flags
# CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -g

# # SDL2 Libraries
# SDL_LIBS := -lSDL2 -lSDL2main

# # Include directories
# INCLUDES := $(sdl2-config --cflags) -I.

# # Source files
# SRCS := $(wildcard *.cpp)

# # Object files
# BUILD_DIR := build
# #OBJS := $(SRCS:.cpp=.o)
# OBJS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# # Executable
# EXEC := build/game

# all: $(EXEC)

# $(EXEC): $(OBJS)
# 	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJS) $(SDL_LIBS) -o $(EXEC)

# $(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
# 	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# $(BUILD_DIR):
# 	mkdir -p $(BUILD_DIR)

# run: $(EXEC)
# 	$(EXEC)


# clean:
# 	rm -rf $(BUILD_DIR)

CXX := g++

# Compiler flags
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -g

# SDL2 Libraries
SDL_LIBS := -lSDL2 -lSDL2main -lSDL2_image

# Include directories
INCLUDES := $(shell sdl2-config --cflags) -I. -Isrc

# Source files
SRCS := $(wildcard src/*.cpp)

# Object files
BUILD_DIR := build
DOC_DIR := doc

OBJS := $(patsubst src/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Executable
EXEC := huseyjav

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJS) $(SDL_LIBS) -o $(EXEC)

$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run: $(EXEC)
	./$(EXEC)

compile: $(OBJS)

clean:
	rm -rf $(BUILD_DIR)

doc:
	doxygen Doxyfile