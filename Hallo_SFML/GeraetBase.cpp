#include "GeraetBase.h"

GeraetBase::GeraetBase(float x, float y, float width, float hight): dasFenster(x + 50, y + 50) {
    shape.setPosition(x, y);
    shape.setSize(Vector2f(width, hight));
    shape.setPosition(Vector2f(x, y));
    shape.setFillColor(Color::Blue);

    for (int i = 0; i < 5; i++) 
    {
        inventar[i] = nullptr; // Inventar leeren
    }

}

void GeraetBase::draw(RenderWindow& window) {
    window.draw(shape);
    this->dasFenster.draw(window);
}

void GeraetBase::handleEvent(const Event& event, const RenderWindow& window) {
    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
        if (shape.getGlobalBounds().contains(mousePos)) 
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
    if (newTexture != nullptr) // Nur setzen, wenn die Textur gültig ist
    {
        texture = newTexture;
        shape.setTexture(texture);

        // Skaliere die Textur passend zur Rechteckform
        shape.setScale(
            shape.getSize().x / texture->getSize().x,
            shape.getSize().y / texture->getSize().y
        );
    }
    else
    {
        cout << "Fehler: Ungültige Textur!" << endl;
    }
}