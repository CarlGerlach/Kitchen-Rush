#pragma once
#include "GeraetBase.h"

class Muell : public GeraetBase
{
protected:
	void setupButtons(Font& newFont, Spieler* player) override;


public:
	Muell(int gridnumber, Font& newFont, Spieler* player, int ini_inventorySize);


};
