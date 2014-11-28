#include "stdafx.h"
#include "Pikachu.h"

Pikachu::Pikachu(void) {

	//ustawienia pikachu

	SetName("Pikachu");
	SetPosition(0,0);
	LoadSpriteFrames("Resources/Images/pikachu/pikachu_001.png", GL_CLAMP, GL_LINEAR);
	SetSpriteFrame(2);
	SetLayer(2);
<<<<<<< HEAD

	walkingright = false;
	walkingleft = false;
	walkingup = false;
	walkingdown = false;
	_pathIndex = 0;
=======
>>>>>>> origin/master

	//reaguje na dane komunikaty

	theSwitchboard.SubscribeTo(this, "GoLeft");
	theSwitchboard.SubscribeTo(this, "GoRight");
	theSwitchboard.SubscribeTo(this, "GoFront");
	theSwitchboard.SubscribeTo(this, "GoBack");
<<<<<<< HEAD
	theSwitchboard.SubscribeTo(this, "PathPointReached");
	theSwitchboard.SubscribeTo(this, "MouseDown");

}

void Pikachu::GoTo(Vector2 newDestination) { 

	Vector2List pathTest;

	theSpatialGraph.GetPath(GetPosition(), newDestination, pathTest);
	
	if (pathTest.size() > 0) {
=======
>>>>>>> origin/master

		_pathPoints = pathTest;
		_pathIndex = 0;
		GetToNextPoint();

	}
}

<<<<<<< HEAD
void Pikachu::GetToNextPoint() { 

	Vector2 next = _pathPoints[++_pathIndex];
	distance = Vector2::Distance(_position, next);
	time = distance / 4.0f;
	angle = Angle(new Vector(10, 0), next);
=======
	Actor::Update(dt);
>>>>>>> origin/master

	std::cout << "next " << next.X << " " << next.Y << std::endl;
	std::cout << angle << std::endl;

<<<<<<< HEAD
	if (angle >= 315 && angle < 45) {
=======
		theSwitchboard.Broadcast(new Message("GoRight"));
>>>>>>> origin/master

		theSwitchboard.Broadcast(new Message("GoingRight"));
	}

	else if (angle >= 45 && angle < 135) {

<<<<<<< HEAD
		theSwitchboard.Broadcast(new Message("GoingUp"));
=======
		theSwitchboard.Broadcast(new Message("GoLeft"));
>>>>>>> origin/master

	}

	else if (angle >= 135 && angle < 225) {

<<<<<<< HEAD
		theSwitchboard.Broadcast(new Message("GoingLeft"));
=======
		theSwitchboard.Broadcast(new Message("GoFront"));
>>>>>>> origin/master

	}

	else if (angle >= 225 && angle < 315) {

<<<<<<< HEAD
		theSwitchboard.Broadcast(new Message("GoingDown"));
=======
		theSwitchboard.Broadcast(new Message("GoBack"));
>>>>>>> origin/master

	}

	else {
<<<<<<< HEAD
=======
		
		theSwitchboard.Broadcast(new Message("NotMoving"));
>>>>>>> origin/master

		theSwitchboard.Broadcast(new Message("Standing"));

<<<<<<< HEAD
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
=======
}

void Pikachu::ReceiveMessage(Message* message) {

	String message_info = message->GetMessageName();
	Vector2 current_position = GetPosition();
>>>>>>> origin/master

	else if (message->GetMessageName() == "EndPointReached") {

<<<<<<< HEAD
			if (walkingright) {
=======
		current_position.Y = current_position.Y + 1.0f;
		PlaySpriteAnimation(0.1f, SAT_OneShot, 4, 6, "WalkingFront");
		MoveTo(current_position, 0.3f, false, "WentFront");
>>>>>>> origin/master

				SetSpriteFrame(13);

			}

<<<<<<< HEAD
			else if (walkingleft) {
=======
		current_position.Y = current_position.Y - 1.0f;
		PlaySpriteAnimation(0.1f, SAT_OneShot, 0, 3, "WalkingBack");
		MoveTo(current_position, 0.3f, false, "WentBack");
>>>>>>> origin/master

				SetSpriteFrame(9);

			}

			else if (walkingup) {

<<<<<<< HEAD
				SetSpriteFrame(5);

			}

			else {

				SetSpriteFrame(1);

			}
=======

	if(message_info == "GoLeft") {

		current_position.X = current_position.X - 1.0f;
		PlaySpriteAnimation(0.1f, SAT_OneShot, 8, 11, "WalkingLeft");
		MoveTo(current_position, 0.3f, false, "WentLeft");
>>>>>>> origin/master

	}


<<<<<<< HEAD
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
=======
		current_position.X = current_position.X + 1.0f;
		PlaySpriteAnimation(0.1f, SAT_OneShot, 12, 15, "WalkingRight");
		MoveTo(current_position, 0.3f, false, "WentRight");

	}

>>>>>>> origin/master

	}

	else if (message->GetMessageName() == "GoingLeft") {

<<<<<<< HEAD
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

=======
	Actor::Render();

}

Pikachu::~Pikachu(void) {

>>>>>>> origin/master
}