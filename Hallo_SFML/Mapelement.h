#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include <iostream>
#include <functional>

#include "mySound.h"
#include "Fenster.h"
#include "Item.h"

using namespace std;
using namespace sf;

class Mapelement
{
private:
	sf::RectangleShape shape;
	std::function<void()> onClick;

	sf::Sprite sprite; // Sprite des Buttons
	sf::Texture* texture; // Zeiger auf eine externe Textur, um Speicherprobleme zu vermeiden

	Fenster* dasFenster;

public:
	Mapelement(int gridnumber, sf::Font ini_font);

	void setOnClick(std::function<void()> callback);
	void draw(sf::RenderWindow& window);
	void handleEvent(const sf::Event& event, const sf::RenderWindow& window);

	void setPosition(float x, float y);
	void setTexture(sf::Texture* newTexture);

	float getPositionX();
	float getPositionY();

	void setScale(float scale);

	Fenster* getFenster();

	void setFenster(Fenster* ini_dasFenster);

};
