OBJS = src/main.cpp src/game.cpp

CC = g++

LINKER_FLAGS = -lSDL2 -lSDL2_image

OBJ_NAME = StackAttack

all: $(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS) -o $(OBJ_NAME)
