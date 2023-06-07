#pragma once
#include <SDL2/SDL.h>
#include "world.h"
#include "renderer.h"
#include "entity.h"
#include "player.h"
#include "hud.h"
#include "npc.h"

class CEntity;


class CGame{
public:
    SDL_Event events;
    bool isRunning=true;
    int state=0;
    CWorld* world;
    static unsigned int tick;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    CCameraRenderer* camrednerer = nullptr;
    CPlayer* localplayer = nullptr;
    CHud* hud=nullptr;
    
    CGame();
    void loop();
    void handleinputs();
    
    ~CGame();

};
