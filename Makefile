CC = g++
FLAGS = -Wall -std=c++11
SRC_DIR = ./src
BUILD_DIR = ./build

voxelpaint: $(SRC_DIR)/main.cpp $(BUILD_DIR)/camera.o $(BUILD_DIR)/cursor.o $(BUILD_DIR)/voxel.o $(BUILD_DIR)/world.o
	$(CC) $(FLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(wildcard $(SRC_DIR)/%.h)
	$(CC) $(FLAGS) -c $^ -o $@
