#include "AuftraegeManager.h"
#include "TableManager.h"
#include "Auftrag.h"
#include "mySound.h"
#include "PauseManager.h"
#include <sstream>
using namespace std;
using namespace sf;



AuftraegeManager::AuftraegeManager(sf::Font ini_font, Texture* ini_textureHintergrundAuftrag, mySound* ini_soundManager, TableManager* ini_tm, Spieler* ini_spieler)
{
	if (ini_textureHintergrundAuftrag != nullptr)
		textureHintergrundAuftrag = ini_textureHintergrundAuftrag;

	spieler = ini_spieler;
	tm = ini_tm;
	letzterAuftragId = 0;
	font = ini_font;
	soundManager = ini_soundManager;  // <--- Soundmanager speichern
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
		letzterAuftragId = ini_auftrag->getId();
		ini_auftrag->clearBestellpositionen();
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

Auftrag* AuftraegeManager::getAuftragMitID(int gesuchteID)
{
	for (Auftrag* auftrag : alleAuftraege)
	{
		if (auftrag != nullptr && auftrag->getId() == gesuchteID)
		{
			return auftrag;
		}
	}
	return nullptr; // Kein passender Auftrag gefunden
}

void AuftraegeManager::setTableManager(TableManager* tm)
{
	this->tm = tm;
}


void AuftraegeManager::draw(sf::RenderWindow& window, float deltaTime, PauseManager& pauseManager)
{
	if (pauseManager.getGameOver() == true)
	{																	  
		pauseManager.togglePause();
	}
	
	updateAuftraege(deltaTime,pauseManager);


	for (size_t i = 0; i < alleAuftraege.size(); ++i)
	{
		if (alleAuftraege[i] != nullptr)
		{

			// Position für den Auftrag und die ID
			alleAuftraege[i]->draw(window);
		}
	}
}





void AuftraegeManager::updateAuftraege(float deltaTime, PauseManager& pauseManager)
{

	//Zufallsinitialisierung nur einmal
	static bool seeded = false;
	if (!seeded) 
	{
		srand(static_cast<unsigned>(time(0)));
		seeded = true;
	}

	for (Auftrag* auftrag : alleAuftraege)
	{
		cout << "Leben: " << spieler->getLeben() << endl;
		if (auftrag)
			auftrag->update(deltaTime, pauseManager);
		if (auftrag->getAbgelaufen())
		{
			if (this->spieler->lebenReduzieren() == false)
			{
				pauseManager.setGameOver(true);
				pauseManager.togglePause();
			}
			else
			{
				removeAuftrag(auftrag);
				einAuftragAbgelaufen = true;
			}
			
		}
		//cout << "Leben: " << spieler->getLeben() << endl;

	}


	std::cout << "Aktive Aufträge: " << Auftrag::getAnzahlAktiveAuftraege() << std::endl;

	while (Auftrag::getAnzahlAktiveAuftraege() < 5 && tm->sollNeuerAuftragErstelltWerden() || Auftrag::getAnzahlAktiveAuftraege() < 5 && einAuftragAbgelaufen)
	{
		if (einAuftragAbgelaufen)
		{
			einAuftragAbgelaufen = false;
		}


		// Anzahl der Positionen pro Auftrag: 1–3
		int anzahlPositionen = rand() % 4 + 1;


		//Auftrag* neuerAuftrag = nullptr;

		cout << "Letzte AuftragID in update(): " << letzterAuftragId << endl;
		Auftrag* neuerAuftrag = new Auftrag(textureHintergrundAuftrag, font, letzterAuftragId);
	
	

		for (int i = 0; i < anzahlPositionen;)
		{
			// Zufällige ItemID wählen
			ItemID zufallsItem = Item::randomItem();

			// Prüfen, ob die ItemID bereits im Auftrag vorhanden ist
			bool schonVorhanden = false;
			for (int j = 0; j < neuerAuftrag->getAnzahlBestellopsitionen(); ++j)
			{
				if (neuerAuftrag->getBestellposition(j)->getPosition() == zufallsItem)
				{
					schonVorhanden = true;
					break;
				}
			}

			if (schonVorhanden)
				continue; // gleiche Zutat -> neue ziehen

			// Zufällige Menge 1–5
			int menge = rand() % 5 + 1;
			Bestellposition* pos = new Bestellposition(zufallsItem, menge);
			neuerAuftrag->addBestellposition(pos);

			++i; // Nur erhöhen, wenn eine einzigartige Zutat hinzugefügt wurde
		}



		addAuftrag(neuerAuftrag);


		//cout << "Neuer Auftrag wurde erstellt" << endl;
	}
}

void AuftraegeManager::finishAuftrag(Auftrag* auftrag)
{
	if (auftrag == nullptr) return;

	// Auftrag aus der Liste entfernen
	removeAuftrag(auftrag);

	// Sound abspielen
	if (soundManager)
		soundManager->playAuftragAbgeschlossenSound();
}



