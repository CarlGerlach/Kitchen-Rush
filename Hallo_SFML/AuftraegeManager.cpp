#include "AuftraegeManager.h"
#include <sstream>
using namespace std;
using namespace sf;



AuftraegeManager::AuftraegeManager(sf::Font ini_font, Texture* ini_textureHintergrundAuftrag)
{	
	if (ini_textureHintergrundAuftrag != nullptr)
	{
		textureHintergrundAuftrag = ini_textureHintergrundAuftrag;
	}

	letzterAuftragId = 0;
	font = ini_font;
}

AuftraegeManager::~AuftraegeManager()
{
}

void AuftraegeManager::addAuftrag(Auftrag* ini_auftrag)
{
	alleAuftraege.push_back(ini_auftrag);
}

// Chatgpt
void AuftraegeManager::removeAuftrag(Auftrag* ini_auftrag)
{
	auto it = std::find(alleAuftraege.begin(), alleAuftraege.end(), ini_auftrag);
	if (it != alleAuftraege.end())
	{
		//Ändern auf Getter und dann set um nicht Static
		//Ändern, dass auch die Bestellpositionen gelöscht werden -> VOn unten aus alles nach oben hin weglöschen

		cout << "Auftrag ID remove: " << ini_auftrag->getId() << endl;
		letzterAuftragId = ini_auftrag->getId() + 1;
		cout << "Letzte Auftrag ID bei Remove: " << letzterAuftragId << endl;

		Auftrag::decrementAnzahlAktiv();
		delete* it;                    // Speicher freigeben
		alleAuftraege.erase(it);      // Zeiger aus dem Vektor entfernen
	}
}



void AuftraegeManager::clearAuftraege()
{
	for (Auftrag* auftrag : alleAuftraege)
	{
		delete auftrag;
	}
	alleAuftraege.clear();
	
}

int AuftraegeManager::getAnzahlAuftraege()
{
	return alleAuftraege.size();
}

vector<Auftrag*> AuftraegeManager::getAuftraege()
{
	return alleAuftraege;
}

Auftrag* AuftraegeManager::getAuftrag(int index)
{
	if (index < 0 || index >= alleAuftraege.size())
	{
		return nullptr;
	}
	auto it = alleAuftraege.begin();
	advance(it, index);	 //Gehe bis zum Auftrag des index
	return *it;
}


void AuftraegeManager::draw(sf::RenderWindow& window)
{
	updateAuftraege();


	for (size_t i = 0; i < alleAuftraege.size(); ++i)
	{
		if (alleAuftraege[i] != nullptr)
		{

			// Position für den Auftrag und die ID
			alleAuftraege[i]->draw(window);
		}
	}
}





void AuftraegeManager::updateAuftraege()
{

	//Zufallsinitialisierung nur einmal
	static bool seeded = false;
	if (!seeded) 
	{
		srand(static_cast<unsigned>(time(0)));
		seeded = true;
	}

	std::cout << "Aktive Aufträge: " << Auftrag::getAnzahlAktiveAuftraege() << std::endl;

	while (Auftrag::getAnzahlAktiveAuftraege() < 5)
	{
		cout << "Neuer Auftrag wird erstellt " << endl;

		// Anzahl der Positionen pro Auftrag: 1–3
		int anzahlPositionen = rand() % 3 + 1;


		//Auftrag* neuerAuftrag = nullptr;

		cout << "Letzte AuftragID in update(): " << letzterAuftragId << endl;
		Auftrag* neuerAuftrag = new Auftrag(textureHintergrundAuftrag, font, letzterAuftragId);
	
		
	
		//Auftrag* neuerAuftrag = new Auftrag(textureHintergrundAuftrag, font);
	
		


		for (int i = 0; i < anzahlPositionen; ++i)
		{
			// Zufällige ItemID wählen
			ItemID zufallsItem = Item::randomItem();

			// Zufällige Menge 1–5
			int menge = rand() % 5 + 1;
			cout << "Menge: " << menge << endl;

			Bestellposition* pos = new Bestellposition(zufallsItem, menge);

			cout << "Test 1" << endl;
			cout << "Letzte Auftrag ID: " << letzterAuftragId << endl;
			neuerAuftrag->addBestellposition(pos);
			cout << "Test 2" << endl;
		}


		addAuftrag(neuerAuftrag);

		cout << "Neuer Auftrag wurde erstellt" << endl;
	}
}

void AuftraegeManager::finishAuftrag(Auftrag* auftrag)
{

}








