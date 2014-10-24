#include "stdafx.h"
#include "Pikachu.h"

//Do ogarniecia, wklecenie 3adnej animacji jak Pikaczu sie rusza, dodatkowo niech uderza w pien drzewa a nie w ca3e, ?eby to mia3o
//rece i nogi.

Pikachu::Pikachu(void) {

	SetName("Pikachu");
	LoadSpriteFrames("Resources/Images/pikachu/pikachu_001.png", GL_CLAMP, GL_LINEAR);
	SetSpriteFrame(0);
	SetDensity(0.8f);
	SetFriction(10.0f);
	SetRestitution(0.7f);
	SetFixedRotation(true); //Pikaczu nie ma rotacji.
	SetShapeType(PhysicsActor::SHAPETYPE_BOX);
	SetPosition(0.0f, 0.0f);
	SetLayer(3);
	InitPhysics();

}

void Pikachu::Update(float dt) {	

	PhysicsActor::Update(dt);

	b2Vec2 currentVelocity = GetBody()->GetLinearVelocity(); // jak sama nazwa wskazuje.
	Vector2 vel(currentVelocity.x, currentVelocity.y);
	
	float maxVel = theTuning.GetFloat("PikachuMaxSpeed"); // plik o nazwie tuning w configu, 3adnie zebrane ró?ne zmienne
	float xVector = 0.0f; 
	float yVector = 0.0f;

	if(theInput.IsKeyDown(ANGEL_KEY_RIGHTARROW)) {

		xVector = 2.0f;

		PlaySpriteAnimation(0.1f, SAT_OneShot, 12, 15, "walkingRight"); 

	}

	if(theInput.IsKeyDown(ANGEL_KEY_LEFTARROW)) {

		xVector = -2.0f;

		PlaySpriteAnimation(0.1f, SAT_OneShot, 8, 11, "walkingLeft"); 

	}

	//Ruch poziomo
	float desiredVelocity = xVector * maxVel;	
	float velocityChangeX = desiredVelocity - currentVelocity.x;
	float impulseX = GetBody()->GetMass() * velocityChangeX;
	ApplyLinearImpulse(Vector2(impulseX, 0), GetPosition());

	if(theInput.IsKeyDown(ANGEL_KEY_UPARROW)) {
	
		yVector = 2.0f;

		PlaySpriteAnimation(0.1f, SAT_OneShot, 4, 7, "walkingUp"); 

	}

	if(theInput.IsKeyDown(ANGEL_KEY_DOWNARROW)) {

		yVector = -2.0f;

		PlaySpriteAnimation(0.1f, SAT_OneShot, 0, 3, "walkingDown"); 

	}

	//Ruch pionowo
	float desiredVelocityY = yVector * maxVel;	
	float velocityChangeY = desiredVelocityY - currentVelocity.y;
	float impulseY = GetBody()->GetMass() * velocityChangeY;
	ApplyLinearImpulse(Vector2(0, impulseY), GetPosition());

}

Pikachu::~Pikachu(void) {

}

void Pikachu::Render() {

	PhysicsActor::Render();

}