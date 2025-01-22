#include "Fenster.h"
#include "Button.h"

Fenster::Fenster(const std::string& label, const sf::Font& font)
{
    this->visible = false;

    // Hintergrund des Fensters
    shape.setPosition(710, 240); // mittig im Fenster
    shape.setSize({ 500, 600 }); // Breite, Höhe
    shape.setFillColor(sf::Color(128, 128, 128)); // Grau

    // Text für das Fenster
    this->font = font;
    text.setFont(this->font);
    text.setString(label);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    text.setPosition(710 + 250, 240 + 50); // Zentriert im oberen Bereich

    // \"X\"-Button oben rechts erstellen
    closeButton = new Button(710 + 500 - 30, 240, 30, 30, "X", this->font, sf::Color::Black, sf::Color::White, nullptr);
    closeButton->setOnClick([this]() { this->setVisible(false); }); // Sichtbarkeit beim Klicken deaktivieren
}

Fenster::~Fenster()
{
    delete closeButton;
}

void Fenster::draw(sf::RenderWindow& window)
{
    if (!visible)
    {
        return;
    }

    window.draw(shape);
    window.draw(text);
    closeButton->draw(window);

    for (auto button : buttons)
    {
        button->draw(window);
    }
}

void Fenster::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
    if (!visible)
    {
        return;
    }

    for (auto button : buttons) {
        button->handleEvent(event, window);
    }

    closeButton->handleEvent(event, window);
}

void Fenster::setPosition(float x, float y)
{
    shape.setPosition(x, y);
    text.setPosition(x + shape.getSize().x / 2.0f, y + 50);
    closeButton->setPosition(x + shape.getSize().x - 40, y);
}

void Fenster::setText(std::string t)
{
    text.setString(t);
}

void Fenster::setVisible(bool isVisible)
{
    visible = isVisible; // Sichtbarkeit ändern
    cout << "Set visible geht" << endl;
}

bool Fenster::isVisible()
{
    return visible;
}

void Fenster::addButton(float x, float y, float width, float height, const std::string& label, const sf::Color& bgColor, const sf::Color& textColor, std::function<void()> onClick)
{
    Button* newButton = new Button(x, y, width, height, label, font, bgColor, textColor, nullptr);
    newButton->setOnClick(onClick);
    buttons.push_back(newButton);
}

