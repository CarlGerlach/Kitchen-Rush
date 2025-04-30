#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "mySound.h"

class PauseManager {
private:
    bool paused;
    sf::RectangleShape overlay;
    sf::Font font;

    Button* buttonResume;
    Button* buttonMusicStart;
    Button* buttonMusicStop;
    Button* buttonVolumeUp;
    Button* buttonVolumeDown;
    Button* buttonExit;

    mySound* soundManager; // SoundManager speichern

public:
    PauseManager(const sf::Vector2u& windowSize, mySound* soundManager);

    void handleInput(const sf::Event& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    bool isPaused() ;
};
