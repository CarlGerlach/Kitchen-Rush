#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "mySound.h"

class StartScreen {
private:
    sf::Font font;
    sf::Text title;
    sf::RectangleShape startButton;
    sf::Text buttonText;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    mySound* soundManager; // <- Hier speichern wir den Zeiger

public:
    StartScreen(mySound* soundManager); // <- Konstruktor nimmt den Zeiger
    bool run(sf::RenderWindow& window);
    void playStartSound(); // <- Methode zum Abspielen des Sounds
};

#endif // STARTSCREEN_H
