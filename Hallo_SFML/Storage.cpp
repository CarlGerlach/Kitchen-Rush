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
           
            cout << "Adresse Storage Inventar in Funktion" << getDevInventar() << endl;
            this->getDevInventar()->addItem(new Item(ItemID::MEHL));
        }
    );

    dasFenster.addKnopf(
        "Nehme Wasser",
        newFont,  // Font übergeben
        [this, player]()
        {
            this->getDevInventar()->addItem(new Item(ItemID::WASSER));
        }
    );

    dasFenster.addKnopf(
        "Nehme Tomate",
        newFont,  // Font übergeben
        [this, player]()
        {
            this->getDevInventar()->addItem(new Item(ItemID::TOMATE));
        }
    );

    dasFenster.addKnopf(
        "Nehme Salat",
        newFont,  // Font übergeben
        [this, player]()
        {
            this->getDevInventar()->addItem(new Item(ItemID::SALAT));
        }
    );

    dasFenster.addKnopf(
        "Nehme Cola",
        newFont,  // Font übergeben
        [this, player]()
        {
            this->getDevInventar()->addItem(new Item(ItemID::COLA));
        }
    );

    dasFenster.addKnopf(
        "Schließen",
        newFont,  // Font übergeben
        [this, player]()
        {
            cout << "Fenster geschlossen" << endl;
            dasFenster.toggle();
        }
    );


}

