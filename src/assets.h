#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class CCameraRenderer;
/**
 * @brief class used to cache assets
 * 
 */
class CAssets{
public:
    SDL_Texture* grassblock;
    SDL_Texture* stoneblock;
    SDL_Texture* fist;
    SDL_Texture* player_sprite;
    SDL_Texture* sword;
    SDL_Texture* meat;
    CAssets(CCameraRenderer* renderer);
    ~CAssets();
};
