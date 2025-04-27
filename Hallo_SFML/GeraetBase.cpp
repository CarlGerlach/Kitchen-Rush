#include "GeraetBase.h"
#include "Grid.h"
#include "DeviceInventar.h"

GeraetBase::GeraetBase(int gridNumber) : dasFenster()
{
    float width = 75;
    float height = 75;
    

    sf::Vector2f gridPos = Grid::getPosition(gridNumber);

    shape.setPosition(gridPos.x - 2, gridPos.y - 2);
    shape.setSize({ width, height });

    for (int i = 0; i < 3; i++)
    {
        deviceInventarSlots[i].setSize(sf::Vector2f(slotSize, slotSize));
        deviceInventarSlots[i].setPosition(startXPos + i * (slotSize + spacing), startYPos); // Position setzen
        deviceInventarSlots[i].setFillColor(sf::Color(100, 100, 100, 200)); // Graue Farbe für Slots
    }
    
    devInventar = new DeviceInventar();
}

void GeraetBase::draw(RenderWindow& window)
{
    window.draw(shape);
    this->dasFenster.drawForDevice(window, deviceInventarSlots, devInventar);
}

void GeraetBase::handleEvent(const Event& event, const RenderWindow& window) 
{
    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) 
    {
 
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
        {
            
            this->dasFenster.toggle();
            
        }
    }
    
    this->dasFenster.handleEvent(event, window);
    
}



void GeraetBase::setTexture(sf::Texture* newTexture)
{ 
    texture = newTexture;
    shape.setTexture(texture);
    shape.setPosition(shape.getPosition()); // Übernehme die Position des Buttons 
}



void GeraetBase::setScale(float scale)
{
    // Aktuelle Skalierung des Buttons abrufen
    sf::Vector2f currentScale = shape.getScale();

    // Skalierung um den angegebenen Faktor erhöhen (1.5 bedeutet z.B. 50% größer)
    shape.setScale(currentScale.x * scale, currentScale.y * scale);
}


DeviceInventar* GeraetBase::getDevInventar()
{
    return devInventar;
}
