#include "Mixer.h"
#include "GameMessage.h"


Mixer::Mixer(int gridnumber, Font& newFont, Spieler* player, int ini_inventorySize) : GeraetBase(gridnumber, player, ini_inventorySize)
{
	setupButtons(newFont, player);
}

bool Mixer::makeTeig()
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
            GameMessage::setText("Kein Platz für Pizza in Slot 3");
            return false;
        }
    }

    GameMessage::setText("Nicht die richtigen Zutaten in Slot 1 und/oder 2");
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
            dasFenster.toggle();
        }
    );
}
