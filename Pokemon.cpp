#include "stdafx.h"
#include "Pokemon.h"


Pokemon::Pokemon(float x, float y, float sizex, float sizey, String pathName) {
	
	SetLayer(3);
	SetSize(sizex, sizey);
	SetPosition(x,y);
	LoadSpriteFrames(pathName, GL_CLAMP, GL_LINEAR);
	SetSpriteFrame(0);

}


Pokemon::~Pokemon(void)
{
}
