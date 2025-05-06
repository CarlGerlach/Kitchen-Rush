#pragma once

#include <vector>
#include "list"
#include "Auftrag.h" 

using namespace std;
using namespace sf;

class AuftraegeManager
{
private:
	vector<Auftrag*> alleAuftraege;

	sf::Text text; // Das ist der Text, der die Aufträge anzeigt

public:
	AuftraegeManager(sf::Font font);
	~AuftraegeManager();

	void addAuftrag(Auftrag* auftrag);
	void removeAuftrag(Auftrag* auftrag);
	void clearAuftraege();
	int getAnzahlAuftraege();
	vector<Auftrag*> getAuftraege();
	Auftrag* getAuftrag(int index);

	void setText(string text);
	Text getText();
	void draw(sf::RenderWindow& window);

	void finishAuftrag(Auftrag* auftrag);
};

