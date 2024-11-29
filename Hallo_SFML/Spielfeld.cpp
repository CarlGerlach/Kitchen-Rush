#include "Spielfeld.h"
#include "Grid.h"

using namespace std;
using namespace sf;

Spielfeld::Spielfeld()
{
	const float gridWidth = 73.0f;
	const float gridHight = 73.0f;
	
	
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			allGrids[i][j] = new Grid();
			allGrids[i][j]->getGridShape().setPosition(i * gridWidth + 200, j * gridHight + 170);
		}
	}

}

void Spielfeld::drawSpielfeld(RenderWindow& window)
{	
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			window.draw(allGrids[i][j]->getGridShape());
		}
	}
}
