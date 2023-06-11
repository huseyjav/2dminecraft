#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <game.h>
using namespace std;

unsigned int CGame::tick = 0;


int main(int argc, char *argv[])
{
	if(argc==1){
		CGame game;
		game.loop();
	}
	else if(argc==2){
		CGame game(argv[1]);
		game.loop();
	}


	
	return 0;
}