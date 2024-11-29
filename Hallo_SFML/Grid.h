#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

using namespace std;
using namespace sf;



class Grid
{
private:
	RectangleShape gridShape;



public:
	Grid();


	RectangleShape& getGridShape();



};

