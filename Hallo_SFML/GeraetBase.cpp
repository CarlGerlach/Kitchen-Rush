#include "GeraetBase.h"
#include "Grid.h"
#include "DeviceInventar.h"

GeraetBase::GeraetBase(int gridNumber, Spieler* ini_player) : dasFenster()
{
    player = ini_player;

    float width = 75;
    float height = 75;
    

    sf::Vector2f gridPos = Grid::getPosition(gridNumber);

    shape.setPosition(gridPos.x - 2, gridPos.y - 2);
    shape.setSize({ width, height });

    for (int i = 0; i < 3; i++)
    {
        deviceInventarSlots[i].setSize(sf::Vector2f(slotSize, slotSize));
        deviceInventarSlots[i].setPosition(startXPos + i * (slotSize + spacing), startYPos); // Position setzen
        deviceInventarSlots[i].setFillColor(sf::Color(100, 100, 100, 200)); // Graue Farbe f¸r Slots
    }
    
    devInventar = new DeviceInventar();

    dasFenster.connectDeviceInventar(devInventar);
    dasFenster.connectPlayer(player);
    dasFenster.connectDeviceSlots(deviceInventarSlots);


}

void GeraetBase::draw(RenderWindow& window)
{
    window.draw(shape);
    this->dasFenster.drawForDevice(window, deviceInventarSlots, devInventar);
}

void GeraetBase::update()
{
    // Wenn Spieler nicht mehr in Reichweite und Fenster offen ? schlieﬂen
    if (!isPlayerInRange() && dasFenster.getIsVisible()) {
        dasFenster.toggle();
    }
}


void GeraetBase::handleEvent(const Event& event, const RenderWindow& window) 
{
    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) 
    {
 
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && isPlayerInRange())
        {
            this->dasFenster.toggle();
            
        }
       


    }
    cout << "Test 4" << endl;

    if (!isPlayerInRange() && this->dasFenster.getIsVisible() == true)
    {
        this->dasFenster.toggle();
    }
    cout << "Test 5" << endl;
    
    this->dasFenster.handleEvent(event, window);
    
}



void GeraetBase::setTexture(sf::Texture* newTexture)
{ 
    texture = newTexture;
    shape.setTexture(texture);
    shape.setPosition(shape.getPosition()); // ‹bernehme die Position des Buttons 
}



void GeraetBase::setScale(float scale)
{
    // Aktuelle Skalierung des Buttons abrufen
    sf::Vector2f currentScale = shape.getScale();

    // Skalierung um den angegebenen Faktor erhˆhen (1.5 bedeutet z.B. 50% grˆﬂer)
    shape.setScale(currentScale.x * scale, currentScale.y * scale);
}

bool GeraetBase::isPlayerInRange()
{
    if (!player) return false;

    sf::Vector2f playerPos = player->getPosition();
    sf::Vector2f geraetPos = shape.getPosition();

    //Berechnung chatGPT

    float dx = playerPos.x - geraetPos.x;
    float dy = playerPos.y - geraetPos.y;
    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance <= 50)return true;


    return false; 


    //Wenn mehrere kg nebeneinander stehen schauen welches N‰her steht
}


DeviceInventar* GeraetBase::getDevInventar()
{
    return devInventar;
}
