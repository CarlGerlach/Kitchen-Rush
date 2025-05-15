#pragma once

#include "Spieler.h"

class SpielstandManager
{
private:
	Spieler* spieler;
public:
	SpielstandManager(Spieler* spieler);
	~SpielstandManager();

	static void saveGame(Spieler* spieler);
	static void loadGame(Spieler* spieler);
	//void deleteGame();
	//void listSaves();
	//void loadSave(int saveIndex);
	//void saveCurrentGameState();
	//void loadCurrentGameState();
	//void deleteCurrentGameState();
	//void listCurrentSaves();
};

