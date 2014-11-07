#include "stdafx.h"
#include "GotoTargetState.h"


GotoTargetState::GotoTargetState(const String& targetTag, float moveSpeed) {

	_targetTag = targetTag;
	_moveSpeed = moveSpeed;
	gototargetaievent = new GotoTargetAIEvent();
	RegisterEvent(gototargetaievent);

}


GotoTargetState::~GotoTargetState(void) {

}

void GotoTargetState::Update(float dt) {

	AIBrainState::Update(dt);

}

void GotoTargetState::BeginState( AIBrainState* previousState ) {

	std::cout << "inicjalizuje gotosquirtle" << std::endl;
	gototargetaievent->Initialize( _targetTag, _moveSpeed );

}

void GotoTargetState::EndState( AIBrainState* nextState ) {

	AIBrainState::EndState(nextState);

}
	
void GotoTargetState::GotoState( const String& id ) {

	std::cout << "gotostate" << std::endl;
	AIBrainState::GotoState( id );
}

AIEvent* GotoTargetState::RegisterEvent( AIEvent* newEvent ) {

	return AIBrainState::RegisterEvent( newEvent );

}

void GotoTargetState::UnregisterEvent( AIEvent* oldEvent ) {

	AIBrainState::UnregisterEvent( oldEvent );

}