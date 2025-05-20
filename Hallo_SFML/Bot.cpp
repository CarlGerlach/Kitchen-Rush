#include "Bot.h"
#include <cmath>

Bot::Bot(const sf::Vector2f& startPos, float schrittweite)
	: position(startPos), zielPosition(startPos), schrittweite(schrittweite), istAmZiel(true)
{;
	sprite.setSize(Vector2f(70.f, 70.f));
	//sprite.setFillColor(Color::Black);
	sprite.setPosition(Vector2f(940.f, 950.f));

	if (!botTexture.loadFromFile("Texturen & Musik/Kunde_oben.png")) {
		cerr << "Fehler beim Laden der Textur!" << endl;
	}
	sprite.setTexture(&botTexture);

	if (!botOben.loadFromFile("Texturen & Musik/Kunde_oben.png") ||
		!botUnten.loadFromFile("Texturen & Musik/Kunde_unten.png") ||
		!botLinks.loadFromFile("Texturen & Musik/Kunde_links.png") ||
		!botRechts.loadFromFile("Texturen & Musik/Kunde_rechts.png")) {
		std::cerr << "Fehler beim Laden einer oder mehrerer Texturen!" << std::endl;
	}
	else {
		sprite.setTexture(&botOben); // Standardrichtung
	}
}

void Bot::setZiel(const sf::Vector2f& ziel)
{
	zielPosition = ziel;
	istAmZiel = false;
}

void Bot::update()
{
    if (istAmZiel) return;

    float epsilon = 0.5f; // Toleranzwert zur Zielerkennung

    // Zuerst Bewegung entlang Y-Achse
    if (std::abs(position.y - zielPosition.y) > epsilon) {
        float dy = zielPosition.y - position.y;
        float richtungY = (dy > 0 ? 1.f : -1.f);
        float bewegung = std::min(schrittweite, std::abs(dy));
        position.y += richtungY * bewegung;

        // Textur setzen
        sprite.setTexture(dy > 0 ? &botUnten : &botOben);
    }
    // Danach Bewegung entlang X-Achse
    else if (std::abs(position.x - zielPosition.x) > epsilon) {
        float dx = zielPosition.x - position.x;
        float richtungX = (dx > 0 ? 1.f : -1.f);
        float bewegung = std::min(schrittweite, std::abs(dx));
        position.x += richtungX * bewegung;

        // Textur setzen
        sprite.setTexture(dx > 0 ? &botRechts : &botLinks);
    }

    // Ziel erreicht?
    if (std::abs(position.x - zielPosition.x) <= epsilon &&
        std::abs(position.y - zielPosition.y) <= epsilon) {
        position = zielPosition;
        istAmZiel = true;
    }
}

void Bot::draw(sf::RenderWindow& window)
{
	sprite.setPosition(position);
	window.draw(sprite);
}

bool Bot::amZiel() const
{
	return istAmZiel;
}

sf::Vector2f Bot::getPosition() const
{
	return position;
}

bool Bot::getIstAmZiel()
{
	return istAmZiel;
}


void Bot::aktualisiereTexturRichtung(const sf::Vector2f& delta) {
    if (std::abs(delta.y) > 0) {
        sprite.setTexture(delta.y > 0 ? &botUnten : &botOben);
    }
    else if (std::abs(delta.x) > 0) {
        sprite.setTexture(delta.x > 0 ? &botRechts : &botLinks);
    }
}
