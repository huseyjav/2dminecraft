#pragma once
enum itemID{
    emptyhand_id,
    sword_id,
    pickaxe_id,
    meat_id,
    grassblock_id
};

enum entityID{
    localplayer_id,
    zombiewithsword_id,
    dropped_sword_id,
    dropped_pickaxe_id,
    dropped_meat_id,
    dropped_grassblock_id
};

enum tileID{
    void_id,
    grass_id
};


entityID getentityID(itemID item);

itemID getitemID(entityID entity);

