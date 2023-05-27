#pragma once
#include <SDL2/SDL.h>
#include "world.h"
#include "renderer.h"
#include "entity.h"
#include "player.h"
#include "hud.h"


class CEntity;


class CGame{
    SDL_Event events;
    bool isRunning=true;
    int state=0;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    CCameraRenderer* camrednerer = nullptr;
    CPlayer* localplayer = nullptr;
public:
    CWorld* world;
    CHud* hud;
    CGame();
    void loop();
    void handleinputs();
    
    ~CGame();

};