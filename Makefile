CC = g++
FLAGS = -Wall -std=c++11
GRAPHICSFLAGS = -lglut -lGL -lGLU
SRC_DIR = ./src
BUILD_DIR = ./build

# make build directory if it doesn't exist
dummy := $(shell mkdir -p $(BUILD_DIR))

voxelpaint : $(SRC_DIR)/main.cpp $(BUILD_DIR)/camera.o $(BUILD_DIR)/voxel.o
	$(CC) $(FLAGS) $^ -o $@ $(GRAPHICSFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(wildcard $(SRC_DIR)/%.h)
	$(CC) $(FLAGS) -c $^ -o $@

.PHONY: clean
clean :
	rm -f $(BUILD_DIR)/*
