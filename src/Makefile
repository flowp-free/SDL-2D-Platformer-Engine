# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -O0 -Wall -Wextra -Wshadow -Wpedantic -Wfloat-equal -Wduplicated-cond -Wlogical-op -Woverloaded-virtual -Wnull-dereference  

# SDL2 libraries
SDL_LIBS = `sdl2-config --cflags --libs` -lSDL2_image

# Source files
SRCS = main.cpp player.cpp map.cpp physics.cpp camera.cpp game.cpp animation.cpp menu.cpp

# Object files go to build/ directory
OBJS = $(patsubst %.cpp,build/%.o,$(SRCS))

# Output binary
TARGET = game

# Default rule
all: $(TARGET)

# Link target from object files in build/
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(SDL_LIBS)

# Compile .cpp files to build/*.o
build/%.o: %.cpp
	mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -rf build $(TARGET)
