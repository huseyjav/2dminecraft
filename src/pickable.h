#pragma once
#include "entity.h"



class CPickable : public CEntity{
public:

    int stackcount;
    CPickable(entityID id,int x, int y, int w, int h,int velocityX,CWorld* world,int stackcount);
    CPickable(pickableread a,CWorld* world);
    /**
     * @brief returns struct used for saving game state and load for constructor
     * 
     * @return pickableread 
     */
    pickableread getpickablread();
    /**
     * @brief saves information needed to reconstruct class from file
     * 
     * @param os 
     */
    virtual void savetofile(ostream & os) override;
    virtual void update() override;
    virtual void render(CCameraRenderer * renderer) override;
    virtual ~CPickable()=default;
};





SDL_Texture* getentTexture(CEntity* ent,CAssets* assets);