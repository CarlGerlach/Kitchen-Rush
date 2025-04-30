#pragma once
#include "GeraetBase.h"

class Mixer : public GeraetBase
{
protected:
	void setupButtons(Font& newFont, Spieler* player) override;


public:
	Mixer(int Grindnumber, Font& newFont, Spieler* player);
	bool makeTeig();

};

