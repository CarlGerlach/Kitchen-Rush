#include "Ofen.h"
#include "Item.h"
#include "Spieler.h"
#include "GameMessage.h"

Ofen::Ofen(int gridnumber, Font& newFont, Spieler* player, int ini_inventorySize) : GeraetBase(gridnumber, player,ini_inventorySize)
{
    setupButtons(newFont, player);
}

bool Ofen::makePizza()
{
    Item* item0 = devInventar->getItem(0);
    Item* item1 = devInventar->getItem(1);

    // Prüfen, ob beide Slots belegt sind
    if (item0 == nullptr)
    {
        GameMessage::setText("Fehlende Zutat in Slot 1");
        return false;
    }
    if (item1 == nullptr)
    {
        GameMessage::setText("Fehlende Zutat in Slot 2");
        return false;
    }

    // Prüfen, ob beide Zutaten vorhanden sind (egal in welchem Slot)
    bool hatTeig = (item0->getItemID() == ItemID::TEIG) || (item1->getItemID() == ItemID::TEIG);
    bool hatTomate = (item0->getItemID() == ItemID::TOMATE) || (item1->getItemID() == ItemID::TOMATE);

    if (hatTeig && hatTomate)
    {
        if (devInventar->getItem(2) == nullptr)
        {
            devInventar->removeItem(0);
            devInventar->removeItem(1);
            devInventar->addItemToSlot(new Item(ItemID::PIZZA), 2);
            if (player->getPlayerInventar()->addItem(this->getDevInventar()->getItem(2)))
            {
                
                this->getDevInventar()->removeItem(2);
            }
            
            return true;
        }
        else
        {
            GameMessage::setText("Ofen ist Voll");
            return false;
        }
    }

    
    GameMessage::setText("Nicht die richtigen Zutaten in Slot 0 oder 1!");
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
        "Schließen",
        newFont,  // Font übergeben
        [this,player]()
        {
            dasFenster.toggle();
        }
    );


    
   
    
 


}
                             