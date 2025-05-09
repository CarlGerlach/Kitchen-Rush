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

public:
	Auftrag(Texture* ini_texture, Font ini_font);
	~Auftrag();


	void addBestellposition(Bestellposition* ini_position);
	
	Bestellposition* getBestellposition(int index);

	int getAnzahlBestellopsitionen();
	static int getAnzahlAktiveAuftraege();
	Vector2f getFensterAuftrag();
	
	static void decrementAnzahlAktiv();


	void draw(RenderWindow& window);

};

