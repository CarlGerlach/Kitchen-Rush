#include "Auftrag.h"

int Auftrag::anzahlAktiv = 0;

Auftrag::Auftrag(Bestellposition* ini_position, Texture* ini_texture, Font ini_font)
{
	if (ini_texture == nullptr)return;
	

	font = ini_font;
	fensterAuftrag.setTexture(ini_texture);
	fensterAuftrag.setSize(Vector2f(100.f, 50.f));
	anzahlAktiv++;

	
	this->derAuftrag[0] = ini_position;
}

void Auftrag::addBestellposition(Bestellposition* ini_position)
{ 
	for (int i = 0; i < 5; i++)
	{
		if (this->derAuftrag[i] == nullptr)
		{
			this->derAuftrag[i] = ini_position;
			anzahlAktiv++;
			break;
		}
	}

	cout << "maximale Anzahl an Bestellpositionen erreicht" << endl;
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

void Auftrag::draw(RenderWindow& window)
{
	window.draw(fensterAuftrag);


}
