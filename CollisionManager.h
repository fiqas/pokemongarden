#pragma once
class CollisionManager : public PhysicsActor
{
public:

	void AddTags(String pathTag);

	CollisionManager(float x, float y ,  float sx, float sy, 
					 String pathTag,
					 Vector2 opposite, Vector2 behind, Vector2 side );

	~CollisionManager(void);

	Vector2 _side;
	Vector2 _behind;
	Vector2 _front;
};
