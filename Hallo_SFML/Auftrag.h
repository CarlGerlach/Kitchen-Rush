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
	Font font;
	static int anzahlAktiv;

	Auftrag(Bestellposition* ini_position, Texture* ini_texture, Font ini_font);

	void addBestellposition(Bestellposition* ini_position);
	
	Bestellposition* getBestellposition(int index);

	int getAnzahlBestellopsitionen();


	void draw(RenderWindow& window);

};

