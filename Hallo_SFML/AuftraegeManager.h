#pragma once

#include <vector>
#include "list"
#include "Auftrag.h" 
#include "mySound.h"
#include "PauseManager.h"
#include "TableManager.h"

using namespace std;
using namespace sf;

class TableManager;

class AuftraegeManager
{
private:
	vector<Auftrag*> alleAuftraege;
	Texture* textureHintergrundAuftrag;
	int letzterAuftragId;
	Font font;
	Spieler* spieler;

	mySound* soundManager;
	TableManager* tm;
	bool einAuftragAbgelaufen = false;



public:
	AuftraegeManager(sf::Font ini_font, Texture* ini_textureHintergrundAuftrag, mySound* ini_soundManager, TableManager* ini_tm, Spieler* ini_spieler);
	~AuftraegeManager();

	void addAuftrag(Auftrag* auftrag);
	void removeAuftrag(Auftrag* auftrag);
	void clearAuftraege();

	int getAnzahlAuftraege();
	vector<Auftrag*> getAuftraege();
	Auftrag* getAuftrag(int index);
	Auftrag* getAuftragMitID(int gesuchteID);

	void setTableManager(TableManager* tm);


	void draw(sf::RenderWindow& window, float deltaTime, PauseManager& pauseManager);

	void updateAuftraege(float deltaTime, PauseManager& pauseManager);

	void finishAuftrag(Auftrag* auftrag);



};