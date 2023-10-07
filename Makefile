all : link

link :
	g++ src/main.cpp  -w  -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2  -o bin/main


linkImgui:
	g++ src/main.cpp -o bin/main -w  -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2 -I src/imgui src/imgui/backends/imgui_impl_sdl2.cpp src/imgui/backends/imgui_impl_sdlrenderer2.cpp src/imgui/imgui*.cpp `sdl2-config --libs` -lGL


clean:
	rm -f bin/main

