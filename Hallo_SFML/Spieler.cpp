#include <sstream>
#include "Spieler.h"


void Spieler::punkteReduzieren(int punkte)
{
  
}

// Konstruktor
Spieler::Spieler(float startX, float startY, float size, float speed, sf::FloatRect bounds, sf::Texture* newTexture)
{
    if (!font.loadFromFile("Texturen & Musik/TDAText.ttf")) {
        std::cerr << "Fehler beim Laden der Schriftart!" << std::endl;
    }

    if (!herzTexture.loadFromFile("Texturen & Musik/Herz.png")) {
        std::cerr << "Fehler beim Laden der Herz-Textur!" << std::endl;
        //cout << "Texturen Test" << endl;
    }

    float herzSize = 60.f;

    
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
    for (int i = 0; i < 5; i++)
    {
        herzen[i].setTexture(&herzTexture);
        herzen[i].setSize(Vector2f(herzSize, herzSize));
        herzen[i].setPosition(80.f + i * (herzSize + spacing), 55.f);
    }


}


// Methode zum �ndern der Textur
void Spieler::setTextureManual(sf::Texture* newTexture)
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
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);
    text.setPosition(viewCenter.x + viewSize.x / 2.f - 120.f, 55.f); // z.B. oben rechts in View
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

            // Debug-Hitbox zeichnen
            //sf::FloatRect b = this->getBounds();
            //
            //sf::RectangleShape debugBox;
            //debugBox.setPosition(b.left, b.top);
            //debugBox.setSize({ b.width, b.height });
            //debugBox.setFillColor(sf::Color::Transparent);
            //debugBox.setOutlineColor(sf::Color::Blue);
            //debugBox.setOutlineThickness(1.f);
            //
            //window.draw(debugBox);  // ? Zeichne die kleine Kollision-Hitbox
        }
    }

    for (int i = 0; i < leben; i++)
    {

        window.draw(herzen[i]);
    }

}


// Funktion zur Bewegung
void Spieler::move(sf::Vector2f movement) {
    sf::Vector2f newPosition = shape.getPosition() + movement;

    if (newPosition.x < bounds.left) newPosition.x = bounds.left;
    if (newPosition.y < bounds.top) newPosition.y = bounds.top;
    if (newPosition.x + shape.getSize().x > bounds.left + bounds.width)
        newPosition.x = bounds.left + bounds.width - shape.getSize().x;
    if (newPosition.y + shape.getSize().y > bounds.top + bounds.height)
        newPosition.y = bounds.top + bounds.height - shape.getSize().y;

    shape.setPosition(newPosition);
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

RectangleShape& Spieler::getShape()
{
    return shape;
}

FloatRect Spieler::getBounds()
{
    //return shape.getGlobalBounds();

    
    sf::FloatRect raw = shape.getGlobalBounds();
    float shrink = 4.f; // Hitbox an jeder Seite 4 Pixel kleiner
    return sf::FloatRect(
        raw.left + shrink,
        raw.top + shrink,
        raw.width - 2 * shrink,
        raw.height - 2 * shrink
    );
}

int Spieler::getLeben()
{
    return leben;
}

bool Spieler::lebenReduzieren()              
{
    if (leben - 1 > 0)
    {
        this->leben--;
        return true;
    }
    else
    {
        return false;
    }
    
}

void Spieler::setLeben(int z)
{
	this->leben = z;
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

void Spieler::setHighscore(int hs)
{
    this->highscore = hs;
}

int Spieler::getHighscore()
{
    return this->highscore;
}

