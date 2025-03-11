#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>

using namespace sf;
using namespace std;

class Knopf 
{
private:
    RectangleShape shape;
    Text text;
    Font font;
    function<void()> onClick;

public:
    Knopf(float x, float y, float width, float height, const string& label, Font& font, function<void()> callback);
    void draw(RenderWindow& window);
    void handleEvent(const Event& event, const RenderWindow& window);
};