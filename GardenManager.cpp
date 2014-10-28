#include "stdafx.h"

GardenManager::GardenManager(void) {

	theWorld.SetupPhysics(Vector2(0.0f, 0.0f));
	theWorld.LoadLevel("pokemon_garden_level");
	Pikachu* pikachu = new Pikachu();
	AddPokemons();
	AddBigTree();
	theWorld.Add(pikachu);

}

void GardenManager::CreatePokemon(float x, float y , float sizex, float sizey, String pathName, String name, String colortag, String nametag, String typetag, String actiontag) {

	theWorld.Add(new Pokemon(x, y, sizex, sizey, pathName, name, colortag, nametag, typetag, actiontag));

}

GardenManager::~GardenManager(void) {

}

void GardenManager::AddBigTree() {

	CollisionManager *bigtree = new CollisionManager(-9.0f, 4.5f, 1.0f, 2.0f, "BigTree", "green", "big tree", "tree", "spawned");
	theWorld.Add(bigtree);
}

void GardenManager::AddPokemons() {

	CreatePokemon(-10.0f, 0.0f, 3.2f, 3.3f, "Resources/Images/pokemons/charizard_001.png", "Charizard", "red", "Charizard", "dragon", "spawned");
	CreatePokemon(9.0f, -4.0f, 1.2f, 1.3f, "Resources/Images/pokemons/squirtle_001.png", "Squirtle", "blue", "Squirtle", "turtle", "spawned");
	CreatePokemon(5.0f, 8.0f, 1.4f, 1.5f, "Resources/Images/pokemons/meowth_001.png", "Meowth", "white", "Charizard", "cat", "spawned");
	CreatePokemon(6.0f, 3.0f, 1.6f, 2.0f, "Resources/Images/pokemons/pidgeot_001.png", "Pidgeot", "orange", "Pidgeot", "bird", "spawned");
	CreatePokemon(-5.0f, -5.0f, 1.8f, 1.6f, "Resources/Images/pokemons/raichu_001.png", "Raichu", "yellow", "Raichu", "mouse", "spawned");

}
