#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include <iostream>
#include <functional>

#include "mySound.h"

using namespace std;
using namespace sf;

class Mapelement
{
private:
	sf::RectangleShape shape;
	std::function<void()> onClick;

	sf::Sprite sprite; // Sprite des Buttons
	sf::Texture* texture; // Zeiger auf eine externe Textur, um Speicherprobleme zu vermeiden

public:
	Mapelement(int gridnumber);

	void setOnClick(std::function<void()> callback);
	void draw(sf::RenderWindow& window);
	void handleEvent(const sf::Event& event, const sf::RenderWindow& window);

	void setPosition(float x, float y);
	void setTexture(sf::Texture* newTexture);

	void setScale(float scale);
};
