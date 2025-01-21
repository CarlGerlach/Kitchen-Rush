#include "Item.h"

Item::Item(const std::string& type, const sf::Texture& texture) : typ(type)
{
	sprite.setTexture(texture);
}

string Item::getTyp() 
{
    return typ;
}

sf::Sprite Item::getSprite()
{
    return sprite;
}
