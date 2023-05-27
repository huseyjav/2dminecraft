#include "game.h"
#include <iostream>

using namespace std;

CGame::CGame() : world(new CWorld(100, 20))
{
    // spawn player in middle of world
    // set camera to render
    

    SDL_CreateWindowAndRenderer(1500, 1000, 0, &window, &renderer);
    camrednerer = new CCameraRenderer(window, renderer, world);
    localplayer = new CPlayer(603, 600, 95, 195, world);
    hud = new CHud(localplayer);
    world->setplayer(localplayer);
}

void CGame::loop()
{
    uint delaytime = 1000 / 60;
    uint expectednexttick;
    while (isRunning)
    {
        expectednexttick = SDL_GetTicks() + delaytime;
        handleinputs();
        world->update();
        camrednerer->centerTo(localplayer->x,localplayer->y);
        SDL_SetRenderDrawColor(renderer, 45, 177, 224, 255);
        SDL_RenderClear(renderer);

        world->render(camrednerer);
        hud->render(camrednerer);
        SDL_RenderPresent(renderer);

        if (expectednexttick > SDL_GetTicks())
            SDL_Delay(expectednexttick - SDL_GetTicks()); // game logic might take more than delay time and might cause it to get negative therefore overflow (40days of delay :X)
                                                          // TODO: implement better tick system
    }
}

void CGame::handleinputs()
{
    const Uint8 *keystates(SDL_GetKeyboardState(nullptr));
    while (SDL_PollEvent(&events))
    {
        if (events.type == SDL_QUIT)
        {
            isRunning = false;
        }
        // if(events.type == SDL_KEYDOWN)
        // {
        //     if(events.key.keysym.sym==SDLK_SPACE){
        //         if(localplayer->alive) localplayer->jump();
        //         else localplayer->respawn();
        //     }
        // }

    }

    if(keystates[SDL_SCANCODE_A]){
        if(localplayer->alive) localplayer->moveLeft();
    }
    if(keystates[SDL_SCANCODE_D]){
        if(localplayer->alive) localplayer->moveRight();
    }
    if(keystates[SDL_SCANCODE_SPACE]){
        if(localplayer->alive) localplayer->jump();
        else localplayer->respawn();
    }
    world->handleInput( camrednerer);
}

CGame::~CGame()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
