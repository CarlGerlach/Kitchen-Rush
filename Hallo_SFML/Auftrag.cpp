#include "Auftrag.h"

Auftrag::Auftrag(Bestellposition* ini_position, Texture* ini_texture)
{
	if (texture == nullptr)return;
	fensterAuftrag.setSize(Vector2f(100.f, 50.f));
	
	this->derAuftrag[0] = ini_position;
}

void Auftrag::addBestellposition(Bestellposition* ini_position)
{ 
	for (int i = 0; i < 5; i++)
	{
		if (this->derAuftrag[i] == nullptr)
		{
			this->derAuftrag[i] = ini_position;
			break;
		}
	}

	cout << "maximale Anzahl an Bestellpositionen erreicht" << endl;
}

Bestellposition* Auftrag::getBestellposition(int index)
{
	return this->derAuftrag[index];
}
