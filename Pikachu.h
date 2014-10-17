#pragma once

class Pikachu : public PhysicsActor {
public:
	Pikachu();
	virtual ~Pikachu();

	bool facing_front;
	bool facing_back;
	bool facing_right;
	bool facing_left;

	virtual void Update(float dt);
	virtual void Render();

	void FlipLeft();
	void FlipRight();
	void FlipFront();
	void FlipBack();
};

