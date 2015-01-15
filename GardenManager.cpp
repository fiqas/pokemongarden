#include "stdafx.h"
#include <windows.h>

GardenManager::GardenManager(void) {

	theWorld.SetupPhysics(Vector2(0.0f, 0.0f));		// Ustawienie fizyki, potrzebne by Pikachu 
	theWorld.LoadLevel("pokemon_garden_level");	    // Wczytujemy plik ze statycznymi elementami œwiata tj. drzewa, p³ot oraz ziemia.
	
	pikachu = new Pikachu();
	
	AddPokemons();									//Funkcje dodaj¹ce odpowiednio kolzje do Pokemonów, managerów kolizji
	AddCollisionManager();
	
	theWorld.Add(pikachu);

	//Obsluga wyswietlanego tekstu

	text = new TextActor("Console", "", TXT_Left);
	text_screen = new FullScreenActor();
	close_text_frame = true;
	text_screen->SetSprite("Resources/Images/text_002.png", 0, GL_CLAMP, GL_LINEAR);
	text_screen->SetLayer(10);
	text->SetPosition(Vector2(-9.0, -5.0));
	text->SetLayer(10);
	theWorld.Add(text_screen);
	theWorld.Add(text);
	
	//Tworzenie grafu po którym bêdzie porusza³ siê Pikachu.
	BoundingBox bounds(Vector2(-20, -20), Vector2(20, 20));
	theSpatialGraph.CreateGraph( 1.0f, bounds);
	theSpatialGraph.EnableDrawGraph(false);

	//Pikachu reaguje na nastêpuj¹ce "wiadomoœci":
	theSwitchboard.SubscribeTo(this, "GoTo");
	theSwitchboard.SubscribeTo(this, "Fight");
	theSwitchboard.SubscribeTo(this, "Talk");

}

void GardenManager::MouseDownEvent(Vec2i screenCoordinates, MouseButtonInput button) {
	

	if(button == MOUSE_LEFT) {

		Analyze();

	}

	if(button == MOUSE_RIGHT) {

		CloseText();

	}

}

void GardenManager::ReceiveMessage(Message* message) {

	if (message->GetMessageName() == "GoTo" ) { 

		TypedMessage<Vector2> *m = (TypedMessage<Vector2>*)message;
		Vector2 destinationCoordinates = m->GetValue();
		pikachu->GoTo(destinationCoordinates);
		
	}

	if (message->GetMessageName() == "Fight" ) {

	
		TypedMessage<String> *m = (TypedMessage<String>*)message;
		String nameOfPokemon = m->GetValue();
		String pathName = "Resources/Images/fighting scenes/" + nameOfPokemon + "_fight_001.png";
		pikachu -> pathName = pathName;
	
		if (pikachu->GetPosition().X != 0) pikachu->Fight();
		
	}

	if (message->GetMessageName() == "Talk") {
	
		TypedMessage<String> *m = (TypedMessage<String>*)message;
		String nameOfPokemon = m->GetValue();
		String pathName = "Resources/Chats/"+ nameOfPokemon + ".txt";
		pikachu -> pathName = pathName;

		if (pikachu->GetPosition().X != 0) pikachu->Talk();

	}


}

void GardenManager::Text(String display_text) {

	close_text_frame = false;
	text_screen->SetSprite("Resources/Images/text_001.png");
	text->SetDisplayString(display_text);

}

void GardenManager::CloseText() {

	text_screen->SetSprite("Resources/Images/text_002.png");
	text->SetDisplayString("");

}

void GardenManager::Helper(Vector2 coordinates){

	pikachu->GoTo(coordinates);

}

void GardenManager::Analyze() {

	//tutaj bêdzie funkcja pobieraj¹ca stringa z mikrofonu

	//tutaj bêdzie funkcja wyci¹gaj¹ca ze stringa podzdania z podzielonymi s³owami wg gramatyki

	//powiedzmy, ¿e tagger wypluje coœ takiego:

	String verb = "fight";
	String adjective = "blue";
	String noun = "pokemon";

	ActorSet pokemons;
	FindTaggedPokemons(pokemons, adjective, noun);
	Actor* concretepokemon;
	bool found = false;
		
	if(pokemons.size() > 1) {

		Text("I don't know what are you talking about, \nyou need to be specific.");

		//jeœli znajdzie wiêcej obiektów spe³niaj¹cych za³o¿enia danych przez przymiotnik i rzeczownik
		//tutaj znowu wywo³a siê funkcjê, która znowu wypluje zestaw danych
		//powiedzmy, ¿e dostaniemy:

		adjective = "water";
		noun = "turtle";

		ActorSet pokemons2;
		ActorSet pokemons3;
		FindTaggedPokemons(pokemons2, adjective, noun);
		

	    for(ActorSet::iterator itr1 = pokemons.begin(); itr1 != pokemons.end(); itr1++ ) {

			for(ActorSet::iterator itr2 = pokemons2.begin(); itr2 != pokemons2.end(); itr2++ ) {

				Actor* targetActor1 = (*itr1);
				Actor* targetActor2 = (*itr2);

				if(targetActor1->GetName() == targetActor2->GetName()) {

					pokemons3.insert(targetActor1);

				}

			}

		}

		if(pokemons3.size() > 1) {

		Text("I don't know what are you talking about, I give up.");
		//przez kilka sekund
		}

		else {

		found = true;
		concretepokemon = (*pokemons3.begin());

		}

	}

	else {

		found = true;
		concretepokemon = (*pokemons.begin());

	}

	if(found) { 
		
	//jeœli znaleŸliœmy konkretnego pokemona, to mo¿emy przejœæ do wykonania czynnoœci
	//oczywiœcie tutaj te¿ bêdzie sprawdza³, czy jest synonimem tych czasowników

		if(verb == "go") {

			TypedMessage<Vector2> *m = new TypedMessage<Vector2>("GoTo", concretepokemon->_side);
			theSwitchboard.Broadcast(m);

		}

		else if(verb == "fight") {

			if (noun == "tree") Text("I can't fight with : " + concretepokemon->GetName() + "\nI can fight just with pokemons.");
			
			else {

				pikachu->fightMode = true;

				if (pikachu -> GetPosition() != concretepokemon->_side) {
		
					TypedMessage<Vector2> *m = new TypedMessage<Vector2>("GoTo", concretepokemon->_side);
					theSwitchboard.Broadcast(m);

				}

				TypedMessage<String> *m = new TypedMessage<String>("Fight", concretepokemon->GetName());
				theSwitchboard.Broadcast(m);

				if		(concretepokemon->IsTagged("electric"))	pikachu->pokemonType = "electric";
				else if (concretepokemon->IsTagged("psychic"))	pikachu->pokemonType = "psychic";
				else if (concretepokemon->IsTagged("normal"))	pikachu->pokemonType = "normal";
				else if (concretepokemon->IsTagged("grass"))	pikachu->pokemonType = "grass";
				else if (concretepokemon->IsTagged("water"))	pikachu->pokemonType = "water";
				else if (concretepokemon->IsTagged("poison"))	pikachu->pokemonType = "poison";
				else if (concretepokemon->IsTagged("fire"))		pikachu->pokemonType = "fire";
		

			}
		
		}

		else if(verb == "talk") {

			if (noun != "pokemon") Text( "I can't talk to : " + concretepokemon->GetName() + "\nI can talk just with pokemons.");

			else {
			
				pikachu->talkMode = true;

				if (pikachu->GetPosition() != concretepokemon->_side) {
				
					TypedMessage<Vector2> *m = new TypedMessage<Vector2>("GoTo", concretepokemon->_side);
					theSwitchboard.Broadcast(m);

				} 

				TypedMessage<String> *m = new TypedMessage<String>("Talk", concretepokemon->GetName());
				theSwitchboard.Broadcast(m);

			}

		}

		else if(verb == "hide") {

			TypedMessage<Vector2> *m = new TypedMessage<Vector2>("GoTo", concretepokemon->_behind);
			theSwitchboard.Broadcast(m);

		}


		else {

			Text("I don't know what you want me to do, stupid.");

		}

	}

}

void GardenManager::FindTaggedPokemons(ActorSet& bothTaggedActors, String adjective, String noun) {

	ActorSet adjectiveTaggedActors;
	ActorSet nounTaggedActors;

	if(!adjective.empty()) { //je¿eli przymiotnik istnieje i string nie jest pusty

		adjectiveTaggedActors = theTagList.GetObjectsTagged(adjective);

		if(noun.empty()) bothTaggedActors = theTagList.GetObjectsTagged(adjective);
		
	} 

	if(!noun.empty()) { //je¿eli rzeczownik istnieje i string nie jest pusty

		nounTaggedActors = theTagList.GetObjectsTagged(noun);
	
		if(adjective.empty()) bothTaggedActors = theTagList.GetObjectsTagged(noun);
	}
	



	for(ActorSet::iterator itr1 = nounTaggedActors.begin(); itr1 != nounTaggedActors.end(); itr1++ ) {

		if (nounTaggedActors.empty() || adjectiveTaggedActors.empty()) break;

		for(ActorSet::iterator itr2 = adjectiveTaggedActors.begin(); itr2 != adjectiveTaggedActors.end(); itr2++ ) {

			Actor* targetActor1 = (*itr1);
			Actor* targetActor2 = (*itr2);

			

			if(targetActor1->GetName() == targetActor2->GetName()) {

				bothTaggedActors.insert(targetActor2);

			}

		}

	}
	
}

void GardenManager::Update(float dt) {

}

void GardenManager::CreatePokemon(float x, float y , float sizex, float sizey, String pathName) {

	theWorld.Add(new Pokemon(x, y, sizex, sizey, pathName));

}

void GardenManager::CreateCollisionManager(float x, float y ,  float sx, float sy, String pathTag, Vector2 opposite, Vector2 behind, Vector2 side) {

	theWorld.Add(new CollisionManager(x, y , sx, sy, pathTag , behind, opposite, side));

}

void GardenManager::AddCollisionManager() {

	//Set tag name!
	CreateCollisionManager(-9.0f, 3.8f, 1.0f, 0.7f, "Resources/Tags/big_tree_tags.txt" , Vector2(-9.2f, 2.63f), Vector2(-8.0f, 5.9f), Vector2(-7.0f, 3.8f));
	CreateCollisionManager(6.5f, -8.0f, 0.3f, 0.7f, "Resources/Tags/big_tree_high_with_leaves_tags.txt", Vector2(6.3f, -9.0f), Vector2(6.34f, -7.16f), Vector2(4.99f, -8.0f));
	CreateCollisionManager(8.8f, 3.0f, 0.5f, 1.0f, "Resources/Tags/big_tree_with_leaves_tags.txt", Vector2(8.77f, 1.49f), Vector2(8.85f, 4.11f), Vector2(7.58f , 3.25f));
	CreateCollisionManager(1.0f, 3.0f, 0.5f, 0.5f, "Resources/Tags/tree_neadles_tags.txt", Vector2(1.75f, 2.28f), Vector2(0.99f, 3.98f), Vector2(0.4f, 3.5f));
	CreateCollisionManager(-11.0f, -7.5f, 1.0f, 0.1f, "Resources/Tags/jigglypuff_tags.txt",Vector2(-10.93f, -8.19f), Vector2(-10.87f, -6.92f), Vector2(-11.98f, -7.11f));
	CreateCollisionManager(3.0f, 7.5f, 1.0f, 0.1f,  "Resources/Tags/victreebel_tags.txt", Vector2(3.29f, 7.48f), Vector2(2.78f, 8.46f), Vector2(1.61f, 7.86f ));
	CreateCollisionManager(3.0f, 4.8f, 1.5f, 0.1f, "Resources/Tags/arbok_tags.txt", Vector2(3.13f, 4.06f), Vector2(3.21f, 6.0f), Vector2(1.43f, 5.49f));
	CreateCollisionManager(4.0f, -4.5f, 1.0f, 0.1f, "Resources/Tags/bulbasaur_tags.txt",Vector2(3.85f, -5.16f), Vector2( 3.77f, -3.81f), Vector2(2.86f ,-4.35f));
	CreateCollisionManager(-4.0f, 7.3f, 1.0f, 0.1f,  "Resources/Tags/psyduck_tags.txt",Vector2(-4.12f, 6.84f), Vector2(-4.02f,8.12f), Vector2(-5.23, 7.81f));
	CreateCollisionManager(-3.0f, -0.5f, 1.0f, 0.1f,  "Resources/Tags/rattata_tags.txt", Vector2(-3.29f, -1.22f), Vector2(-2.96f, 0.14f), Vector2(-4.10f, -0.33f));
	CreateCollisionManager(11.0f, -5.5f, 1.0f, 0.1f, "Resources/Tags/slowpoke_tags.txt", Vector2(10.82f, -6.19f), Vector2(11.03f, -4.84f), Vector2( 9.2f, -5.22f));
	CreateCollisionManager(5.0f, 8.5f, 1.0f, 0.1f, "Resources/Tags/koffing_tags.txt", Vector2(5.04f, 8.0f), Vector2( 5.1f, 10.19f), Vector2(3.91f, 8.97f));
	CreateCollisionManager(6.0f, -0.9f, 1.0f, 0.1f, "Resources/Tags/snorlax_tags.txt", Vector2(5.88f, -1.28f), Vector2(6.04f, -0.12f), Vector2( 4.58f, -0.41f));
	CreateCollisionManager(-10.0f, -1.5f, 1.0f, 0.1f, "Resources/Tags/charizard_tags.txt", Vector2(-10.0f , -1.92f), Vector2(-9.63f, 0.66f), Vector2(-8.31f, -1.28f));
	CreateCollisionManager(9.0f, -1.5f, 1.0f, 0.1f, "Resources/Tags/squirtle_tags.txt", Vector2(8.87f, -2.38f), Vector2(8.93, -0.6f), Vector2(8.8f, 0.22f));
	CreateCollisionManager(-0.5f, 7.0f, 1.0f, 0.1f,  "Resources/Tags/meowth_tags.txt", Vector2(-0.48f, 5.97f), Vector2( -0.51f, 7.7f), Vector2(-1.53f, 7.19f));
	CreateCollisionManager(6.0f, 2.5f, 1.0f, 0.1f, "Resources/Tags/pidgeot_tags.txt", Vector2(6.04f, 1.82f), Vector2(6.09f, 3.27f), Vector2(4.85f, 2.82f));
	CreateCollisionManager(-5.0f, -5.7f, 1.0f, 0.1f, "Resources/Tags/raichu_tags.txt", Vector2(-4.96f, -6.46f), Vector2(-4.8f, -4.62f), Vector2(-6.12f, -5.08f));
	
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
