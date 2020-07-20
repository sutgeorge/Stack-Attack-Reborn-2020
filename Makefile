OBJS = src/main.cpp src/game.cpp src/pipe.cpp src/crane.cpp src/block.cpp src/block_container.cpp src/textures.cpp

CC = g++

LINKER_FLAGS = -pthread -g -lSDL2 -lSDL2_image

OBJ_NAME = StackAttack

all: $(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS) -o $(OBJ_NAME)
