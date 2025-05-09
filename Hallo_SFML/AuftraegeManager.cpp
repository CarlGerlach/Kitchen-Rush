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

	// Schriftgröße für den Auftragstext und die ID setzen
	Text text;
	text.setFont(font);
	text.setCharacterSize(18);
	text.setFillColor(sf::Color::Black);

	for (size_t i = 0; i < alleAuftraege.size(); ++i)
	{
		if (alleAuftraege[i] != nullptr)
		{
			// Zeige die ID (Index) des Auftrags an
			stringstream idStream;
			idStream << "ID: " << i + 1;  // ID = Index im Vektor
			text.setString(idStream.str());

			// Position für den Auftrag und die ID
			alleAuftraege[i]->draw(window);

			// Position der ID (oben links im Auftrag)
			text.setPosition(alleAuftraege[i]->getFensterAuftrag().x + 5,
				alleAuftraege[i]->getFensterAuftrag().y + 20); // ID-Text etwas versetzt
			window.draw(text);
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

	while (Auftrag::getAnzahlAktiveAuftraege() < 5)
	{
		// Anzahl der Positionen pro Auftrag: 1–3
		int anzahlPositionen = rand() % 3 + 1;

		Auftrag* neuerAuftrag = new Auftrag(textureHintergrundAuftrag, font);

		for (int i = 0; i < anzahlPositionen; ++i)
		{
			// Zufällige ItemID wählen
			ItemID zufallsItem = Item::randomItem();

			// Zufällige Menge 1–5
			int menge = rand() % 5 + 1;
			cout << "Menge: " << menge << endl;

			Bestellposition* pos = new Bestellposition(zufallsItem, menge);
			neuerAuftrag->addBestellposition(pos);
		}

		addAuftrag(neuerAuftrag);
	}
}

void AuftraegeManager::finishAuftrag(Auftrag* auftrag)
{
}



