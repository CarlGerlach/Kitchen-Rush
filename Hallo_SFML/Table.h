#pragma once
#include <iostream>
#include "GeraetBase.h"
#include "AuftraegeManager.h"
#include "Bot.h"
#include <vector>
#include <memory>

using namespace std;
using namespace sf;

class AuftraegeManager;

class Table : public GeraetBase
{
protected:
	void setupButtons(Font& newFont, Spieler* player) override;
	AuftraegeManager* am;
	static int index;
	int tableID;
	Font font;
	

	std::unique_ptr<Bot> derBot;
	Vector2f zielPosition = Vector2f(1000.f,800.f); // Rückgabeort
	bool botAktiv;
	bool isBotAmTable;
	bool auftragErledigtUndAngekommen = false;

	bool warImTableBereich = false;


public:
	Table(int gridnumber, Font& newFont, Spieler* player, int ini_inventorySize, AuftraegeManager* ini_am);
	bool checkAuftragErfüllbar();
	bool versucheAuftragZuErfüllen();

	void updateBot();
	void drawBot(RenderWindow& window);
	void drawTableID(RenderWindow& window);

	void setZielPosition(Vector2f& pos); // Ziel (z.B. Lager)

	bool getIsBotAmTable();
	RectangleShape getCollisionBounds();


	

	bool darfNeuenAuftragErstellen();
	void resetNeuenAuftragErlaubt();

};
