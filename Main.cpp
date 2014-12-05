#include "stdafx.h"

int main(int argc, char* argv[]) {
	
	theWorld.Initialize();							// Inicjalizacja œwiata, bez niej œwiat gry nie zostanie utworzony
	theWorld.SetGameManager(new GardenManager());	// Ustawienie "centrum dowodzenia gr¹"

	theWorld.StartGame();
	
	theWorld.Destroy();
	
	return 0;

}
