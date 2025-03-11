#include "Knopf.h"


Knopf::Knopf(float x, float y, float width, float height, const string& label, Font& font, function<void()> callback)
{
    shape.setPosition(x, y);
    shape.setSize(Vector2f(width, height));
    shape.setFillColor(Color::White);

    this->font = font;

    //font.loadFromFile("arial.ttf"); // Stelle sicher, dass die Datei existiert
    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(14);
    text.setFillColor(Color::Black);
    text.setPosition(x + 10, y + 10);

    onClick = callback;
}

void Knopf::draw(RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}

void Knopf::handleEvent(const Event& event, const RenderWindow& window) 
{
    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) 
    {
        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
        if (shape.getGlobalBounds().contains(mousePos)) 
        {
            if (onClick) 
            {
                onClick();
            }
        }
    }
}