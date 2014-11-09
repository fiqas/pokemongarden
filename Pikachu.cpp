#include "stdafx.h"
#include "Pikachu.h"

Pikachu::Pikachu(void) {

	//ustawienia pikachu

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

	//reaguje na dane komunikaty

	theSwitchboard.SubscribeTo(this, "GoLeft");
	theSwitchboard.SubscribeTo(this, "GoRight");
	theSwitchboard.SubscribeTo(this, "GoFront");
	theSwitchboard.SubscribeTo(this, "GoBack");
	theSwitchboard.SubscribeTo(this, "GotoSquirtle");
	
	//sensory kontaktu

	b2PolygonShape sensorShape;
	b2FixtureDef sensorFixtureDef;
	sensorFixtureDef.isSensor = true;
	sensorFixtureDef.shape = &sensorShape;

	sensorShape.SetAsBox(0.5f, 0.5f, b2Vec2(0.0f, -(GetSize().Y * 0.5f)), 0.0f);
	_footSensor = GetBody()->CreateFixture(&sensorFixtureDef);
	_footSensor->SetUserData(this);

	sensorShape.SetAsBox(0.5f, 0.5f, b2Vec2(0.0f, (GetSize().Y * 0.5f)), 0.0f); 
	_headSensor = GetBody()->CreateFixture(&sensorFixtureDef);
	_headSensor->SetUserData(this);

	sensorShape.SetAsBox(0.5f, 0.5f, b2Vec2((GetSize().X * 0.5f), 0.0f), 0.0f); 
	_rightSensor = GetBody()->CreateFixture(&sensorFixtureDef);
	_rightSensor->SetUserData(this);

	sensorShape.SetAsBox(0.5f, 0.5f, b2Vec2(-(GetSize().X * 0.5f), 0.0f), 0.0f); 
	_leftSensor = GetBody()->CreateFixture(&sensorFixtureDef);
	_leftSensor->SetUserData(this);

	

}


void Pikachu::Update(float dt) {	

	Sentient::Update(dt);
	//theSwitchboard.Broadcast(new Message("GotoSquirtle"));
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
	
	//Kolizje

	if ( message_info == "CollisionStartWith" + GetName() || message_info == "CollisionEndWith" + GetName()){
		
		TypedMessage<b2Contact*>* contactMessage = (TypedMessage<b2Contact*>*)message;
		b2Contact* contact = contactMessage->GetValue();
		PhysicsActor* other = NULL; // co� z czym si� zderzamy
		b2Fixture* fixture = NULL;

		if (contact->GetFixtureA()->GetUserData() == this) {
			
			other = (PhysicsActor*)contact->GetFixtureB()->GetBody()->GetUserData();
			fixture = contact->GetFixtureA();
		
		}
		
		else {
			
			other = (PhysicsActor*)contact->GetFixtureA()->GetBody()->GetUserData();
			fixture = contact->GetFixtureB();
		
		}
		
		if (other == NULL) {

			return;
	
		}

	}

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

	if(message_info == "GotoSquirtle") {

		std::cout << "Goto" << std::endl;
		//_brain.GotoState("Going to Squirtle");

	}

}

Pikachu::~Pikachu(void) {

}

void Pikachu::Render() {

	Sentient::Render();

}

void Pikachu::InitializeBrain() {

	Pikabrain = &_brain;
	std::cout << Pikabrain->GetActor()->GetName() << std::endl;
	std::cout << _brain.GetActor()->GetName() << std::endl;
	std::cout << "InitializeBrain()" << std::endl;	
	GotoTargetState* gototargetstate = new GotoTargetState("red", 0.2f, Pikabrain);
	_brain.AddState("Going to Squirtle", gototargetstate);
	 //theSwitchboard.Broadcast(new Message("GotoSquirtle"));
	 
}

void Pikachu::StartBrain() {

	std::cout << "StartBrain()" << std::endl;
	BoundingBox bounds(Vector2(-20, -20), Vector2(20, 20));
	theSpatialGraph.CreateGraph(0.75f, bounds);
	_brain.GotoState("Going to Squirtle");

}
