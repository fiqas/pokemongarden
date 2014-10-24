#include "stdafx.h"
#include "Pikachu.h"

//Do ogarniêcia, wklecenie ³adnej animacji jak Pikaczu siê rusza, dodatkowo niech uderza w pieñ drzewa a nie w ca³e, ¿eby to mia³o
//rêce i nogi.

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
<<<<<<< HEAD
	InitPhysics();

	facing_front = true;
	facing_back = false;
	facing_right = false;
	facing_left = false;
}

void Pikachu::FlipLeft() {
	SetSpriteFrame(8);
	facing_left = true;
	facing_right = false;
	facing_front = false;
	facing_back = false;
}

void Pikachu::FlipRight() {
	SetSpriteFrame(12);
	facing_left = false;
	facing_right = true;
=======
>>>>>>> origin/master
	facing_front = false;
	facing_back = true;
	facing_right = false;
	facing_left = false;
	InitPhysics();

}

void Pikachu::Update(float dt) {	

	b2Vec2 currentVelocity = GetBody()->GetLinearVelocity(); // jak sama nazwa wskazuje.
	Vector2 vel(currentVelocity.x, currentVelocity.y);
	
	float maxVel = theTuning.GetFloat("PikachuMaxSpeed"); // plik o nazwie tuning w configu, ³adnie zebrane ró¿ne zmienne
	float xVector = 0.0f; 
	float yVector = 0.0f;

	if(theInput.IsKeyDown(ANGEL_KEY_RIGHTARROW)) {
<<<<<<< HEAD
		xVector = 1.0f;

		if(facing_right) {
			PlaySpriteAnimation(0.1f, SAT_OneShot, 12, 15, "walkingRight"); 
		} else {
			FlipRight();
			PlaySpriteAnimation(0.1f, SAT_OneShot, 12, 15, "walkingRight"); 
		}
=======

		facing_front = false;
		facing_back = false;
		facing_right = true;
		facing_left = false;
		xVector = 3.0f;
>>>>>>> origin/master

	}

	if(theInput.IsKeyDown(ANGEL_KEY_LEFTARROW)) {
		
		facing_front = false;
		facing_back = false;
		facing_right = false;
		facing_left = true;
		xVector = -3.0f;

	}

	//Ruch poziomo
	float desiredVelocity = xVector * maxVel;	
	float velocityChangeX = desiredVelocity - currentVelocity.x;
	float impulseX = GetBody()->GetMass() * velocityChangeX;

	if (!IsSpriteAnimPlaying() && facing_left) {
		PlaySpriteAnimation(0.1f, SAT_Loop, 8, 11, "walkingLeft");
	}

	if(IsSpriteAnimPlaying() && impulseX == 0.0f) {

		SetSpriteFrame(9);

	}

	if (!IsSpriteAnimPlaying() && facing_right) {
		PlaySpriteAnimation(0.1f, SAT_Loop, 12, 15, "walkingRight");
	}

	if (!IsSpriteAnimPlaying() && facing_front) {

		std::cout << "front" << std::endl;
		PlaySpriteAnimation(0.1f, SAT_Loop, 4, 7, "walkingUp"); 
	}

	if (!IsSpriteAnimPlaying() && facing_back) {
		std::cout << "back" << std::endl;
		PlaySpriteAnimation(0.1f, SAT_Loop, 0, 3, "walkingDown"); 
	}

	if(theInput.IsKeyDown(ANGEL_KEY_UPARROW)) {
		yVector = 3.0f;

		facing_front = true;
		facing_back = false;
		facing_right = false;
		facing_left = false;

	}

	if(theInput.IsKeyDown(ANGEL_KEY_DOWNARROW)) {
		yVector = -3.0f;

		facing_front = false;
		facing_back = true;
		facing_right = false;
		facing_left = false;

	}
<<<<<<< HEAD

	//Ruch poziomo
	float desiredVelocity = xVector * maxVel;	
	float velocityChange = desiredVelocity - currentVelocity.x;
	float impulse = GetBody()->GetMass() * velocityChange;
	ApplyLinearImpulse(Vector2(impulse, 0), Vector2());
=======
>>>>>>> origin/master

	//Ruch pionowo
	float desiredVelocityY = yVector * maxVel;	
	float velocityChangeY = desiredVelocityY - currentVelocity.y;
	float impulseY = GetBody()->GetMass() * velocityChangeY;

/*	if(impulseY == 0.0f && impulseX == 0.0f && facing_right) {

		SetSpriteFrame(13);

	}


	if(impulseY == 0.0f && impulseX == 0.0f && facing_left) {

		SetSpriteFrame(9);

	}

	if(impulseY == 0.0f && impulseX == 0.0f && facing_front) {

		SetSpriteFrame(6);

	}

	if(impulseY == 0.0f && impulseX == 0.0f && facing_back) {

		SetSpriteFrame(1);

	}
*/
	ApplyLinearImpulse(Vector2(impulseX, 0), GetPosition());
	ApplyLinearImpulse(Vector2(0, impulseY), GetPosition());
	PhysicsActor::Update(dt);

}

Pikachu::~Pikachu(void) {

}

void Pikachu::Render() {

	PhysicsActor::Render();

}
