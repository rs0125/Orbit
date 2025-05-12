# Compiler
CXX := clang++

# Compiler flags
CXXFLAGS := `sdl2-config --cflags` -ggdb3 -O0 -std=c++17 -Wall
LDFLAGS := `sdl2-config --libs` -lSDL2_image -lm

# Source and output
SRCS := main.cpp utils.cpp
OBJS := $(SRCS:.cpp=.o)
EXEC := sdl_app

# Default target
all: $(EXEC)

# Link
$(EXEC): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Compile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build
clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean
