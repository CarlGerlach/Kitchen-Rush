#include "Spielfeld.h"
#include "Grid.h"

#include <thread> // Für std::this_thread::sleep_for
#include <chrono> // Für std::chrono::seconds



using namespace std;
using namespace sf;

//Erstellt ein Spielfeld
Spielfeld::Spielfeld()
{
	sf::Texture* wallTexture = new sf::Texture();
	wallTexture->loadFromFile("Texturen & Musik/Wand.png");

	sf::Texture* floorTexture = new sf::Texture();
	floorTexture->loadFromFile("Texturen & Musik/Fliesen_Boden.png");

	sf::Texture* doorTexture = new sf::Texture();
	doorTexture->loadFromFile("Texturen & Musik/Tuer.png");

	sf::Texture* windowUpTexture = new sf::Texture();
	windowUpTexture->loadFromFile("Texturen & Musik/Fenster_oben.png");

	sf::Texture* windowDownTexture = new sf::Texture();
	windowDownTexture->loadFromFile("Texturen & Musik/Fenster_unten.png");

	sf::Texture* windowLeftTexture = new sf::Texture();
	windowLeftTexture->loadFromFile("Texturen & Musik/Fenster_links.png");

	sf::Texture* windowRightTexture = new sf::Texture();
	windowRightTexture->loadFromFile("Texturen & Musik/Fenster_rechts.png");


	
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
				allGrids[i][j]->setGridTexture(wallTexture);
			}
			else // Inneres Grid
			{
				allGrids[i][j]->setGridTexture(floorTexture);
			}
			allGrids[i][j]->getGridShape().setPosition(i * gridWidth + 200, j * gridHight + 170);



		}
	}


	//Andere Perspektive
	allGrids[0][2]->setGridTexture(windowDownTexture);
	allGrids[0][6]->setGridTexture(windowDownTexture);
	allGrids[19][3]->setGridTexture(windowDownTexture);
	allGrids[19][7]->setGridTexture(windowDownTexture);
	allGrids[10][9]->setGridTexture(doorTexture);
	//cout << allGrids[10][9]->getNumberOfGrid() << endl;


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
