#include "dasFenster.h"

dasFenster::dasFenster() 
{
    background.setOrigin(windowWidth / 2, windowHight / 2);

    background.setPosition(1920 / 2, 1080 / 2);

    background.setSize(Vector2f(windowWidth, windowHight));
    background.setFillColor(Color(200, 200, 200, 255)); // Graues Fenster
    visible = false;
}

void dasFenster::addKnopf(const string& label, Font& font, function<void()> callback)
{
    float buttonWidth = 160.0f;  // Standard-Breite
    float buttonHeight = 30.0f;  // Standard-Höhe

    // Berechne X-Position: Mittig ausrichten
    float x = (1920 - buttonWidth) / 2.0f;

    // Berechne Y-Position: Abstand von oben plus vorherige Buttons
    float y = 200.0f + (amountOfButtons * (buttonHeight + buttonDistance));

    // Knopf zum Vektor hinzufügen
    knoepfe.push_back(Knopf(x, y, buttonWidth, buttonHeight, label, font, callback));

    // Anzahl der Buttons erhöhen
    amountOfButtons++;
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