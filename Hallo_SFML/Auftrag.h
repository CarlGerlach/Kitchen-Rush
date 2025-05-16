#pragma once
#include <iostream>
#include "Item.h"
#include "Spieler.h"
#include "Bestellposition.h"
#include "PauseManager.h"

using namespace std;
using namespace sf;


class Auftrag
{

private:
	Bestellposition* derAuftrag[5];
	RectangleShape fensterAuftrag;
	Font font;
	static int anzahlAktiv;
	int id;
	bool wurdeInitialisiert;

	float lebensdauer = 60.f;      
	float timer = 0.f;             // aktuelle verstrichene Zeit
	bool abgelaufen = false;
	bool lebenverloren = false;


	Spieler* spieler; // Zeiger auf Spieler
public:
	Auftrag(Texture* ini_texture, Font ini_font);
	Auftrag(Texture* ini_texture, Font ini_font, int id);
	~Auftrag();


	void addBestellposition(Bestellposition* ini_position);
	
	Bestellposition* getBestellposition(int index);

	int getAnzahlBestellopsitionen();
	static int getAnzahlAktiveAuftraege();
	Vector2f getFensterAuftrag();
	int getId();

	void clearBestellpositionen();
	
	
	static void decrementAnzahlAktiv();
	void update(float deltaTime, PauseManager& pauseManager);

	void setSpieler(Spieler* s);

	void draw(RenderWindow& window);

};

