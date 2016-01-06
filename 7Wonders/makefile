CC=/home-reseau/aaudinot/tmp/gcc/bin/g++
SOURCE=7Wonders/*.cpp
FLAGS=-std=c++11
INCLUDE_PATH=-I7Wonders/ -I../SFML-2.3.2_l/include/
LIBRARY_PATH=-L../SFML-2.3.2_l/lib/
LIBRARY=-lsfml-graphics -lsfml-window -lsfml-system
OUTPUT=exe/7Wonders_exe


all:
	$(CC) $(SOURCE) $(FLAGS) $(INCLUDE_PATH) $(LIBRARY_PATH) $(LIBRARY) -o $(OUTPUT)

