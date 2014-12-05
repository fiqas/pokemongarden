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

	theSwitchboard.SubscribeTo(this, "GoingLeft");
	theSwitchboard.SubscribeTo(this, "GoingRight");
	theSwitchboard.SubscribeTo(this, "GoingUp");
	theSwitchboard.SubscribeTo(this, "GoingDown");
	theSwitchboard.SubscribeTo(this, "PathPointReached");  //Osi�gni�cie wierzcho�ka grafu
	theSwitchboard.SubscribeTo(this, "EndPointReached");   //Zako�czenie wyznaczonej �cie�ki
	theSwitchboard.SubscribeTo(this, "MouseDown");		   //Naci�ni�cie przycisku myszy 	

}

void Pikachu::GoTo(Vector2 newDestination) { 

	//Funkcja tworz�ca �cie�k�

	Vector2List pathTest;

	theSpatialGraph.GetPath(GetPosition(), newDestination, pathTest);
	
	if (pathTest.size() > 0) {

		_pathPoints = pathTest;
		_pathIndex = 0;
		GetToNextPoint();

	}

}

void Pikachu::GetToNextPoint() { 

	//Ta funkcja jest odpowiedzialna za puszczanie odpowiedniej animacji, 
	//przenoszenie Pikachu z jednego wierzcho�ka do drugiego.

	Vector2 next = _pathPoints[++_pathIndex];
	distance = Vector2::Distance(_position, next);
	time = distance / 4.0f;
	angle = Angle(Vector2(GetPosition().X,GetPosition().Y), next);

	std::cout << angle << std::endl;
	

	//Opracowanie w kt�r� stron� Pikachu wykona ruch.

	if (GetPosition().X < next.X) {
		
		std::cout << " Right " << std::endl;
		theSwitchboard.Broadcast(new Message("GoingRight"));

		if (angle >= 315 && angle < 360 || angle >= 0 && angle < 45) {

			std::cout << " Right " << std::endl;
			theSwitchboard.Broadcast(new Message("GoingRight"));

		}

	}

	else if (angle >= 45 && angle < 135) {

		std::cout << " Up "<< std::endl;
		theSwitchboard.Broadcast(new Message("GoingUp"));

	}

	else if (GetPosition().X > next.X) {

		std::cout << " Left "<< std::endl;
		theSwitchboard.Broadcast(new Message("GoingLeft"));
	
		if (angle >= 135 && angle < 225) {

			std::cout << " Left "<< std::endl;
			theSwitchboard.Broadcast(new Message("GoingLeft"));

		}
	
	}

	else if (angle >= 225 && angle < 315) {

		std::cout << " Down "<< std::endl;
		theSwitchboard.Broadcast(new Message("GoingDown"));

	}
	
	else {

		std::cout << " stoi "<< std::endl;
		theSwitchboard.Broadcast(new Message("Standing"));

	}

	MoveTo(next, time, false, "PathPointReached");

}

double Pikachu::Angle(Vector2 position, Vector2 destination) {

	//Funkcja obliczaj�ca k�t mi�dzy dwoma wektorami - jednym kt�ry zawiera punkt przechodz�cy przez obecn� poz. Pikachu
	//oraz drugi zawieraj�cy wierzcho�ek docelowy.

	scalar = position.X * destination.X + position.Y * destination.Y;
    positionlength = sqrt(pow(position.X, 2) + pow(position.Y, 2));
    destinationlength = sqrt(pow(destination.X, 2) + pow(destination.Y, 2));
    cosinus = scalar / (positionlength * destinationlength);

	if ( destination.Y < position.Y)  angle = 360 - acos(cosinus) * 180 / M_PI;
    else angle = acos(cosinus) * 180 / M_PI;
	
	return angle;

}


void Pikachu::Update(float dt) {	

	Actor::Update(dt);

}

void Pikachu::ReceiveMessage(Message* message) {

	if ( (message->GetMessageName() == "PathPointReached") && (message->GetSender() == this) ) { 

		//Zosta�a odebrana wiadomo�� o dotarciu do wierzcho�ka grafu, ktory jest zawarty w naszej �cie�ce.
		
		if (_pathIndex < _pathPoints.size() - 1) {

			//Przechodzenie do kolejnych punkt�w

			GetToNextPoint();

		}

		else {

			//Kiedy przeszli�my przez wszystkie wierzcho�ki na naszej �cie�ce.

			theSwitchboard.Broadcast(new Message("EndPointReached", this));
			_pathPoints.clear();
			_pathIndex = 0;

		}

	}

	else if (message->GetMessageName() == "EndPointReached") {

			//Kiedy dotrzemy do celu warto by�oby zastopowa� animacj�, w tym celu ustawiona zostaje odpowiednia klatka
			//w zale�no�ci od kierunku poruszania si� postaci.

			if (walkingright) {

				PlaySpriteAnimation(0.1f, SAT_Loop, 13, 13);						

			}

			else if (walkingleft) {

				PlaySpriteAnimation(0.1f, SAT_Loop, 9, 9);
				
			}

			else if (walkingup) {
				
				PlaySpriteAnimation(0.1f, SAT_Loop, 5, 5);

			}

			else {

				PlaySpriteAnimation(0.1f, SAT_Loop, 1, 1);

			}

	}


	else if (message->GetMessageName() == "MouseDown") { 

		TypedMessage<Vec2i> *m = (TypedMessage<Vec2i>*)message;
		Vec2i screenCoordinates = m->GetValue();
		Vector2 worldCoordinates = MathUtil::ScreenToWorld(screenCoordinates);
		GoTo(worldCoordinates);

	}

	// Poni�sze funkcje ustawiaj� warto�ci true/false dotycz�ce kierunku poruszania si� postaci
	// a tak�e graj� odpowiedni� animacj�.

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

// Gatunki pokemon�w, koordynaty i teksty.