#include "Bestellposition.h"

Bestellposition::Bestellposition(ItemID id, int ini_anzahl)
{		
	switch (id)
	{
	case ItemID::PIZZA:
		position = ItemID::PIZZA;
		break;
	default:
		break;

	}


}

ItemID Bestellposition::getPosition()
{
	return position;
}

int Bestellposition::getAnzahl()
{
	return anzahl;
}
