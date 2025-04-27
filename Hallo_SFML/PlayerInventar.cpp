#include "PlayerInventar.h"

PlayerInventar::PlayerInventar() : Inventar(5) {}

// Spieler: fügt in den ersten freien Slot ein
bool PlayerInventar::addItem(Item* item) 
{
    for (int i = 0; i < slotAnzahl; ++i) 
    {
        if (slot[i] == nullptr) 
        {
            slot[i] = item;
            return true;
        }
    }
    return false; // Inventar voll
}