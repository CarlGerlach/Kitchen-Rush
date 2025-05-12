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

int Bestellposition::getPointsForItem(ItemID searchedId)
{
	switch (searchedId)
	{
	case ItemID::WASSER: return 1;
	//case ItemID::MEHL:   return 2;
	//case ItemID::TEIG:   return 3;
	//case ItemID::TOMATE: return 2;
	case ItemID::PIZZA:  return 5;
	case ItemID::COLA:   return 2;
	case ItemID::SALAT:  return 3;
	default:             return 0;
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





