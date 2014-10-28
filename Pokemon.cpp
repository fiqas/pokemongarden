#include "stdafx.h"
#include "Pokemon.h"


Pokemon::Pokemon(float x, float y, float sizex, float sizey, String pathName, String name, String colortag, String nametag, String typetag, String actiontag) {
	
	SetName(name);
	SetLayer(3);
	SetSize(sizex, sizey);
	SetDensity(0.0f); 
	SetFriction(0.0f); 
	SetRestitution(0.1f);
	SetPosition(x,y);
	LoadSpriteFrames(pathName, GL_CLAMP, GL_LINEAR);
	SetSpriteFrame(0);
	Tag(colortag);
	Tag(nametag);
	Tag(typetag);
	Tag(actiontag);
	InitPhysics();

}


Pokemon::~Pokemon(void)
{
}
