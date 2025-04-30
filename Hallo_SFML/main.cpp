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

#include "Auftrag.h"
#include "AuftraegeManager.h"

using namespace std;
using namespace sf;

int main()
{
    //Fenster erstellen------------------------------------------------------------------------
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Kitchen Rush");
    window.setFramerateLimit(60);


    //Alles was geladen wird--------------------------------------------------------------------
    sf::Font font;
    if (!font.loadFromFile("Texturen & Musik/arial.ttf"))
        return -1;

    sf::Texture placeholder;
    placeholder.loadFromFile("Texturen & Musik/temp.png");

    sf::FloatRect spielfeldGrenzen(273.f, 243.f, 1312.f, 582.f);
    Spieler spieler1(300.f, 300.f, 50.f, 5.0f, spielfeldGrenzen, "Texturen & Musik/Char-links.png");

    mySound* soundManager = new mySound();  //Das und folgende Zeilen als eine Funktion
    if (soundManager->loadHintergrundMusik("Texturen & Musik/Hintergrund-Musik.ogg"))
    {
        soundManager->setMusicLautstaerke(10.0f);
        soundManager->playHintergrundMusik();
    }


    // Starte Startscreen
    StartScreen startScreen;
    if (!startScreen.run(window))
        return 0;
  



    //Erstellt SPielfeld
    Spielfeld* playField = new Spielfeld();

    
    
    Ofen ofen1(42, font, &spieler1);
    ofen1.setTexture(&placeholder);


 
  
    Button buttonMusikStart(550, 25, 200, 50, "Musik Start", font, sf::Color::Blue, sf::Color::White, soundManager);
    buttonMusikStart.setOnClick([soundManager]() {
        cout << "Musik wird gestartet." << endl;
        soundManager->getMeinSound().play();
        if (!soundManager->isMusicPlaying())
            soundManager->playHintergrundMusik();
        });


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

    ofen1.getDevInventar()->addItem(new Item(ItemID::TEIG));
    ofen1.getDevInventar()->addItem(new Item(ItemID::TOMATE));
    spieler1.getPlayerInventar()->addItem(new Item(ItemID::TEIG));

    


    
    

    //Aufträge liste
	//list<Auftrag*> auftraege;
    
	AuftraegeManager auftraegeManager(&font);
	auftraegeManager.setText("Auftraege:\n");


	auftraegeManager.addAuftrag(new Auftrag("Hamburger", 2, 10));
    auftraegeManager.addAuftrag(new Auftrag("Nudeln", 2, 10));





 

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
        }
      




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



       

        window.clear();
        playField->drawSpielfeld(window);
        spieler1.draw(window);
        ofen1.draw(window);

      

		auftraegeManager.draw(window);


       

        buttonMusikStopp.draw(window);
        buttonMusikStart.draw(window);

        window.display();
    }

    soundManager->stopHintergrundMusik();

    return 0;
}
