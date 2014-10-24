#include "stdafx.h"
#include "Pokemon.h"


Pokemon::Pokemon(float x, float y , String pathName, int frameNumber)
{
	SetLayer(3);
	SetSize(1.2f, 1.3f);
	SetDensity(0.0f); // jest nieruchomy
	SetFriction(0.0f); // tarcie wynosi 0, rzecz jasna.
	SetRestitution(0.1f); // pikaczu lekko siê odbije.
	SetPosition(x,y);
	LoadSpriteFrames(pathName, GL_CLAMP, GL_LINEAR);
	SetSpriteFrame(frameNumber);
	InitPhysics();
}


Pokemon::~Pokemon(void)
{
}
