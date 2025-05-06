#pragma once
#include "GeraetBase.h"

class Ausgabe : public GeraetBase
{
protected:
	void setupButtons(Font& newFont, Spieler* player) override;


public:
	Ausgabe(int Grindnumber, Font& newFont, Spieler* player, int ini_inventorySize);
	

};
