#pragma once
#include <SDL2/SDL.h>
#include "world.h"
#include "renderer.h"
#include "entity.h"
#include "player.h"
#include "hud.h"
#include "npc.h"
#include "assets.h"
class CEntity;


class CGame{
public:
    SDL_Event events;
    bool isRunning=true;
    int state=0;
    CWorld* world=nullptr;
    static unsigned int tick;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    CCameraRenderer* camrednerer = nullptr;
    CPlayer* localplayer = nullptr;
    CHud* hud=nullptr;
    CAssets* assets=nullptr;
    const char* filename = "";
    CGame();
    CGame(const char* savefile);
    void writesavefile();
    void loop();
    void handleinputs();
    
    ~CGame();

};
