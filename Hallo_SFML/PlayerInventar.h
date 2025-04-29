#pragma once
#include "Inventar.h"

class PlayerInventar : public Inventar 
{
public:
    PlayerInventar();
    bool addItem(Item* item) override;
};