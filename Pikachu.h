#pragma once
#include "stdafx.h"

class Pikachu : public PhysicsActor {
public:
	Pikachu();
	virtual ~Pikachu();

	float GoUpDown(float yVector, b2Vec2 currentVelocity);
	float GoLeftRight(float xVector, b2Vec2 currentVelocity);
	
	b2Fixture* _footSensor;
	b2Fixture* _rightSensor;
	b2Fixture* _leftSensor;
	b2Fixture* _headSensor;
	
	GotoSquirtle* gotosquirtle;

	virtual void Update(float dt);
	virtual void Render();
	virtual void ReceiveMessage(Message* message);

};

