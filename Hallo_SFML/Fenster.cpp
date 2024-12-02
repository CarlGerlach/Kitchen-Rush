#include "Fenster.h"

Fenster::Fenster(const std::string& label, const sf::Font& font)
{
    // Setze die Form
    shape.setPosition(400, 300); // x, y
    shape.setSize({ 500, 600 }); // width, height
    shape.setFillColor(sf::Color::Black);

    // Setze den Text
    this->font = font;  // Font speichern
    text.setFont(this->font);
    text.setString(label);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    // Zentriere den Text im Button
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);

    //                x + width           y + height
    text.setPosition(400 + 500 / 2.0f, 300 + 600 / 2.0f);
}

Fenster::Fenster(float x, float y, float width, float height, const std::string& label, const Font& font, const Color& fillColor, const Color& textColor)
{
    // Setze die Form
    shape.setPosition(x, y);
    shape.setSize({ width, height });
    shape.setFillColor(fillColor);

    // Setze den Text
    this->font = font;  // Font speichern
    text.setFont(this->font);
    text.setString(label);
    text.setCharacterSize(24);
    text.setFillColor(textColor);

    // Zentriere den Text im Button
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    text.setPosition(x + width / 2.0f, y + height / 2.0f);
}

void Fenster::draw(RenderWindow& window)
{
    window.draw(shape);
    window.draw(text);
}

void Fenster::setPosition(float x, float y)
{
    shape.setPosition(x, y);
    text.setPosition(x + shape.getSize().x / 2.0f, y + shape.getSize().y / 2.0f);
}

void Fenster::setText(string t)
{
    text.setString(t);
}
