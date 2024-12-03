#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include <iostream>

#include "Grid.h"
#include "Spielfeld.h"
#include "Button.h"
#include "Fenster.h"

using namespace std;
using namespace sf;

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


    Fenster f("Koch Menü", font); // Erstellt das Fenster "Kochfenster"


    button.setOnClick([&f]() { f.setVisible(true); }); // Öffnet das Fenster "Kochfenster"


    // Buttons innerhalb der List des Kochfensters hinzufügen
    // (x von f + offset, y von f + offset, width, height, Label, ... )
    f.addButton(710 + 200, 240 + 150, 100, 40, "Rezept 1", sf::Color::Cyan, sf::Color::Black, []() { cout << "Rezept 1 gewaehlt!" << endl; });

    f.addButton(710 + 200, 240 + 250, 100, 40, "Rezept 2", sf::Color::Magenta, sf::Color::Black, []() { cout << "Rezept 2 gewaehlt!" << endl; });







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






    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Handler für Fenster events wie "Close" und weitere Buttons in "Kochfenster"
            f.handleEvent(event, window);

            // Verarbeite Button-Klick
            button.handleEvent(event, window);
        }

        window.clear();

        playField->drawSpielfeld(window);

        button.draw(window);



        if (f.isVisible()) {
            f.draw(window);
        }

        window.display();
    }

    return 0;
}
