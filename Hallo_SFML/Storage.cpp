#include "Storage.h"

Storage::Storage(int gridnumber, Font& newFont, Spieler* player) : GeraetBase(gridnumber, player)
{
	setupButtons(newFont, player);
}


void Storage::setupButtons(Font& newFont, Spieler* player)
{
    dasFenster.addKnopf(
        "Mehl nehmen",
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
        "Schließen",
        newFont,  // Font übergeben
        [this, player]()
        {
            cout << "Fenster geschlossen" << endl;
            dasFenster.toggle();
        }
    );


}

