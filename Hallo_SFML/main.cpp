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

using namespace std;
using namespace sf;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Kitchen Rush");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("Texturen & Musik/arial.ttf"))
        return -1;

    // Starte Startscreen
    StartScreen startScreen;
    if (!startScreen.run(window))
        return 0;

    sf::Texture* brickWall = new sf::Texture();
    sf::Texture* floor = new sf::Texture();
    brickWall->loadFromFile("Texturen & Musik/Wand.png");
    floor->loadFromFile("Texturen & Musik/Fliesen_Boden.png");

    Spielfeld* playField = new Spielfeld(brickWall, floor);
    mySound* soundManager = new mySound();

    sf::Texture placeholder;
    placeholder.loadFromFile("Texturen & Musik/temp.png");

    sf::Texture theke01;
    theke01.loadFromFile("Texturen & Musik/Theke_03.png");

    sf::Texture kgTexture;
    kgTexture.loadFromFile("Texturen & Musik/Herd_01.png");

    sf::Texture doorTexture;
    doorTexture.loadFromFile("Texturen & Musik/Tuer.png");

    sf::Texture windowUpTexture;
    windowUpTexture.loadFromFile("Texturen & Musik/Fenster_oben.png");

    sf::Texture windowDownTexture;
    windowDownTexture.loadFromFile("Texturen & Musik/Fenster_unten.png");

    sf::Texture windowLeftTexture;
    windowLeftTexture.loadFromFile("Texturen & Musik/Fenster_links.png");

    sf::Texture windowRightTexture;
    windowRightTexture.loadFromFile("Texturen & Musik/Fenster_rechts.png");

    int radius = 100;
    bool isPlayerInRadiusZuTheke = false;
    bool isPlayerInRadiusZuHerd = false;

    Item* fertigesItem1 = new Item("Anderer Test1", placeholder);
    Item* fertigesItem2 = new Item("Anderer Test2", placeholder);

    sf::FloatRect spielfeldGrenzen(273.f, 243.f, 1312.f, 582.f);
    Spieler spieler1(300.f, 300.f, 50.f, 5.0f, spielfeldGrenzen, "Texturen & Musik/Char-links.png");

    if (soundManager->loadHintergrundMusik("Texturen & Musik/Hintergrund-Musik.ogg"))
    {
        soundManager->setMusicLautstaerke(10.0f);
        soundManager->playHintergrundMusik();
    }

    Ofen ofen1(400, 400, font);
    ofen1.setTexture(&placeholder);
    ofen1.addItem(fertigesItem1);
    ofen1.addItem(fertigesItem2);

    Item* testItem = new Item("Test", placeholder);

    Mapelement theke(16);
    theke.setTexture(&theke01);

    Fenster theke_fenster("Theke Fenster", font);
    theke.setOnClick([&theke_fenster, &isPlayerInRadiusZuTheke]() {
        if (isPlayerInRadiusZuTheke)
            theke_fenster.setVisible(true);
        });

    theke_fenster.addButton(910, 390, 100, 40, "Gib Test Item!", sf::Color::Cyan, sf::Color::Black, [&spieler1, &testItem]() {
        spieler1.addItem(testItem, 1);
        });

    Mapelement herd(15);
    herd.setTexture(&kgTexture);
    herd.setScale(1.0f);

    Fenster herd_fenster("Herd Fenster", font);
    herd.setOnClick([&herd_fenster, &isPlayerInRadiusZuHerd]() {
        if (isPlayerInRadiusZuHerd)
            herd_fenster.setVisible(true);
        });

    herd_fenster.addButton(910, 390, 100, 40, "Rezept 1", sf::Color::Cyan, sf::Color::Black, []() {
        cout << "Rezept 1 gewaehlt!" << endl;
        });
    herd_fenster.addButton(910, 490, 100, 40, "Rezept 2", sf::Color::Magenta, sf::Color::Black, []() {
        cout << "Rezept 2 gewaehlt!" << endl;
        });

    Button buttonMusikStart(550, 25, 200, 50, "Musik Start", font, sf::Color::Blue, sf::Color::White, soundManager);
    buttonMusikStart.setOnClick([soundManager]() {
        cout << "Musik wird gestartet." << endl;
        soundManager->getMeinSound().play();
        if (!soundManager->isMusicPlaying())
            soundManager->playHintergrundMusik();
        });

    Button buttonMusikStopp(300, 25, 200, 50, "Musik Stop", font, sf::Color::Blue, sf::Color::White, soundManager);
    buttonMusikStopp.setOnClick([soundManager]() {
        cout << "Musik wird gestoppt." << endl;
        soundManager->getMeinSound().play();
        soundManager->stopHintergrundMusik();
        });

    // Fenster & Tür
    Mapelement tuer(1);
    tuer.setTexture(&doorTexture);
    tuer.setPosition(960.f, 820.f);

    Mapelement fensterOben1(2); fensterOben1.setTexture(&windowUpTexture); 
    fensterOben1.setPosition(450.f, 240.f);
   

    Mapelement fensterUnten1(6); fensterUnten1.setTexture(&windowDownTexture);
    fensterUnten1.setPosition(450.f, 820.f);
    

    Mapelement fensterLinks1(10); fensterLinks1.setTexture(&windowLeftTexture); 
    fensterLinks1.setPosition(270.f, 200.f);
   

    Mapelement fensterRechts1(13); fensterRechts1.setTexture(&windowRightTexture);
    fensterRechts1.setPosition(1585.f, 400.f);
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            buttonMusikStopp.handleEvent(event, window);
            buttonMusikStart.handleEvent(event, window);
            ofen1.handleEvent(event, window);
            theke.handleEvent(event, window);
            herd.handleEvent(event, window);
            theke_fenster.handleEvent(event, window);
            herd_fenster.handleEvent(event, window);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
                spieler1.addItem(fertigesItem1, 0);
        }

        float distanceZuTheke = sqrt(pow(spieler1.getPosition().x - theke.getPositionX(), 2) + pow(spieler1.getPosition().y - theke.getPositionY(), 2));
        isPlayerInRadiusZuTheke = distanceZuTheke <= radius;

        float distanceZuHerd = sqrt(pow(spieler1.getPosition().x - herd.getPositionX(), 2) + pow(spieler1.getPosition().y - herd.getPositionY(), 2));
        isPlayerInRadiusZuHerd = distanceZuHerd <= radius;

        sf::Vector2f direction(0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) direction.y -= 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) direction.y += 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { spieler1.setTexture("Texturen & Musik/Char-links.png"); direction.x -= 1.f; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { spieler1.setTexture("Texturen & Musik/Char-rechts.png"); direction.x += 1.f; }

        spieler1.move(direction);

        window.clear();
        playField->drawSpielfeld(window);
        spieler1.draw(window);
        ofen1.draw(window);
        theke.draw(window);
        herd.draw(window);
        tuer.draw(window);

        fensterOben1.draw(window);
        

        fensterUnten1.draw(window);
     

        fensterLinks1.draw(window);
       

        fensterRechts1.draw(window);
        

        if (theke_fenster.isVisible()) theke_fenster.draw(window);
        if (herd_fenster.isVisible()) herd_fenster.draw(window);

        buttonMusikStopp.draw(window);
        buttonMusikStart.draw(window);

        window.display();
    }

    soundManager->stopHintergrundMusik();
    return 0;
}
