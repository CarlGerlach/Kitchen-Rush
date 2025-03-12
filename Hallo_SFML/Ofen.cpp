#include "Ofen.h"
#include "Item.h"
#include "Spieler.h"

Ofen::Ofen(int gridnumber, Font& newFont, Spieler& player) : GeraetBase(gridnumber)
{
    setupButtons(newFont, player);
}

void Ofen::setupButtons(Font& newFont, Spieler& player)
{
    dasFenster.addKnopf(
        "Mache neues Item",
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

                inventar[4] = neuestItem;
            }
               
            cout << "Inventar ist leer!" << endl;
        
            cout << inventar[4]->getTyp() << endl;
        }
    );

    dasFenster.addKnopf(
        "Nehme Item",
        newFont,  // Font übergeben
        [this, & player]()
        {
            cout << "Starte Ofen2 " << endl;

            itemRausnehmen(player);
            
            player.inventarKonsole();
        }
    );

    dasFenster.addKnopf(
        "Schließen",
        newFont,  // Font übergeben
        [this, &player]()
        {
            cout << "Fenster geschlossen" << endl;
            dasFenster.toggle();
        }
    );
    
}
                             