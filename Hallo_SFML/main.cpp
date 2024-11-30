#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include <iostream>

#include "Grid.h"
#include "Spielfeld.h"
#include "Button.h"
#include "mySound.h"

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
    Button button(300, 200, 200, 50, "Klick mich!", font, sf::Color::Blue, sf::Color::White);

    // Setze die OnClick-Funktion
    button.setOnClick([](){ cout << "Button geklickt!" << endl; });


  






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
                testSound->getMeinSound().play();
            }


            // Verarbeite Button-Klick
            button.handleEvent(event, window);

        }

        window.clear();
 
        playField->drawSpielfeld(window);

        button.draw(window);

        window.display();
    }

    return 0;
}
