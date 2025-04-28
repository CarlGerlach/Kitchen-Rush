#include "Ofen.h"
#include "Item.h"
#include "Spieler.h"

Ofen::Ofen(int gridnumber, Font& newFont, Spieler* player) : GeraetBase(gridnumber, player)
{
    setupButtons(newFont, player);
}

void Ofen::setupButtons(Font& newFont, Spieler* player)
{
    dasFenster.addKnopf(
        "Mache Pizza",
        newFont,  // Font übergeben
        [this, player]() 
        { 
            if (devInventar->getItem(0)->getItemID() == ItemID::TOMATE && devInventar->getItem(1)->getItemID() == ItemID::TEIG || devInventar->getItem(1)->getItemID() == ItemID::TOMATE && devInventar->getItem(0)->getItemID() == ItemID::TEIG)
            {
                devInventar->removeItem(0);
                devInventar->removeItem(1);
 
                devInventar->addItemToSlot(new Item(ItemID::PIZZA),2);   
            }
       

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
                             