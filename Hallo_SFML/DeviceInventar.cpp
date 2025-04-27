#include "DeviceInventar.h"

DeviceInventar::DeviceInventar() : Inventar(3) {}

// Ger�t: Nur Slot 0 und 1 d�rfen belegt werden
bool DeviceInventar::addItem(Item* item) 
{
    for (int i = 0; i < 2; ++i) 
    { // Nur die ersten 2 Pl�tze
        if (slot[i] == nullptr) 
        {
            slot[i] = item;
            return true;
        }
    }
    return false; // Keine freien Input-Slots
}