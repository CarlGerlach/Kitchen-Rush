#include "StartScreen.h"

StartScreen::StartScreen() {
    // Hintergrundbild laden 
    if (!backgroundTexture.loadFromFile("Texturen & Musik/background.png")) {
        std::cerr << "Fehler: Hintergrundbild konnte nicht geladen werden!\n";
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Skalierung
    float scaleX = static_cast<float>(1920) / backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(1080) / backgroundTexture.getSize().y;
    backgroundSprite.setScale(scaleX, scaleY);

    // Schriftart laden
    if (!font.loadFromFile("Texturen & Musik/arial.ttf")) {
        std::cerr << "Fehler: Schriftart konnte nicht geladen werden!\n";
    }

    // Titel
    title.setFont(font);
    title.setString("Kitchen Rush");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    title.setPosition(120.f, 10.f);

    // Start-Button
    startButton.setSize(sf::Vector2f(200.f, 50.f));
    startButton.setFillColor(sf::Color(0, 0, 0, 100));
    startButton.setPosition(285.f, 303.f);

    // Text auf dem Button
    buttonText.setFont(font);
    buttonText.setString("Start");
    buttonText.setCharacterSize(30);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(350.f, 310.f);
}

bool StartScreen::run(sf::RenderWindow& window) {
    bool started = false;
    while (window.isOpen() && !started) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (startButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    started = true;
                }
            }
        }

        window.clear();
        window.draw(backgroundSprite);  // Hintergrundbild zuerst zeichnen
        window.draw(title);
        window.draw(startButton);
        window.draw(buttonText);
        window.display();
    }
    return started;
}
