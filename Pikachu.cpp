#include "stdafx.h"
#include "Pikachu.h"

Pikachu::Pikachu(void) {

	//ustawienia pikachu

	SetName("Pikachu");
	SetPosition(0,0);
	LoadSpriteFrames("Resources/Images/pikachu/pikachu_001.png", GL_CLAMP, GL_LINEAR);
	SetSpriteFrame(2);
	SetLayer(2);

	walkingright = false;
	walkingleft = false;
	walkingup = false;
	walkingdown = false;
	_pathIndex = 0;

	//reaguje na dane komunikaty

	theSwitchboard.SubscribeTo(this, "GoLeft");
	theSwitchboard.SubscribeTo(this, "GoRight");
	theSwitchboard.SubscribeTo(this, "GoFront");
	theSwitchboard.SubscribeTo(this, "GoBack");
	theSwitchboard.SubscribeTo(this, "PathPointReached");
	theSwitchboard.SubscribeTo(this, "MouseDown");

}

void Pikachu::GoTo(Vector2 newDestination) { 

	Vector2List pathTest;

	theSpatialGraph.GetPath(GetPosition(), newDestination, pathTest);
	
	if (pathTest.size() > 0) {

		_pathPoints = pathTest;
		_pathIndex = 0;
		GetToNextPoint();

	}
}

void Pikachu::GetToNextPoint() { 

	Vector2 next = _pathPoints[++_pathIndex];
	distance = Vector2::Distance(_position, next);
	time = distance / 4.0f;
	angle = Angle(new Vector(10, 0), next);

	std::cout << "next " << next.X << " " << next.Y << std::endl;
	std::cout << angle << std::endl;

	if (angle >= 315 && angle < 45) {

		theSwitchboard.Broadcast(new Message("GoingRight"));
	}

	else if (angle >= 45 && angle < 135) {

		theSwitchboard.Broadcast(new Message("GoingUp"));

	}

	else if (angle >= 135 && angle < 225) {

		theSwitchboard.Broadcast(new Message("GoingLeft"));

	}

	else if (angle >= 225 && angle < 315) {

		theSwitchboard.Broadcast(new Message("GoingDown"));

	}

	else {

		theSwitchboard.Broadcast(new Message("Standing"));

	}

	MoveTo(next, time, false, "PathPointReached");

}

double Pikachu::Angle(Vector2 position, Vector2 destination) {

	scalar = position.X * destination.X + position.Y * destination.Y;
    positionlength = sqrt(pow(position.X, 2) + pow(position.Y, 2));
    destinationlength = sqrt(pow(destination.X, 2) + pow(destination.Y, 2));
    cosinus = scalar / (positionlength * destinationlength);
	
	return acos(cosinus) * 180 / M_PI;

}


void Pikachu::Update(float dt) {	

	Actor::Update(dt);

}

void Pikachu::ReceiveMessage(Message* message) {

	if ( (message->GetMessageName() == "PathPointReached") && (message->GetSender() == this) ) { 

		if (_pathIndex < _pathPoints.size() - 1) {

			GetToNextPoint();

		}

		else {

			theSwitchboard.Broadcast(new Message("EndPointReached", this));
			_pathPoints.clear();
			_pathIndex = 0;

		}

	}

	else if (message->GetMessageName() == "EndPointReached") {

			if (walkingright) {

				SetSpriteFrame(13);

			}

			else if (walkingleft) {

				SetSpriteFrame(9);

			}

			else if (walkingup) {

				SetSpriteFrame(5);

			}

			else {

				SetSpriteFrame(1);

			}

	}


	else if (message->GetMessageName() == "MouseDown") { 

		TypedMessage<Vec2i> *m = (TypedMessage<Vec2i>*)message;
		Vec2i screenCoordinates = m->GetValue();
		Vector2 worldCoordinates = MathUtil::ScreenToWorld(screenCoordinates);
		GoTo(worldCoordinates);

	}

	else if (message->GetMessageName() == "GoingRight") {

		walkingright = true;
		walkingleft = false;
		walkingup = false;
		walkingdown = false;
		PlaySpriteAnimation(time, SAT_PingPong, 12, 15, "WalkingRight");

	}

	else if (message->GetMessageName() == "GoingUp") {

		walkingright = false;
		walkingleft = false;
		walkingup = true;
		walkingdown = false;
		PlaySpriteAnimation(time, SAT_PingPong, 4, 6, "WalkingFront");

	}

	else if (message->GetMessageName() == "GoingLeft") {

		walkingright = false;
		walkingleft = true;
		walkingup = false;
		walkingdown = false;
		PlaySpriteAnimation(time, SAT_PingPong, 8, 11, "WalkingLeft");

	}

	else if (message->GetMessageName() == "GoingDown") {

		walkingright = false;
		walkingleft = false;
		walkingup = false;
		walkingdown = true;
		PlaySpriteAnimation(time, SAT_PingPong, 0, 3, "WalkingBack");

	}

}

void Pikachu::Render() {

	Actor::Render();

}

Pikachu::~Pikachu(void) {

}