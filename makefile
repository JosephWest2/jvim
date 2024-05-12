DEPENDENCIES = -lSDL2 -lSDL2_ttf

all:
	gcc *.c $(DEPENDENCIES) -Wall -L/opt/homebrew/include -o jvim
