#pragma once
#include "GeraetBase.h"

class Salatbar : public GeraetBase
{
protected:
	void setupButtons(Font& newFont, Spieler* player) override;


public:
	Salatbar(int Grindnumber, Font& newFont, Spieler* player, int ini_inventorySize);


};
