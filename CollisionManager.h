#pragma once
class CollisionManager : public PhysicsActor
{
public:
	CollisionManager(float x, float y ,  float sx, float sy, String name, String colortag, String nametag, String typetag, String actiontag);
	~CollisionManager(void);
};

