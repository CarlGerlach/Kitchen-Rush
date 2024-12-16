#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Spieler
{
private:
    sf::RectangleShape shape;  // Form des Spielers
    float speed;               // Bewegungsgeschwindigkeit
    sf::FloatRect bounds;      // Spielfeldgrenzen
    sf::Texture texture;       // Textur für den Spieler

public:
    // Konstruktor
    Spieler(float startX, float startY, float size, float speed, sf::FloatRect bounds, const std::string& texturPfad);

    // Methode zum Ändern der Textur
    void setTexture(const std::string& texturPfad);

    // Funktion zum Zeichnen des Spielers
    void draw(sf::RenderWindow& window);

    // Funktion zur Bewegung
    void move(sf::Vector2f direction);

    // Zugriff auf die Position
    sf::Vector2f getPosition();
};
