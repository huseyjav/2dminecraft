#pragma once
#include "SDL2/SDL.h"
#include "tile.h"
#include "utils.h"

#include "renderable.h"

class CWorld;

class CCameraRenderer{
public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    CWorld* world;
    int centerX, centerY; //world pos of where camera is 

    
    CCameraRenderer(SDL_Window* window,SDL_Renderer* renderer,CWorld* world);
    
    void centerTo(int x, int y);


    /// @brief return leftmost tile to render
    int getLeftmosttile();
    
    /// @brief return rightmost tile to render
    int getRightmosttile();
    
    /// @brief return topmost tile to render
    int getTopmosttile();

    /// @brief return bottom tile to render
    int getBottomtile();
    
    /**
     * @brief converts position in world to screen
     * 
     * @param worldpos 
     * @return vector2 
     */
    vector2 worldtoscreen(vector2 worldpos);

    vector2 screentoworld(vector2 screenpos);

    //void renderTile(CTile* tile);

    
};