#include "AuftraegeManager.h"
#include "Auftrag.h"
#include "mySound.h"
#include "PauseManager.h"
#include <sstream>
using namespace std;
using namespace sf;



AuftraegeManager::AuftraegeManager(sf::Font ini_font, Texture* ini_textureHintergrundAuftrag, mySound* ini_soundManager)
{
	if (ini_textureHintergrundAuftrag != nullptr)
		textureHintergrundAuftrag = ini_textureHintergrundAuftrag;

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
	if (ini_auftrag == nullptr) return;

	letzterAuftragId = ini_auftrag->getId();
	ini_auftrag->clearBestellpositionen();
	Auftrag::decrementAnzahlAktiv();
	delete ini_auftrag;  // Speicher freigeben
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


void AuftraegeManager::draw(sf::RenderWindow& window, float deltaTime, PauseManager& pauseManager)
{
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
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned>(time(0)));
        seeded = true;
    }

    for (size_t i = 0; i < alleAuftraege.size(); ++i)
    {
        Auftrag* auftrag = alleAuftraege[i];

        if (!auftrag) continue;

        auftrag->update(deltaTime, pauseManager);

        // Erledigte oder abgelaufene Aufträge ersetzen
        if (auftrag->isExpired() || auftrag->isFinished())
        {
            // Wenn Auftrag abgelaufen ist, Leben abziehen
            if (auftrag->isExpired() && spieler)
            {
                spieler->verliereLeben();
            }

            Vector2f altePosition = auftrag->getFensterAuftrag();

            auftrag->clearBestellpositionen();
            delete auftrag;
            Auftrag::decrementAnzahlAktiv();

            // Neuen Auftrag an gleicher Stelle erzeugen ...
            // [rest bleibt wie vorher]


            // Neuen Auftrag an genau dieser Stelle erstellen
            Auftrag* neuerAuftrag = new Auftrag(textureHintergrundAuftrag, font, ++letzterAuftragId);
            if (spieler)
                neuerAuftrag->setSpieler(spieler);

            // Fenster-Position übernehmen
            neuerAuftrag->setFensterPosition(altePosition);

            // Bestellpositionen hinzufügen
            int anzahlPositionen = rand() % 3 + 1;
            for (int j = 0; j < anzahlPositionen; ++j)
            {
                ItemID item = Item::randomItem();
                int menge = rand() % 5 + 1;
                neuerAuftrag->addBestellposition(new Bestellposition(item, menge));
            }

            alleAuftraege[i] = neuerAuftrag;  // exakt dieselbe Stelle ersetzen
        }
    }

    // Wenn aus irgendeinem Grund weniger als 5 Aufträge vorhanden sind, auffüllen
    while (alleAuftraege.size() < 5)
    {
        Auftrag* neuerAuftrag = new Auftrag(textureHintergrundAuftrag, font, ++letzterAuftragId);
        if (spieler)
            neuerAuftrag->setSpieler(spieler);

        int anzahlPositionen = rand() % 3 + 1;
        for (int j = 0; j < anzahlPositionen; ++j)
        {
            ItemID item = Item::randomItem();
            int menge = rand() % 5 + 1;
            neuerAuftrag->addBestellposition(new Bestellposition(item, menge));
        }

        alleAuftraege.push_back(neuerAuftrag);
    }

    
    if (spieler && spieler->getLeben() == 0)
    {
        pauseManager.togglePause();
        pauseManager.setGameOver(true);
    }

}





void AuftraegeManager::finishAuftrag(Auftrag* auftrag)
{
	if (!auftrag) return;

	auftrag->markAsFinished(); // Auftrag als fertig markieren

	if (soundManager)
		soundManager->playAuftragAbgeschlossenSound();
}





