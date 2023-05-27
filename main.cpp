#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <game.h>
using namespace std;

int main(int argc, char * argv[])
{
	CGame game;
	game.loop();


	
	return 0;
}