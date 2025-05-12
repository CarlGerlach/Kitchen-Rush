#include <random>
#include "Bestellposition.h"
#include "Item.h"



Bestellposition::Bestellposition(ItemID id, int ini_anzahl)
{		
	switch (id)
	{
	case ItemID::PIZZA:
		position = ItemID::PIZZA;
		break;
	case ItemID::SALAT:
		position = ItemID::SALAT;
		break;
	case ItemID::COLA:
		position = ItemID::COLA;
		break;
	case ItemID::WASSER:
		position = ItemID::WASSER;
		break;
	default:
		break;
	}
	anzahl = ini_anzahl;
}

ItemID Bestellposition::getPosition()
{
	return position;
}

int Bestellposition::getAnzahl()
{
	return anzahl;
}





