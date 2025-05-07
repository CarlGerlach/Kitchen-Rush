#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Item.h"
#include "PlayerInventar.h"

using namespace std;
using namespace sf;

class Spieler
{
private:
    sf::RectangleShape shape;  // Form des Spielers
    float speed;               // Bewegungsgeschwindigkeit
    sf::FloatRect bounds;      // Spielfeldgrenzen
    sf::Texture texture;       // Textur für den Spieler
    PlayerInventar* inventar;       // Inventar mit 5 Slots
    int points;

    // Grafische Elemente für das Inventar
    sf::RectangleShape inventarSlots[5]; // 5 Slots für das Inventar
    sf::Font font;                      // Schriftart für Item-Anzahl
    bool lookingLeft;
    bool lookingRight;
    

public:
    // Konstruktor
    Spieler(float startX, float startY, float size, float speed, sf::FloatRect bounds, sf::Texture* newTexture);

    // Methode zum Ändern der Textur
    void setTexture(sf::Texture* newTexture);

    // Funktion zum Zeichnen des Spielers und Inventars
    void draw(sf::RenderWindow& window);

    // Funktion zur Bewegung
    void move(sf::Vector2f direction);

    // Zugriff auf die Position
    sf::Vector2f getPosition();


    PlayerInventar* getPlayerInventar();
    RectangleShape& getInventarSlots(int slotIndex);


    int getPoints();
    void addPoints(int ini_points);

    void setLookingLeft(bool lookingleft);
    void setLookingRight(bool lookingright);

    bool isLookingLeft();
    bool isLookingRight();
};
