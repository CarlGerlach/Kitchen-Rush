#pragma once
#include <iostream>
#include "Item.h"
#include "Auftrag.h"
#include "Mapelement.h"


using namespace std;



class Theke : public Mapelement
{
private:
	Item* inventar;
	Auftrag* derAuftrag;

public:
	Theke(int gridNr, sf::Font font) : Mapelement(gridNr, font)
	{
		inventar = nullptr;
		derAuftrag = nullptr;
	}

	void setInventar(string itemName, sf::Texture texture);

	void setAuftrag(string ini_gericht, int ini_anzahlSoll, int ini_winPoints);
	
	void anzeigeTheke();




};

