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

#include "Storage.h"
#include "Mixer.h"


#include "PauseManager.h"

#include "Auftrag.h"
#include "AuftraegeManager.h"

using namespace std;
using namespace sf;

int main()
{
    
    //Fenster erstellen-
    RenderWindow window(VideoMode(1920, 1080), "Kitchen Rush");
    window.setFramerateLimit(60);


    //Alles was geladen wird
    
    Font font;
    if (!font.loadFromFile("Texturen & Musik/arial.ttf"))
        return -1;

    //Ofen
	Texture ofenTexture;
    if (!ofenTexture.loadFromFile("Texturen & Musik/Ofen.png")) {
        cerr << "Fehler beim Laden der Ofen-Textur!" << endl;
        return -1;
    }
    
    //Lager
    Texture lagerTexture;
    if (!lagerTexture.loadFromFile("Texturen & Musik/Lager.png")) {
        cerr << "Fehler beim Laden der Lager-Textur!" << endl;
        return -1;
    }

    //Mixer
    Texture mixerTexture;
    if (!mixerTexture.loadFromFile("Texturen & Musik/Mixer.png")) {
        cerr << "Fehler beim Laden der Mixer-Textur!" << endl;
        return -1;
    }

	//Placeholder
    Texture placeholder;
    if (!placeholder.loadFromFile("Texturen & Musik/temp.png")) {
        cerr << "Fehler beim Laden der Placeholder-Textur!" << endl;
        return -1;
    }

	//Texturen für den Spieler nach Links
    Texture playerLeftTexture;
    if (!playerLeftTexture.loadFromFile("Texturen & Musik/Char-links.png")) {
        cerr << "Fehler beim Laden der linken Textur!" << endl;
        return -1;
    }

	//Texturen für den Spieler nach Rechts
    Texture playerRightTexture;
    if (!playerRightTexture.loadFromFile("Texturen & Musik/Char-rechts.png")) {
        cerr << "Fehler beim Laden der rechten Textur!" << endl;
        return -1;
    }



    // Spielfeldbegrenzung und Spieler
    FloatRect spielfeldGrenzen(273.f, 243.f, 1312.f, 582.f);
    Spieler spieler1(300.f, 300.f, 50.f, 5.0f, spielfeldGrenzen, &playerLeftTexture);

    //Sound
    mySound* soundManager = new mySound();

    if (!soundManager->loadGameStartSound("Texturen & Musik/game start.ogg")) {
        std::cerr << "Fehler beim Laden von game start.ogg!" << std::endl;
    }

    if (!soundManager->loadGameOverSound("Texturen & Musik/game over.ogg")) {
        std::cerr << "Fehler beim Laden von game over.ogg!" << std::endl;
    }
    soundManager->setGameOverVolume(30.f); // z. B. 20 % Lautstärke




    if (soundManager->loadHintergrundMusik("Texturen & Musik/Hintergrund-Musik.ogg")) {
        soundManager->setMusicLautstaerke(10.f);
        soundManager->playHintergrundMusik();
    }
    else {
        cout << "Fehler beim Laden der Hintergrundmusik!" << endl;
    }


    // übergebe soundManager an StartScreen
    StartScreen startScreen(soundManager);

    if (!startScreen.run(window))
		return 0; // Starte das Spiel, wenn der Button gedrückt wird

    startScreen.playStartSound(); // -> Spiel beginnt, Sound abspielen


   


    // Spielfeld
    Spielfeld* playField = new Spielfeld();

    // Ofen
    Ofen ofen1(32, font, &spieler1);
    ofen1.setTexture(&ofenTexture);        

	// Lager
    Storage storage1(12, font, &spieler1);
    storage1.setTexture(&lagerTexture);

	// Mixer
    Mixer mixer1(22, font, &spieler1);
    mixer1.setTexture(&mixerTexture);


   
   


    // Hintergrund-Bild fürs Pausenmenü laden
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("Texturen & Musik/pausenMenue.png")) {
        cerr << "Fehler beim Laden des Pause-Hintergrunds!" << endl;
        return -1;
    }
    Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(
        (float)window.getSize().x / backgroundTexture.getSize().x,
        (float)window.getSize().y / backgroundTexture.getSize().y
    );

    
    AuftraegeManager auftraegeManager(&font);
    auftraegeManager.setText("Auftraege:\n");


    auftraegeManager.addAuftrag(new Auftrag("Hamburger", 2, 10));
    auftraegeManager.addAuftrag(new Auftrag("Nudeln", 2, 10));
    

    // PauseManager mit Musiksteuerung
    PauseManager pauseManager(window.getSize(), soundManager);

    Clock clock;


    


    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
				// Musik stoppen
                soundManager->stopHintergrundMusik();

                // Sound spielen
                soundManager->playGameOverSound();

                // Warte kurz, damit der Sound hörbar ist
                sf::sleep(sf::seconds(2.8)); // anpassen je nach Soundlänge

                window.close();
            }


            // ESC soll jederzeit die Pause toggeln
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                pauseManager.togglePause();  // eine Methode, die Pause-Status umschaltet

                continue; // alle weiteren Events ignorieren in diesem Frame
            }

            if (pauseManager.isPaused()) 
            {
                pauseManager.handleInput(event, window);
            }
            else 
            {
                cout << "Test 2 " << endl;
                ofen1.handleEvent(event, window);
                storage1.handleEvent(event, window);
                mixer1.handleEvent(event, window); 

                cout << "Test 3 " << endl;
            }
        }

        if (!pauseManager.isPaused()) {
            Vector2f direction(0.f, 0.f);

            if (Keyboard::isKeyPressed(Keyboard::W)) direction.y -= 1.f;
            if (Keyboard::isKeyPressed(Keyboard::S)) direction.y += 1.f;
            if (Keyboard::isKeyPressed(Keyboard::A))
            {
                direction.x -= 1.f;
                if(!spieler1.isLookingLeft())
                {

                spieler1.setTexture(&playerLeftTexture);
                spieler1.setLookingLeft(true);
                }
           
            }
            if (Keyboard::isKeyPressed(Keyboard::D)) 
            {
                direction.x += 1.f;
                if (!spieler1.isLookingRight()) {
                    spieler1.setTexture(&playerRightTexture);
                    spieler1.setLookingRight(true);
                }

            }

            spieler1.move(direction);

        }

        //Lowkey keine Ahnung wieso update, aber es hat das Fenster nicht schnell genug geschlossen, wenn man weggegangen ist deshalb update()

        window.clear();

        if (pauseManager.isPaused()) {
            window.draw(backgroundSprite);
        }
        else {
            playField->drawSpielfeld(window);
            
            spieler1.draw(window);

            ofen1.update();
            ofen1.draw(window);

            storage1.update();
            storage1.draw(window);

            mixer1.update();
            mixer1.draw(window);

            auftraegeManager.draw(window);
        }

        pauseManager.draw(window);
        window.display();

    }

    soundManager->stopHintergrundMusik();
    return 0;
}
