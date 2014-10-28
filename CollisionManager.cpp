#include "stdafx.h"
#include "CollisionManager.h"


CollisionManager::CollisionManager(float x, float y ,  float sx, float sy, String name)
{
	SetName(name);
	SetLayer(3);
	SetPosition(x, y);
	SetSize(sx, sy);
	SetShapeType(PhysicsActor::SHAPETYPE_BOX);
	SetColor(1.0f, 0.0f, 0.0f, 0.0f);
	SetDensity(0.0f); // jest nieruchomy
	SetFriction(0.0f); // tarcie wynosi 0, rzecz jasna.
	SetRestitution(0.1f); // pikaczu lekko siê odbije.
	InitPhysics();
	Tag(name);
}

CollisionManager::~CollisionManager(void)
{
}
