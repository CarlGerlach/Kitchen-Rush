#include "DeviceInventar.h"

DeviceInventar::DeviceInventar() : Inventar(3) {}

// Ger�t: Nur Slot 0 und 1 d�rfen belegt werden
bool DeviceInventar::addItem(Item* item) 
{
    int slotAnzahl = getSlotAnzahl();
    
    for (int i = 0; i < slotAnzahl - 1; ++i) 
    { // Nur die ersten 2 Pl�tze
        if (slot[i] == nullptr) 
        {
            slot[i] = item;
            return true;
        }
    }
    return false; // Keine freien Input-Slots
}

bool DeviceInventar::checkIfClearInventory()
{
    for (int i = 0; i < 2; i++)
    {
        if (slot[i] != nullptr)
        {
            return false;
        }
    }
    return true;
}

void DeviceInventar::changeInventorySize(int ini_newInventorySize)
{
    this->setSlotAnzahl(ini_newInventorySize);
}

int DeviceInventar::getItemAnzahl(ItemID id)
{
    int summe = 0;

    for (int i = 0; i < slotAnzahl; ++i)
    {
        Item* item = slot[i];

        if (item != nullptr && item->getItemID() == id)
        {
            summe += 1; // genau ein Item in jedem belegten Slot
        }
    }

    return summe;
}
