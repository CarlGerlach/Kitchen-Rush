#include "Auftrag.h"

Auftrag::Auftrag()
{
	gericht = "";
	anzahlSoll = 0;
	winPoints = 0;
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

void Auftrag::setIsDone(bool done)
{
	this->isDone = done;
}

bool Auftrag::getIsDone()
{
	return this->isDone;
}







