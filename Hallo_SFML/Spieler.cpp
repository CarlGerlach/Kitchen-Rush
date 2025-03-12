#include "Spieler.h"

// Konstruktor
Spieler::Spieler(float startX, float startY, float size, float speed, sf::FloatRect bounds, const std::string& texturPfad)
{
    this->speed = speed;
    this->bounds = bounds;
    this->points = 0;

    if (!texture.loadFromFile(texturPfad)) {
        std::cerr << "Fehler beim Laden der Textur: " << texturPfad << std::endl;
        exit(-1);
    }

    shape.setTexture(&texture);
    shape.setSize(sf::Vector2f(size, size));
    shape.setPosition(startX, startY);

    // Inventar initialisieren (alle Felder auf nullptr setzen)
    for (int i = 0; i < 5; i++) {
        inventar[i] = nullptr;
    }

    // Grafische Darstellung der Inventarslots (zentriert am unteren Bildschirmrand)
    float slotSize = 50.f;
    float spacing = 10.f;
    float totalWidth = 5 * slotSize + 4 * spacing; // Gesamtbreite des Inventars
    float startXPos = (bounds.width - totalWidth) / 2.f; // Zentrierte Position
    float startYPos = bounds.height - slotSize - 20.f; // Etwas über dem unteren Rand

    for (int i = 0; i < 5; i++) 
    {
        inventarSlots[i].setSize(sf::Vector2f(slotSize, slotSize));
        inventarSlots[i].setPosition(startXPos + i * (slotSize + spacing), startYPos);
        inventarSlots[i].setFillColor(sf::Color(100, 100, 100, 200));

  
    }
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

void Spieler::draw(sf::RenderWindow& window) {
    window.draw(shape);

    // Bildschirmbreite neu berechnen für eine dynamische Mitte
    float screenWidth = window.getSize().x;
    float slotSize = 50.f;  // Größe eines Inventarslots
    float spacing = 10.f;   // Abstand zwischen Slots
    float totalWidth = 5 * slotSize + 4 * spacing;
    float startXPos = (screenWidth - totalWidth) / 2.f;  // Inventar mittig platzieren
    float startYPos = window.getSize().y - slotSize - 20.f;  // Inventar am unteren Rand platzieren

    for (int i = 0; i < 5; i++) {
        inventarSlots[i].setPosition(startXPos + i * (slotSize + spacing), startYPos);
        window.draw(inventarSlots[i]);

        if (inventar[i] != nullptr) {
            sf::Sprite sprite = inventar[i]->getSprite();

            // Skalierung beibehalten
            sprite.setScale(3.f, 3.f);

            // Berechnung der neuen Position für die Mitte des Slots
            sf::Vector2f slotPos = inventarSlots[i].getPosition();
            sf::Vector2f slotCenter = sf::Vector2f(slotPos.x + slotSize / 2.f, slotPos.y + slotSize / 2.f);

            // Sprite-Größe basierend auf Textur und Skalierung berechnen
            sf::Vector2f spriteSize = sf::Vector2f(sprite.getTexture()->getSize());
            spriteSize *= sprite.getScale().x;  // Berücksichtigt die Skalierung (3x)

            // Setze das Sprite mittig in den Slot
            sprite.setPosition(slotCenter.x - spriteSize.x / 2.f, slotCenter.y - spriteSize.y / 2.f);

            window.draw(sprite);
        }
    }
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

// Item zum Inventar hinzufügen
bool Spieler::addItem(Item* item, int slotIndex) {
    if (slotIndex < 0 || slotIndex >= 5) return false; // Ungültiger Slot

    if (inventar[slotIndex] == nullptr) {
        inventar[slotIndex] = item;
        return true;
    }
    return false; // Slot ist voll
}

// Item aus Inventar entfernen
bool Spieler::removeItem(int slotIndex) {
    if (slotIndex < 0 || slotIndex >= 5) return false;

    if (inventar[slotIndex] != nullptr) {
        inventar[slotIndex] = nullptr;
        return true;
    }
    return false;
}

void Spieler::inventarKonsole()
{
    for (int i = 0; i < 5; i++)
    {
        cout << "Inventar" << i << inventar[i]->getTyp() << endl;

    }
    cout << "Ausgegeben" << endl;
}


// Punkteverwaltung
int Spieler::getPoints()
{
    return points;
}

void Spieler::addPoints(int ini_points)
{
    points += ini_points;
}
