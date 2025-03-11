#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Knopf.h"

using namespace sf;
using namespace std;

class dasFenster {
private:
    RectangleShape background;
    vector<Knopf> knoepfe;
    bool visible;

public:
    dasFenster(float x, float y);
    void addKnopf(const Knopf& knopf);
    void draw(RenderWindow& window);
    void handleEvent(const Event& event, const RenderWindow& window);
    void toggle();
};