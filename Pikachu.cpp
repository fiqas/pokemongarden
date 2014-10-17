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
	InitPhysics();
	SetPosition(0.0f, 0.0f);
	SetLayer(3);

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
	facing_front = false;
	facing_back = false;
}

void Pikachu::FlipFront() {
	SetSpriteFrame(4);
	facing_left = false;
	facing_right = false;
	facing_front = true;
	facing_back = false;
}

void Pikachu::FlipBack() {
	SetSpriteFrame(0);
	facing_left = false;
	facing_right = false;
	facing_front = false;
	facing_back = true;
}

void Pikachu::Update(float dt) {
	

	b2Vec2 currentVelocity = GetBody()->GetLinearVelocity(); // jak sama nazwa wskazuje.
	
	float maxVel = theTuning.GetFloat("PikachuMaxSpeed"); // plik o nazwie tuning w configu, ³adnie zebrane ró¿ne zmienne
	float xVector = 0.0f; 
	float yVector = 0.0f;

	
	/*if ((currentVelocity.x < 0.0f) && facing_right) FlipLeft();
	else if ((currentVelocity.x > 0.0f) && !facing_right) FlipRight();
	if ((currentVelocity.y < 0.0f) && facing_front) FlipBack();
	else if ((currentVelocity.y > 0.0f) && !facing_front) FlipFront();
	*/
	if(theInput.IsKeyDown(ANGEL_KEY_RIGHTARROW)) {
		xVector = 1.0f;
		
		if(facing_right) {
			PlaySpriteAnimation(0.1f, SAT_OneShot, 12, 15, "walkingRight"); 
		} else {
			FlipRight();
			PlaySpriteAnimation(0.1f, SAT_OneShot, 12, 15, "walkingRight"); 
		}
	}

	if(theInput.IsKeyDown(ANGEL_KEY_LEFTARROW)) {
		xVector = -1.0f;

		if(facing_left) {
			PlaySpriteAnimation(0.1f, SAT_OneShot, 8, 11, "walkingLeft"); 
		} else {
			FlipLeft();
			PlaySpriteAnimation(0.1f, SAT_OneShot, 8, 11, "walkingLeft"); 
		}
	}

	if(theInput.IsKeyDown(ANGEL_KEY_UPARROW)) {
	
		yVector = 1.0f;

		if(facing_front) {
			PlaySpriteAnimation(0.1f, SAT_OneShot, 4, 7, "walkingUp"); 
		} else {
			FlipFront();
			PlaySpriteAnimation(0.1f, SAT_OneShot, 4, 7, "walkingUp"); 
		}
	}

	if(theInput.IsKeyDown(ANGEL_KEY_DOWNARROW)) {
		yVector = -1.0f;

		if(facing_back) {
			PlaySpriteAnimation(0.1f, SAT_OneShot, 0, 3, "walkingDown"); 			
		} else {
			FlipBack();
			PlaySpriteAnimation(0.1f, SAT_OneShot, 0, 3, "walkingDown"); 
		}
	}
	//Ruch poziomo
	float desiredVelocity = xVector * maxVel;	
	float velocityChange = desiredVelocity - currentVelocity.x;
	float impulse = GetBody()->GetMass() * velocityChange;
	ApplyLinearImpulse(Vector2(impulse, 0), Vector2());

	//Ruch pionowo
	float desiredVelocityY = yVector * maxVel;	
	float velocityChangeY = desiredVelocityY - currentVelocity.y;
	float impulseY = GetBody()->GetMass() * velocityChangeY;
	ApplyLinearImpulse(Vector2(0, impulseY), Vector2());
	//Wiem, ¿e wygl¹da jak psu z gard³a ale dzia³y siê cuda jak te rzeczy by³y w warunkach.

	PhysicsActor::Update(dt);
}

Pikachu::~Pikachu(void) {

}

void Pikachu::Render() {

	PhysicsActor::Render();

}
