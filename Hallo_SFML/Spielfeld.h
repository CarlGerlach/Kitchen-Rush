#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Grid.h"


using namespace std;
using namespace sf;




class Spielfeld
{
private:
	Grid* allGrids[20][10];


public:
	Spielfeld();	
	void drawSpielfeld(RenderWindow& Window);

};

