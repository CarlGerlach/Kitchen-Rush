#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Item
{
private:
    std::string typ;
    sf::Sprite sprite;

public:
    Item();
    Item(const std::string& type, const sf::Texture& texture);

    std::string getTyp();
    sf::Sprite getSprite();
};