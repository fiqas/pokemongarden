#pragma once
class CollisionManager : public PhysicsActor
{
public:

	CollisionManager(float x, float y ,  float sx, float sy, 
					 String name, String colortag, String nametag, String typetag,
					 Vector2 opposite, Vector2 behind, Vector2 side );

	~CollisionManager(void);

	Vector2 SideLeftOrRight;
	Vector2 SideBack;
	Vector2 SideOpposite;
};

