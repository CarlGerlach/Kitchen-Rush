#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "mySound.h"
#include "Spieler.h"
#include "SpielstandManager.h"

class PauseManager
{
private:
    bool paused;
    bool gameOver = false;
    sf::RectangleShape overlay;
    sf::Font font;

    Spieler* spieler;

    Button* buttonResume;
    Button* buttonMusicStart;
    Button* buttonMusicStop;
    Button* buttonVolumeUp;
    Button* buttonVolumeDown;
    Button* buttonExit;

    Button* buttonFXUp;      // Neue Buttons für Lautstärke der Soundeffekte
    Button* buttonFXDown;

    Button* buttonSaveGame;
	Button* buttonLoadGame;

    mySound* soundManager;

public:
    PauseManager(const sf::Vector2u& windowSize, mySound* soundMgr, Spieler* spieler);
    void handleInput(const sf::Event& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    bool isPaused();
    void setGameOver(bool value);
    bool getGameOver();
    bool getPauseStatus();

    void togglePause();  // Methode zum Umschalten der Pause
};
