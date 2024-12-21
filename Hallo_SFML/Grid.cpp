#include <iostream>
#include <SFML/System/Vector2.hpp>

#include "Grid.h"

using namespace std;
using namespace sf;

std::map<int, sf::Vector2f> Grid::gridPositions;
int Grid::numberOfAllGrids = 1;

std::vector<Grid*> Grid::allGrids;

//Erstelen eines Grids
Grid::Grid()
{
	const Vector2f sizeOfShape{ 73.0f, 73.0f };
	gridShape.setSize(sizeOfShape);
	//gridShape.setFillColor(Color::Red);
	gridShape.setOutlineColor(sf::Color::Black);
	gridShape.setOutlineThickness(2.f);
	numberOfGrid = numberOfAllGrids;

	gridPositions[numberOfGrid] = gridShape.getPosition(); // Speichere Position
	allGrids.push_back(this); // Speichere Zeiger auf dieses Grid

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

sf::Vector2f Grid::getPosition(int gridNum)
{
	if (gridNum > 0 && gridNum <= allGrids.size())
	{
		return allGrids[gridNum - 1]->gridShape.getPosition();
	}
	return sf::Vector2f(-1.0f, -1.0f); // Ungültige Position
}

/*
sf::Vector2f Grid::getPosition(int gridNum)
{
	for (int i = 0; i < numberOfAllGrids; i++)
	{
		gridPositions[i] = gridShape.getPosition(); // Speichere Position
	}


	if (gridPositions.find(gridNum) != gridPositions.end())
	{
		return gridPositions[gridNum];
	}
	return sf::Vector2f(-1.0f, -1.0f); // Ungültige Position
}
*/
