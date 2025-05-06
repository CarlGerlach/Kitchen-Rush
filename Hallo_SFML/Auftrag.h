#pragma once
#include <iostream>
#include "Item.h"
#include "Bestellposition.h"

using namespace std;


class Auftrag
{
private:
	Bestellposition* derAuftrag[5];

	
public:
	Auftrag(Bestellposition* ini_position);

	void addAuftrag(Bestellposition* ini_position);


};

