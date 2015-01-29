#include "stdafx.h"
#include <ctime>
#include <locale.h>

int main(int argc, char* argv[]) {
	
	srand(time(NULL));
	theWorld.Initialize();							// Inicjalizacja �wiata, bez niej �wiat gry nie zostanie utworzony
	theWorld.SetGameManager(new GardenManager());	// Ustawienie "centrum dowodzenia gr�"
	theWorld.StartGame();
	theWorld.Destroy();
	
	return 0;

}
