#include "stdafx.h"
#include "Object.h"


Object::Object(float x, float y , String pathName, int frameNumber, float sx, float sy, String name)
{
	SetName(name);
	SetLayer(3);
	SetPosition(x, y);
	LoadSpriteFrames(pathName, GL_CLAMP, GL_LINEAR);
	SetSpriteFrame(frameNumber);
	SetSize(sx, sy);
}


Object::~Object(void)
{
}
