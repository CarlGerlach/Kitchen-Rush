#include "PauseManager.h"

PauseManager::PauseManager(const sf::Vector2u& windowSize, const sf::Font& font)
    : paused(false)
{
    overlay.setSize(sf::Vector2f(windowSize));
    overlay.setFillColor(sf::Color(0, 0, 0, 150)); // halbtransparentes Schwarz

    pauseText.setFont(font);
    pauseText.setString("PAUSIERT");
    pauseText.setCharacterSize(100);
    pauseText.setFillColor(sf::Color::White);
    pauseText.setStyle(sf::Text::Bold);

    // Zentriere den Text
    sf::FloatRect textRect = pauseText.getLocalBounds();
    pauseText.setOrigin(textRect.width / 2, textRect.height / 2);
    pauseText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
}

void PauseManager::handleInput(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        paused = !paused;
    }
}

bool PauseManager::isPaused() const
{
    return paused;
}

void PauseManager::draw(sf::RenderWindow& window)
{
    if (paused)
    {
        window.draw(overlay);
        window.draw(pauseText);
    }
}

