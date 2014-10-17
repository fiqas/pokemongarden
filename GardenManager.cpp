#include "stdafx.h"
#include "GardenManager.h"


//blablabla
GardenManager::GardenManager(void) {
	theWorld.LoadLevel("pokemon_garden_level");
	Pikachu* pikachu = new Pikachu();
	Object* tree = new Object( -9.0f, 6.0f, "Resources/Images/objects/bigtree.png", 0, 7.0f, 8.0f );	
	Object *tree1 = new Object( -9.0f, -6.0f, "Resources/Images/objects/tree1.png", 0, 1.0f, 1.0f);
	Object *tree2 = new Object( -9.0f, -7.0f, "Resources/Images/objects/tree2.png", 0, 1.0f, 1.0f);
	Object *tree3 = new Object( -10.0f, -6.0f, "Resources/Images/objects/tree3.png", 0,  1.0f, 1.0f);
	Pokemon* squirtle = new Pokemon( 9.0f, -4.0f, "Resources/Images/pokemons/squirtle.png", 0 );
	theWorld.Add(pikachu);
	theWorld.Add(tree);
	theWorld.Add(tree1);
	theWorld.Add(tree2);
	theWorld.Add(squirtle);
	theWorld.SetupPhysics(Vector2(0.0f, 0.0f));
	theWorld.SetSideBlockers(true, 0.7f);
}


GardenManager::~GardenManager(void) {

}
