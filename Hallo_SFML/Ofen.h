#pragma once

#include "GeraetBase.h"

class Ofen : public GeraetBase {
protected:
    void setupButtons() override; // Überschreibt Buttons für den Ofen

public:
    Ofen(float x, float y);
};