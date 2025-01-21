#include "Spieler.h"

// Konstruktor
Spieler::Spieler(float startX, float startY, float size, float speed, sf::FloatRect bounds, const std::string& texturPfad)
{
    this->speed = speed;
    this->bounds = bounds;

    if (!texture.loadFromFile(texturPfad)) {
        std::cerr << "Fehler beim Laden der Textur: " << texturPfad << std::endl;
        exit(-1);
    }

    shape.setTexture(&texture);
    shape.setSize(sf::Vector2f(size, size));
    shape.setPosition(startX, startY);
}

// Methode zum Ändern der Textur
void Spieler::setTexture(const std::string& texturPfad)
{
    if (!texture.loadFromFile(texturPfad)) {
        std::cerr << "Fehler beim Laden der Textur: " << texturPfad << std::endl;
    }
    else {
        shape.setTexture(&texture);
    }
}

// Funktion zum Zeichnen
void Spieler::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

// Funktion zur Bewegung
void Spieler::move(sf::Vector2f direction) {
    if (direction.x != 0.f || direction.y != 0.f) {
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= length;

        sf::Vector2f newPosition = shape.getPosition() + direction * speed;

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
sf::Vector2f Spieler::getPosition() {
    return shape.getPosition();
}

Item* Spieler::getAktuellesItem()
{
    return aktuellesItem;
}

void Spieler::setAktuellesItem(Item* ini_Item)
{
    aktuellesItem = ini_Item;
}

int Spieler::getPoints()
{
    return points;
}

void Spieler::addPoints(int ini_points)
{
    points += ini_points;
}
