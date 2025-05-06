#pragma once
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;



enum class ItemID
{
    WASSER = 1,
    MEHL = 2,
    TEIG = 3,
    TOMATE = 4,
    PIZZA = 5,
    COLA = 6,
    SALAT = 7

};


class Item 
{
private: 
    ItemID id;
    string name;
    int points;
    sf::Sprite sprite;
    sf::Texture texture;

    void setupItem(); // Hilfsfunktion: Setzt Name, Textur, etc. anhand der ID

public:
    Item(ItemID id);

    void print();
    sf::Sprite& getSprite();
    ItemID getItemID();

   static string enumToString(ItemID ini_id);
};