#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include <iostream>

#include "Grid.h"
#include "Spielfeld.h"
#include "Button.h"
#include "Fenster.h"

using namespace std;
using namespace sf;

bool fensterTest = false;

int test = 1;


int main()
{



    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Kitchen Rush");

    //Erstellt SPielfeld

    ///////////////////Singleton
    Spielfeld* playField = new Spielfeld();


    sf::Font font;

    if (!font.loadFromFile("arial.ttf")) { // Stelle sicher, dass eine Schriftart geladen wird
        return -1;
    }


    // Erstelle einen Button
    Button button(300, 200, 200, 50, "Klick mich!", font, sf::Color::Blue, sf::Color::White);

    // Setze die OnClick-Funktion
    //button.setOnClick([]() { cout << "Button geklickt!" << endl; });


    //Fenster f(500, 400, 200, 50, "Hallo!", font, sf::Color::Black, sf::Color::White);


    Fenster f("Koch Menü", font);


    button.setOnClick([]()
        { 
            //fensterTest = true;
            test++;
        });







    //Sounds
    // Sound-Puffer und Sound einmal erstellen
    //sf::SoundBuffer buffer;
    //if (!buffer.loadFromFile("Button-Click.wav")) // WAV-Datei statt MP3
    //{
    //    std::cout << "Fehler beim Laden der Sound-Datei!" << std::endl;
    //    return -1;
    //    //Falls leer
    //}

    //sf::Sound sound;
    //sound.setBuffer(buffer);






    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {   
            if (event.type == sf::Event::Closed)
                window.close();

            // Sound nur bei einem spezifischen Ereignis abspielen
            //if (event.type == sf::Event::KeyPressed) // Beispiel: Tastendruck
            //{
            //    sound.play();
            //}


            // Verarbeite Button-Klick
            button.handleEvent(event, window);

        }

        window.clear();
 
        playField->drawSpielfeld(window);

        button.draw(window);

        /*
        if (fensterTest == true)
        {
            f.draw(window);
        }
        */

        if (test % 2 == 0)
        {
            f.draw(window);
        }

        window.display();
    }

    return 0;
}
