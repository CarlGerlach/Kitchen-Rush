#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include <iostream>
#include <functional>

#include "mySound.h"

using namespace std;
using namespace sf;

class Button
{
private:
    sf::RectangleShape shape;   // Form des Buttons
    sf::Text text;              // Text des Buttons
    sf::Font font;              // Schriftart (für den Text)
    std::function<void()> onClick; // Funktion, die beim Klick ausgeführt wird
    mySound* soundOfButton;


public:
    // Konstruktor
    Button(float x, float y, float width, float height, const std::string& label, const sf::Font& font, const sf::Color& buttonColor, const sf::Color& textColor, mySound* ini_soundOfButton);

    // Setter für die OnClick-Funktion
    void setOnClick(std::function<void()> callback);

    // Zeichne den Button
    void draw(sf::RenderWindow& window);

    // Überprüfe, ob der Button angeklickt wurde
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);

    // Setter für die Position
    void setPosition(float x, float y);
};
