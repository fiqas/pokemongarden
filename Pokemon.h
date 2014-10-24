#pragma once
class Pokemon : public PhysicsActor
{
public:
	Pokemon( float x, float y, String pathName, int frameNumber);
	~Pokemon(void);
};

