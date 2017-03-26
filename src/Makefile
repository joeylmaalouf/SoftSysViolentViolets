CC = g++
FLAGS = -Wall -std=c++11

voxelpaint: main.cpp camera.o cursor.o voxel.o world.o
	$(CC) $(FLAGS) $^ -o $@

%.o: %.cpp %.h
	$(CC) $(FLAGS) -c $^ -o $@
