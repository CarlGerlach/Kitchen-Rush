#pragma once
#include "GeraetBase.h"

class Storage : public GeraetBase
{
protected:
	void setupButtons(Font& newFont, Spieler* player) override;


public:
	Storage(int Grindnumber, Font& newFont, Spieler* player);


};

