#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
using namespace std;
using namespace sf;

class Fenster
{
private:
    RectangleShape shape;   // Form des Buttons
    Text text;              // Text des Buttons
    Font font;              // Schriftart (für den Text)

public:

    Fenster(const std::string& label, const sf::Font& font);

    Fenster(float x, float y, float width, float height, const std::string& label, const sf::Font& font, const sf::Color& buttonColor, const sf::Color& textColor);

    // Zeichne den Button
    void draw(sf::RenderWindow& window);

    // Setter 
    void setPosition(float x, float y);
    void setText(string t);
};

