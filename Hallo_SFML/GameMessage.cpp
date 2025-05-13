#include "GameMessage.h"

// Initialisierung der static Member
sf::Text GameMessage::messageText;
float GameMessage::timeLeft = 0.0f;
bool GameMessage::active = false;

void GameMessage::init(const sf::Font& font)
{
    messageText.setFont(font);
    messageText.setCharacterSize(24);
    messageText.setFillColor(sf::Color::Red);
    messageText.setPosition(800, 100);
}





void GameMessage::setText(const std::string& text)
{
    messageText.setString(text);
    timeLeft = 0.3f;
    active = true;
}

void GameMessage::update(float deltaTime)
{
    if (active)
    {
        timeLeft -= deltaTime;
        if (timeLeft <= 0.0f)
        {
            active = false;
        }
    }
}

void GameMessage::draw(sf::RenderWindow& window)
{
    if (active)
    {
        window.draw(messageText);
    }
}
