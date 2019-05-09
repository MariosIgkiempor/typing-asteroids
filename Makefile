OBJS = *.cpp

CC = g++

COMPILER_FLAGS = -w

LINKER_FLAGS = -lSDL2main -lSDL2_ttf -lSDL2

OUT = asteroids

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OUT)
