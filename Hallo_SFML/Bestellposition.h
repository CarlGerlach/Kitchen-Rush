#pragma once 
#include "Item.h"


class Bestellposition
{
private:
	ItemID position;
	int anzahl;

public:
	Bestellposition(ItemID id, int ini_anzahl);

	ItemID getPosition();
	int getAnzahl();






};

