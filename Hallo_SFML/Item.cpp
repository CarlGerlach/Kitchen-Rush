#include "Item.h"
#include <iostream>

Item::Item(ItemID id): id(id)
{
    setupItem(); // Direkt beim Erstellen alle Werte setzen
}

void Item::setupItem() {
    switch (id) {
    case ItemID::WASSER:
        name = "Wasser";
        texture.loadFromFile("Texturen & Musik/Wasser.png"); // Pfad zur Bilddatei
        break;
    case ItemID::MEHL:
        name = "Mehl";
        texture.loadFromFile("Texturen & Musik/Mehl.png");
        break;
    case ItemID::TEIG:
        name = "Teig";
        texture.loadFromFile("Texturen & Musik/Teig.png");
        break;
    case ItemID::TOMATE:
        name = "Tomate";
        texture.loadFromFile("Texturen & Musik/Tomate.png");
        break;
    case ItemID::PIZZA:
        name = "Pizza";
        texture.loadFromFile("Texturen & Musik/Pizza.png");
        break;
    default:
        name = "Unbekannt";
        break;
    }
    sprite.setTexture(texture); // Sprite bekommt die geladene Textur
}

void Item::print()
{
    cout << "Itemname: " << name << endl;
}

sf::Sprite& Item::getSprite()
{
    return sprite;
}

ItemID Item::getItemID()
{
    return id;
}
