#include "AuftraegeManager.h"

AuftraegeManager::AuftraegeManager(sf::Font font)
{


	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);
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

void AuftraegeManager::setText(string text)
{
	this->text.setString(text);
}

sf::Text AuftraegeManager::getText()
{
	return text; // Könnte probleme machen bitte später testen
}

void AuftraegeManager::draw(sf::RenderWindow& window)
{
	int i = 0;

	// Überschrift setzen und zeichnen
	text.setString("Aufträge:");
	text.setPosition(70, 70);
	window.draw(text);

	i++; // Damit die Aufträge unter der Überschrift anfangen (z.B. bei 30 Pixel Höhe statt 10)

	// Alle Aufträge durchgehen
	for (Auftrag* auftrag : alleAuftraege)
	{
		text.setPosition(10, 10 + i * 20); // Abstand von 20 Pixel pro Zeile
		window.draw(text); // Text direkt zeichnen
		i++;
	}
}

void AuftraegeManager::finishAuftrag(Auftrag* auftrag)
{
}



