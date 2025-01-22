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
#include "Theke.h"

#include "Mapelement.h"

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
    
    sf::Texture* brickWall;
    sf::Texture* floor;

	int radius = 100; // Radius, in dem der Spieler sein muss, um mit dem Objekt zu interagieren
    bool isPlayerInRadius = false;

    
    brickWall = new sf::Texture();
    floor = new sf::Texture();

    brickWall->loadFromFile("Texturen & Musik/BrickWall.jpg");
    floor->loadFromFile("Texturen & Musik/Boden.jpg");
    





    //Erstellt SPielfeld
    ///////////////////Singleton
    Spielfeld* playField = new Spielfeld(brickWall, floor);



    //Sound
    mySound* soundManager = new mySound(); // Unbennant von "testSound" weil cooler oder so

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

    

   

    

    // Spielfeldbegrenzung (x, y, Breite, Höhe)
    sf::FloatRect spielfeldGrenzen(273.f, 243.f, 1312.f, 582.f);

    //erstellt Spieler

    Spieler spieler1(300.f, 300.f, 50.f, 5.0f, spielfeldGrenzen, "Texturen & Musik/Char-links.png");


    //Sprite für Herd
    sf::Texture kgTexture;
    if (!kgTexture.loadFromFile("Texturen & Musik/Herd_01.png")) 
    {
        cerr << "Fehler beim Laden der kg-Sprite-Textur!" << endl;
        return -1;
    }





    

    //Sprite für Herd
    sf::Texture placeholder;
    if (!placeholder.loadFromFile("Texturen & Musik/temp.png"))
    {
        cerr << "Fehler beim Laden der kg-Sprite-Textur!" << endl;
        return -1;
    }

	Item* testItem = new Item("Test", placeholder);


	
    Theke theke(35, font);
   // theke.setTexture(kgTexture);
    theke.setAuftrag("Pizza", 2, 100);
    theke.setInventar("Burger", placeholder);
    
    Mapelement herd(34, font);


   



    //Spielschleife
    while (window.isOpen()) 
    {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();



            // Verarbeite Button-Klick
            theke.handleEvent(event, window);


            // Handler für Fenster events wie "Close" und weitere Buttons
            theke.getFenster()->handleEvent(event, window);
   


            // Verarbeite Button-Klick
            buttonMusikStopp.handleEvent(event, window);
            buttonMusikStart.handleEvent(event, window);


        }



        //Distanz zwischen Spieler1 und Theke wird geprüft und in der Konsole in Form eines Bools ausgegeben        
        float distance = std::sqrt(std::pow(spieler1.getPosition().x - theke.getPositionX(), 2) + std::pow(spieler1.getPosition().y - theke.getPositionY(), 2));
        
        isPlayerInRadius = distance <= radius; // Spieler ist im Radius, wenn die Distanz kleiner/gleich dem Radius ist
        
		cout << isPlayerInRadius << endl; // Ausgabe, ob Spieler im Radius ist



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

        theke.draw(window);
        
        spieler1.draw(window);

        
        if (theke.getFenster()->isVisible())
        {
            theke.anzeigeTheke();
            theke.getFenster()->draw(window);
        }

    


        buttonMusikStopp.draw(window);

        buttonMusikStart.draw(window);

        window.display();
    }

    // Hintergrundmusik stoppen, wenn das Programm beendet wird
    soundManager->stopHintergrundMusik();

    return 0;
}
