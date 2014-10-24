#pragma once

class Pikachu : public PhysicsActor {
public:
	Pikachu();
	virtual ~Pikachu();

	virtual void Update(float dt);
	virtual void Render();

};

