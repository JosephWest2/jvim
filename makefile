DEPENDENCIES = -lSDL2 -lSDL2_ttf

all:
	gcc *.c $(DEPENDENCIES) -L/opt/homebrew/include -o jvim
