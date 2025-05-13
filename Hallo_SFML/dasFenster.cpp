#include "dasFenster.h"
#include "Spieler.h"

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

void dasFenster::drawForDevice(RenderWindow& window, std::vector<sf::RectangleShape>& deviceInventorySlots, DeviceInventar* devInventar)
{
    if (visible)
    {
        window.draw(background);

        for (auto& knopf : knoepfe)
        {
            knopf.draw(window);
        }

        for (size_t i = 0; i < deviceInventorySlots.size(); i++)
        {
            window.draw(deviceInventorySlots[i]);

            if (devInventar->getItem(i) != nullptr)
            {
                sf::Sprite sprite = devInventar->getItem(i)->getSprite();

                float scaleX = deviceInventorySlots[i].getSize().x / sprite.getTexture()->getSize().x;
                float scaleY = deviceInventorySlots[i].getSize().y / sprite.getTexture()->getSize().y;
                sprite.setScale(scaleX, scaleY);

                sf::Vector2f slotPos = deviceInventorySlots[i].getPosition();
                sf::Vector2f slotCenter = sf::Vector2f(
                    slotPos.x + deviceInventorySlots[i].getSize().x / 2.f,
                    slotPos.y + deviceInventorySlots[i].getSize().y / 2.f
                );

                sf::Vector2f spriteSize = sf::Vector2f(sprite.getTexture()->getSize());
                spriteSize *= sprite.getScale().x;

                sprite.setPosition(slotCenter.x - spriteSize.x / 2.f,
                    slotCenter.y - spriteSize.y / 2.f);

                window.draw(sprite);
            }
        }
    }
}



void dasFenster::handleEvent(const Event& event, const RenderWindow& window)
{
    if (!visible)
        return;

    for (auto& knopf : knoepfe)
    {
        knopf.handleEvent(event, window);
    }

    if (connectedDeviceInventar && connectedPlayer)
    {
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
        {
            Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

            for (size_t i = 0; i < connectedDeviceSlots.size(); i++)
            {
                RectangleShape& slot = connectedDeviceSlots[i];

                if (slot.getGlobalBounds().contains(mousePos))
                {
                    Item* item = connectedDeviceInventar->getItem(i);

                    if (item != nullptr)
                    {
                        if (connectedPlayer->getPlayerInventar()->addItem(item) == true)
                        {
                            connectedDeviceInventar->removeItem(i);
                        }
                        else
                        {
                            cout << "Inventar ist Voll" << endl;
                        }
                        
                    }
                }
            }

           
            for (int i = 0; i < 5; i++)
            {
                RectangleShape& playerSlot = getConnectedPlayer()->getInventarSlots(i);

                if (playerSlot.getGlobalBounds().contains(mousePos))
                {
                    PlayerInventar* playerInv = connectedPlayer->getPlayerInventar();
                    Item* selectedItem = playerInv->getItem(i);

                    if (selectedItem == nullptr)
                    {
                        std::cout << "Kein Item im Spielerinventar ausgewählt\n";
                        return;
                    }

                    bool success = connectedDeviceInventar->addItem(selectedItem);
                    if (success)
                    {
                        playerInv->removeItem(i);
                        //std::cout << "Item wurde erfolgreich vom Spieler ins Gerät übertragen\n";
                    }
                    else
                    {
                        std::cout << "Fehler beim Übertragen des Items\n";
                    }
                }
            }
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

void dasFenster::connectDeviceInventar(DeviceInventar* inventar)
{
    connectedDeviceInventar = inventar;
}

void dasFenster::connectPlayer(Spieler* player)
{
    connectedPlayer = player;
}

void dasFenster::connectDeviceSlots(vector<RectangleShape> ini_connectedDeviceSlots)
{
    connectedDeviceSlots = ini_connectedDeviceSlots;
}

Spieler* dasFenster::getConnectedPlayer()
{
    return connectedPlayer;
}

bool dasFenster::getIsVisible()
{
    return visible;
}
