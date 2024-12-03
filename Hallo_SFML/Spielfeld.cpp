#include "Spielfeld.h"
#include "Grid.h"

#include <thread> // Für std::this_thread::sleep_for
#include <chrono> // Für std::chrono::seconds



using namespace std;
using namespace sf;

//Erstellt ein Spielfeld
Spielfeld::Spielfeld()
{
	//Werte des Grids
	const float gridWidth = 73.0f;
	const float gridHight = 73.0f;
	
	//Spalte zu spalte
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 10; j++)
		{


			///////////////////////////Später 21 und 22 in eine Zeile
			allGrids[i][j] = new Grid();
			
			if (i == 0 || i == 19 || j == 0 || j == 9) // Äußeres Grid
			{
				allGrids[i][j]->setGridTexture("BrickWall.jpg");
			}
			else // Inneres Grid
			{
				allGrids[i][j]->setGridTexture("Boden.jpg");
			}
			allGrids[i][j]->getGridShape().setPosition(i * gridWidth + 200, j * gridHight + 170);
		}
	}

}


//Draw des Spielfelds
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
