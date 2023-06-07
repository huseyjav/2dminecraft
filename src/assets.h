#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "renderer.h"


class CAssets{
public:
    SDL_Texture* grassblock;
    SDL_Texture* stoneblock;

    SDL_Texture* player_sprite;

    CAssets(CCameraRenderer* renderer);
};
