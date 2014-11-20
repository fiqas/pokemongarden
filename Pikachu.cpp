#include "stdafx.h"
#include "Pikachu.h"

Pikachu::Pikachu(void) {

	//ustawienia pikachu

	SetName("Pikachu");
	SetPosition(0,0);
	LoadSpriteFrames("Resources/Images/pikachu/pikachu_001.png", GL_CLAMP, GL_LINEAR);
	SetSpriteFrame(2);
	SetLayer(2);

	//reaguje na dane komunikaty

	theSwitchboard.SubscribeTo(this, "GoLeft");
	theSwitchboard.SubscribeTo(this, "GoRight");
	theSwitchboard.SubscribeTo(this, "GoFront");
	theSwitchboard.SubscribeTo(this, "GoBack");

}


void Pikachu::Update(float dt) {	

	Actor::Update(dt);

	if(theInput.IsKeyDown(ANGEL_KEY_RIGHTARROW)) {

		theSwitchboard.Broadcast(new Message("GoRight"));

	}

	else if(theInput.IsKeyDown(ANGEL_KEY_LEFTARROW)) {

		theSwitchboard.Broadcast(new Message("GoLeft"));

	}

	else if(theInput.IsKeyDown(ANGEL_KEY_UPARROW)) {

		theSwitchboard.Broadcast(new Message("GoFront"));

	}

	else if(theInput.IsKeyDown(ANGEL_KEY_DOWNARROW)) {

		theSwitchboard.Broadcast(new Message("GoBack"));

	}

	else {
		
		theSwitchboard.Broadcast(new Message("NotMoving"));

	}

}

void Pikachu::ReceiveMessage(Message* message) {

	String message_info = message->GetMessageName();
	Vector2 current_position = GetPosition();

	if(message_info == "GoFront") {

		current_position.Y = current_position.Y + 1.0f;
		PlaySpriteAnimation(0.1f, SAT_OneShot, 4, 6, "WalkingFront");
		MoveTo(current_position, 0.3f, false, "WentFront");

	}

	if(message_info == "GoBack") {

		current_position.Y = current_position.Y - 1.0f;
		PlaySpriteAnimation(0.1f, SAT_OneShot, 0, 3, "WalkingBack");
		MoveTo(current_position, 0.3f, false, "WentBack");

	}


	if(message_info == "GoLeft") {

		current_position.X = current_position.X - 1.0f;
		PlaySpriteAnimation(0.1f, SAT_OneShot, 8, 11, "WalkingLeft");
		MoveTo(current_position, 0.3f, false, "WentLeft");

	}

	if(message_info == "GoRight") {

		current_position.X = current_position.X + 1.0f;
		PlaySpriteAnimation(0.1f, SAT_OneShot, 12, 15, "WalkingRight");
		MoveTo(current_position, 0.3f, false, "WentRight");

	}


}

void Pikachu::Render() {

	Actor::Render();

}

Pikachu::~Pikachu(void) {

}