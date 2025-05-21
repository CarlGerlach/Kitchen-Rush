#include "Muell.h"

void Muell::setupButtons(Font& newFont, Spieler* player)
{
    dasFenster.addKnopf(
        "Wegwerfen",
        newFont,  // Font übergeben
        [this, player]()
        {
            auto inventar = this->getDevInventar();

            for (int i = 4; i >= 0; --i)
            {
                Item* item = inventar->getItem(i);
                if (item != nullptr)
                {
                    player->punkteReduzieren(item->getPunkteForItem(item->getItemID()));
                    inventar->removeItem(i);
                }
            }
            player->punkteReduzieren(this->getDevInventar()->getItem(0)->getPunkteForItem(this->getDevInventar()->getItem(0)->getItemID()));
           // this->getDevInventar()->removeItem(0);
           // player->punkteReduzieren(this->getDevInventar()->getItem(1)->getPunkteForItem(this->getDevInventar()->getItem(1)->getItemID()));
           // this->getDevInventar()->removeItem(1);
           // player->punkteReduzieren(this->getDevInventar()->getItem(2)->getPunkteForItem(this->getDevInventar()->getItem(2)->getItemID()));
           // this->getDevInventar()->removeItem(2);
           // player->punkteReduzieren(this->getDevInventar()->getItem(2)->getPunkteForItem(this->getDevInventar()->getItem(3)->getItemID()));
           // this->getDevInventar()->removeItem(3);
           // player->punkteReduzieren(this->getDevInventar()->getItem(4)->getPunkteForItem(this->getDevInventar()->getItem(4)->getItemID()));
           // this->getDevInventar()->removeItem(4);
        }
    );
}

Muell::Muell(int gridnumber, Font& newFont, Spieler* player, int ini_inventorySize) : GeraetBase(gridnumber, player, ini_inventorySize)
{
    setupButtons(newFont, player);
}
