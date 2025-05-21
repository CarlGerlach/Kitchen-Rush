#pragma once
#include "GeraetBase.h"

class Kuehlschrank : public GeraetBase
{
protected:
	void setupButtons(Font& newFont, Spieler* player) override;


public:
	Kuehlschrank(int Grindnumber, Font& newFont, Spieler* player, int ini_inventorySize);


};
