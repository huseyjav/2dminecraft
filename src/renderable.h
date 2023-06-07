#pragma once
#include "renderer.h"


class CCameraRenderer;


class CRenderable{
public:
    virtual void render(CCameraRenderer * renderer) = 0;
};