#pragma once
#include "stdafx.h"

class Pikachu : public Actor, public MouseListener {
public:
	Pikachu();
	virtual ~Pikachu();
	
	void Update(float dt);
	void Render();
	void ReceiveMessage(Message* message);

	void GetToNextPoint();
	void GoTo(Vector2 newDestination);
	void Fight();
	void Talk();
	void Text(String display_text);
	virtual void MouseDownEvent(Vec2i screenCoordinates, MouseButtonInput button);

	double scalar;
    double positionlength;
    double destinationlength;
    double cosinus;
    double angle;
	float time;
	float distance;
	double Angle(Vector2 position, Vector2 destination);
	Vector2 currentPosition;

	bool walkingright;
	bool walkingleft;
	bool walkingup;
	bool walkingdown;

	String pathName;
	String pokemonType;
	String pokemonName;
	Actor* actioner;

	AngelSampleHandle happyPikachuSound;
	AngelSampleHandle sadPikachuSound;
	AngelSampleHandle battleSound;
	AngelSampleHandle pikachuTalking;
	AngelSampleHandle pikachuDialoguePokemon;

	Vector2List _pathPoints; 
	unsigned int _pathIndex; 

	FullScreenActor* chat_screen;
	TextActor* chat;
	bool fightMode;
	bool talkMode;

};

