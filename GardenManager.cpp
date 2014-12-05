#include "stdafx.h"

GardenManager::GardenManager(void) {

	theWorld.SetupPhysics(Vector2(0.0f, 0.0f));		// Ustawienie fizyki, potrzebne by Pikachu 
	theWorld.LoadLevel("pokemon_garden_level");	    // Wczytujemy plik ze statycznymi elementami œwiata tj. drzewa, p³ot oraz ziemia.
	
	pikachu = new Pikachu();
	text = new TextActor("Console", "", TXT_Left);
	text_screen = new FullScreenActor();
	close_text_frame = false;
	
	AddPokemons();									//Funkcje dodaj¹ce odpowiednio kolzje do Pokemonów, managerów kolizji
	AddCollisionManager();
	
	theWorld.Add(pikachu);
	
	//Tworzenie grafu po którym bêdzie porusza³ siê Pikachu.
	BoundingBox bounds(Vector2(-20, -20), Vector2(20, 20));
	theSpatialGraph.CreateGraph( 1.0f, bounds);
	theSpatialGraph.EnableDrawGraph(false);

	//Pikachu reaguje na nastêpuj¹ce "wiadomoœci":
	theSwitchboard.SubscribeTo(this, "GoTo");

}

void GardenManager::MouseDownEvent(Vec2i screenCoordinates, MouseButtonInput button) {
	
//Œmiechostka - jak bêdziesz klikaæ raz lewy, raz prawy, to pokemony bêd¹ w co 2 razie wchodziæ na okienko :D
//Chyba trzeba bêdzie zmieniæ, ¿e zamiast Remove, to ustawienie tekstu na pusty ("") i zmiana sprite'a na przezroczysty ca³y.
//Poprawi³am te¿ chodzenie - Pikachu teraz w szerszych k¹tach chodzi w górê i w dó³, co wygl¹da chyba bardziej realistycznie.
	if(button == MOUSE_LEFT) {

		Text("HANNIBAL CANNIBAL! \n IT FUCKING RHYMES!");
		
		//Work in progress
		//Analyze();

		TypedMessage<Vec2i> *m = new TypedMessage<Vec2i>("GoTo", screenCoordinates);
		theSwitchboard.Broadcast(m);

	}

	if(button == MOUSE_RIGHT) {

		theWorld.Remove(text_screen);
		theWorld.Remove(text);

	}

}

void GardenManager::ReceiveMessage(Message* message) {

	if (message->GetMessageName() == "GoTo") { 

		std::cout << "odbiór!" << std::endl;

		TypedMessage<Vec2i> *m = (TypedMessage<Vec2i>*)message;
		Vec2i screenCoordinates = m->GetValue();
		Vector2 worldCoordinates = MathUtil::ScreenToWorld(screenCoordinates);
		pikachu->GoTo(worldCoordinates);

	}

}

void GardenManager::Text(String display_text) {

	close_text_frame = false;
	text_screen->SetSprite("Resources/Images/text.png", 0, GL_CLAMP, GL_LINEAR);
	text_screen->SetLayer(10);
	text->SetDisplayString(display_text);
	text->SetPosition(Vector2(-9.0, -5.0));
	text->SetLayer(10);
	theWorld.Add(text_screen);
	theWorld.Add(text);

}

void GardenManager::Analyze() {

	//tutaj bêdzie funkcja pobieraj¹ca stringa z mikrofonu

	//tutaj bêdzie funkcja wyci¹gaj¹ca ze stringa podzdania z podzielonymi s³owami wg gramatyki

	//powiedzmy, ¿e tagger wypluje coœ takiego:
	String verb = "go";
	String adjective = "yellow";
	String noun = "pokemon";

	Vector2 destination;

	if(verb == "go") {

		int counter;
		
		for(int i = 0; i < 3; i++) {

			ActorSet taggedActors = theTagList.GetObjectsTagged(adjective);
			Actor* taggedActor;

			for( ActorSet::iterator itr = taggedActors.begin(); itr != taggedActors.end(); itr++ ) {

				counter++;
				taggedActor = (*itr);
				std::cout << "Yellow pokemon of name: " << taggedActor->GetName();


			}

			if(counter > 1) {

				//tu siê zapyta o wiêksz¹ precyzjê
				//u¿ytkownik sprecyzuje i tagger wypluje:
				adjective = "electric";

				if(i == 2) {

					//jeœli u¿ytkownik 3 razy nie zgadnie
					//Pikachu wyklnie go od g³upich :D

				}

			}

			else {

				//jeœli dopracowaliœmy zapytania, to mo¿emy w koñcu wywo³aæ funkcjê,
				//dziêki której Pikachu dojdzie do konkretnego pokemona pokemona.
				//póki co tylko po tagach bêdzie odsiewa³, mam nadziejê dodaæ te¿ obs³ugê
				//s³ów takich jak 'najbli¿szy' itp.


				//UWAGA! TU SIÊ PLUJE. NIE WIEM, JAK TO ROZWIAZAC.
				//Mamy listê wskaŸników na Aktorów. Ale ja chcê wyci¹gn¹æ zmienn¹, która jest w CollisionManager.
				//No i krzyczy, ¿e nie ma takiej zmiennej w Actor... Chyba na pa³ê trzeba bêdzie w klasie Actor wcisn¹æ te zmienne 
				//i ustawiæ je w pochodnej klasie CollisionManager.

				//destination = taggedActor->_side;
				//pikachu->GoTo(destination);

			}

		}

	}

}

void GardenManager::Update(float dt) {

}

void GardenManager::CreatePokemon(float x, float y , float sizex, float sizey, String pathName) {

	theWorld.Add(new Pokemon(x, y, sizex, sizey, pathName));

}

void GardenManager::CreateCollisionManager(float x, float y ,  float sx, float sy, String name, String colortag, String nametag, String typetag, Vector2 opposite, Vector2 behind, Vector2 side) {

	theWorld.Add(new CollisionManager(x, y , sx, sy, name,colortag, nametag, typetag, behind, opposite, side));

}

void GardenManager::AddCollisionManager() {

	//Set tag name!
	CreateCollisionManager(-9.0f, 3.8f, 1.0f, 0.7f, "BigTree", "green", "big tree", "tree", Vector2(-9.2f, 2.63f), Vector2(-8.0f, 5.9f), Vector2(-7.0f, 3.8f));
	CreateCollisionManager(6.5f, -8.0f, 0.3f, 0.7f, "BigTreeHighWithLeaves", "green", "big tree", "tree", Vector2(6.3f, -9.0f), Vector2(6.34f, -7.16f), Vector2(4.99f, -8.0f));
	CreateCollisionManager(8.8f, 3.0f, 0.5f, 1.0f, "BigTreeWithLeaves", "green", "big tree", "tree", Vector2(8.77f, 1.49f), Vector2(8.85f, 4.11f), Vector2(7.58f , 3.25f));
	CreateCollisionManager(1.0f, 3.0f, 0.5f, 0.5f, "TreeNeadles", "green", "notSoBig", "tree", Vector2(1.75f, 2.28f), Vector2(0.99f, 3.98f), Vector2(0.4f, 3.5f));
	CreateCollisionManager(-11.0f, -7.5f, 1.0f, 0.1f, "Jigglypuff", "pink", "normal", "thing",  Vector2(-10.93f, -8.19f), Vector2(-10.87f, -6.92f), Vector2(-11.98f, -7.11f));
	CreateCollisionManager(3.0f, 7.5f, 1.0f, 0.1f,  "Victreebel", "yellow", "grass", "flower", Vector2(3.29f, 7.48f), Vector2(2.78f, 8.46f), Vector2(1.61f, 7.86f ));
	CreateCollisionManager(3.0f, 4.8f, 1.5f, 0.1f, "Arbok", "purple", "poison", "snake",  Vector2(3.13f, 4.06f), Vector2(3.21f, 6.0f), Vector2(1.43f, 5.49f));
	CreateCollisionManager(4.0f, -4.5f, 1.0f, 0.1f, "Bulbasaur", "green", "grass", "plant", Vector2(3.85f, -5.16f), Vector2( 3.77f, -3.81f), Vector2(2.86f ,-4.35f));
	CreateCollisionManager(-4.0f, 7.3f, 1.0f, 0.1f,  "Psyduck", "yellow", "water", "duck", Vector2(-4.12f, 6.84f), Vector2(-4.02f,8.12f), Vector2(-5.23, 7.81f));
	CreateCollisionManager(-3.0f, -0.5f, 1.0f, 0.1f,  "Rattata", "purple", "normal", "rat", Vector2(-3.29f, -1.22f), Vector2(-2.96f, 0.14f), Vector2(-4.10f, -0.33f));
	CreateCollisionManager(11.0f, -5.5f, 1.0f, 0.1f, "Slowpoke", "pink", "psychic", "lazy asshole", Vector2(10.82f, -6.19f), Vector2(11.03f, -4.84f), Vector2( 9.2f, -5.22f));
	CreateCollisionManager(5.0f, 8.5f, 1.0f, 0.1f, "Koffing", "purple", "poison", "ball", Vector2(5.04f, 8.0f), Vector2( 5.1f, 10.19f), Vector2(3.91f, 8.97f));
	CreateCollisionManager(6.0f, -0.9f, 1.0f, 0.1f, "Snorlax", "blue-white", "normal", "sleepyhead",  Vector2(5.88f, -1.28f), Vector2(6.04f, -0.12f), Vector2( 4.58f, -0.41f));
	CreateCollisionManager(-10.0f, -1.5f, 1.0f, 0.1f, "Charizard", "red", "fire", "dragon", Vector2(-10.0f , -1.92f), Vector2(-9.63f, 0.66f), Vector2(-8.31f, -1.28f));
	CreateCollisionManager(9.0f, -1.5f, 1.0f, 0.1f, "Squirtle", "blue", "water", "turtle",  Vector2(8.87f, -2.38f), Vector2(8.93, -0.6f), Vector2(7.8f, 1.22f));
	CreateCollisionManager(-0.5f, 7.0f, 1.0f, 0.1f,  "Meowth", "white", "normal", "cat",  Vector2(-0.48f, 5.97f), Vector2( -0.51f, 7.7f), Vector2(-1.53f, 7.19f));
	CreateCollisionManager(6.0f, 2.5f, 1.0f, 0.1f, "Pidgeot", "orange", "flying", "bird",  Vector2(6.04f, 1.82f), Vector2(6.09f, 3.27f), Vector2(4.85f, 2.82f));
	CreateCollisionManager(-5.0f, -5.7f, 1.0f, 0.1f, "Raichu", "yellow", "electric", "mouse", Vector2(-4.96f, -6.46f), Vector2(-4.8f, -4.62f), Vector2(-6.12f, -5.08f));

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
	CreatePokemon(-0.5f, 7.5f, 1.4f, 1.5f, "Resources/Images/pokemons/meowth_001.png");
	CreatePokemon(6.0f, 3.0f, 1.0f, 1.5f, "Resources/Images/pokemons/pidgeot_001.png");
	CreatePokemon(-5.0f, -5.0f, 1.8f, 1.6f, "Resources/Images/pokemons/raichu_001.png");

}

GardenManager::~GardenManager(void) {

}
