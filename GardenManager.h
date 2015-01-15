#pragma once
#include "stdafx.h"

//centrum dowodzenia gr¹

class GardenManager : public GameManager, public MouseListener {

public:

	GardenManager(void);
	virtual ~GardenManager(void);
	
	void CreatePokemon(float x, float y , float sizex, float sizey, String pathName);
	void CreateCollisionManager(float x, float y ,  float sx, float sy, String pathTag, Vector2 oposite, Vector2 side, Vector2 behind);
	void AddCollisionManager();
	void AddPokemons();
	void Update(float dt);
	void ReceiveMessage(Message* message);
	void Text(String display_text);
	void CloseText();

	void Analyze();
	void FindTaggedPokemons(ActorSet& bothTaggedActors, String adjective, String noun);
	void Helper(Vector2 coordinates);
	
	virtual void MouseDownEvent(Vec2i screenCoordinates, MouseButtonInput button);


	Pikachu* pikachu;
	FullScreenActor* text_screen;
	TextActor* text;
	bool close_text_frame;

};

