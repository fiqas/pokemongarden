#include "stdafx.h"
#include "GardenManager.h"

GardenManager::GardenManager(void) {
	theWorld.SetupPhysics(Vector2(0.0f, 0.0f));
	theWorld.LoadLevel("pokemon_garden_level");
	Pikachu* pikachu = new Pikachu();
	PhysicsActor *squirtle = (PhysicsActor*)Actor::Create("Squirtle");
	squirtle->InitPhysics();
	theWorld.Add(squirtle);
	theWorld.Add(pikachu);

}


GardenManager::~GardenManager(void) {

}
