#include "game.h"
#include <iostream>
#include "hostilenpc.h"
//#include "utils.h"
using namespace std;



CGame::CGame() : world(new CWorld(100, 20))
{
    //tick=0;
    // spawn player in middle of world
    // set camera to render
    localplayer = new CPlayer(603, 600, 70, 195,10, world);
    hud = new CHud(localplayer);
    SDL_CreateWindowAndRenderer(1500, 1000, 0, &window, &renderer);
    camrednerer = new CCameraRenderer(window, renderer, world);
    assets = new CAssets(camrednerer);
    world->setplayer(localplayer);
    world->worldnpcs.push_back(new CZombie(2000,800,90,195,7,world,localplayer));
    //world->worldnpcs.push_back(new CNpc(2000,800,90,195,7,world,localplayer));
    camrednerer->assets = assets;
    //cout << "asd " << assets;
}

void CGame::loop()
{
    uint delaytime = 1000 / 60;
    uint expectednexttick;

    vector2 a{0,0};
    vector2 b{100,-100};
    for(auto i : bresenhamalgo(a,b)){
        cout << i << endl;
    }
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
        tick++;
        if (expectednexttick > SDL_GetTicks())
            SDL_Delay(expectednexttick - SDL_GetTicks()); // game logic might take more than delay time and might cause it to get negative therefore overflow (40days of delay :X)
                                                          // TODO: implement better tick system
    }
}

void CGame::handleinputs()
{
    int mouseX;
    int mouseY;
    Uint32 state = SDL_GetMouseState(&mouseX, &mouseY);
    const Uint8 *keystates(SDL_GetKeyboardState(nullptr));
    while (SDL_PollEvent(&events))
    {
        if (events.type == SDL_QUIT)
        {
            isRunning = false;
        }
        if(events.type == SDL_KEYDOWN)
        {
            if(events.key.keysym.sym==SDLK_SPACE){
                if(localplayer->alive) localplayer->jump();
                else localplayer->respawn();
            }
            if(events.key.keysym.sym == SDLK_1){
                if(localplayer->alive) localplayer->setactiveitem(1);
            }
            if(events.key.keysym.sym == SDLK_2){
                if(localplayer->alive) localplayer->setactiveitem(2);
            }
            if(events.key.keysym.sym == SDLK_3){
                if(localplayer->alive) localplayer->setactiveitem(3);
            }
            if(events.key.keysym.sym == SDLK_4){
                if(localplayer->alive) localplayer->setactiveitem(4);
            }
            if(events.key.keysym.sym == SDLK_5){
                if(localplayer->alive) localplayer->setactiveitem(5);
            }
            if(events.key.keysym.sym == SDLK_6){
                if(localplayer->alive) localplayer->setactiveitem(6);
            }
        }

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
    if(state & SDL_BUTTON(1)){
        localplayer->useactiveitem(camrednerer->screentoworld(vector2{mouseX,mouseY}));
    }
    world->handleInput( camrednerer);
}

CGame::~CGame()
{
    
    //cout << "adasd" << endl;
    delete world;
    delete camrednerer;
    delete localplayer;
    delete hud;
    delete assets;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
