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

void dasFenster::drawForDevice(RenderWindow& window, RectangleShape(&deviceInventarSlots)[3], DeviceInventar* devInventar)
{
    if (visible)
    {
        window.draw(background);

        // Zeichne alle Buttons
        for (auto& knopf : knoepfe)
        {
            knopf.draw(window);
        }

        // Zeichne die Slots des Geräts
        for (int i = 0; i < 3; i++)
        {
            window.draw(deviceInventarSlots[i]);  // Zugriff auf Slots über das Array

            // Wenn ein Item im Slot existiert, zeichne es
            if (devInventar->getItem(i) != nullptr)
            {
                sf::Sprite sprite = devInventar->getItem(i)->getSprite();

                // Berechne die Skalierung des Sprites basierend auf der Slot-Größe
                float scaleX = deviceInventarSlots[i].getSize().x / sprite.getTexture()->getSize().x;
                float scaleY = deviceInventarSlots[i].getSize().y / sprite.getTexture()->getSize().y;

                // Setze die Skalierung des Sprites, um in den Slot zu passen
                sprite.setScale(scaleX, scaleY);

                // Berechne die Mitte des Slots und setze das Sprite in die Mitte des Slots
                sf::Vector2f slotPos = deviceInventarSlots[i].getPosition();
                sf::Vector2f slotCenter = sf::Vector2f(slotPos.x + deviceInventarSlots[i].getSize().x / 2.f,
                    slotPos.y + deviceInventarSlots[i].getSize().y / 2.f);

                // Berechne die Größe des Sprites und zentriere es
                sf::Vector2f spriteSize = sf::Vector2f(sprite.getTexture()->getSize());
                spriteSize *= sprite.getScale().x;  // Berücksichtige die Skalierung

                sprite.setPosition(slotCenter.x - spriteSize.x / 2.f, slotCenter.y - spriteSize.y / 2.f);

                window.draw(sprite);  // Zeichne das Sprite im Slot
            }
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