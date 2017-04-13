CC = g++
COMPILE_FLAGS = -Wall -std=c++11
GRAPHICS_FLAGS = -lglut -lGL -lGLU
SRC_DIR = ./src
BUILD_DIR = ./build

# make build directory if it doesn't exist
dummy := $(shell mkdir -p $(BUILD_DIR))

voxelpaint : $(SRC_DIR)/main.cpp $(BUILD_DIR)/camera.o $(BUILD_DIR)/cursor.o $(BUILD_DIR)/fileio.o $(BUILD_DIR)/voxel.o $(BUILD_DIR)/world.o
	$(CC) $(COMPILE_FLAGS) $^ -o $@ $(GRAPHICS_FLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(wildcard $(SRC_DIR)/%.h)
	$(CC) $(COMPILE_FLAGS) -c $^ -o $@

.PHONY: clean
clean :
	rm -f $(BUILD_DIR)/*
