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
	text_screen = new FullScreenActor();
	text_screen->SetSprite("Resources/Images/text_002.png", 0, GL_CLAMP, GL_LINEAR);
	text_screen->SetLayer(10);
	
	text = new TextActor("Console", "", TXT_Left);
	text->SetPosition(Vector2(-9.0, -5.0));
	text->SetLayer(10);
	close_text_frame = true;

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

	SynonymsLoader();
	counterPtr = &counter;
	*counterPtr = 0;

	pikachuOrder = theSound.LoadSample("Resources/Sounds/pikachuOrdered.mp3", false);
	pikachuQuestion = theSound.LoadSample("Resources/Sounds/pikachuQuestion.mp3", false);
	pikachuLaughing = theSound.LoadSample("Resources/Sounds/pikachuLaugh.mp3", false);
	acidSound = theSound.LoadSample("Resources/Sounds/acid.wav", false);

	pikachuOnAcid = new FullScreenActor();
	pikachuOnAcid->LoadSpriteFrames("Resources/Images/Animation/pikachuOnAcid_001.png", GL_CLAMP, GL_LINEAR);
	pikachuOnAcid->SetLayer(5);
	pikachuOnAcid->SetSpriteFrame(43);
	theWorld.Add(pikachuOnAcid);

}

GardenManager::~GardenManager(void) {

	delete pikachu;
	delete text;
	delete text_screen;
	delete counterPtr;
	delete pikachuOnAcid;

}

void GardenManager::MouseDownEvent(Vec2i screenCoordinates, MouseButtonInput button) {
	
	

	if(button == MOUSE_LEFT) {

		if (*counterPtr < SentencesList.size()) Analyze(*counterPtr);
		
		else {

			pikachuOnAcid -> PlaySpriteAnimation(0.1f, SAT_OneShot, 0, 43, "drugs");
			theSound.PlaySound(acidSound);
			*counterPtr = 0;

		}

		*counterPtr = *counterPtr +1; 

	}

	if(button == MOUSE_RIGHT) {
	

		DoThings();

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
	
		if (pikachu->GetPosition().X == concretepokemon->_side.X) pikachu->Fight();
		
	}

	if (message->GetMessageName() == "Talk") {
	
		TypedMessage<String> *m = (TypedMessage<String>*)message;
		String nameOfPokemon = m->GetValue();
		String pathName = "Resources/Chats/"+ nameOfPokemon + ".txt";
		pikachu->pathName = pathName;
		pikachu->pokemonName = nameOfPokemon;

		if (pikachu->GetPosition().X == concretepokemon->_side.X) pikachu->Talk();

	}


}

void GardenManager::Text(String display_text) {

	text_screen->SetSprite("Resources/Images/text_001.png");
	text->SetDisplayString(display_text);

}

void GardenManager::CloseText() {

	text_screen->SetSprite("Resources/Images/text_002.png");
	text->SetDisplayString("");

}

void GardenManager::SynonymsLoader() {

	std::fstream fileFight;
	std::fstream fileTalk;
	std::fstream fileHide;
	std::fstream fileGo;

	fileFight.open("Resources/Synonyms/walczyæ.txt", std::ios::in);
	fileTalk.open("Resources/Synonyms/rozmawiaæ.txt", std::ios::in);
	fileHide.open("Resources/Synonyms/chowaæ.txt", std::ios::in);
	fileGo.open("Resources/Synonyms/iœæ.txt", std::ios::in);

	if( fileFight.good() || fileTalk.good() || fileHide.good() || fileGo.good()) {
		
		String lineOfFight, lineOfTalk, lineOfHide, lineOfGo;

		while ( !fileFight.eof() ) {

			getline(fileFight, lineOfFight);
			synonymsOfFight.push_back(lineOfFight);

		}

		while (!fileTalk.eof()) {
		
			getline(fileTalk, lineOfTalk);
			synonymsOfTalk.push_back(lineOfTalk);

		}

		while (!fileHide.eof()) {

			getline(fileHide, lineOfHide);
			synonymsOfHide.push_back(lineOfHide);
		
		}

		while (!fileGo.eof()) {
		
			getline(fileGo, lineOfGo);
			synonymsOfGo.push_back(lineOfGo);
		
		}

		
		fileFight.close();
		fileTalk.close();
		fileHide.close();
		fileGo.close();


	} else std::cout << "Err! file  not found."  << std::endl;


}

void GardenManager::DoThings() {

	Forms partOfSentence;
	std::fstream fileOutput;
	fileOutput.open("output.txt", std::ios::in);

	if( fileOutput.good() ) {
		
		String words;

		while ( !fileOutput.eof() ) {

			getline(fileOutput, partOfSentence.verb);
			getline(fileOutput, partOfSentence.adjective);
			getline(fileOutput, partOfSentence.noun);

			SentencesList.push_back(partOfSentence);
			
		}
		
		fileOutput.close();
	
	}	


}

void GardenManager::Analyze(int toDo) {
	
	ActorSet pokemons;

	FindTaggedPokemons(pokemons, SentencesList[toDo].adjective, SentencesList[toDo].noun);

	if (pokemons.size() == 1) theSound.PlaySound(pikachuOrder);

	bool found = false;

	if(pokemons.size() > 1 || pokemons.size() == 0) {
		
		
		if (pokemons.size() > 1) {
		
			theSound.PlaySound(pikachuQuestion);

			std::cout << "Pikachu nie wie co zrobic, musisz doprecyzowac : " << std::endl;

			std::cin >> specified_adjective;
			std::cin >> specified_noun;

		}			

		ActorSet pokemons2;
		ActorSet pokemons3;
		
		FindTaggedPokemons(pokemons2, specified_adjective, specified_noun);
		

		for(ActorSet::iterator itr1 = pokemons.begin(); itr1 != pokemons.end(); itr1++ ) {

			for(ActorSet::iterator itr2 = pokemons2.begin(); itr2 != pokemons2.end(); itr2++ ) {

				Actor* targetActor1 = (*itr1);
				Actor* targetActor2 = (*itr2);

				if(targetActor1->GetName() == targetActor2->GetName()) {

					pokemons3.insert(targetActor1);

				}

			}

		}


		if(pokemons3.size() > 1 || pokemons3.size() == 0) {

			theSound.PlaySound(pikachuLaughing);
			Text("Poddaje sie. Nie wiem o czym mowisz, jestes zbyt glupi \nby zostac trenerem pokemon...");

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

		if(std::find(synonymsOfGo.begin(), synonymsOfGo.end(), SentencesList[toDo].verb)!=synonymsOfGo.end()) {
				
			int found = SentencesList[toDo].verb.find("nie ");

			if (found < 0) {

				TypedMessage<Vector2> *m = new TypedMessage<Vector2>("GoTo", concretepokemon->_side);
				theSwitchboard.Broadcast(m);
			}

			else Text("Jak nie to nie.");

		}

		else if(std::find(synonymsOfFight.begin(), synonymsOfFight.end(), SentencesList[toDo].verb)!=synonymsOfFight.end()) {

			if (!concretepokemon->IsTagged("pokemon")) {
				
				Text("Serio, myslisz ze bede walczyc z : " + concretepokemon->GetName() + "\n przeciez walcze tylko z pokemonami.");
				theSound.PlaySound(pikachuLaughing);

			}
	 
			else {
				
				int found = SentencesList[toDo].verb.find("nie ");

				if (found < 0) {

					pikachu->fightMode = true;

					if (pikachu -> GetPosition() != concretepokemon->_side) {
		
						TypedMessage<Vector2> *m = new TypedMessage<Vector2>("GoTo", concretepokemon->_side);
						theSwitchboard.Broadcast(m);

					}

					TypedMessage<String> *m = new TypedMessage<String>("Fight", concretepokemon->GetName());
					theSwitchboard.Broadcast(m);

					if		(concretepokemon->IsTagged("elektryczny")) pikachu->pokemonType = "elektryczny";
					else if (concretepokemon->IsTagged("psychiczny")) pikachu->pokemonType = "psychiczny";
					else if (concretepokemon->IsTagged("normalny")) pikachu->pokemonType = "normalny";
					else if (concretepokemon->IsTagged("roœlinny")) pikachu->pokemonType = "roœlinny";
					else if (concretepokemon->IsTagged("wodny")) pikachu->pokemonType = "wodny";
					else if (concretepokemon->IsTagged("truj¹cy")) pikachu->pokemonType = "truj¹cy";
					else if (concretepokemon->IsTagged("ognisty")) pikachu->pokemonType = "ognisty";
				
				}

				else Text("Jak nie to nie.");

			}
		
		}

		else if(std::find(synonymsOfTalk.begin(), synonymsOfTalk.end(), SentencesList[toDo].verb)!=synonymsOfTalk.end()) {

			if (!concretepokemon->IsTagged("pokemon")) {
				
				Text("Serio myslisz, ze bede walczyc z : " + concretepokemon->GetName() + "\nRozmawiam tylko z pokemonami.");
				theSound.PlaySound(pikachuLaughing);

			}

			else {

				int found = SentencesList[toDo].verb.find("nie ");
			
				if (found < 0) {

					pikachu->talkMode = true;

					if (pikachu->GetPosition() != concretepokemon->_side) {
				
						TypedMessage<Vector2> *m = new TypedMessage<Vector2>("GoTo", concretepokemon->_side);
						theSwitchboard.Broadcast(m);

					} 

					TypedMessage<String> *m = new TypedMessage<String>("Talk", concretepokemon->GetName());
					theSwitchboard.Broadcast(m);

				} 
				
				else Text("Jak nie to nie.");

			}

		}	

		else if(std::find(synonymsOfHide.begin(), synonymsOfHide.end(), SentencesList[toDo].verb)!=synonymsOfHide.end()) {
			
			int found = SentencesList[toDo].verb.find("nie ");
			
			if (found < 0) {

				TypedMessage<Vector2> *m = new TypedMessage<Vector2>("GoTo", concretepokemon->_behind);
				theSwitchboard.Broadcast(m);

			}

			else Text("Jak nie to nie.");

		}


		else {

			theSound.PlaySound(pikachuLaughing);
			Text("Jesteœ zbyt g³upi by zostaæ trenerem pokemon.");
			
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

		if	(nounTaggedActors.empty() || adjectiveTaggedActors.empty()) break;
	
		else if (nounTaggedActors.empty() && adjectiveTaggedActors.empty()) break;

		for(ActorSet::iterator itr2 = adjectiveTaggedActors.begin(); itr2 != adjectiveTaggedActors.end(); itr2++ ) {

			Actor* targetActor1 = (*itr1);
			Actor* targetActor2 = (*itr2);

			if(targetActor1->GetName() == targetActor2->GetName()) bothTaggedActors.insert(targetActor2);

		}
		
	}
	
}

void GardenManager::Update(float dt) {

	GameManager::Update(dt);

	if(theInput.IsKeyDown(ANGEL_KEY_SPACE)) {
	
		CloseText();

	}

}

void GardenManager::CreatePokemon(float x, float y , float sizex, float sizey, String pathName) {

	theWorld.Add(new Pokemon(x, y, sizex, sizey, pathName));

}

void GardenManager::CreateCollisionManager(float x, float y ,  float sx, float sy, String pathTag, Vector2 opposite, Vector2 behind, Vector2 side) {

	theWorld.Add(new CollisionManager(x, y , sx, sy, pathTag , behind, opposite, side));

}

void GardenManager::AddCollisionManager() {

	CreateCollisionManager(-4.2f, -1.7f, 1.0f, 0.1f, "Resources/Tags/szary_kamien_tags.txt", Vector2(-4.28f, -2.98f), Vector2(-5.92f, -1.48f), Vector2(-4.6f, -0.7f));
	CreateCollisionManager(-5.6f, -2.7f, 1.0f, 0.1f, "Resources/Tags/zloty_kamien_tags.txt", Vector2(-5.7f, -3.9f), Vector2(-7.23f, -2.26f), Vector2(-6.0f, -1.9f));
	CreateCollisionManager(-9.0f, 3.8f, 1.0f, 0.7f, "Resources/Tags/big_tree_tags.txt" , Vector2(-9.2f, 2.63f), Vector2(-8.0f, 5.9f), Vector2(-7.0f, 3.8f));
	CreateCollisionManager(6.5f, -8.0f, 0.3f, 0.7f, "Resources/Tags/big_tree_high_with_leaves_tags.txt", Vector2(6.3f, -9.0f), Vector2(6.34f, -7.16f), Vector2(4.99f, -8.0f));
	CreateCollisionManager(8.8f, 3.0f, 0.5f, 1.0f, "Resources/Tags/big_tree_with_leaves_tags.txt", Vector2(8.77f, 1.49f), Vector2(8.85f, 4.11f), Vector2(7.58f , 3.25f));
	CreateCollisionManager(1.0f, 3.0f, 0.5f, 0.5f, "Resources/Tags/tree_neadles_tags.txt", Vector2(1.75f, 2.28f), Vector2(0.99f, 3.98f), Vector2(0.4f, 3.5f));
	CreateCollisionManager(-11.0f, -7.5f, 1.0f, 0.1f, "Resources/Tags/jigglypuff_tags.txt",Vector2(-10.95f, -8.41f), Vector2(-9.16f, -6.91f), Vector2(-11.07f, -6.23f));
	CreateCollisionManager(3.0f, 7.5f, 1.0f, 0.1f,  "Resources/Tags/victreebel_tags.txt", Vector2(2.04f, 6.8f), Vector2(1.52f, 6.83f), Vector2(3.41f, 8.79f ));
	CreateCollisionManager(3.0f, 4.8f, 1.5f, 0.1f, "Resources/Tags/arbok_tags.txt", Vector2(3.35f, 3.99f), Vector2(1.17f, 5.66f), Vector2(3.19f, 6.34f));
	CreateCollisionManager(4.0f, -4.5f, 1.0f, 0.1f, "Resources/Tags/bulbasaur_tags.txt",Vector2(3.92f, -5.27f), Vector2( 2.18f, -4.09f), Vector2(4.03f ,-3.36f));
	CreateCollisionManager(-4.0f, 7.3f, 1.0f, 0.1f,  "Resources/Tags/psyduck_tags.txt",Vector2(-4.09f, 6.56f), Vector2(-5.56f,8.12f), Vector2(-3.71f, 8.55f));
	CreateCollisionManager(-3.0f, -0.5f, 1.0f, 0.1f,  "Resources/Tags/rattata_tags.txt", Vector2(-3.13f, -1.37f), Vector2(-4.44f, 0.04f), Vector2(-3.02f, 0.72f));
	CreateCollisionManager(11.0f, -5.5f, 1.0f, 0.1f, "Resources/Tags/slowpoke_tags.txt", Vector2(11.05f, -6.31f), Vector2(9.49f, -5.11f), Vector2( 11.15f, -4.29f));
	CreateCollisionManager(-5.59f, 2.25f, 1.0f, 0.1f, "Resources/Tags/koffing_tags.txt", Vector2(-5.64f, 1.78f), Vector2( -4.25f, 2.49f), Vector2(-5.48f, 2.98f));
	CreateCollisionManager(6.0f, -0.9f, 1.0f, 0.1f, "Resources/Tags/snorlax_tags.txt", Vector2(5.88f, -1.28f), Vector2(6.04f, -0.12f), Vector2( 5.94f, 0.06f));
	CreateCollisionManager(-10.0f, -1.5f, 1.0f, 0.1f, "Resources/Tags/charizard_tags.txt", Vector2(-10.0f , -2.6f), Vector2(-7.28f, -0.8f), Vector2(-9.81f, 0.53f));
	CreateCollisionManager(9.0f, -1.5f, 1.0f, 0.1f, "Resources/Tags/squirtle_tags.txt", Vector2(8.81f, -2.25f), Vector2(7.58, -1.07f), Vector2(8.84f, -0.22f));
	CreateCollisionManager(-0.5f, 7.0f, 1.0f, 0.1f,  "Resources/Tags/meowth_tags.txt", Vector2(-0.79f, 6.27f), Vector2( -2.04f, 7.4f), Vector2(-0.53f, 8.25f));
	CreateCollisionManager(6.0f, 2.5f, 1.0f, 0.1f, "Resources/Tags/pidgeot_tags.txt", Vector2(5.94f, 1.7f), Vector2(4.47f, 3.69f), Vector2(6.24f, 3.94f));
	CreateCollisionManager(-5.0f, -5.7f, 1.0f, 0.1f, "Resources/Tags/raichu_tags.txt", Vector2(-4.96f, -6.94f), Vector2(-6.79f, -4.5f), Vector2(-4.42f, -3.94f));
	CreateCollisionManager(-5.86f,0.2f ,1.0f, 0.1f, "Resources/Tags/wobbuffet_tags.txt", Vector2(-6.0f,-0.5f),Vector2 (-7.09f,0.34f), Vector2(-5.87f,0.91f));
	CreateCollisionManager(-0.5f, -4.9f, 1.0f, 0.1f, "Resources/Tags/mew_tags.txt", Vector2(-0.79f,-5.41f),Vector2 (-1.9f,-4.46f), Vector2(0.0f,-4.1f));
	CreateCollisionManager( -9.46f,-5.3f , 1.0f, 0.1f , "Resources/Tags/mewtwo_tags.txt", Vector2(-9.63f,-6.5f),Vector2 (-11.26f,-4.5f), Vector2(-9.38f,-3.77f));
	CreateCollisionManager( -3.84, 4.02f, 1.0f, 0.1f , "Resources/Tags/gyarados_tags.txt", Vector2(-3.19f,2.66f),Vector2 (-4.0f,5.6f), Vector2(-4.0f,5.2f));
	CreateCollisionManager( 2.81f, -7.58f, 1.0f, 0.1f , "Resources/Tags/scyther_tags.txt", Vector2(1.5f,-8.5f),Vector2 (0.68f,-6.78f), Vector2(2.7f,-5.9f));
	CreateCollisionManager( 10.58, 2.57f, 1.0f, 0.1f , "Resources/Tags/staryu_tags.txt", Vector2(10.5f,1.15f),Vector2 (11.8f,2.8f), Vector2(10.6f,3.2f));
	CreateCollisionManager( 9.41, -7.7f, 1.0f, 0.1f , "Resources/Tags/licktung_tags.txt", Vector2(9.3f,-8.6f),Vector2 (7.4f,-7.2f), Vector2(9.3f,-6.8f));
	CreateCollisionManager( -10.8f, 2.3f, 1.0f, 0.1f , "Resources/Tags/muk_tags.txt", Vector2(-10.8f,1.62f),Vector2 (-9.3f,2.82f), Vector2(-10.9f,3.2f));
	CreateCollisionManager( -7.8f, -8.3f, 1.0f, 0.1f , "Resources/Tags/rapidash_tags.txt", Vector2(-8.1f,-8.9f),Vector2 (-9.4f,-7.7f), Vector2(-7.25f,-6.9f));
	CreateCollisionManager( 2.29f, 0.17f, 1.0f, 0.1f , "Resources/Tags/alakazam_tags.txt", Vector2(2.5f,-0.5f),Vector2 (3.9f,0.69f), Vector2(2.3f,1.1f));
	CreateCollisionManager( -4.4f, -8.22f, 1.0f, 0.1f , "Resources/Tags/ninetales_tags.txt", Vector2(-4.6f,-9.3f),Vector2 (-3.1f,-8.1f), Vector2(-4.7f,-7.0f));
	CreateCollisionManager( 8.0f, -3.42f, 1.0f, 0.1f , "Resources/Tags/caterpie_tags.txt", Vector2(7.8f,-4.1f),Vector2 (9.2f,-2.9f), Vector2(7.7f,-2.6f));

}

void GardenManager::AddPokemons() {

	CreatePokemon(-11.0f, -7.0f, 1.0f, 1.0f, "Resources/Images/pokemons/jigglypuff.png" );
	CreatePokemon(3.0f, 8.0f, 1.5f, 1.8f, "Resources/Images/pokemons/victreebel.png");
	CreatePokemon(3.0f, 6.0f, 2.1f, 2.5f, "Resources/Images/pokemons/arbok.png");
	CreatePokemon(4.0f, -4.0f, 1.5f, 1.5f, "Resources/Images/pokemons/bulbasaur.png");
	CreatePokemon(-4.0f, 8.0f, 1.5f, 1.5f, "Resources/Images/pokemons/psyduck.png");
	CreatePokemon(-3.0f, 0.0f, 1.0f, 1.4f, "Resources/Images/pokemons/rattata.png");
	CreatePokemon(11.0f, -5.0f, 1.5f, 1.2f, "Resources/Images/pokemons/slowpoke.png");
	CreatePokemon(-5.5f, 2.7f, 1.6f, 1.5f, "Resources/Images/pokemons/koffing.png");
	CreatePokemon(6.0f, 0.0f, 1.8f, 2.0f, "Resources/Images/pokemons/snorlax.png");
	CreatePokemon(-10.0f, 0.0f, 3.2f, 3.3f, "Resources/Images/pokemons/charizard_001.png");
	CreatePokemon(9.0f, -1.0f, 1.2f, 1.3f, "Resources/Images/pokemons/squirtle_001.png");
	CreatePokemon(-0.5f, 7.5f, 1.4f, 1.5f, "Resources/Images/pokemons/meowth_001.png");
	CreatePokemon(6.0f, 3.0f, 1.0f, 1.5f, "Resources/Images/pokemons/pidgeot_001.png");
	CreatePokemon(-5.0f, -5.0f, 1.8f, 1.6f, "Resources/Images/pokemons/raichu_001.png");
	CreatePokemon(-5.8f, 0.5f, 2.0f, 2.0f, "Resources/Images/pokemons/wobbuffet.png");
	CreatePokemon(-0.5f, -4.5f, 2.5f, 2.5f, "Resources/Images/pokemons/mew.png");
	CreatePokemon(-9.5f, -4.3f,  3.0f, 3.0f, "Resources/Images/pokemons/mewtwo.png");
	CreatePokemon(-4.17f, 4.8f,  2.5f, 2.5f, "Resources/Images/pokemons/gyarados.png");
	CreatePokemon(2.4f, -6.73f,  3.5f, 3.5f, "Resources/Images/pokemons/scyther.png");
	CreatePokemon(10.7f, 2.9f,  2.0f, 2.0f, "Resources/Images/pokemons/staryu.png");
	CreatePokemon(9.3f, -7.3f,  2.5f, 2.5f, "Resources/Images/pokemons/licktung.png");
	CreatePokemon(-10.8f, 3.04f,  2.0f, 2.0f, "Resources/Images/pokemons/muk.png");
	CreatePokemon(-7.6f, -7.8f,  2.0f, 2.0f, "Resources/Images/pokemons/rapidash.png");
	CreatePokemon(2.5f, 0.8f, 2.0f, 2.0f, "Resources/Images/pokemons/alakazam.png");
	CreatePokemon(-4.5f, -7.8f, 2.0f, 2.0f, "Resources/Images/pokemons/ninetales.png");
	CreatePokemon(8.1f, -2.9f, 3.0f, 3.0f, "Resources/Images/pokemons/caterpie.png");

}
