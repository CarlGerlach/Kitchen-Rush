#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include <iostream>
using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    // Sound-Puffer und Sound einmal erstellen
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("Button-Click.wav")) // WAV-Datei statt MP3
    {
        std::cout << "Fehler beim Laden der Sound-Datei!" << std::endl;
        return -1;
        //Falls leer
    }

    sf::Sound sound;
    sound.setBuffer(buffer);

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
                sound.play();
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
