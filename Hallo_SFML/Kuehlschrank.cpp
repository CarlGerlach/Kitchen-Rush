#include "Kuehlschrank.h"

void Kuehlschrank::setupButtons(Font& newFont, Spieler* player)
{
    dasFenster.addKnopf(
        "Nehme Cola",
        newFont,  // Font �bergeben
        [this, player]()
        {
            this->player->getPlayerInventar()->addItem(new Item(ItemID::COLA));
        }
    );
    dasFenster.addKnopf(
        "Nehme Wasser",
        newFont,  // Font �bergeben
        [this, player]()
        {
            this->player->getPlayerInventar()->addItem(new Item(ItemID::WASSER));
        }
    );
    dasFenster.addKnopf(
        "Schlie�en",
        newFont,  // Font �bergeben
        [this, player]()
        {
            dasFenster.toggle();
        }
    );
}

Kuehlschrank::Kuehlschrank(int gridnumber, Font& newFont, Spieler* player, int ini_inventorySize) : GeraetBase(gridnumber, player, ini_inventorySize)
{
    setupButtons(newFont, player);
}
