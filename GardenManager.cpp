#include "stdafx.h"
#include "GardenManager.h"

GardenManager::GardenManager(void) {

	theWorld.SetupPhysics(Vector2(0.0f, 0.0f));
	theWorld.LoadLevel("pokemon_garden_level");
	
	Pikachu* pikachu = new Pikachu();
	PhysicsActor *squirtle = (PhysicsActor*)Actor::Create("Squirtle");
	
	
	Object *bigTree = new Object(5.0f, 2.0f , "Resources/Images/objects/bigtree.png", 0, 8.0f, 10.0f, "BigTree");
	CollisionManager *bigTreeManager = new CollisionManager (bigTree->GetPosition().X, bigTree->GetPosition().Y-2.0f , 1.0f, 2.0f, "BigTree");
	
	Object *smallTree = new Object(-5.0f, 2.0f , "Resources/Images/objects/tree1.png", 0, 1.0f, 1.0f, "SmallTree");
	CollisionManager *smallTreeManager = new CollisionManager (smallTree->GetPosition().X, smallTree->GetPosition().Y , 0.5f, 0.5f, "SmallTree");
	
	theWorld.Add(pikachu);
	theWorld.Add(bigTree);
	theWorld.Add(smallTree);
	theWorld.Add(squirtle);
}

GardenManager::~GardenManager(void) {
}
