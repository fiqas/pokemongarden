#pragma once
#include "stdafx.h"

//centrum dowodzenia gr¹

class GardenManager : public GameManager {
public:
	GardenManager(void);
	virtual ~GardenManager(void);
	Pikachu* pikachu;
	void CreatePokemon(float x, float y , float sizex, float sizey, String pathName, String name, String colortag, String nametag, String typetag, String actiontag);
	void AddBigTree();
	void AddPokemons();
};

