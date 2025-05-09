#pragma once
#include "Inventar.h"

class DeviceInventar : public Inventar {
public:
    DeviceInventar();
    bool addItem(Item* item) override;
    bool checkIfClearInventory();
    void changeInventorySize(int ini_newInventorySize);

    int getItemAnzahl(ItemID id);
   
};