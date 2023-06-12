#include "game.h"
#include <iostream>
#include "hostilenpc.h"
#include "fstream"
#include "helperstructs.h"
#include "itemfactory.h"
//#include "utils.h"
using namespace std;

void SaveTilesToFile(ofstream & os, const std::vector<std::vector<CTile>>& tiles) {
    //std::ofstream outputFile(filename, std::ios::binary);

    int numRows = tiles.size();
    int numCols = (numRows > 0) ? tiles[0].size() : 0;
    os.write(reinterpret_cast<const char*>(&numRows), sizeof(int));
    os.write(reinterpret_cast<const char*>(&numCols), sizeof(int));

    for (const auto& row : tiles) {
        for (const auto& tile : row) {
            os.write(reinterpret_cast<const char*>(&tile), sizeof(CTile));
        }
    }

}



CGame::CGame() 
{
    //tick=0;
    // spawn player in middle of world
    // set camera to render
    world = new CWorld(100, 20);
    localplayer = new CPlayer(600, 600, 70, 195,10, world);
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

CGame::CGame(const char* savefile){
    filename = savefile;
    auto is = ifstream(filename,ios_base::binary);
    if(!is){
        world = new CWorld(100,20);
        localplayer = new CPlayer(603, 600, 70, 195,10, world);
    }
    else{
        world= new CWorld(is);
        playerread playerdata;
        is.read(reinterpret_cast<char*>(&playerdata),sizeof(playerread));
        localplayer = new CPlayer(playerdata,world);
        for(size_t i = 0 ;  i < localplayer->hotbar.size();i++){
            bool exists;
            is.read(reinterpret_cast<char*>(&exists),sizeof(bool));
            if(!exists) continue;

            localplayer->hotbar[i] = extractfromfile(is);
            localplayer->hotbar[i]->owner = localplayer;
        }
    }



    hud = new CHud(localplayer);
    SDL_CreateWindowAndRenderer(1500, 1000, 0, &window, &renderer);
    camrednerer = new CCameraRenderer(window, renderer, world);
    assets = new CAssets(camrednerer);
    world->setplayer(localplayer);

    camrednerer->assets = assets;
    
    while(is.peek()!=EOF){
        world->entities.push_back(extractentityfromfile(is,world));
    }


    is.close();
}

void CGame::writesavefile(){
    ofstream os(filename,ios_base::binary);
    if(!os) return;
    SaveTilesToFile(os,world->tiles);
    playerread a = localplayer->getplayerread();
    os.write(reinterpret_cast<char*>(&a),sizeof(a));
    for(size_t i = 0 ; i < localplayer->hotbar.size() ; i ++){
        bool exists=true;
        if(!localplayer->hotbar[i]){
            exists=false;
            os.write(reinterpret_cast<char*>(&exists),sizeof(bool));
            continue;
        }
        os.write(reinterpret_cast<char*>(&exists),sizeof(bool));
        localplayer->hotbar[i]->savetofile(os);
    }

    for(size_t i = 0 ; i<world->entities.size();i++){
        world->entities[i]->savetofile(os);
    }

    os.close();
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
            writesavefile();
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
   // world->handleInput( camrednerer);
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
