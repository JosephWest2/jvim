DEPENDENCIES = -lSDL2 -lSDL2_ttf

all:
	gcc *.c $(DEPENDENCIES) -o jvim
