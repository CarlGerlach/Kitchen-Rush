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
	Texture* textureHintergrundAuftrag;
	int letzterAuftragId;
	Font font;


public:
	AuftraegeManager(sf::Font ini_font, Texture* ini_textureHintergrundAuftrag);
	~AuftraegeManager();

	void addAuftrag(Auftrag* auftrag);
	void removeAuftrag(Auftrag* auftrag);
	void clearAuftraege();
	int getAnzahlAuftraege();
	vector<Auftrag*> getAuftraege();
	Auftrag* getAuftrag(int index);
	Auftrag* getAuftragMitID(int gesuchteID);


	void draw(sf::RenderWindow& window);

	void updateAuftraege();

	void finishAuftrag(Auftrag* auftrag);



};

