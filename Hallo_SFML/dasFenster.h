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
    bool visible = false;

public:
    dasFenster(float x, float y);
    void addKnopf(float x, float y, float width, float height, const string& label, Font& font, function<void()> callback);  // Neue Methode mit Font
    void draw(RenderWindow& window);
    void handleEvent(const Event& event, const RenderWindow& window);
    void toggle();
};