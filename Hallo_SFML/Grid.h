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
	Texture textureOfGrid; 
	int numberOfGrid;
	static int numberOfAllGrids;




public:
	Grid();


	RectangleShape& getGridShape();
	void setNumberOfGrid(int ini_numberOfGrid);
	int getNumberOfGrid();
	void setGridTexture(string nameOfFile);



};

