#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Bot
{
private:
	sf::Vector2f position;
	sf::Vector2f zielPosition;
	float schrittweite;
	bool istAmZiel;
	RectangleShape sprite;
	Texture botTexture;
	

public:
	Bot(const sf::Vector2f& startPos, float schrittweite = 3.0f);

	void setZiel(const sf::Vector2f& ziel);
	void update();
	void draw(sf::RenderWindow& window);

	bool amZiel() const;
	sf::Vector2f getPosition() const;
};
