#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include <iostream>
#include <list>
#include <cmath>

#include "Grid.h"
#include "Spielfeld.h"
#include "Button.h"
#include "Fenster.h"
#include "mySound.h"
#include "Spieler.h"
#include "StartScreen.h"
#include "Mapelement.h"
#include "GeraetBase.h"
#include "Ofen.h"
#include "PauseManager.h"

using namespace std;
using namespace sf;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Kitchen Rush");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("Texturen & Musik/arial.ttf"))
    {
        return -1;
    }

    // Hintergrund-Bild laden
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("Texturen & Musik/pausenMenue.png"))
    {
        cerr << "Fehler beim Laden des Pause-Hintergrunds!" << endl;
        return -1;
    }
    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(
        (float)window.getSize().x / backgroundTexture.getSize().x,
        (float)window.getSize().y / backgroundTexture.getSize().y
    );

    // Starte StartScreen
    StartScreen startScreen;
    if (!startScreen.run(window))
        return 0;

    // Texturen laden
    sf::Texture* brickWall = new sf::Texture();
    sf::Texture* floor = new sf::Texture();

    brickWall->loadFromFile("Texturen & Musik/BrickWall.jpg");
    floor->loadFromFile("Texturen & Musik/Boden.jpg");

    // Spielfeld erstellen
    Spielfeld* playField = new Spielfeld(brickWall, floor);

    // Soundsystem
    mySound* soundManager = new mySound();

    sf::Texture placeholder;
    if (!placeholder.loadFromFile("Texturen & Musik/temp.png"))
    {
        cerr << "Fehler beim Laden der Placeholder-Textur!" << endl;
        return -1;
    }

    // Spielfeldgrenzen
    sf::FloatRect spielfeldGrenzen(273.f, 243.f, 1312.f, 582.f);

    // Spieler erstellen
    Spieler spieler1(300.f, 300.f, 50.f, 5.0f, spielfeldGrenzen, "Texturen & Musik/Char-links.png");

    // Hintergrundmusik
    if (soundManager->loadHintergrundMusik("Texturen & Musik/Hintergrund-Musik.ogg"))
    {
        soundManager->setMusicLautstaerke(10.0f);
        soundManager->playHintergrundMusik();
    }
    else
    {
        cout << "Fehler beim Laden der Hintergrundmusik!" << endl;
    }

    // Ofen erstellen
    Ofen ofen1(42, font, spieler1);
    ofen1.setTexture(&placeholder);
    ofen1.getDevInventar()->addItem(new Item(ItemID::TEIG));
    ofen1.getDevInventar()->addItem(new Item(ItemID::TOMATE));

    // Buttons Musik Start/Stop
    Button buttonMusikStart(550, 25, 200, 50, "Musik Start", font, Color::Blue, Color::White, soundManager);
    buttonMusikStart.setOnClick([soundManager] {
        cout << "Musik wird gestartet." << endl;
        soundManager->getMeinSound().play();
        if (!soundManager->isMusicPlaying()) {
            soundManager->playHintergrundMusik();
        }
        else {
            cout << "Musik läuft bereits." << endl;
        }
        });

    Button buttonMusikStopp(300, 100, 200, 50, "Musik Stop", font, Color::Blue, Color::White, soundManager);
    buttonMusikStopp.setOnClick([soundManager] {
        cout << "Musik wird gestoppt." << endl;
        soundManager->getMeinSound().play();
        soundManager->stopHintergrundMusik();
        });

    // PauseManager initialisieren
    PauseManager pauseManager(window.getSize(), font);

    sf::Clock clock;

    // Spielschleife
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            pauseManager.handleInput(event); // ESC abfangen

            if (!pauseManager.isPaused())
            {
                // NUR wenn NICHT pausiert: normale Events behandeln!
                buttonMusikStopp.handleEvent(event, window);
                buttonMusikStart.handleEvent(event, window);

                ofen1.handleEvent(event, window);

                // Andere Event-Dinge kommen hier hin (z.B. Maus, Tastatur usw.)
            }
        }

        if (!pauseManager.isPaused())
        {
            // Musik sicherstellen
            if (!soundManager->isMusicPlaying())
            {
                soundManager->playHintergrundMusik();
            }

            // Spielerbewegung
            sf::Vector2f direction(0.f, 0.f);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) direction.y -= 1.f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) direction.y += 1.f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                direction.x -= 1.f;
                spieler1.setTexture("Texturen & Musik/Char-links.png");
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                direction.x += 1.f;
                spieler1.setTexture("Texturen & Musik/Char-rechts.png");
            }

            spieler1.move(direction);
        }
        else
        {
            // Musik anhalten oder leise machen
            if (soundManager->isMusicPlaying())
            {
                soundManager->stopHintergrundMusik();
            }
        }

        // Zeichnen
        window.clear();

        if (pauseManager.isPaused())
        {
            window.draw(backgroundSprite);
            pauseManager.draw(window);
        }
        else
        {
            playField->drawSpielfeld(window);
            spieler1.draw(window);
            ofen1.draw(window);
            buttonMusikStart.draw(window);
            buttonMusikStopp.draw(window);
        }

        window.display();
    }

    // Musik stoppen beim Beenden
    soundManager->stopHintergrundMusik();

    return 0;
}