#pragma once
#include <SFML/Graphics.hpp>

class PauseManager
{
private:
    bool paused;
    sf::RectangleShape overlay;
    sf::Text pauseText;

public:
    PauseManager(const sf::Vector2u& windowSize, const sf::Font& font);

    void handleInput(const sf::Event& event);
    bool isPaused() const;

    void draw(sf::RenderWindow& window);
};