#pragma once
#include "stdafx.h"

//centrum dowodzenia gr�

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

	Pikachu* pikachu;
	FullScreenActor* text_screen;
	TextActor* text;
	bool close_text_frame;

	struct Forms {

		String noun;
		String verb;
		String adjective;

	};

	void DoThings();
	bool Analyze(Forms sentence);
	void FindTaggedPokemons(ActorSet& bothTaggedActors, String adjective, String noun);
	
	virtual void MouseDownEvent(Vec2i screenCoordinates, MouseButtonInput button);

	std::vector<String> synonymsOfFight;
	std::vector<String> synonymsOfTalk;
	std::vector<String> synonymsOfHide;
	std::vector<String> synonymsOfGo;
	std::vector <Forms> SentencesList;
	int sentences_counter;
	int* pointer;
	bool* fightMode_pointer;
	bool* talkMode_pointer;
	bool* finished_pointer;
	bool done;

};

