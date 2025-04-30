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

	bool isDone;

	//Items als Gerüst bereit halten, speichern in Liste, abfragen per ENUM und SWITCH CASE damit der string "gericht" und die benötigten items automatisch je nach case bestimmt werden

public:
	Auftrag();
	Auftrag(string ini_gericht, int ini_anzahlSoll, int ini_winPoints);

	int getPoints();
	int getAnzahlSoll();
	string getGericht();


	void setIsDone(bool done);
	bool getIsDone();


};

