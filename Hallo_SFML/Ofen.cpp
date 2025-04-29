#include "Ofen.h"
#include "Item.h"
#include "Spieler.h"

Ofen::Ofen(int gridnumber, Font& newFont, Spieler* player) : GeraetBase(gridnumber, player)
{
    setupButtons(newFont, player);
}

bool Ofen::makePizza()
{
    Item* item0 = devInventar->getItem(0);
    Item* item1 = devInventar->getItem(1);

    // Prüfen, ob beide Slots belegt sind
    if (item0 == nullptr || item1 == nullptr)
    {
        std::cout << "Fehlende Zutat in Slot 0 oder 1!" << std::endl;
        return false;
    }

    // Prüfen, ob beide Zutaten vorhanden sind (egal in welchem Slot)
    bool hatTeig = (item0->getItemID() == ItemID::TEIG) || (item1->getItemID() == ItemID::TEIG);
    bool hatTomate = (item0->getItemID() == ItemID::TOMATE) || (item1->getItemID() == ItemID::TOMATE);

    if (hatTeig && hatTomate)
    {
        // Entferne beide Items sicher (auch wenn z.?B. Tomate in Slot 1 ist)
        devInventar->removeItem(0);
        devInventar->removeItem(1);

        // Füge Pizza in Slot 2 ein, wenn dieser leer ist
        if (devInventar->getItem(2) == nullptr)
        {
            devInventar->addItemToSlot(new Item(ItemID::PIZZA), 2);
            return true;
        }
        else
        {
            std::cout << "Slot 2 ist belegt. Kein Platz für Pizza!" << std::endl;
            return false;
        }
    }

    std::cout << "Nicht die richtigen Zutaten in Slot 0 und 1!" << std::endl;
    return false;
}

void Ofen::setupButtons(Font& newFont, Spieler* player)
{
    dasFenster.addKnopf(
        "Mache Pizza",
        newFont,  // Font übergeben
        [this, player]() 
        { 
            this->makePizza();
        }
    );

    dasFenster.addKnopf(
        "Nehme Item",
        newFont,  // Font übergeben
        [this, player]()
        {
        
        }
    );

    dasFenster.addKnopf(
        "Schließen",
        newFont,  // Font übergeben
        [this,player]()
        {
            cout << "Fenster geschlossen" << endl;
            dasFenster.toggle();
        }
    );


    
   
    
 


}
                             