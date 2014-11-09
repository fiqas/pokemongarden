#pragma once
#include "stdafx.h"

class GotoTargetState : public AIBrainState {

public:
	GotoTargetState(const String& targetTag, float moveSpeed, AIBrain* brain);
	~GotoTargetState(void);

	void Initialize( AIBrain* brain ) {
		std::cout << "mózg : " << brain << std::endl;
		_brain = brain;
		std::cout << "mózg : " << _brain << std::endl;
		std::cout << "Imie : " << _brain->GetActor()->GetName() << std::endl;
	}
	void Update(float dt);
	void BeginState( AIBrainState* previousState );
	void EndState( AIBrainState* nextState );
	GotoTargetAIEvent* gototargetaievent;

protected:
	void GotoState( const String& id );
	AIEvent* RegisterEvent( AIEvent* newEvent );
	void UnregisterEvent( AIEvent* oldEvent );

	String _targetTag;
	float _moveSpeed;

};

