#include "AuftraegeManager.h"

AuftraegeManager::AuftraegeManager(sf::Font *font)
{
	anzahlAuftraege = 0;
	auftraege.clear();

	text.setFont(*font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);
}

AuftraegeManager::~AuftraegeManager()
{
}

void AuftraegeManager::addAuftrag(Auftrag* auftrag)
{
	auftraege.push_back(auftrag);
	anzahlAuftraege++;
	// cout << auftraege.size() << endl;
	// cout << auftrag->getGericht() << endl;
	// cout << auftrag->getAnzahlSoll() << endl;
	// cout << auftrag->getPoints() << endl;
}

void AuftraegeManager::removeAuftrag(Auftrag* auftrag)
{
	auftraege.remove(auftrag);
	anzahlAuftraege--;
	// cout << auftraege.size() << endl;
	// cout << auftrag->getGericht() << endl;
	// cout << auftrag->getAnzahlSoll() << endl;
	// cout << auftrag->getPoints() << endl;
	delete auftrag;
	auftrag = nullptr;
}

void AuftraegeManager::clearAuftraege()
{
	for (Auftrag* auftrag : auftraege)
	{
		delete auftrag;
	}
	auftraege.clear();
	anzahlAuftraege = 0;
	// cout << auftraege.size() << endl;
	// cout << auftrag->getGericht() << endl;
	// cout << auftrag->getAnzahlSoll() << endl;
	// cout << auftrag->getPoints() << endl;
}

int AuftraegeManager::getAnzahlAuftraege()
{
	return auftraege.size();
}

list<Auftrag*> AuftraegeManager::getAuftraege()
{
	return list<Auftrag*>();
}

Auftrag* AuftraegeManager::getAuftrag(int index)
{
	if (index < 0 || index >= auftraege.size())
	{
		return nullptr;
	}
	auto it = auftraege.begin();
	advance(it, index);
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
	text.setPosition(10, 10);
	window.draw(text);

	i++; // Damit die Aufträge unter der Überschrift anfangen (z.B. bei 30 Pixel Höhe statt 10)

	// Alle Aufträge durchgehen
	for (Auftrag* auftrag : auftraege)
	{
		text.setString(auftrag->getGericht() + "  ||  " + std::to_string(auftrag->getAnzahlSoll()) + "x " + std::to_string(auftrag->getPoints()) + "p");
		text.setPosition(10, 10 + i * 20); // Abstand von 20 Pixel pro Zeile
		window.draw(text); // Text direkt zeichnen
		i++;
	}
}



