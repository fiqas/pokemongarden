#pragma once
#include "stdafx.h"

class GotoTargetState : public AIBrainState {

public:
	GotoTargetState(const String& targetTag, float moveSpeed);
	~GotoTargetState(void);
	void Initialize( AIBrain* brain ) {_brain = brain;}
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

