#pragma once
#include "GeraetBase.h"
#include "AuftraegeManager.h"

class Ausgabe : public GeraetBase
{

protected:
	void setupButtons(Font& newFont, Spieler* player) override;
	AuftraegeManager* derAuftraegeManager;

public:
	Ausgabe(int Grindnumber, Font& newFont, Spieler* player, int ini_inventorySize, AuftraegeManager* ini_derAuftraegeManager);
	bool checkAuftragErf�llbar(int gesuchteID);
	bool versucheAuftragZuErf�llen(int auftragIndex);

};
