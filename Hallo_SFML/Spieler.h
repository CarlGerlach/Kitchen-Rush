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
    Item* aktuellesItem;
    int points;


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

    Item* getAktuellesItem();
    void setAktuellesItem(Item* ini_Item);

    int getPoints();
    void addPoints(int ini_points);
    

};
