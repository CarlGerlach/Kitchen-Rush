#pragma once

#include "GeraetBase.h"

class Ofen : public GeraetBase 
{
protected:
    void setupButtons(Font& newFont, Spieler* player) override; // �berschreibt Buttons f�r den Ofen

public:
    Ofen(int Grindnumber, Font& newFont, Spieler* spieler);
};