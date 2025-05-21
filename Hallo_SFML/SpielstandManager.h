#pragma once

#include "Spieler.h"
#include "DeviceManager.h"

class SpielstandManager
{
private:
	Spieler* spieler;
public:
	SpielstandManager(Spieler* spieler);
	~SpielstandManager();

	static void saveGame(Spieler* spieler, DeviceManager* dm);
	static void loadGame(Spieler* spieler, DeviceManager* dm);
	//void deleteGame();
	//void listSaves();
	//void loadSave(int saveIndex);
	//void saveCurrentGameState();
	//void loadCurrentGameState();
	//void deleteCurrentGameState();
	//void listCurrentSaves();
};
