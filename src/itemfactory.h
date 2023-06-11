#pragma once
#include "melee.h"
#include "constids.h"
#include <fstream>


CItem* makeitem(itemID id);



CItem* extractfromfile(ifstream& is);

CEntity* extractentityfromfile(ifstream& is,CWorld* world);