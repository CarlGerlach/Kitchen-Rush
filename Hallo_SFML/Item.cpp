#include "Item.h"
#include <iostream>
#include <random>

Item::Item(ItemID id): id(id)
{
    setupItem(); // Direkt beim Erstellen alle Werte setzen
}

void Item::setupItem() 
{
    switch (id) 
    {
    case ItemID::WASSER:
        name = "Wasser";
        //points = 1;
        texture.loadFromFile("Texturen & Musik/Wasser.png"); // Pfad zur Bilddatei
        break;
    case ItemID::MEHL:
        name = "Mehl";
        //points = 1;
        texture.loadFromFile("Texturen & Musik/Mehl.png");
        break;
    case ItemID::TEIG:
        name = "Teig";
        //points = 1;
        texture.loadFromFile("Texturen & Musik/Teig.png");
        break;
    case ItemID::TOMATE:
        name = "Tomate";
        //points = 1;
        texture.loadFromFile("Texturen & Musik/Tomate.png");
        break;
    case ItemID::PIZZA:
        name = "Pizza";
        points = 2;
        texture.loadFromFile("Texturen & Musik/Pizza.png");
        break;
    case ItemID::COLA:
        name = "Cola";
        points = 2;
        texture.loadFromFile("Texturen & Musik/Cola.png");
        break;
    case ItemID::SALAT:
        name = "Salat";
        points = 2;
        texture.loadFromFile("Texturen & Musik/Salat.png");
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
        cout << "Fehler bei Random Item für Bestellposition" << endl;

    }


}
