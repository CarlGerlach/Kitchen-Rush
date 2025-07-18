#include "Item.h"
#include <iostream>
#include <random>

std::map<ItemID, sf::Texture> Item::textureCache; //(chatgpt)

Item::Item(ItemID id) : id(id)
{
    setupItem(); // Direkt beim Erstellen alle Werte setzen
}

void Item::setupItem()
{
    switch (id)
    {
    case ItemID::WASSER:
        name = "Wasser";
        break;
    case ItemID::MEHL:
        name = "Mehl";
        break;
    case ItemID::TEIG:
        name = "Teig";
        break;
    case ItemID::TOMATE:
        name = "Tomate";
        break;
    case ItemID::PIZZA:
        name = "Pizza";
        points = 5;
        break;
    case ItemID::COLA:
        name = "Cola";
        points = 2;
        break;
    case ItemID::SALAT:
        name = "Salat";
        points = 6;
        break;
    case ItemID::GURKE:
        name = "Gurke";
        points = 0;
        break;
    case ItemID::SALATKOPF:
        name = "Salatkopf";
        points = 0;
        break;
    case ItemID::UNBEKANNT:
        name = "LEER";
        break;
    default:
        name = "Unbekannt";
        return;
    }


    //(Chatgpt)
    // Textur nur beim ersten Mal laden
    if (textureCache.find(id) == textureCache.end()) {
        sf::Texture tex;
        std::string path = "Texturen & Musik/" + name + ".png";

        if (!tex.loadFromFile(path)) {
            std::cerr << "Fehler beim Laden der Textur: " << path << std::endl;
        }

        textureCache[id] = std::move(tex);
    }

    // Sprite mit gecachter Textur setzen
    sprite.setTexture(textureCache[id]);
}


void Item::print()
{
    ///cout << "Itemname: " << name << endl;
}

sf::Sprite& Item::getSprite()
{
    return sprite;
}

ItemID Item::getItemID()
{
    return id;
}

string Item::enumToString(ItemID ini_id)
{
    switch (ini_id)
    {
    case ItemID::WASSER: return "Wasser";
    case ItemID::MEHL: return "Mehl";
    case ItemID::TEIG: return "Teig";
    case ItemID::TOMATE: return "Tomate";
    case ItemID::PIZZA: return "Pizza";
    case ItemID::COLA: return "Cola";
    case ItemID::SALAT: return "Salat";
    case ItemID::GURKE: return "Gurke";
    case ItemID::SALATKOPF: return "Salatkopf";
    case ItemID::UNBEKANNT: return "LEER";

    default: return "Unbekannt";
    }
}

ItemID Item::randomItem()
{
    //Chatgpt
    // Direkt in der Methode
    static mt19937 rng(std::random_device{}());  // Initialisiert nur EINMAL
    std::uniform_int_distribution<int> dist(1, 4); // beliebig oft neu definierbar
    int randomZahl = dist(rng);  // schnell und effizient

    switch (randomZahl)
    {
    case 1:
        return ItemID::PIZZA;
    case 2:
        return ItemID::SALAT;
    case 3:
        return ItemID::WASSER;
    case 4:
        return ItemID::COLA;

    defalt:
        cout << "Fehler bei Random Item f�r Bestellposition" << endl;

    }
}

int Item::getPunkteForItem(ItemID searchedId)
{
    switch (searchedId)
    {
    case ItemID::WASSER: return 1;
        //case ItemID::MEHL:   return 2;
        //case ItemID::TEIG:   return 3;
        //case ItemID::TOMATE: return 2;
    case ItemID::PIZZA:  return 5;
    case ItemID::COLA:   return 2;
    case ItemID::SALAT:  return 7;
    default:             return 0;
    }
}
