#pragma once
#include "stdafx.h"

//centrum dowodzenia gr¹

class GardenManager : public GameManager, public MouseListener {

public:

	GardenManager(void);
	virtual ~GardenManager(void);
	
	void CreatePokemon(float x, float y , float sizex, float sizey, String pathName);
	void CreateCollisionManager(float x, float y ,  float sx, float sy, String name, String colortag, String nametag, String typetag, Vector2 oposite, Vector2 side, Vector2 behind);
	void AddCollisionManager();
	void AddPokemons();
	void Update(float dt);
	
	virtual void MouseDownEvent(Vec2i screenCoordinates, MouseButtonInput button);


	Pikachu* pikachu;
};

