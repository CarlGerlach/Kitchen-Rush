#pragma once

#include <vector>
#include "list"
#include "Spieler.h"
#include "Auftrag.h" 
#include "mySound.h"
#include "PauseManager.h"

using namespace std;
using namespace sf;

class AuftraegeManager
{
private:
	vector<Auftrag*> alleAuftraege;
	Texture* textureHintergrundAuftrag;
	int letzterAuftragId;
	Font font;

	mySound* soundManager;

	Spieler* spieler = nullptr;

public:
	AuftraegeManager(sf::Font ini_font, Texture* ini_textureHintergrundAuftrag, mySound* ini_soundManager);
	~AuftraegeManager();

	void addAuftrag(Auftrag* auftrag);
	void removeAuftrag(Auftrag* auftrag);
	void clearAuftraege();
	int getAnzahlAuftraege();
	vector<Auftrag*> getAuftraege();
	Auftrag* getAuftrag(int index);
	Auftrag* getAuftragMitID(int gesuchteID);


	void draw(sf::RenderWindow& window, float deltaTime, PauseManager& pauseManager);

	void updateAuftraege(float deltaTime, PauseManager& pauseManager);

	void finishAuftrag(Auftrag* auftrag);


	void setSpieler(Spieler* s) { spieler = s; }

};