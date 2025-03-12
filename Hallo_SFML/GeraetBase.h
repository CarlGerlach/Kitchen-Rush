#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Item.h"
#include "dasFenster.h"
#include "Spieler.h"

using namespace sf;
using namespace std;

class GeraetBase 
{
protected:
    RectangleShape shape;
    Texture* texture;
    Item* inventar[5];
    dasFenster dasFenster;

    virtual void setupButtons(Font& newFont, Spieler& player) = 0; // Wird von den Unterklassen implementiert

public:
    GeraetBase(int gridnumber);
    virtual ~GeraetBase() {}

    void draw(RenderWindow& window);
    void handleEvent(const Event& event, const RenderWindow& window);
    void addItem(Item* item);
    void removeItem();
    void setTexture(sf::Texture* newTexture);


    void itemReinlegen(Spieler& player);
    void itemRausnehmen(Spieler& player);

    void setScale(float scale);

};                           