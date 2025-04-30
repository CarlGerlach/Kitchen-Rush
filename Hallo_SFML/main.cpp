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
#include "Auftrag.h"
#include "AuftraegeManager.h"

using namespace std;
using namespace sf;

int main()
{
    //Fenster erstellen-
    RenderWindow window(VideoMode(1920, 1080), "Kitchen Rush");
    window.setFramerateLimit(60);


    //Alles was geladen wird
    Font font;
    if (!font.loadFromFile("Texturen & Musik/arial.ttf"))
        return -1;

    Texture placeholder;
    if (!placeholder.loadFromFile("Texturen & Musik/Ofen.png")) {
        cerr << "Fehler beim Laden der Placeholder-Textur!" << endl;
        return -1;
    }

    // Spielfeldbegrenzung und Spieler
    FloatRect spielfeldGrenzen(273.f, 243.f, 1312.f, 582.f);
    Spieler spieler1(300.f, 300.f, 50.f, 5.0f, spielfeldGrenzen, "Texturen & Musik/Char-links.png");

    //Sound
    mySound* soundManager = new mySound();
    if (soundManager->loadHintergrundMusik("Texturen & Musik/Hintergrund-Musik.ogg")) {
        soundManager->setMusicLautstaerke(10.f);
        soundManager->playHintergrundMusik();
    }
    else {
        cout << "Fehler beim Laden der Hintergrundmusik!" << endl;
    }

    // Startscreen
    StartScreen startScreen;
    if (!startScreen.run(window))
        return 0;

    // Spielfeld
    Spielfeld* playField = new Spielfeld();

    // Ofen
    Ofen ofen1(42, font, &spieler1);
    ofen1.setTexture(&placeholder);
    ofen1.getDevInventar()->addItem(new Item(ItemID::TEIG));
    ofen1.getDevInventar()->addItem(new Item(ItemID::TOMATE));

    // Hintergrund-Bild fürs Pausenmenü laden
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("Texturen & Musik/pausenMenue.png")) {
        cerr << "Fehler beim Laden des Pause-Hintergrunds!" << endl;
        return -1;
    }
    Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(
        (float)window.getSize().x / backgroundTexture.getSize().x,
        (float)window.getSize().y / backgroundTexture.getSize().y
    );

    
    AuftraegeManager auftraegeManager(&font);
    auftraegeManager.setText("Auftraege:\n");


    auftraegeManager.addAuftrag(new Auftrag("Hamburger", 2, 10));
    auftraegeManager.addAuftrag(new Auftrag("Nudeln", 2, 10));
    

    // PauseManager mit Musiksteuerung
    PauseManager pauseManager(window.getSize(), soundManager);

    Clock clock;

    while (window.isOpen()) 
    {
        
        Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == Event::Closed)
                window.close();



            if (!pauseManager.isPaused()) {
                ofen1.handleEvent(event, window);
                // Weitere Ingame-Events hier
                
            }
            pauseManager.handleInput(event, window);

            if (!pauseManager.isPaused()) {
                Vector2f direction(0.f, 0.f);

                if (Keyboard::isKeyPressed(Keyboard::W)) direction.y -= 1.f;
                if (Keyboard::isKeyPressed(Keyboard::S)) direction.y += 1.f;
                if (Keyboard::isKeyPressed(Keyboard::A)) {
                    direction.x -= 1.f;
                    spieler1.setTexture("Texturen & Musik/Char-links.png");
                }
                if (Keyboard::isKeyPressed(Keyboard::D)) {
                    direction.x += 1.f;
                    spieler1.setTexture("Texturen & Musik/Char-rechts.png");
                }

                spieler1.move(direction);
            }

            window.clear();

            if (pauseManager.isPaused()) {
                window.draw(backgroundSprite);
            }
            else {
                playField->drawSpielfeld(window);
                spieler1.draw(window);
                ofen1.draw(window);
            }

            pauseManager.draw(window);
            window.display();
        }
    }

    soundManager->stopHintergrundMusik();
    return 0;
}
