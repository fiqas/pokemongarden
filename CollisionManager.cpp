#include "stdafx.h"

CollisionManager::CollisionManager(float x, float y ,  float sx, float sy, String name, String colortag, String nametag, String typetag, Vector2 front, Vector2 behind, Vector2 side) {

	SetName(name);
	SetLayer(4);
	SetPosition(x, y);
	SetSize(sx, sy);
	SetShapeType(PhysicsActor::SHAPETYPE_BOX);
	SetColor(1.0f, 0.0f, 0.0f);
	SetDensity(0.0f);
	SetFriction(0.0f); 
	SetRestitution(0.1f);
	Tag(colortag);
	Tag(nametag);
	Tag(typetag);
	InitPhysics();

	_side = side;    //Punkt lewy albo prawy
	_behind = behind;		   //Punkt za obiektem
	_front = front;   //Punkt na przeciwko

}

CollisionManager::~CollisionManager(void)
{
}
