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
    { // Stelle sicher, dass eine Schriftart geladen wird
        return -1;
    }

    //Sprite für Herd
    sf::Texture kgTexture;
    if (!kgTexture.loadFromFile("Texturen & Musik/Herd_01.png"))
    {
        cerr << "Fehler beim Laden der kg-Sprite-Textur!" << endl;
        return -1;
    }


    

    
    // Starte den Startscreen
    StartScreen startScreen;
    if (!startScreen.run(window))
        return 0; // Fenster wurde z.B. geschlossen




    sf::Texture* brickWall;
    sf::Texture* floor;

	int radius = 100; // Radius, in dem der Spieler sein muss, um mit dem Objekt zu interagieren
    bool isPlayerInRadiusZuTheke = false;
    bool isPlayerInRadiusZuHerd = false;

    
    brickWall = new sf::Texture();
    floor = new sf::Texture();

    brickWall->loadFromFile("Texturen & Musik/BrickWall.jpg");
    floor->loadFromFile("Texturen & Musik/Boden.jpg");

    // Grafische Elemente für das Inventar
    sf::RectangleShape inventarSlots[5]; // 5 Slots für das Inventar
         
    //Erstellt SPielfeld
    Spielfeld* playField = new Spielfeld(brickWall, floor);

    //Sound
    mySound* soundManager = new mySound(); // Unbennant von "testSound" weil cooler oder so


    sf::Texture placeholder;
    if (!placeholder.loadFromFile("Texturen & Musik/temp.png"))
    {
        cerr << "Fehler beim Laden der kg-Sprite-Textur!" << endl;
        return -1;
    }

    sf::Texture theke01;
    if (!theke01.loadFromFile("Texturen & Musik/Theke_03.png"))
    {
        cerr << "Fehler beim Laden der kg-Sprite-Textur!" << endl;
        return -1;
    }








    Item* fertigesItem1 = new Item("Anderer Test1", placeholder);
    Item* fertigesItem2 = new Item("Anderer Test2", placeholder);








    // Spielfeldbegrenzung (x, y, Breite, Höhe)
    sf::FloatRect spielfeldGrenzen(273.f, 243.f, 1312.f, 582.f);

    //erstellt Spieler
    Spieler spieler1(300.f, 300.f, 50.f, 5.0f, spielfeldGrenzen, "Texturen & Musik/Char-links.png");

    // Hintergrundmusik laden und abspielen
    if (soundManager->loadHintergrundMusik("Texturen & Musik/Hintergrund-Musik.ogg"))
    {
        soundManager->setMusicLautstaerke(10.0f); // Lautstärke auf 10 % setzen, weil sonst zu laut -.-

        soundManager->playHintergrundMusik();
    }
    else
    {
        cout << "Fehler beim Laden der Hintergrundmusik!" << endl;
    }

    


    
    Ofen ofen1(42, font, spieler1);
    ofen1.setTexture(&placeholder);
    ofen1.addItem(fertigesItem1);
    ofen1.addItem(fertigesItem2);
  
    cout << "Das ist ein Test" << endl;


    Item* testItem = new Item("Test", placeholder);

    Mapelement theke(16);
    theke.setTexture(&theke01);

    Fenster theke_fenster("Theke Fenster", font); // Erstellt das Fenster "Theken Fenster"
    theke.setOnClick([&theke_fenster, &isPlayerInRadiusZuTheke]() // Öffnet das Fenster nur, wenn der Spieler im Radius ist
        {
            if (isPlayerInRadiusZuTheke == true)
            {
                theke_fenster.setVisible(true); // öffnet das Fenster "Theken Fenster"
            }
        });

    theke_fenster.addButton(710 + 200, 240 + 150, 100, 40, "Gib Test Item!", sf::Color::Cyan, sf::Color::Black, [&spieler1, &testItem]() { spieler1.addItem(testItem, 1); });
    // Set Origin der Buttons anpassen


    Mapelement herd(15);

    herd.setTexture(&kgTexture);
    herd.setScale(1.0f);

    Fenster herd_fenster("Herd Fenster", font); // Erstellt das Fenster "Kochfenster"

    //herd.setOnClick([&herd_fenster]() { herd_fenster.setVisible(true); }); // öffnet das Fenster "Kochfenster"

    herd.setOnClick([&herd_fenster, &isPlayerInRadiusZuHerd]() // Öffnet das Fenster nur, wenn der Spieler im Radius ist
        {
            if (isPlayerInRadiusZuHerd == true)
            {
                herd_fenster.setVisible(true); // öffnet das Fenster "Theken Fenster"
            }
        });


    // Buttons innerhalb der List des Kochfensters hinzuf�gen
    // (x von f + offset, y von f + offset, width, height, Label, ... )
    herd_fenster.addButton(710 + 200, 240 + 150, 100, 40, "Rezept 1", sf::Color::Cyan, sf::Color::Black, []() { cout << "Rezept 1 gewaehlt!" << endl; });

    herd_fenster.addButton(710 + 200, 240 + 250, 100, 40, "Rezept 2", sf::Color::Magenta, sf::Color::Black, []() { cout << "Rezept 2 gewaehlt!" << endl; });





    


    // Erstelle Button Start Musik
    Button buttonMusikStart(550, 25, 200, 50, "Musik Start", font, sf::Color::Blue, sf::Color::White, soundManager);

  
  
    // Starte die Musik und gib diesen Text in Konsole aus
    buttonMusikStart.setOnClick
    ([soundManager]
        {
            cout << "Musik wird gestartet." << endl;
            soundManager->getMeinSound().play(); // Spiele den Button-Klick-Sound ab


            // nur wenn Musik nicht schon spielt
            if (soundManager->isMusicPlaying()) // ÃberprÃ¼fen, ob Musik spielt
            {
                cout << "Die Musik spielt bereits." << endl;
            }
            else
            {
                soundManager->playHintergrundMusik(); // Starte die Musik
            }
        }
    );


    // Erstelle Button Stop Musik
    Button buttonMusikStopp(300, 100, 200, 50, "Musik Stop", font, sf::Color::Blue, sf::Color::White, soundManager);

    // Stoppe die Musik und gib diesen Text in Konsole aus
    buttonMusikStopp.setOnClick
    ([soundManager]
        {
            cout << "Musik wird gestoppt." << endl;
            soundManager->getMeinSound().play(); // Spiele den Button-Klick-Sound ab
            soundManager->stopHintergrundMusik(); // Stoppe die Musik
        }
    );










 

    //Spielschleife
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

            // Handler für Fenster events wie "Close" und weitere Buttons
            theke_fenster.handleEvent(event, window);
            herd_fenster.handleEvent(event, window);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
            {
                spieler1.addItem(fertigesItem1, 0);
            }

        }



       //Konsolen check für collision mit gerät
       //Distanz zwischen Spieler1 und Theke wird geprüft und in der Konsole in Form eines Bools ausgegeben        
       float distanceZuTheke = std::sqrt(std::pow(spieler1.getPosition().x - theke.getPositionX(), 2) + std::pow(spieler1.getPosition().y - theke.getPositionY(), 2));
       isPlayerInRadiusZuTheke = distanceZuTheke <= radius; // Spieler ist im Radius, wenn die Distanz kleiner/gleich dem Radius ist 
	   //cout << isPlayerInRadiusZuTheke << endl; // Ausgabe, ob Spieler im Radius ist




       //Konsolen check für collision mit gerät
       //Distanz zwischen Spieler1 und Theke wird geprüft und in der Konsole in Form eines Bools ausgegeben        
       float distanceZuHerd = std::sqrt(std::pow(spieler1.getPosition().x - theke.getPositionX(), 2) + std::pow(spieler1.getPosition().y - herd.getPositionY(), 2));
       isPlayerInRadiusZuHerd = distanceZuHerd <= radius; // Spieler ist im Radius, wenn die Distanz kleiner/gleich dem Radius ist 
       //cout << isPlayerInRadiusZuHerd << endl; // Ausgabe, ob Spieler im Radius ist




        // Spieler bewegen (mit WASD)
        sf::Vector2f direction(0.f, 0.f);
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
        {
            direction.y -= 1.f; // Nach oben
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) 
        {
            direction.y += 1.f; // Nach unten
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
        {                                                                                        
            spieler1.setTexture("Texturen & Musik/Char-links.png");
            
        
            direction.x -= 1.f; // Nach links
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
        {
            spieler1.setTexture("Texturen & Musik/Char-rechts.png");
        
            direction.x += 1.f; // Nach rechts
        }
        
        spieler1.move(direction);


      
      
      
      
        // Draw Sachen

        window.clear();

        playField->drawSpielfeld(window);

        spieler1.draw(window);

        ofen1.draw(window);

        theke.draw(window);

        if (theke_fenster.isVisible()) {
            theke_fenster.draw(window);
        }

		herd.draw(window);
        
        if (herd_fenster.isVisible()) {
            herd_fenster.draw(window);
        }




        buttonMusikStopp.draw(window);

        buttonMusikStart.draw(window);

        window.display();
    }

    // Hintergrundmusik stoppen, wenn das Programm beendet wird
    soundManager->stopHintergrundMusik();

    return 0;
}
