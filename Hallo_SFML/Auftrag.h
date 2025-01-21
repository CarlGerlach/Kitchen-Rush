#pragma once
#include <iostream>
#include "Item.h"

using namespace std;


class Auftrag
{
private:
	string gericht;
	int anzahlSoll;
	int winPoints;

public:
	Auftrag();
	Auftrag(string ini_gericht, int ini_anzahlSoll, int ini_winPoints);

	int getPoints();
	int getAnzahlSoll();
	string getGericht();





};

