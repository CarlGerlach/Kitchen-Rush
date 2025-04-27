#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Item.h"
#include "dasFenster.h"
#include "Spieler.h"
#include "DeviceInventar.h"

using namespace sf;
using namespace std;

class GeraetBase 
{
protected:
    RectangleShape shape;
    Texture* texture;
    dasFenster dasFenster;
    DeviceInventar* devInventar;

    RectangleShape deviceInventarSlots[3]; // 3 Slots für das Gerät-Inventar
    const float slotSize = 50.f;
    const float spacing = 10.f;
    const float startXPos = 800.f;  // Fest definierte Position von links
    const float startYPos = 700.f;  // Fest definierte Position von unten


    virtual void setupButtons(Font& newFont, Spieler& player) = 0; // Wird von den Unterklassen implementiert

public:
    GeraetBase(int gridnumber);
    virtual ~GeraetBase() {}

    void draw(RenderWindow& window);
    void handleEvent(const Event& event, const RenderWindow& window);
   
    void setTexture(sf::Texture* newTexture);

    void setScale(float scale);

    DeviceInventar* getDevInventar();

};                           