#pragma once
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

class Item
{
private:

	string typ;
	sf::Sprite sprite;

public:

	Item(const std::string& type, const sf::Texture& texture);

	string getTyp();

	sf::Sprite getSprite(); 
};

