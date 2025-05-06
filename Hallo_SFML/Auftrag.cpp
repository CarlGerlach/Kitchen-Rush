#include "Auftrag.h"

Auftrag::Auftrag(Bestellposition* ini_position)
{
	this->derAuftrag[0] = ini_position;
}

void Auftrag::addAuftrag(Bestellposition* ini_position)
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
