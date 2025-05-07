#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "mySound.h"

class PauseManager {
public:
    bool paused;
private:

    

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

    void setPaused(bool paused) {
		this->paused = paused;
	}
		
    void togglePause() {
        if (paused == 0) {
			paused = 1;
		}
        else {
			paused = 0;
		}
	}
		
};
