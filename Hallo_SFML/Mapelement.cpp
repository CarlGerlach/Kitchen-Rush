//#include "Mapelement.h"
//#include "mySound.h"
//#include "Grid.h"
//#include "Spielfeld.h"
//#include "Item.h"
//
//Mapelement::Mapelement(int gridNumber)
//{
//	float width = 75;
//	float height = 75;
//	auto buttonColor = sf::Color::Blue;
//
//	sf::Vector2f gridPos = Grid::getPosition(gridNumber);
//
//	shape.setPosition(gridPos.x - 2, gridPos.y - 2);
//	shape.setSize({ width, height });
//	shape.setFillColor(buttonColor);
//}
//
//void Mapelement::setOnClick(std::function<void()> callback)
//{
//	onClick = callback;
//}
//
//void Mapelement::draw(sf::RenderWindow& window)
//{
//    if (texture) {
//        window.draw(sprite);
//    }
//    else {
//        window.draw(shape); // Fallback auf Standardform falls keine textur vorhanden
//    }
//    //window.draw(text);
//}
//
//void Mapelement::handleEvent(const sf::Event& event, const sf::RenderWindow& window)
//{
//    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
//    {
//        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
//        if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
//        {
//            if (onClick)
//            {
//                onClick();  // Rufe die OnClick-Funktion auf
//            }
//        }
//    }
//}
//
//void Mapelement::setPosition(float x, float y)
//{
//    shape.setPosition(x, y);
//    //text.setPosition(x + shape.getSize().x / 2.0f, y + shape.getSize().y / 2.0f);
//}
//
//void Mapelement::setTexture(sf::Texture* newTexture)
//{
//    texture = newTexture;
//    sprite.setTexture(*texture);
//    sprite.setPosition(shape.getPosition()); // Übernehme die Position des Buttons
//    sprite.setScale(
//        shape.getSize().x / texture->getSize().x,
//        shape.getSize().y / texture->getSize().y
//    ); // Skaliere die Textur auf die Größe des Buttons
//}
//
//float Mapelement::getPositionX()
//{
//    return sprite.getPosition().x;
//}
//
//float Mapelement::getPositionY()
//{
//    return sprite.getPosition().y;
//}
//
//void Mapelement::setScale(float scale)
//{
//    // Aktuelle Skalierung des Buttons abrufen
//    sf::Vector2f currentScale = sprite.getScale();
//
//    // Skalierung um den angegebenen Faktor erhöhen (1.5 bedeutet z.B. 50% größer)
//    sprite.setScale(currentScale.x * scale, currentScale.y * scale);
//}
//
//void Mapelement::setItem(Item newItem)
//{
//	item = newItem;
//}
