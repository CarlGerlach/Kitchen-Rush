#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Item.h"

class Spieler
{
private:
    sf::RectangleShape shape;  // Form des Spielers
    float speed;               // Bewegungsgeschwindigkeit
    sf::FloatRect bounds;      // Spielfeldgrenzen
    sf::Texture texture;       // Textur für den Spieler
    Item* inventar[5];         // Inventar mit 5 Slots
    int points;

    // Grafische Elemente für das Inventar
    sf::RectangleShape inventarSlots[5]; // 5 Slots für das Inventar
    sf::Font font;                      // Schriftart für Item-Anzahl
    sf::Text itemCountText[5];          // Text für die Anzahl der Items pro Slot

public:
    // Konstruktor
    Spieler(float startX, float startY, float size, float speed, sf::FloatRect bounds, const std::string& texturPfad);

    // Methode zum Ändern der Textur
    void setTexture(const std::string& texturPfad);

    // Funktion zum Zeichnen des Spielers und Inventars
    void draw(sf::RenderWindow& window);

    // Funktion zur Bewegung
    void move(sf::Vector2f direction);

    // Zugriff auf die Position
    sf::Vector2f getPosition();

    // Inventar-Methoden
    bool addItem(Item* item, int slotIndex);
    bool removeItem(int slotIndex);
    void showInventar();

    int getPoints();
    void addPoints(int ini_points);
};
