#include "Button.h"
#include "mySound.h"

Button::Button(float x, float y, float width, float height, const std::string& label, const sf::Font& font, const sf::Color& buttonColor, const sf::Color& textColor, mySound* ini_soundOfButton)
{
    // Setze die Form
    shape.setPosition(x, y);
    shape.setSize({ width, height });
    shape.setFillColor(buttonColor);

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

    soundOfButton = ini_soundOfButton;
}

// Setter für die OnClick-Funktion
void Button::setOnClick(std::function<void()> callback)
{
    onClick = callback;
   
}

// Zeichne den Button
void Button::draw(sf::RenderWindow& window)
{
    window.draw(shape);
    window.draw(text);
}

// Überprüfe, ob der Button angeklickt wurde
void Button::handleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
        {
            if (onClick)
            {
                if (soundOfButton != nullptr)
                {
                    soundOfButton->getMeinSound().play();
                }

                onClick();  // Rufe die OnClick-Funktion auf
            }
        }
    }
}

// Setter für die Position
void Button::setPosition(float x, float y)
{
    shape.setPosition(x, y);
    text.setPosition(x + shape.getSize().x / 2.0f, y + shape.getSize().y / 2.0f);
}