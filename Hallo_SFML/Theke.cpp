#include "Theke.h"

void Theke::setInventar(string itemName, sf::Texture texture)
{
	inventar = new Item(itemName, texture);
}

void Theke::setAuftrag(string ini_gericht, int ini_anzahlSoll, int ini_winPoints)
{
	derAuftrag = new Auftrag(ini_gericht, ini_anzahlSoll, ini_winPoints);
}

void Theke::anzeigeTheke()
{
	
	if (inventar)
	{
		this->getFenster()->addButton(710 + 50, 240 + 250, 200, 40, "Inventar: " + inventar->getTyp(), sf::Color::White, sf::Color::Black, []() {});
	}

	if (derAuftrag)
	{

		this->getFenster()->addButton(710 + 50, 240 + 100, 200, 40, "Gericht: " + derAuftrag->getGericht(), sf::Color::White, sf::Color::Black, []() {});
		this->getFenster()->addButton(710 + 50, 240 + 150, 200, 40, "Wie oft: " + derAuftrag->getAnzahlSoll(), sf::Color::White, sf::Color::Black, []() {});
	}
	



}
