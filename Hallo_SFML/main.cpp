#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include <iostream>

#include "Grid.h"
#include "Spielfeld.h"
#include "Button.h"
#include "mySound.h"
#include "Spieler.h"

using namespace std;
using namespace sf;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Kitchen Rush");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    { // Stelle sicher, dass eine Schriftart geladen wird
        return -1;
    }



    //Erstellt SPielfeld
    ///////////////////Singleton
    Spielfeld* playField = new Spielfeld();

    //Sound
    mySound* soundManager = new mySound(); // Unbennant von "testSound" weil cooler oder so

    // Hintergrundmusik laden und abspielen
    if (soundManager->loadHintergrundMusik("Hintergrund-Musik.ogg"))
    {
        soundManager->setMusicLautstaerke(10.0f); // LautstÃ¤rke auf 10 % setzen, weil sonst zu laut -.-

        soundManager->playHintergrundMusik();
    }
    else
    {
        cout << "Fehler beim Laden der Hintergrundmusik!" << endl;
    }





    // Erstelle einen Button
    Button button(300, 200, 200, 50, "Klick mich!", font, sf::Color::Blue, sf::Color::White, soundManager);

    // Setze die OnClick-Funktion
    button.setOnClick([]() 
        { cout << "Button geklickt!" << endl; });




    // Erstelle Button Start Musik
    Button buttonMusikStart(300, 350, 200, 50, "Musik Start", font, sf::Color::Blue, sf::Color::White, soundManager);

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
    Button buttonMusikStopp(300, 275, 200, 50, "Musik Stop", font, sf::Color::Blue, sf::Color::White, soundManager);

    // Stoppe die Musik und gib diesen Text in Konsole aus
    buttonMusikStopp.setOnClick
    ([soundManager]
        {
            cout << "Musik wird gestoppt." << endl;
            soundManager->getMeinSound().play(); // Spiele den Button-Klick-Sound ab
            soundManager->stopHintergrundMusik(); // Stoppe die Musik
        }
    );

    

   

    // Spielfeldbegrenzung (x, y, Breite, HÃ¶he)
    sf::FloatRect spielfeldGrenzen(200.f, 170.f, 1460.f, 730.f);

    // Spielfeldbegrenzung (x, y, Breite, Höhe)
    sf::FloatRect spielfeldGrenzen(273.f, 243.f, 1312.f, 582.f);

    //erstellt Spieler
    Spieler spieler1(300.f, 300.f, 50.f, 0.4f, spielfeldGrenzen);







    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {   
            if (event.type == sf::Event::Closed)
                window.close();

            // Sound nur bei einem spezifischen Ereignis abspielen


            if (event.type == sf::Event::KeyPressed) // Beispiel: Tastendruck
            {
                soundManager->getMeinSound().play();
            }

          

           


            // Verarbeite Button-Klick
            button.handleEvent(event, window);
            buttonMusikStopp.handleEvent(event, window);
            buttonMusikStart.handleEvent(event, window);

        }



        // Spieler bewegen (mit WASD)
        sf::Vector2f direction(0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            direction.y -= 1.f; // Nach oben
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            direction.y += 1.f; // Nach unten
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            direction.x -= 1.f; // Nach links
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            direction.x += 1.f; // Nach rechts
        }

        spieler1.move(direction);



        window.clear();
 
        playField->drawSpielfeld(window);

        spieler1.draw(window);

        button.draw(window);

        buttonMusikStopp.draw(window);

        buttonMusikStart.draw(window);

        window.display();
    }

    // Hintergrundmusik stoppen, wenn das Programm beendet wird
    soundManager->stopHintergrundMusik();

    return 0;
}
