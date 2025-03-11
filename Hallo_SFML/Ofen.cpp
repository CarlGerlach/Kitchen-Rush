#include "Ofen.h"
#include "Item.h"

Ofen::Ofen(float x, float y, Font& newFont) : GeraetBase(x, y, 50, 50)
{
    setupButtons(newFont);
}

void Ofen::setupButtons(Font& newFont)
{
    dasFenster.addKnopf(
        shape.getPosition().x + 200,
        shape.getPosition().y + 200,
        80, 30,
        "Start",
        newFont,  // Font übergeben
        [this]() 
        { 

            cout << "Ofen startet!" << endl; 
            bool foundFirstItem = false;
            bool foundSecondItem = false;
            int index1 = 0;
            int index2 = 0;

            sf::Texture platzhalter;
            if (!platzhalter.loadFromFile("Texturen & Musik/Herd_01.png"))
            {
                cerr << "Fehler beim Laden der kg-Sprite-Textur!" << endl;
                return -1;
            }
           

            for(int i = 0; i < 5; i++) 
            {
                cout << inventar[i]->getTyp() << endl;

                if (inventar[i]->getTyp() == "Anderer Test1")
                {
                    foundFirstItem = true;
                    index1 = i;
                   
                }

               ;

                if (inventar[i]->getTyp() == "Anderer Test2")
                {
                    foundSecondItem = true;
                    index2 = i;
                    break;
                }
            }

            cout << foundFirstItem << endl;
            cout << foundSecondItem << endl;
            

            if (foundFirstItem == true && foundSecondItem == true)
            {
                delete inventar[index1];
                delete inventar[index2];
                Item* neuestItem = new Item("dasNeueItem", platzhalter);

                inventar[index1] = neuestItem;
            }
               
            cout << "Inventar ist leer!" << endl;
        
            cout << inventar[index1]->getTyp() << endl;
        }
    );

    
}
                             