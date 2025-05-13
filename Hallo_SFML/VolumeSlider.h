#ifndef VOLUMESLIDER_H
#define VOLUMESLIDER_H

#include <SFML/Graphics.hpp>
#include "mySound.h"

class VolumeSlider {
private:
    sf::RectangleShape backgroundBar;
    sf::RectangleShape fillBar;
    sf::Font font;
    sf::Text label;
    float volume; // zwischen 0.0 und 100.0
    mySound* soundManager;

public:
    VolumeSlider(sf::Vector2f position, sf::Vector2f size, mySound* soundManager);

    void draw(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void setVolume(float vol); // explizit clamping vermeiden
    float getVolume() const { return volume; }
};

#endif
