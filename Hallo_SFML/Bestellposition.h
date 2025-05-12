#pragma once 
#include <random>
#include <iostream>
#include "Item.h"

using namespace std;
using namespace sf;




class Bestellposition
{
private:
	ItemID position;
	int anzahl;

public:
	Bestellposition(ItemID id, int ini_anzahl);

	int getPointsForItem(ItemID searchedId);
	ItemID getPosition();
	int getAnzahl();








};

