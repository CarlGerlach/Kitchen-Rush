#include "DeviceInventar.h"

DeviceInventar::DeviceInventar() : Inventar(3) {}

// Gerät: Nur Slot 0 und 1 dürfen belegt werden
bool DeviceInventar::addItem(Item* item) 
{
    for (int i = 0; i < 2; ++i) 
    { // Nur die ersten 2 Plätze
        if (slot[i] == nullptr) 
        {
            slot[i] = item;
            return true;
        }
    }
    return false; // Keine freien Input-Slots
}