#include "Inventar.h"
#include <iostream>

Inventar::Inventar(int slots) : slotAnzahl(slots)
{
    for (int i = 0; i < MAX_SLOTS; ++i) 
    {
        slot[i] = nullptr;
    }
}

Inventar::~Inventar() {
    for (int i = 0; i < slotAnzahl; ++i) 
    {
        delete slot[i];
    }
}

bool Inventar::removeItem(int slotIndex) 
{
    if (slotIndex < 0 || slotIndex >= slotAnzahl || slot[slotIndex] == nullptr)
    {
        return false;
    }

    slot[slotIndex] = nullptr;
    return true;
}

bool Inventar::removeItems(ItemID id, int menge)
{
    int entfernt = 0;

    for (int i = 0; i < slotAnzahl && entfernt < menge; ++i)
    {
        if (slot[i] != nullptr && slot[i]->getItemID() == id)
        {
            delete slot[i];        // Speicher freigeben
            slot[i] = nullptr;     // Slot leeren
            entfernt++;
        }
    }

    return entfernt == menge; // Erfolg nur bei vollständiger Entfernung
}

bool Inventar::addItemToSlot(Item* item, int slotToAdd)
{
    if (slot[slotToAdd] == nullptr)
    {
        slot[slotToAdd] = item;
        return true;
    }
    return false;

}

Item* Inventar::getItem(int slotIndex) const 
{
    if (slotIndex < 0 || slotIndex >= slotAnzahl)
        return nullptr;

    return slot[slotIndex];
}

void Inventar::swapItems(int slotA, Inventar& anderesInventar, int slotB) {
    if (slotA < 0 || slotA >= slotAnzahl || slotB < 0 || slotB >= anderesInventar.slotAnzahl)
        return;

    std::swap(slot[slotA], anderesInventar.slot[slotB]);
}


void Inventar::setSlotAnzahl(int ini_newSlotSize)
{
    slotAnzahl = ini_newSlotSize;
}

int Inventar::getSlotAnzahl()
{
    return slotAnzahl;
}
