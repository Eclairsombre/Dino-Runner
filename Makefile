all : link

link :
	g++ src/main.cpp -w -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2 -o bin/main