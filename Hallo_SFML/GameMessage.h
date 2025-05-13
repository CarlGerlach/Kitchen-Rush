#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class GameMessage
{
private:
    static sf::Text messageText;
    static float timeLeft;
    static bool active;

public:
    static void init(const sf::Font& font);                        // Einmal aufrufen
    static void setText(const std::string& text); // Nachricht anzeigen
    static void update(float deltaTime);                           // Zeit aktualisieren
    static void draw(sf::RenderWindow& window);
};
