#include "stdafx.h"
#include "GotoSquirtle.h"


GotoSquirtle* GotoSquirtle::Initialize(const String& targetTag, float moveSpeed, float arrivalDist) {
	
	std::cout << "wchodze w gotosquirtle" << std::endl;
	GotoTargetAIEvent::Initialize(targetTag, moveSpeed, arrivalDist);

	return this;
	
}

void GotoSquirtle::Update(float dt) {

	GotoTargetAIEvent::Update(dt);

	if(theInput.IsKeyDown(ANGEL_KEY_S)) {

		GotoTargetAIEvent::Initialize("Squirtle", 0.2f);

	}

}

GotoSquirtle::GotoSquirtle() {

}

GotoSquirtle::~GotoSquirtle(void) {

}
