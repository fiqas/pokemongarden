#pragma once
#include "Pikachu.h"
#include "Pokemon.h"
#include "Object.h"
#include "CollisionManager.h"

//centrum dowodzenia gr¹

class GardenManager : public GameManager {
public:
	GardenManager(void);
	virtual ~GardenManager(void);
	Pikachu* pikachu;
};

