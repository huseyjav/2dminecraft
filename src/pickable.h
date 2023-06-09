#pragma once
#include "entity.h"



class CPickable : public CEntity{
public:
    int stackcount;
    virtual void update() override;
};