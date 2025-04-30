#include "Spieler.h"

// Konstruktor
Spieler::Spieler(float startX, float startY, float size, float speed, sf::FloatRect bounds, const std::string& texturPfad)
{
    this->speed = speed;
    this->bounds = bounds;
    this->points = 0;

    inventar = new PlayerInventar();


    if (!texture.loadFromFile(texturPfad)) {
        std::cerr << "Fehler beim Laden der Textur: " << texturPfad << std::endl;
        exit(-1);
    }

    shape.setTexture(&texture);
    shape.setSize(sf::Vector2f(size, size));
    shape.setPosition(startX, startY);

  

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
    else 
    {
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

    for (int i = 0; i < 5; i++) 
    {
        cout << "Test1" << endl;
        inventarSlots[i].setPosition(startXPos + i * (slotSize + spacing), startYPos);
        window.draw(inventarSlots[i]);

        cout << "Test2" << endl;
        if (inventar->getItem(i) != nullptr) {
            sf::Sprite sprite = inventar->getItem(i)->getSprite();

            cout << "Test3" << endl;

            // Berechne die Skalierung des Sprites basierend auf der Slot-Größe
            float scaleX = inventarSlots[i].getSize().x / sprite.getTexture()->getSize().x;
            float scaleY = inventarSlots[i].getSize().y / sprite.getTexture()->getSize().y;

            // Setze die Skalierung des Sprites, um in den Slot zu passen
            sprite.setScale(scaleX, scaleY);

            // Berechne die Mitte des Slots und setze das Sprite in die Mitte des Slots
            sf::Vector2f slotPos = inventarSlots[i].getPosition();
            sf::Vector2f slotCenter = sf::Vector2f(slotPos.x + inventarSlots[i].getSize().x / 2.f,
                slotPos.y + inventarSlots[i].getSize().y / 2.f);

            // Berechne die Größe des Sprites und zentriere es
            sf::Vector2f spriteSize = sf::Vector2f(sprite.getTexture()->getSize());
            spriteSize *= sprite.getScale().x;  // Berücksichtige die Skalierung

            sprite.setPosition(slotCenter.x - spriteSize.x / 2.f, slotCenter.y - spriteSize.y / 2.f);

            window.draw(sprite);  // Zeichne das Sprite im Slot

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

PlayerInventar* Spieler::getPlayerInventar()
{
    return inventar;
}

RectangleShape& Spieler::getInventarSlots(int slotIndex)
{
    return inventarSlots[slotIndex];
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

void Spieler::setLookingLeft(bool lookingleft)
{
    lookingRight = false;
	lookingLeft = lookingleft;
}

void Spieler::setLookingRight(bool lookingright)
{
    lookingLeft = false;
	lookingRight = lookingright;
}

bool Spieler::isLookingLeft()
{
    return lookingLeft;
}

bool Spieler::isLookingRight()
{
	return lookingRight;
}

