#pragma once

class Pikachu : public PhysicsActor {
public:
	Pikachu();
	virtual ~Pikachu();

	float GoUpDown(float yVector, b2Vec2 currentVelocity);
	float GoLeftRight(float xVector, b2Vec2 currentVelocity);

	virtual void Update(float dt);
	virtual void Render();
	virtual void ReceiveMessage(Message* message);

};

