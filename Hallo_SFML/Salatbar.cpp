#include "Salatbar.h"
#include "Item.h"
#include "GameMessage.h"
#include <vector>;
#include <set>

using namespace std;
using namespace sf;

void Salatbar::setupButtons(Font& newFont, Spieler* player)
{
    //Teils chatgpt
    
    dasFenster.addKnopf(
        "Mache Salat",
        newFont,  // Font übergeben
        [this, player]()
        {
            // Sicherstellen, dass alle drei Slots belegt sind
            Item* item0 = devInventar->getItem(0);
            Item* item1 = devInventar->getItem(1);
            Item* item2 = devInventar->getItem(2);

            if (!item0 || !item1 || !item2)
            {
                GameMessage::setText("Drei Zutaten werden benötigt (Tomate, Gurke, Salatkopf)");
                return false;
            }

            // Zutaten prüfen – egal in welcher Reihenfolge
            set<ItemID> zutaten;
            zutaten.insert(item0->getItemID());
            zutaten.insert(item1->getItemID());
            zutaten.insert(item2->getItemID());

            if (zutaten.count(ItemID::TOMATE) &&
                zutaten.count(ItemID::GURKE) &&
                zutaten.count(ItemID::SALATKOPF))
            {
                // Alle Zutaten entfernen
                devInventar->removeItem(0);
                devInventar->removeItem(1);
                devInventar->removeItem(2);

                // Salat in Slot 2 legen (oder woanders je nach Design)
                devInventar->addItemToSlot(new Item(ItemID::SALAT), 3);
                if (player->getPlayerInventar()->addItem(this->getDevInventar()->getItem(3)))
                {

                    this->getDevInventar()->removeItem(3);
                }

                GameMessage::setText("Salat wurde hergestellt!");
                return true;
            }

            GameMessage::setText("Falsche Zutaten – benötigt: Tomate, Gurke, Eisbergsalat");
            return false;

        }
    );
}

Salatbar::Salatbar(int gridnumber, Font& newFont, Spieler* player, int ini_inventorySize) : GeraetBase(gridnumber, player, ini_inventorySize) 
{
	setupButtons(newFont, player);
}
