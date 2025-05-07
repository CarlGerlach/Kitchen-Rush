#pragma once
#include <iostream>
#include "Item.h"
#include "Bestellposition.h"

using namespace std;
using namespace sf;


class Auftrag
{
private:
	Bestellposition* derAuftrag[5];
	RectangleShape fensterAuftrag;
	Texture* texture;

	
public:
	Auftrag(Bestellposition* ini_position, Texture* ini_texture);

	void addBestellposition(Bestellposition* ini_position);
	
	Bestellposition* getBestellposition(int index);

};

