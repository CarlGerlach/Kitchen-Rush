#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include <iostream>

#include "Grid.h"
#include "Spielfeld.h"
#include "Button.h"
#include "Fenster.h"
#include "mySound.h"
#include "Spieler.h"

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

    







    // Erstelle einen Button
    Button button(300, 25, 200, 50, "Koch Menue", font, sf::Color::Blue, sf::Color::White, soundManager);

    // Setze die OnClick-Funktion

    //button.setOnClick([]() { cout << "Button geklickt!" << endl; });


    //Fenster f(500, 400, 200, 50, "Hallo!", font, sf::Color::Black, sf::Color::White);


    //Fenster erstellen
    Fenster f("Koch Menue", font); // Erstellt das Fenster "Kochfenster"


    button.setOnClick([&f]() { f.setVisible(true); }); // öffnet das Fenster "Kochfenster"


    // Buttons innerhalb der List des Kochfensters hinzuf�gen
    // (x von f + offset, y von f + offset, width, height, Label, ... )
    f.addButton(710 + 200, 240 + 150, 100, 40, "Rezept 1", sf::Color::Cyan, sf::Color::Black, []() { cout << "Rezept 1 gewaehlt!" << endl; });

    f.addButton(710 + 200, 240 + 250, 100, 40, "Rezept 2", sf::Color::Magenta, sf::Color::Black, []() { cout << "Rezept 2 gewaehlt!" << endl; });



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



    /* ALTER CODE - ALTER CODE - ALTER CODE

	//Button für Herd konfigurieren

    Button kg(15); // Erstelle Küchengerät -> Syntax: kg(GridNum) -> Küchengerät kg wird bei Grid Nummer X erstellt.
    kg.setTexture(&kgTexture); // Weise die Herd-Textur zu
	kg.setText(" "); // Kein Text auf dem Button
    
	kg.setScale(1.0f);  // Skalierung des Buttons auf 90% setzen

    */




    Mapelement herd(15);

    herd.setTexture(&kgTexture);
    herd.setScale(1.0f);

	Fenster herd_fenster("Herd Fenster", font); // Erstellt das Fenster "Kochfenster"

    herd.setOnClick([&herd_fenster]() { herd_fenster.setVisible(true); }); // öffnet das Fenster "Kochfenster"

    // Buttons innerhalb der List des Kochfensters hinzuf�gen
    // (x von f + offset, y von f + offset, width, height, Label, ... )
    herd_fenster.addButton(710 + 200, 240 + 150, 100, 40, "Rezept 1", sf::Color::Cyan, sf::Color::Black, []() { cout << "Rezept 1 gewaehlt!" << endl; });

    herd_fenster.addButton(710 + 200, 240 + 250, 100, 40, "Rezept 2", sf::Color::Magenta, sf::Color::Black, []() { cout << "Rezept 2 gewaehlt!" << endl; });





    

    //Sprite für Herd
    sf::Texture placeholder;
    if (!placeholder.loadFromFile("Texturen & Musik/temp.png"))
    {
        cerr << "Fehler beim Laden der kg-Sprite-Textur!" << endl;
        return -1;
    }

	Item testitem("Test", placeholder);






    //Spielschleife
    while (window.isOpen()) 
    {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();


            // Handler f�r Fenster events wie "Close" und weitere Buttons in "Kochfenster"
            f.handleEvent(event, window);
			herd_fenster.handleEvent(event, window);

            // Verarbeite Button-Klick
            button.handleEvent(event, window);

			herd.handleEvent(event, window);



            // Verarbeite Button-Klick
            button.handleEvent(event, window);
            buttonMusikStopp.handleEvent(event, window);
            buttonMusikStart.handleEvent(event, window);


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


      
      
      
      
        // Draw Sachen

        window.clear();

        playField->drawSpielfeld(window);

        spieler1.draw(window);

        button.draw(window);

        herd.draw(window);

        if (f.isVisible()) {
            f.draw(window);
        }

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
