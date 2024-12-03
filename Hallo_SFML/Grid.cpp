#include <iostream>
#include <SFML/System/Vector2.hpp>

#include "Grid.h"

using namespace std;
using namespace sf;

int Grid::numberOfAllGrids = 1;

//Erstelen eines Grids
Grid::Grid()
{
	const Vector2f sizeOfShape{ 73.0f, 73.0f };
	gridShape.setSize(sizeOfShape);
	//gridShape.setFillColor(Color::Red);
	gridShape.setOutlineColor(sf::Color::Black);
	gridShape.setOutlineThickness(2.f);
	numberOfGrid = numberOfAllGrids;
	numberOfAllGrids++;
}


//Referenz der Shape als Returnwert
RectangleShape& Grid::getGridShape()
{
	return gridShape;
}

void Grid::setNumberOfGrid(int ini_numberOfGrid)
{
	numberOfGrid = ini_numberOfGrid;
}

int Grid::getNumberOfGrid()
{
	return numberOfGrid;
}

void Grid::setGridTexture(Texture* t)
{
	gridShape.setTexture(t);
	numberOfGrid = numberOfAllGrids;
}

