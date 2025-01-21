#include "Auftrag.h"

Auftrag::Auftrag()
{
}

Auftrag::Auftrag(string ini_gericht, int ini_anzahlSoll, int ini_winPoints)
{
	gericht = ini_gericht;
	anzahlSoll = ini_anzahlSoll;
	winPoints = ini_winPoints;
}

int Auftrag::getPoints()
{
	return winPoints;
}

int Auftrag::getAnzahlSoll()
{
	return anzahlSoll;
}

string Auftrag::getGericht()
{
	return gericht;
}







