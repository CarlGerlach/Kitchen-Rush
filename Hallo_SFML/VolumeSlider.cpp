#include "VolumeSlider.h"
#include <iostream>

VolumeSlider::VolumeSlider(sf::Vector2f position, sf::Vector2f size, mySound* sm)
    : volume(100.0f), soundManager(sm)
{
    backgroundBar.setPosition(position);
    backgroundBar.setSize(size);
    backgroundBar.setFillColor(sf::Color(100, 100, 100));

    fillBar.setPosition(position);
    fillBar.setSize(sf::Vector2f(size.x, size.y));
    fillBar.setFillColor(sf::Color(0, 200, 0));

    if (!font.loadFromFile("Texturen & Musik/TDAText.ttf")) {
        std::cerr << "Fehler beim Laden der Schriftart!" << std::endl;
    }

    label.setFont(font);
    label.setString("Soundeffekt-Lautstärke");
    label.setCharacterSize(24);
    label.setPosition(position.x, position.y - 35);
    label.setFillColor(sf::Color::White);
}

void VolumeSlider::draw(sf::RenderWindow& window)
{
    window.draw(label);
    window.draw(backgroundBar);
    window.draw(fillBar);
}

void VolumeSlider::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (backgroundBar.getGlobalBounds().contains(mousePos)) {
            float relativeX = mousePos.x - backgroundBar.getPosition().x;
            float percentage = relativeX / backgroundBar.getSize().x;
            if (percentage < 0.f) percentage = 0.f;
            if (percentage > 1.f) percentage = 1.f;

            volume = percentage * 100.0f;
            fillBar.setSize(sf::Vector2f(backgroundBar.getSize().x * percentage, backgroundBar.getSize().y));
            if (soundManager) {
                soundManager->setVolume(volume);
            }
        }
    }
}

void VolumeSlider::setVolume(float vol)
{
    if (vol < 0.f) vol = 0.f;
    if (vol > 100.f) vol = 100.f;
    volume = vol;
    float percent = volume / 100.f;
    fillBar.setSize(sf::Vector2f(backgroundBar.getSize().x * percent, backgroundBar.getSize().y));
    if (soundManager) {
        soundManager->setVolume(volume);
    }
   
}