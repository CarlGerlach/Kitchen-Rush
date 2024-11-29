#include <iostream>
#include <SFML/System/Vector2.hpp>

#include "Grid.h"




Grid::Grid()
{
	const Vector2f sizeOfShape{ 73.0f, 73.0f };
	gridShape.setSize(sizeOfShape);
	gridShape.setFillColor(Color::Red);
	gridShape.setOutlineColor(sf::Color::White);
	gridShape.setOutlineThickness(2.f);
}

RectangleShape& Grid::getGridShape()
{
	return gridShape;
}
