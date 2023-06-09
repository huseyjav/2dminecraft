#pragma once
#include "player.h"
#include "renderable.h"
#include "SDL2/SDL.h"

class CHud : public CRenderable{
public:
    CPlayer* localplayer;
    CHud() = default;
    CHud(CPlayer* localplayer);
    void render(CCameraRenderer* camrenderer) override;
    void renderhealth(CCameraRenderer* camrenderer);
    void renderhotbar(CCameraRenderer* camrenderer);

    virtual ~CHud();
};
