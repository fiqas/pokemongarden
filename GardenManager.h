#pragma once
#include "stdafx.h"

//centrum dowodzenia gr¹

class GardenManager : public GameManager, public MouseListener {

public:

	GardenManager(void);
	virtual ~GardenManager(void);
	
	void CreatePokemon(float x, float y , float sizex, float sizey, String pathName);
	void CreateCollisionManager(float x, float y ,  float sx, float sy, String pathTag, Vector2 oposite, Vector2 side, Vector2 behind);
	void AddCollisionManager();
	void AddPokemons();
	void Update(float dt);
	void ReceiveMessage(Message* message);
	void Text(String display_text);
	void CloseText();
	void SynonymsLoader();
	void DoThings();
	void Analyze(int toDo);
	void FindTaggedPokemons(ActorSet& bothTaggedActors, String adjective, String noun);
	
	virtual void MouseDownEvent(Vec2i screenCoordinates, MouseButtonInput button);


	Pikachu* pikachu;
	Actor* concretepokemon;
	FullScreenActor* text_screen;
	FullScreenActor* pikachuOnAcid;
	TextActor* text;
	bool close_text_frame;

	AngelSampleHandle pikachuOrder;
	AngelSampleHandle pikachuQuestion;
	AngelSampleHandle pikachuLaughing;
	AngelSampleHandle acidSound;
	
	int counter;
	int* counterPtr;

	struct Forms {

		String noun;
		String verb;
		String adjective;

	};


	std::vector<String> synonymsOfFight;
	std::vector<String> synonymsOfTalk;
	std::vector<String> synonymsOfHide;
	std::vector<String> synonymsOfGo;
	std::vector <Forms> SentencesList;

	String specified_adjective;
	String specified_noun;

};

