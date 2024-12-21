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
	Texture* textureOfGrid; 
	int numberOfGrid;
	static int numberOfAllGrids;

	static std::map<int, sf::Vector2f> gridPositions; // Speichert Nummern und Positionen

	static std::vector<Grid*> allGrids;

public:
	Grid();


	RectangleShape& getGridShape();
	void setNumberOfGrid(int ini_numberOfGrid);
	int getNumberOfGrid();
	void setGridTexture(Texture* t);

	//Vector2f getPosition(int gridNum);

	static sf::Vector2f getPosition(int gridNum);
};

