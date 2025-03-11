#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Item.h"
#include "dasFenster.h"

using namespace sf;
using namespace std;

class GeraetBase 
{
protected:
    RectangleShape shape;
    Texture* texture;
    Item* inventar[5];
    dasFenster dasFenster;

    virtual void setupButtons() = 0; // Wird von den Unterklassen implementiert

public:
    GeraetBase(float x, float y, float width, float hight);
    virtual ~GeraetBase() {}

    void draw(RenderWindow& window);
    void handleEvent(const Event& event, const RenderWindow& window);
    void addItem(Item* item);
    void removeItem();
    void setTexture(sf::Texture* newTexture);
};