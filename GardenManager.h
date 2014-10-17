#pragma once
#include "Pikachu.h"
#include "Pokemon.h"
#include "Object.h"

//centrum dowodzenia gr�

class GardenManager : public GameManager {
public:
	GardenManager(void);
	virtual ~GardenManager(void);
	Pikachu* pikachu;
	Pokemon *squirtle;
	Object *tree;
};

