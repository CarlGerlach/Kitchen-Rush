#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "list"

class Fenster {
private:
    sf::RectangleShape shape;  // Hintergrund des Fensters
    sf::Text text;             // Titel des Fensters
    sf::Font font;             // Schriftart des Fensters
    Button* closeButton;       // Button zum Schlieﬂen des Fensters

    std::list<Button*> buttons;// Buttons im Fenster

    bool visible;              // Sichtbarkeitsstatus

    mySound* soundOfButton;

public:
    Fenster(const std::string& label, const sf::Font& font);
    ~Fenster();

    void draw(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void setPosition(float x, float y);
    void setText(std::string t);

    void setVisible(bool isVisible);
    bool isVisible();

    void addButton(float x, float y, float width, float height, const std::string& label, const sf::Color& bgColor, const sf::Color& textColor, std::function<void()> onClick);
};
