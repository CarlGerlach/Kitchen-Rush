#pragma once
#include "Inventar.h"

class DeviceInventar : public Inventar {
public:
    DeviceInventar();
    bool addItem(Item* item) override;
};