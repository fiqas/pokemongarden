#pragma once
class Object : public PhysicsActor
{
public:
	Object(float x, float y , String pathName, int frameNumber, float sx, float sy);
	~Object(void);
};

