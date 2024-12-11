#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include <iostream>
#include <functional>
class Spieler 
{
private:
    sf::RectangleShape shape; // Form des Spielers
    float speed; // Bewegungsgeschwindigkeit
    sf::FloatRect bounds; //Spielfeldgrenzen

    sf::Texture texture; //texture für spieler (ente)

public:
   
    
    
    
   
    
    
    Spieler(float startX, float startY, float size, float speed, sf::FloatRect bounds, const std::string& texturPfad)
      {
        this->speed = speed;         
        this->bounds = bounds;     

        //Textur laden

        if (!texture.loadFromFile("Texturen & Musik/Char-links.png")) {
            std::cerr << "Fehler beim Laden der Textur!" << std::endl;
            exit(-1);
        }

        shape.setTexture(&texture);

        shape.setSize(sf::Vector2f(size, size));

       /* shape.setFillColor(sf::Color::Blue);*/
        //Unnötig weil keine Farbe im sprite

        shape.setPosition(startX, startY);

    }

    // Funktion zum Zeichnen des Spielers
    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }

    // Funktion zur Bewegung
    void move(sf::Vector2f direction) {
        if (direction.x != 0.f || direction.y != 0.f) {
            // Länge des Vektors berechnen (Pythagoras)
            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

            // Richtung normalisieren
            direction /= length;

            // Neue Position berechnen
            sf::Vector2f newPosition = shape.getPosition() + direction * speed;

            // Begrenzungen prüfen
            if (newPosition.x < bounds.left) newPosition.x = bounds.left;
            if (newPosition.y < bounds.top) newPosition.y = bounds.top;
            if (newPosition.x + shape.getSize().x > bounds.left + bounds.width)
                newPosition.x = bounds.left + bounds.width - shape.getSize().x;
            if (newPosition.y + shape.getSize().y > bounds.top + bounds.height)
                newPosition.y = bounds.top + bounds.height - shape.getSize().y;

            shape.setPosition(newPosition);
        }

        
    }

    // Zugriff auf die Position
    sf::Vector2f getPosition() {
        return shape.getPosition();
    }
};

