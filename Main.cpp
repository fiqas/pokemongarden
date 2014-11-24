
#include "stdafx.h"

int main(int argc, char* argv[]) {
	
	theWorld.Initialize();
	theWorld.SetGameManager(new GardenManager());

	theWorld.StartGame();
	
	theWorld.Destroy();
	
	return 0;

}
