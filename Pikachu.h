#pragma once
#include "stdafx.h"

class Pikachu : public Actor {
public:
	Pikachu();
	virtual ~Pikachu();
	
	void Update(float dt);
	void Render();
	void ReceiveMessage(Message* message);

	Vector2List _pathPoints; 
	unsigned int _pathIndex; 
	void GetToNextPoint();
	void GoTo(Vector2 newDestination);

	double scalar;
    double positionlength;
    double destinationlength;
    double cosinus;
    double angle;
	float time;
	float distance;
	double Angle(Vector2 position, Vector2 destination);

	bool walkingright;
	bool walkingleft;
	bool walkingup;
	bool walkingdown;

};

