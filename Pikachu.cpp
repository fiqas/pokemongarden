#include "stdafx.h"
#include "Pikachu.h"

//SIEMKA <3


Pikachu::Pikachu(void) {

	SetName("Pikachu");
	LoadSpriteFrames("Resources/Images/pikachu/pikachu_001.png", GL_CLAMP, GL_LINEAR);
	SetSpriteFrame(0);
	SetDensity(0.8f);
	SetFriction(10.0f);
	SetRestitution(0.7f);
	SetFixedRotation(true);
	SetShapeType(PhysicsActor::SHAPETYPE_BOX);
	SetPosition(0.0f, 0.0f);
	SetLayer(3);
	InitPhysics();
	theSwitchboard.SubscribeTo(this, "GoLeft");
	theSwitchboard.SubscribeTo(this, "GoRight");
	theSwitchboard.SubscribeTo(this, "GoFront");
	theSwitchboard.SubscribeTo(this, "GoBack");

}

void Pikachu::Update(float dt) {	

	PhysicsActor::Update(dt);
	b2Vec2 currentVelocity = GetBody()->GetLinearVelocity();
	float maxVel = theTuning.GetFloat("PikachuMaxSpeed");
	float xVector = 0.0f; 
	float yVector = 0.0f;
	float impulseY = 0.0f;
	float impulseX = 0.0f;

	if(theInput.IsKeyDown(ANGEL_KEY_RIGHTARROW)) {

		theSwitchboard.Broadcast(new Message("GoRight"));
		xVector = 2.0f;

	}

	else if(theInput.IsKeyDown(ANGEL_KEY_LEFTARROW)) {

		theSwitchboard.Broadcast(new Message("GoLeft"));
		xVector = -2.0f;

	}

	else if(theInput.IsKeyDown(ANGEL_KEY_UPARROW)) {

		theSwitchboard.Broadcast(new Message("GoFront"));
		yVector = 2.0f;

	}

	else if(theInput.IsKeyDown(ANGEL_KEY_DOWNARROW)) {

		theSwitchboard.Broadcast(new Message("GoBack"));
		yVector = -2.0f;

	}

	else {
		
	theSwitchboard.Broadcast(new Message("NotMoving"));

	}

	impulseY = GoUpDown(yVector, currentVelocity);
	impulseX = GoLeftRight(xVector, currentVelocity);

	ApplyLinearImpulse(Vector2(impulseX, 0), Vector2());
	ApplyLinearImpulse(Vector2(0, impulseY), Vector2());

}

float Pikachu::GoUpDown(float yVector, b2Vec2 currentVelocity) {

	float maxVel = theTuning.GetFloat("PikachuMaxSpeed"); 
	float desiredVelocityY = yVector * maxVel;	
	float velocityChangeY = desiredVelocityY - currentVelocity.y;
	float impulseY = GetBody()->GetMass() * velocityChangeY;

	return impulseY;

}

float Pikachu::GoLeftRight(float xVector, b2Vec2 currentVelocity) {

	float maxVel = theTuning.GetFloat("PikachuMaxSpeed"); 
	float desiredVelocity = xVector * maxVel;	
	float velocityChangeX = desiredVelocity - currentVelocity.x;
	float impulseX = GetBody()->GetMass() * velocityChangeX;

	return impulseX;

}


void Pikachu::ReceiveMessage(Message* message) {

	String message_info = message->GetMessageName();

	if(message_info == "GoFront") {

		PlaySpriteAnimation(0.1f, SAT_OneShot, 4, 6, "WalkingFront");

	}

	if(message_info == "GoBack") {

		PlaySpriteAnimation(0.1f, SAT_OneShot, 0, 3, "WalkingBack");

	}


	if(message_info == "GoLeft") {

		PlaySpriteAnimation(0.1f, SAT_OneShot, 8, 11, "WalkingLeft");

	}

	if(message_info == "GoRight") {

		PlaySpriteAnimation(0.1f, SAT_OneShot, 12, 15, "WalkingRight");

	}

}

Pikachu::~Pikachu(void) {

}

void Pikachu::Render() {

	PhysicsActor::Render();

}