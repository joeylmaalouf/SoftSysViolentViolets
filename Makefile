CC = g++
FLAGS = -Wall -std=c++11
GRAPHICSFLAGS = -lglut -lGL -lGLU
BUILD_DIR = build
SOURCE_DIR = src

# make build directory if it doesn't exist
dummy := $(shell mkdir -p $(BUILD_DIR))

voxelpaint : $(SOURCE_DIR)/main.cpp $(BUILD_DIR)/camera.o $(BUILD_DIR)/voxel.o
	$(CC) $(FLAGS) $^ -o $@ $(GRAPHICSFLAGS)

$(BUILD_DIR)/%.o : $(SOURCE_DIR)/%.cpp $(SOURCE_DIR)/*.h
	$(CC) $(FLAGS) -c $< -o $@

.PHONY: clean
clean :
	rm -f $(BUILD_DIR)/*
