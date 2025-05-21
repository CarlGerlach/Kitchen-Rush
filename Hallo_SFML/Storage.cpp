#include "Storage.h"

Storage::Storage(int gridnumber, Font& newFont, Spieler* player, int ini_inventorySize) : GeraetBase(gridnumber, player, ini_inventorySize)
{
	setupButtons(newFont, player);
}


void Storage::setupButtons(Font& newFont, Spieler* player)
{
    dasFenster.addKnopf(
        "Nehme Mehl",
        newFont,  // Font übergeben
        [this, player]()
        {
            player->getPlayerInventar()->addItem(new Item(ItemID::MEHL));
        }
    );

    dasFenster.addKnopf(
        "Nehme Tomate",
        newFont,  // Font übergeben
        [this, player]()
        {  
            player->getPlayerInventar()->addItem(new Item(ItemID::TOMATE));
        }
    );

    //dasFenster.addKnopf(
    //    "Nehme Salat",
    //    newFont,  // Font übergeben
    //    [this, player]()
    //    {
    //        player->getPlayerInventar()->addItem(new Item(ItemID::SALAT));
    //    }
    //);


    dasFenster.addKnopf(
        "Nehme Gurke",
        newFont,  // Font übergeben
        [this, player]()
        {
            player->getPlayerInventar()->addItem(new Item(ItemID::GURKE));
        }
    );

    dasFenster.addKnopf(
        "Nehme Salatkopf",
        newFont,  // Font übergeben
        [this, player]()
        {
            player->getPlayerInventar()->addItem(new Item(ItemID::SALATKOPF));
        }
    );

    dasFenster.addKnopf(
        "Wegwerfen",
        newFont,  // Font übergeben
        [this, player]()
        {
            this->getDevInventar()->removeItem(0);
            this->getDevInventar()->removeItem(1);
            this->getDevInventar()->removeItem(2);
            this->getDevInventar()->removeItem(3);
            this->getDevInventar()->removeItem(4);
        }
    );




    //dasFenster.addKnopf(
    //    "Nehme Pizza",
    //    newFont,  // Font übergeben
    //    [this, player]()
    //    {
    //        this->getDevInventar()->addItem(new Item(ItemID::PIZZA));
    //    }
    //);

    dasFenster.addKnopf(
        "Schließen",
        newFont,  // Font übergeben
        [this, player]()
        {
            dasFenster.toggle();
        }
    );


}

