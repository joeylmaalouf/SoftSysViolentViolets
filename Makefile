CC = g++
COMPILE_FLAGS = -Wall -std=c++11
SRC_DIR = ./src
BUILD_DIR = ./build
OS := $(shell uname)
ifeq ($(OS), Darwin)
  # MAC
  GRAPHICS_FLAGS = -framework OpenGL -framework GLUT
else
  GRAPHICS_FLAGS = -lglut -lGL -lGLU
endif

# make build directory if it doesn't exist
dummy := $(shell mkdir -p $(BUILD_DIR))

voxelpaint : $(SRC_DIR)/main.cpp $(BUILD_DIR)/camera.o $(BUILD_DIR)/cursor.o $(BUILD_DIR)/fileio.o $(BUILD_DIR)/voxel.o $(BUILD_DIR)/world.o
	$(CC) $(COMPILE_FLAGS) $^ -o $@ $(GRAPHICS_FLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(wildcard $(SRC_DIR)/%.h)
	$(CC) $(COMPILE_FLAGS) -c $^ -o $@

.PHONY: clean
clean :
	rm -f $(BUILD_DIR)/*

.PHONY: lint
lint :
	cpplint src/*.cpp
