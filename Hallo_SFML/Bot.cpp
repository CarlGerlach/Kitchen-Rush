#include "Bot.h"
#include <cmath>

Bot::Bot(const sf::Vector2f& startPos, float schrittweite)
	: position(startPos), zielPosition(startPos), schrittweite(schrittweite), istAmZiel(true)
{;
	sprite.setSize(Vector2f(20.f, 20.f));
	//sprite.setFillColor(Color::Black);
	sprite.setPosition(Vector2f(940.f, 950.f));

	if (!botTexture.loadFromFile("Texturen & Musik/Char-links.png")) {
		cerr << "Fehler beim Laden der Textur!" << endl;
	}
	sprite.setTexture(&botTexture);
}

void Bot::setZiel(const sf::Vector2f& ziel)
{
	zielPosition = ziel;
	istAmZiel = false;
}

void Bot::update()
{
	if (istAmZiel) return;

	sf::Vector2f richtung = zielPosition - position;
	float dist = std::sqrt(richtung.x * richtung.x + richtung.y * richtung.y);

	if (dist < schrittweite) {
		position = zielPosition;
		istAmZiel = true;
		return;
	}

	sf::Vector2f normRichtung = richtung / dist;
	position += normRichtung * schrittweite;

	if (std::abs(position.x - zielPosition.x) < 0.5f &&
		std::abs(position.y - zielPosition.y) < 0.5f) {
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
