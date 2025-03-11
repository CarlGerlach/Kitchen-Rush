#include "dasFenster.h"

dasFenster::dasFenster(float x, float y) 
{
    background.setPosition(x, y);
    background.setSize(Vector2f(200, 200));
    background.setFillColor(Color(200, 200, 200, 255)); // Graues Fenster
    visible = false;
}

void dasFenster::addKnopf(const Knopf& knopf)
{
    knoepfe.push_back(knopf);
}

void dasFenster::draw(RenderWindow& window) 
{
    if (visible) {
        window.draw(background);
        for (auto& knopf : knoepfe) {
            knopf.draw(window);
        }
    }
}

void dasFenster::handleEvent(const Event& event, const RenderWindow& window) 
{
    if (visible) 
    {
        for (auto& knopf : knoepfe) {
            knopf.handleEvent(event, window);
        }
    }
}

void dasFenster::toggle() 
{
    visible = !visible;
}