CC=g++
#CFLAGS=-g -Wall
CFLAGS=-O3
LDFLAGS=-lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
OUTPUT=flappyjames
OBJECTS= src/close.cpp src/events.cpp src/init.cpp src/load.cpp src/main.cpp\
		 src/render.cpp src/texture.cpp src/util.cpp src/face.cpp\
		 src/update.cpp src/pipes.cpp src/ground.cpp src/collision.cpp\
		 src/reset.cpp src/hud.cpp src/files.cpp src/menu.cpp src/clouds.cpp\
		 src/buildings.cpp src/bushes.cpp src/stars.cpp src/resize.cpp\
		 src/sounds.cpp src/args.cpp src/timer.cpp

all:	$(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(OUTPUT) $(LDFLAGS)
