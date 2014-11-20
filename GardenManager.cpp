#include "stdafx.h"

GardenManager::GardenManager(void) {

	theWorld.SetupPhysics(Vector2(0.0f, 0.0f));
	theWorld.LoadLevel("pokemon_garden_level");
	Pikachu* pikachu = new Pikachu();
	AddPokemons();
	AddBigTree();
	theWorld.Add(pikachu);
	BoundingBox bounds(Vector2(-20, -20), Vector2(20, 20));
	theSpatialGraph.CreateGraph( 1.0f, bounds);
	theSpatialGraph.EnableDrawGraph(true);

}

void GardenManager::Update(float dt) {

}

void GardenManager::CreatePokemon(float x, float y , float sizex, float sizey, String pathName, String name, String colortag, String nametag, String typetag, String actiontag) {

	theWorld.Add(new Pokemon(x, y, sizex, sizey, pathName, name, colortag, nametag, typetag, actiontag));

}

void GardenManager::CreateCollisionManager(float x, float y ,  float sx, float sy, String name, String colortag, String nametag, String typetag, String actiontag) {

	theWorld.Add(new CollisionManager(x, y , sx, sy, name,colortag, nametag, typetag, actiontag));

}

void GardenManager::AddBigTree() {

	CreateCollisionManager(-9.0f, 3.8f, 1.0f, 0.7f, "BigTree", "green", "big tree", "tree", "spawned");
	CreateCollisionManager(6.5f, -8.0f, 0.3f, 0.7f, "BigTreeHighWithLeaves", "green", "big tree", "tree", "spawned");
	CreateCollisionManager(9.0f, 3.0f, 0.5f, 1.0f, "BigTreeWithLeaves", "green", "big tree", "tree", "spawned");
	CreateCollisionManager(1.0f, 3.0f, 0.5f, 0.5f, "TreeNeadles", "green", "notSoBig", "tree", "spawned");

}

void GardenManager::AddPokemons() {

	CreatePokemon(-11.0f, -7.0f, 1.0f, 1.0f, "Resources/Images/pokemons/jigglypuff.png", "Jigglypuff", "pink", "Jigglypuff", "thing", "spawned" );
	CreatePokemon(3.0f, 8.0f, 1.5f, 1.8f, "Resources/Images/pokemons/victreebel.png", "Victreebel", "yellow", "Victreebel", "flower", "spawned" );
	CreatePokemon(3.0f, 6.0f, 2.1f, 2.5f, "Resources/Images/pokemons/arbok.png", "Arbok", "purple", "Arbok", "snake", "spawned" );
	CreatePokemon(4.0f, -4.0f, 1.5f, 1.5f, "Resources/Images/pokemons/bulbasaur.png", "Bulbasaur", "green", "Bulbasaur", "plant", "spawned" );
	CreatePokemon(-4.0f, 8.0f, 1.5f, 1.5f, "Resources/Images/pokemons/psyduck.png", "Psyduck", "yellow", "Psyduck", "duck", "spawned" );
	CreatePokemon(-3.0f, 0.0f, 1.0f, 1.4f, "Resources/Images/pokemons/rattata.png", "Rattata", "purple", "Rattata", "rat", "spawned" );
	CreatePokemon(11.0f, -5.0f, 1.5f, 1.2f, "Resources/Images/pokemons/slowpoke.png", "Slowpoke", "pink", "Slowpoke", "lazy asshole", "spawned" );
	CreatePokemon(-9.0f, 6.0f, 1.0f, 1.0f, "Resources/Images/pokemons/butterfree.png", "Butterfree", "purple", "Butterfree", "butterfly", "spawned" );
	CreatePokemon(5.0f, 9.0f, 1.6f, 1.5f, "Resources/Images/pokemons/koffing.png", "Koffing", "purple", "Koffing", "ball", "spawned" );
	CreatePokemon(6.0f, 0.0f, 1.8f, 2.0f, "Resources/Images/pokemons/snorlax.png", "Snorlax", "blue-white", "Snorlax", "sleepyhead", "spawned" );
	CreatePokemon(-10.0f, 0.0f, 3.2f, 3.3f, "Resources/Images/pokemons/charizard_001.png", "Charizard", "red", "Charizard", "dragon", "spawned");
	CreatePokemon(9.0f, -1.0f, 1.2f, 1.3f, "Resources/Images/pokemons/squirtle_001.png", "Squirtle", "blue", "Squirtle", "turtle", "spawned");
	CreatePokemon(5.0f, 7.5f, 1.4f, 1.5f, "Resources/Images/pokemons/meowth_001.png", "Meowth", "white", "Meowth", "cat", "spawned");
	CreatePokemon(6.0f, 3.0f, 1.0f, 1.5f, "Resources/Images/pokemons/pidgeot_001.png", "Pidgeot", "orange", "Pidgeot", "bird", "spawned");
	CreatePokemon(-5.0f, -5.0f, 1.8f, 1.6f, "Resources/Images/pokemons/raichu_001.png", "Raichu", "yellow", "Raichu", "mouse", "spawned");

}

GardenManager::~GardenManager(void) {

}
