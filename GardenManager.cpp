#include "stdafx.h"

GardenManager::GardenManager(void) {

	theWorld.SetupPhysics(Vector2(0.0f, 0.0f));		// Ustawienie fizyki, potrzebne by Pikachu 
	theWorld.LoadLevel("pokemon_garden_level");	    // Wczytujemy plik ze statycznymi elementami œwiata tj. drzewa, p³ot oraz ziemia.
	
	Pikachu* pikachu = new Pikachu();
	
	AddPokemons();									//Funkcje dodaj¹ce odpowiednio kolzje do Pokemonów, managerów kolizji
	AddCollisionManager();
	
	theWorld.Add(pikachu);
	
	//Tworzenie grafu po którym bêdzie porusza³ siê Pikachu.
	BoundingBox bounds(Vector2(-20, -20), Vector2(20, 20));
	theSpatialGraph.CreateGraph( 1.0f, bounds);
	theSpatialGraph.EnableDrawGraph(false);

}

void GardenManager::MouseDownEvent(Vec2i screenCoordinates, MouseButtonInput button) {
	
	TypedMessage<Vec2i> *m = new TypedMessage<Vec2i>("MouseDown", screenCoordinates);
	theSwitchboard.Broadcast(m);	

}

void GardenManager::Update(float dt) {

}

void GardenManager::CreatePokemon(float x, float y , float sizex, float sizey, String pathName) {

	theWorld.Add(new Pokemon(x, y, sizex, sizey, pathName));

}

void GardenManager::CreateCollisionManager(float x, float y ,  float sx, float sy, String name, String colortag, String nametag, String typetag, String actiontag, Vector2 opposite, Vector2 behind, Vector2 side) {

	theWorld.Add(new CollisionManager(x, y , sx, sy, name,colortag, nametag, typetag, actiontag, behind, opposite, side));

}

void GardenManager::AddCollisionManager() {

	CreateCollisionManager(-9.0f, 3.8f, 1.0f, 0.7f, "BigTree", "green", "big tree", "tree", "spawned", Vector2(0,0), Vector2(0,0), Vector2(0,0));
	CreateCollisionManager(6.5f, -8.0f, 0.3f, 0.7f, "BigTreeHighWithLeaves", "green", "big tree", "tree", "spawned", Vector2(0,0), Vector2(0,0), Vector2(0,0));
	CreateCollisionManager(8.8f, 3.0f, 0.5f, 1.0f, "BigTreeWithLeaves", "green", "big tree", "tree", "spawned", Vector2(0,0), Vector2(0,0), Vector2(0,0));
	CreateCollisionManager(1.0f, 3.0f, 0.5f, 0.5f, "TreeNeadles", "green", "notSoBig", "tree", "spawned", Vector2(0,0), Vector2(0,0), Vector2(0,0));
	CreateCollisionManager(-11.0f, -7.5f, 1.0f, 0.1f, "Jigglypuff", "pink", "Jigglypuff", "thing", "spawned", Vector2(0,0), Vector2(0,0), Vector2(0,0));
	CreateCollisionManager(3.0f, 7.5f, 1.0f, 0.1f,  "Victreebel", "yellow", "Victreebel", "flower", "spawned" , Vector2(0,0), Vector2(0,0), Vector2(0,0));
	CreateCollisionManager(3.0f, 4.8f, 1.5f, 0.1f, "Arbok", "purple", "Arbok", "snake", "spawned" , Vector2(0,0), Vector2(0,0), Vector2(0,0));
	CreateCollisionManager(4.0f, -4.5f, 1.0f, 0.1f, "Bulbasaur", "green", "Bulbasaur", "plant", "spawned" , Vector2(0,0), Vector2(0,0), Vector2(0,0));
	CreateCollisionManager(-4.0f, 7.3f, 1.0f, 0.1f,  "Psyduck", "yellow", "Psyduck", "duck", "spawned", Vector2(0,0), Vector2(0,0), Vector2(0,0));
	CreateCollisionManager(-3.0f, -0.5f, 1.0f, 0.1f,  "Rattata", "purple", "Rattata", "rat", "spawned" , Vector2(0,0), Vector2(0,0), Vector2(0,0));
	CreateCollisionManager(11.0f, -5.5f, 1.0f, 0.1f, "Slowpoke", "pink", "Slowpoke", "lazy asshole", "spawned" , Vector2(0,0), Vector2(0,0), Vector2(0,0));
	CreateCollisionManager(5.0f, 8.5f, 1.0f, 0.1f, "Koffing", "purple", "Koffing", "ball", "spawned" , Vector2(0,0), Vector2(0,0), Vector2(0,0));
	CreateCollisionManager(6.0f, -0.9f, 1.0f, 0.1f, "Snorlax", "blue-white", "Snorlax", "sleepyhead", "spawned", Vector2(0,0), Vector2(0,0), Vector2(0,0));
	CreateCollisionManager(-10.0f, -1.5f, 1.0f, 0.1f, "Charizard", "red", "Charizard", "dragon", "spawned" , Vector2(0,0), Vector2(0,0), Vector2(0,0));
	CreateCollisionManager(9.0f, -1.5f, 1.0f, 0.1f, "Squirtle", "blue", "Squirtle", "turtle", "spawned", Vector2(0,0), Vector2(0,0), Vector2(0,0));
	CreateCollisionManager(5.0f, 7.0f, 1.0f, 0.1f,  "Meowth", "white", "Meowth", "cat", "spawned", Vector2(0,0), Vector2(0,0), Vector2(0,0));
	CreateCollisionManager(6.0f, 2.5f, 1.0f, 0.1f, "Pidgeot", "orange", "Pidgeot", "bird", "spawned", Vector2(0,0), Vector2(0,0), Vector2(0,0));
	CreateCollisionManager(-5.0f, -5.7f, 1.0f, 0.1f, "Raichu", "yellow", "Raichu", "mouse", "spawned", Vector2(0,0), Vector2(0,0), Vector2(0,0));

}

void GardenManager::AddPokemons() {

	CreatePokemon(-11.0f, -7.0f, 1.0f, 1.0f, "Resources/Images/pokemons/jigglypuff.png" );
	CreatePokemon(3.0f, 8.0f, 1.5f, 1.8f, "Resources/Images/pokemons/victreebel.png");
	CreatePokemon(3.0f, 6.0f, 2.1f, 2.5f, "Resources/Images/pokemons/arbok.png");
	CreatePokemon(4.0f, -4.0f, 1.5f, 1.5f, "Resources/Images/pokemons/bulbasaur.png");
	CreatePokemon(-4.0f, 8.0f, 1.5f, 1.5f, "Resources/Images/pokemons/psyduck.png");
	CreatePokemon(-3.0f, 0.0f, 1.0f, 1.4f, "Resources/Images/pokemons/rattata.png");
	CreatePokemon(11.0f, -5.0f, 1.5f, 1.2f, "Resources/Images/pokemons/slowpoke.png");
	CreatePokemon(5.0f, 9.0f, 1.6f, 1.5f, "Resources/Images/pokemons/koffing.png");
	CreatePokemon(6.0f, 0.0f, 1.8f, 2.0f, "Resources/Images/pokemons/snorlax.png");
	CreatePokemon(-10.0f, 0.0f, 3.2f, 3.3f, "Resources/Images/pokemons/charizard_001.png");
	CreatePokemon(9.0f, -1.0f, 1.2f, 1.3f, "Resources/Images/pokemons/squirtle_001.png");
	CreatePokemon(5.0f, 7.5f, 1.4f, 1.5f, "Resources/Images/pokemons/meowth_001.png");
	CreatePokemon(6.0f, 3.0f, 1.0f, 1.5f, "Resources/Images/pokemons/pidgeot_001.png");
	CreatePokemon(-5.0f, -5.0f, 1.8f, 1.6f, "Resources/Images/pokemons/raichu_001.png");

}

GardenManager::~GardenManager(void) {

}
