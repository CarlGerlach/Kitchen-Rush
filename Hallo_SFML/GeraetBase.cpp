#include "GeraetBase.h"
#include "Grid.h"

GeraetBase::GeraetBase(int gridNumber) : dasFenster()
{
    float width = 75;
    float height = 75;
    

    sf::Vector2f gridPos = Grid::getPosition(gridNumber);

    shape.setPosition(gridPos.x - 2, gridPos.y - 2);
    shape.setSize({ width, height });
    

    for (int i = 0; i < 5; i++) 
    {
        inventar[i] = nullptr; // Inventar leeren
    }

}

void GeraetBase::draw(RenderWindow& window) {
    window.draw(shape);
    this->dasFenster.draw(window);
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

void GeraetBase::addItem(Item* item) 
{
    for (int i = 0; i < 5; i++)
    {
        if (inventar[i] == nullptr) 
        {
            inventar[i] = item;
            cout << "Item hinzugefügt auf Platz " << i << endl;
            return;
        }
    }
    cout << "Inventar voll!" << endl;
}

void GeraetBase::removeItem() 
{
    for (int i = 4; i >= 0; i--) 
    {
        if (inventar[i] != nullptr) 
        {
            cout << "Item entfernt von Platz " << i << endl;
            delete inventar[i];
            inventar[i] = nullptr;
            return;
        }
    }
    cout << "Inventar ist leer!" << endl;
}

void GeraetBase::setTexture(sf::Texture* newTexture)
{
   
    texture = newTexture;
    shape.setTexture(texture);
    shape.setPosition(shape.getPosition()); // Übernehme die Position des Buttons
    


   
}

void GeraetBase::itemReinlegen(Spieler& player)
{   
    



}

void GeraetBase::itemRausnehmen(Spieler& player)
{
    if (inventar[4] != nullptr)
    {
        player.addItem(inventar[4], 4);
        delete inventar[4];
        cout << inventar[4] << endl;
        inventar[4] = nullptr;
        cout << inventar[4] << endl;
        cout << "Inventar5" << inventar[4]->getTyp();
        cout << "Player5: ";  player.inventarKonsole(); cout << endl;
   
    }
    else
    {
        cout << "Kein fertiges Item vorhanden" << endl;
    }
}

void GeraetBase::setScale(float scale)
{
    // Aktuelle Skalierung des Buttons abrufen
    sf::Vector2f currentScale = shape.getScale();

    // Skalierung um den angegebenen Faktor erhöhen (1.5 bedeutet z.B. 50% größer)
    shape.setScale(currentScale.x * scale, currentScale.y * scale);
}