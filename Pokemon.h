#pragma once
#include "stdafx.h"

class Pokemon : public PhysicsActor
{
public:
	Pokemon(float x, float y, float sizex, float sizey, String pathName, String name, String colortag, String nametag, String typetag, String actiontag);
	~Pokemon(void);

};

