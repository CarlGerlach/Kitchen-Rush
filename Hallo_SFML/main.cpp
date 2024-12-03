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
    if (!font.loadFromFile("arial.ttf")) { // Stelle sicher, dass eine Schriftart geladen wird
        return -1;
    }



    //Erstellt SPielfeld
    ///////////////////Singleton
    Spielfeld* playField = new Spielfeld();

    //Sound
    mySound* testSound = new mySound();






    // Erstelle einen Button
    Button button(300, 200, 200, 50, "Klick mich!", font, sf::Color::Blue, sf::Color::White, testSound);

    // Setze die OnClick-Funktion
    button.setOnClick([](){ cout << "Button geklickt!" << endl; });


    // Spielfeldbegrenzung (x, y, Breite, Höhe)
    sf::FloatRect spielfeldGrenzen(200.f, 170.f, 1460.f, 730.f);
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
          


            // Verarbeite Button-Klick
            button.handleEvent(event, window);

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

        window.display();
    }

    return 0;
}
