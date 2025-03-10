#include "Item.h"

// Standardkonstruktor
Item::Item() : typ("") {}

// Konstruktor mit Typ und Textur
Item::Item(const std::string& type, const sf::Texture& texture) : typ(type) {
    sprite.setTexture(texture);
}

// Item-Typ abrufen
std::string Item::getTyp() {
    return typ;
}

// Sprite abrufen
sf::Sprite Item::getSprite() {
    return sprite;
}