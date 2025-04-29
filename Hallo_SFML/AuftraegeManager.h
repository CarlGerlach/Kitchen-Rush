#pragma once

#include "list"
#include "Auftrag.h"

class AuftraegeManager
{
private:
	list<Auftrag*> auftraege;
	int anzahlAuftraege;

	sf::Text text; // Das ist der Text, der die Aufträge anzeigt

public:
	AuftraegeManager(sf::Font *font);
	~AuftraegeManager();

	void addAuftrag(Auftrag* auftrag);
	void removeAuftrag(Auftrag* auftrag);
	void clearAuftraege();
	int getAnzahlAuftraege();
	list<Auftrag*> getAuftraege();
	Auftrag* getAuftrag(int index);

	void setText(string text);
	sf::Text getText();
	void draw(sf::RenderWindow& window);

	void finishAuftrag(Auftrag* auftrag);
};

