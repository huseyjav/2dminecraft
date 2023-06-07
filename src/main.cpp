#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <game.h>
using namespace std;

unsigned int CGame::tick = 0;


int main()
{
	
	CGame game;
	game.loop();


	
	return 0;
}