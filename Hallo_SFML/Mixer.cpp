#include "Mixer.h"


Mixer::Mixer(int gridnumber, Font& newFont, Spieler* player, int ini_inventorySize) : GeraetBase(gridnumber, player, ini_inventorySize)
{
	setupButtons(newFont, player);
}

bool Mixer::makeTeig()
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
    bool hatMehl = (item0->getItemID() == ItemID::MEHL) || (item1->getItemID() == ItemID::MEHL);
    bool hatWasser = (item0->getItemID() == ItemID::WASSER) || (item1->getItemID() == ItemID::WASSER);

    if (hatMehl && hatWasser)
    {
        if (devInventar->getItem(2) == nullptr)
        {
            devInventar->removeItem(0);
            devInventar->removeItem(1);
            devInventar->addItemToSlot(new Item(ItemID::TEIG), 2);

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

void Mixer::setupButtons(Font& newFont, Spieler* player)
{
    dasFenster.addKnopf(
        "Mache Teig",
        newFont,  // Font übergeben
        [this, player]()
        {
            makeTeig();
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
