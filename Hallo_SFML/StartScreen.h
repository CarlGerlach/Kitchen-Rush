#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <SFML/Graphics.hpp>
#include <iostream>

class StartScreen {
private:
    sf::Font font;
    sf::Text title;
    sf::RectangleShape startButton;
    sf::Text buttonText;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

public:
    StartScreen();
    bool run(sf::RenderWindow& window);
};

#endif // STARTSCREEN_H
