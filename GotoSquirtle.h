#pragma once
#include "stdafx.h"

class GotoSquirtle : public GotoTargetAIEvent
{
public:
	GotoSquirtle* Initialize(const String& targetTag, float moveSpeed, float arrivalDist = 0.2f);
	GotoSquirtle();
	~GotoSquirtle(void);
	void Update(float dt);
};

