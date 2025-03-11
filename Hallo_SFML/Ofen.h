#pragma once

#include "GeraetBase.h"

class Ofen : public GeraetBase {
protected:
    void setupButtons(Font& newFont) override; // Überschreibt Buttons für den Ofen

public:
    Ofen(float x, float y, Font& newFont);
};