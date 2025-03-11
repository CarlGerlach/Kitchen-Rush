#include "dasFenster.h"

dasFenster::dasFenster(float x, float y) 
{
    background.setPosition(x, y);
    background.setSize(Vector2f(600, 800));
    background.setFillColor(Color(200, 200, 200, 255)); // Graues Fenster
    visible = false;
}

void dasFenster::addKnopf(float x, float y, float width, float height, const string& label, Font& font, function<void()> callback)
{
    knoepfe.push_back(Knopf(x, y, width, height, label, font, callback));
}

void dasFenster::draw(RenderWindow& window)
{
    if (visible)
    {
        window.draw(background);
       for (auto& knopf : knoepfe)
       {
           knopf.draw(window);
        }
    }
    
}

void dasFenster::handleEvent(const Event& event, const RenderWindow& window) 
{
    if (visible) 
    {
        for (auto& knopf : knoepfe) 
        {
            knopf.handleEvent(event, window);
        }
    }
}

void dasFenster::toggle() 
{
    if (visible == true)
    {
        visible = false;
        return;
    }
    
    if(visible == false)
    {
        visible = true;
        return;
    }
    
}