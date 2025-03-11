#include "GeraetBase.h"

GeraetBase::GeraetBase(float x, float y, float width, float hight): dasFenster(x + 50, y + 50) 
{
   
    shape.setSize(Vector2f(width, hight));
    shape.setPosition(Vector2f(x, y));

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
    if (newTexture && newTexture->getSize().x > 0 && newTexture->getSize().y > 0) // Sicherstellen, dass die Textur valide ist
    {
        texture = newTexture; // Zeiger speichern
        shape.setTexture(texture);

        // Textur korrekt skalieren
        shape.setScale(
            shape.getSize().x / static_cast<float>(texture->getSize().x),
            shape.getSize().y / static_cast<float>(texture->getSize().y)
        );

        cout << "Textur gesetzt und skaliert." << endl;
    }
    else
    {
        cout << "Fehler: Ungültige oder leere Textur übergeben!" << endl;
    }
}