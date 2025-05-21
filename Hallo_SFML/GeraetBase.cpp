#include "GeraetBase.h"
#include "Grid.h"
#include "DeviceInventar.h"

int GeraetBase::id = 1;

GeraetBase::GeraetBase(int gridNumber, Spieler* ini_player, int ini_inventorySize) : dasFenster()
{
    geraetID = id;
    player = ini_player;

    float width = 75;
    float height = 75;
    

    sf::Vector2f gridPos = Grid::getPosition(gridNumber);

    shape.setPosition(gridPos.x - 2, gridPos.y - 2);
    shape.setSize({ width, height });


    for (int i = 0; i < ini_inventorySize; i++)
    {
        RectangleShape slot;

        if (i < 5)
        {
            slot.setSize(Vector2f(slotSize, slotSize));
            slot.setPosition(startXPos + i * (slotSize + spacing), startYPos);
            slot.setFillColor(sf::Color(100, 100, 100, 200));
        }
        else if (i < 10)
        {
            slot.setSize(Vector2f(slotSize, slotSize));
            slot.setPosition(startXPos + (i - 5) * (slotSize + spacing), startYPos + slotSize + spacing);
            slot.setFillColor(sf::Color(100, 100, 100, 200));
        }
        else if (i < 15)
        {

            slot.setSize(Vector2f(slotSize, slotSize));
            slot.setPosition(startXPos + (i - 10) * (slotSize + spacing), startYPos + 2* slotSize + 2 * spacing);
            slot.setFillColor(sf::Color(100, 100, 100, 200));
        }
        else if (i < 21)
        {

            slot.setSize(Vector2f(slotSize, slotSize));
            slot.setPosition(startXPos + (i - 15) * (slotSize + spacing), startYPos + 3* slotSize + 3* spacing);
            slot.setFillColor(sf::Color(100, 100, 100, 200));
        }
        

        deviceInventorySlots.push_back(slot);
    }


    
    devInventar = new DeviceInventar();
    devInventar->setSlotAnzahl(ini_inventorySize);

    dasFenster.connectDeviceInventar(devInventar);
    dasFenster.connectPlayer(player);
    dasFenster.connectDeviceSlots(deviceInventorySlots);
    id++;


}

void GeraetBase::draw(RenderWindow& window)
{
    window.draw(shape);
    this->dasFenster.drawForDevice(window, deviceInventorySlots, devInventar);

    // Debug-Hitbox zeichnen
   //sf::FloatRect b = shape.getGlobalBounds();
   //
   //sf::RectangleShape debugBox;
   //debugBox.setPosition(b.left, b.top);
   //debugBox.setSize({ b.width, b.height });
   //debugBox.setFillColor(sf::Color::Transparent);
   //debugBox.setOutlineColor(sf::Color::Red);
   //debugBox.setOutlineThickness(1.f);
   //
   //window.draw(debugBox);  // ? Zeichne die kleine Kollision-Hitbox
}

void GeraetBase::update()
{
    // Wenn Spieler nicht mehr in Reichweite und Fenster offen ? schließen
    if (!isPlayerInRange() && dasFenster.getIsVisible()) 
    {
        dasFenster.toggle();
    }
}

void GeraetBase::handleEvent(const Event& event, const RenderWindow& window)
{
    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
        {
     
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    
            if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && isPlayerInRange())
            {
                this->dasFenster.toggle();        
            }
        }

    // Prüfe auf Leertaste gedrückt
    if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
    {
        if (isPlayerInRange())
        {
            this->dasFenster.toggle();
        }
    }

    // Fenster automatisch schließen, wenn Spieler sich entfernt
    if (!isPlayerInRange() && this->dasFenster.getIsVisible())
    {
        this->dasFenster.toggle();
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

void GeraetBase::setInventory(int index, vector<DeviceInventar*> ini_allInventory)
{ 
    for (int i = 0; i < ini_allInventory.size(); i++)
    {
        if (i = index - 1)
        {
            DeviceInventar* inv = ini_allInventory[i];
            devInventar = inv;
        }
    }
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

    if (distance <= 80)return true;


    return false; 


    //Wenn mehrere kg nebeneinander stehen schauen welches Näher steht
}


DeviceInventar* GeraetBase::getDevInventar()
{
    return devInventar;
}

RectangleShape& GeraetBase::getShape()
{
    return shape;
}
