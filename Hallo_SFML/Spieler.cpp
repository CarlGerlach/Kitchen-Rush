#include <sstream>
#include "Spieler.h"


// Konstruktor
Spieler::Spieler(float startX, float startY, float size, float speed, sf::FloatRect bounds, sf::Texture* newTexture)
{
    if (!font.loadFromFile("Texturen & Musik/TDAText.ttf")) {
        std::cerr << "Fehler beim Laden der Schriftart!" << std::endl;
    }
    this->speed = speed;
    this->bounds = bounds;
    this->points = 0;
    lookingLeft = false;
    lookingRight = false;
    leben = 5;

    inventar = new PlayerInventar();

    shape.setTexture(newTexture);
    shape.setSize(sf::Vector2f(size, size));
    shape.setPosition(startX, startY);

  

    // Grafische Darstellung der Inventarslots (zentriert am unteren Bildschirmrand)
    float slotSize = 50.f;
    float spacing = 10.f;
    float startXPos = 800.f; // Feste X-Position des ersten Inventarslots
    float startYPos = bounds.height - slotSize - 20.f; // Y-Position bleibt gleich

    for (int i = 0; i < 5; i++)
    {
        inventarSlots[i].setSize(sf::Vector2f(slotSize, slotSize));
        inventarSlots[i].setPosition(startXPos + i * (slotSize + spacing), startYPos);
        inventarSlots[i].setFillColor(sf::Color(100, 100, 100, 200));
    }
}


// Methode zum Ändern der Textur
void Spieler::setTexture(sf::Texture* newTexture)
{
    shape.setTexture(newTexture);
}

void Spieler::draw(sf::RenderWindow& window)
{
    window.draw(shape);

    float slotSize = 50.f;
    float spacing = 10.f;
    float totalWidth = 5 * slotSize + 4 * spacing;

    // Aktuelle View holen
    sf::View view = window.getView();
    sf::Vector2f viewSize = view.getSize();
    sf::Vector2f viewCenter = view.getCenter();

    // Zentrierte Position berechnen
    float startXPos = viewCenter.x - viewSize.x / 2.f + (viewSize.x - totalWidth) / 2.f;
    float startYPos = viewCenter.y + viewSize.y / 2.f - slotSize - 100.f;

    // Punktanzeige (bleibt wie gehabt)
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setPosition(viewCenter.x + viewSize.x / 2.f - 120.f, viewCenter.y - viewSize.y / 2.f + 70.f); // z.B. oben rechts in View
    text.setString(std::to_string(points));
    window.draw(text);

    for (int i = 0; i < 5; i++)
    {
        inventarSlots[i].setPosition(startXPos + i * (slotSize + spacing), startYPos);
        window.draw(inventarSlots[i]);

        if (inventar->getItem(i) != nullptr) {
            sf::Sprite sprite = inventar->getItem(i)->getSprite();

            float scaleX = inventarSlots[i].getSize().x / sprite.getTexture()->getSize().x;
            float scaleY = inventarSlots[i].getSize().y / sprite.getTexture()->getSize().y;
            sprite.setScale(scaleX, scaleY);

            sf::Vector2f slotPos = inventarSlots[i].getPosition();
            sf::Vector2f slotCenter = sf::Vector2f(
                slotPos.x + inventarSlots[i].getSize().x / 2.f,
                slotPos.y + inventarSlots[i].getSize().y / 2.f
            );

            sf::Vector2f spriteSize = sf::Vector2f(sprite.getTexture()->getSize());
            spriteSize.x *= sprite.getScale().x;
            spriteSize.y *= sprite.getScale().y;

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
sf::Vector2f Spieler::getPosition() 
{
    return shape.getPosition();
}

void Spieler::setPosition(float x, float y)
{
	shape.setPosition(x, y);
}

PlayerInventar* Spieler::getPlayerInventar()
{
    return inventar;
}

RectangleShape& Spieler::getInventarSlots(int slotIndex)
{
    return inventarSlots[slotIndex];
}

int Spieler::getLeben()
{
    return leben;
}

bool Spieler::lebenReduzieren()              
{
    if (leben > 0)
    {
        this->leben--;
        return true;
    }
    else
    {
        return false;
    }
    
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

void Spieler::setPoints(int ini_points)
{
	points = ini_points;
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

