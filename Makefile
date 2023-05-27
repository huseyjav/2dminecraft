
# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

# SDL2 Libraries
SDL_LIBS := -lSDL2 -lSDL2main

# Include directories
INCLUDES := $(sdl2-config --cflags) -I.

# Source files
SRCS := $(wildcard *.cpp)

# Object files
BUILD_DIR := build
#OBJS := $(SRCS:.cpp=.o)
OBJS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Executable
EXEC := build/game

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJS) $(SDL_LIBS) -o $(EXEC)

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run: $(EXEC)
	$(EXEC)


clean:
	rm -rf $(BUILD_DIR)
