#pragma once

#include "GeraetBase.h"

class Ofen : public GeraetBase {
protected:
    void setupButtons(Font& newFont) override; // �berschreibt Buttons f�r den Ofen

public:
    Ofen(float x, float y, Font& newFont);
};