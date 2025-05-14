#include "Button.h"
#include "mySound.h"
#include "Grid.h"
#include "Spielfeld.h"

Button::Button(float x, float y, float width, float height, const std::string& label, const sf::Font& font, const sf::Color& buttonColor, const sf::Color& textColor, mySound* ini_soundOfButton)
{
    // Setze die Form
    shape.setPosition(x, y);
    shape.setSize({ width, height });
    shape.setFillColor(buttonColor);

    // Setze den Text
    this->font = font;  // Font speichern
    text.setFont(this->font);
    text.setString(label);
    text.setCharacterSize(24);
    text.setFillColor(textColor);

    // Zentriere den Text im Button
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    text.setPosition(x + width / 2.0f, y + height / 2.0f);
    soundOfButton = ini_soundOfButton;

    clicked = false;
}


// Definition der Funktion wasClicked  
bool Button::wasClicked() {
    if (clicked) {
        clicked = false;
        return true;
    }
    return false;
}
    



/*
Button::Button(int gridNumber)
{
    float width = 75;
    float height = 75;
    auto buttonColor = sf::Color::Blue;
    string label = "TestKnopf";
    auto textColor = sf::Color::White;


    // HIER ANHAND VON GRIDNUMBER DIE POSITION EINES GRIDS ERMITTELN
    sf::Vector2f gridPos = Grid::getPosition(gridNumber);



    // Setze die Form
    shape.setPosition(gridPos.x - 2, gridPos.y - 2);
    shape.setSize({ width, height });
    shape.setFillColor(buttonColor);

    // Setze den Text
    this->font = font;  // Font speichern
    text.setFont(this->font);
    text.setString(label);
    text.setCharacterSize(24);
    text.setFillColor(textColor);

    // Zentriere den Text im Button
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    text.setPosition(gridPos.x + width / 2.0f, gridPos.y + height / 2.0f);

    soundOfButton = nullptr;
}
*/

// Setter für die OnClick-Funktion
void Button::setOnClick(std::function<void()> callback)
{
    onClick = callback;
   
}

// Zeichne den Button
void Button::draw(sf::RenderWindow& window)
{
    if (texture) {
        window.draw(sprite);
    }
    else {
		window.draw(shape); // Fallback auf Standardform falls keine textur vorhanden
    }
    window.draw(text);
}

// Überprüfe, ob der Button angeklickt wurde
void Button::handleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
        {
			clicked = true; // Setze den Klick-Status auf true
            // Hier wird der Button-Click Sound abgespielt
            if (soundOfButton == nullptr)
            {
                return;
            }

            soundOfButton->getMeinSound().play();
        }
    }
}


// Setter für die Position
void Button::setPosition(float x, float y)
{
    shape.setPosition(x, y);
    text.setPosition(x + shape.getSize().x / 2.0f, y + shape.getSize().y / 2.0f);
}


void Button::setTexture(sf::Texture* newTexture) {
    texture = newTexture;
    sprite.setTexture(*texture);
    sprite.setPosition(shape.getPosition()); // Übernehme die Position des Buttons
    sprite.setScale(
        shape.getSize().x / texture->getSize().x,
        shape.getSize().y / texture->getSize().y
    ); // Skaliere die Textur auf die Größe des Buttons
}


//Setter für den Text
string Button::setText(const string& newText) 
{
	text.setString(newText);
	return newText;
}