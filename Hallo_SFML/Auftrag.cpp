#include "Auftrag.h"
#include <sstream>

int Auftrag::anzahlAktiv = 0;

Auftrag::Auftrag(Texture* ini_texture, Font ini_font)
{
	if (ini_texture == nullptr)return;

	font = ini_font;
	fensterAuftrag.setPosition(Vector2f(500 + anzahlAktiv * 170, -5));
	fensterAuftrag.setTexture(ini_texture);
	fensterAuftrag.setSize(Vector2f(200.f, 180.f));
	anzahlAktiv++;



}

Auftrag::Auftrag(Texture* ini_texture, Font ini_font, int id)
{
	if (ini_texture == nullptr)return;

	anzahlAktiv++;

	if(id == 0)
	{
		//cout << "Anzahl Aktiv vor erstellung: " << anzahlAktiv << endl;
		this->id = anzahlAktiv;

		fensterAuftrag.setPosition(Vector2f(500 + (anzahlAktiv - 1) * 170, -5));
		
		//cout << "Id Auftrag erstellung: " << id << endl;
	}
	else																							
	{
		///cout << "Test 2 Auftrag erstellen" << endl;
		this->id = id;

		fensterAuftrag.setPosition(Vector2f(500 + (id - 1) * 170, -5));
	}

	font = ini_font;
	fensterAuftrag.setTexture(ini_texture);
	fensterAuftrag.setSize(Vector2f(200.f, 180.f));
}



Auftrag::~Auftrag()
{
	for (int i = 0; i < 5; ++i)
	{
		delete derAuftrag[i];
		derAuftrag[i] = nullptr;
	}
}



void Auftrag::addBestellposition(Bestellposition* ini_position)
{ 
	for (int i = 0; i < 5; i++)
	{
		if (this->derAuftrag[i] == nullptr)
		{
			this->derAuftrag[i] = ini_position;
			return;
		}
	}

	//cout << "maximale Anzahl an Bestellpositionen erreicht" << endl;
}

Bestellposition* Auftrag::getBestellposition(int index)
{
	return this->derAuftrag[index];
}

int Auftrag::getAnzahlBestellopsitionen()
{
	int anzahl = 0;

	for (int i = 0; i < 5; i++)
	{
		if (derAuftrag[i] != nullptr)
		{
			anzahl++;
		}
	}

	return anzahl;
}

int Auftrag::getAnzahlAktiveAuftraege()
{
	return anzahlAktiv;
}

Vector2f Auftrag::getFensterAuftrag()
{
	return fensterAuftrag.getPosition();
}

int Auftrag::getId()
{
	return id;
}

void Auftrag::clearBestellpositionen()
{
	for (int i = 0; i < 5; i++)
	{
		if (derAuftrag[i] != nullptr)
		{		  
			delete derAuftrag[i];
			derAuftrag[i] = nullptr;
		}
	}
}

void Auftrag::decrementAnzahlAktiv()
{
	anzahlAktiv--;
}



void Auftrag::draw(RenderWindow& window)
{
	window.draw(fensterAuftrag);

	Text text;
	text.setFont(font);
	text.setCharacterSize(18);
	text.setFillColor(sf::Color::Black);
	
	stringstream idStream;
	idStream << this->getId();
	text.setString(idStream.str());


	// Position der ID (oben links im Auftrag)
	text.setPosition(fensterAuftrag.getPosition().x + 35,
		fensterAuftrag.getPosition().y + 20); // ID-Text etwas versetzt
	window.draw(text);

	
	for (int i = 0; i < 5; i++)
	{
		if (derAuftrag[i] != nullptr)
		{
			Text text;
			text.setFont(font);
			text.setCharacterSize(18);
			text.setFillColor(Color::Black);
																						  


			string itemName = Item::enumToString(derAuftrag[i]->getPosition());
			int anzahl = derAuftrag[i]->getAnzahl();

			stringstream ss;
			ss << anzahl << "x " << itemName;

			text.setString(ss.str());

			// Setze die Position, z. B. gestaffelt untereinander
			text.setPosition(fensterAuftrag.getPosition().x + 30,
				fensterAuftrag.getPosition().y + 57 + i * 25);

			window.draw(text);
		}
	}
}



