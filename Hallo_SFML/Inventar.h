#pragma once
#include "Item.h"

class Inventar {
protected:
    static const int MAX_SLOTS = 20; // Maximale Anzahl, aus Sicherheitsgründen (chatgpt)
    Item* slot[MAX_SLOTS]; // (chatgpt)
    int slotAnzahl; // Tatsächliche Slotanzahl

public:
    Inventar(int slots);
    virtual ~Inventar();

    virtual bool addItem(Item* item) = 0; // Pure virtual (abstrakt)
    virtual bool removeItem(int slot);
    bool addItemToSlot(Item* item, int slotToAdd);
    Item* getItem(int slot) const;
    void swapItems(int slotA, Inventar& anderesInventar, int slotB);
    void print();

    void setSlotAnzahl(int ini_newSlotSize);
    int getSlotAnzahl();
};