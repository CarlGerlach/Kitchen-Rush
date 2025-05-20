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
#include "Ausgabe.h"
#include "Table.h"

#include "Item.h"

#include "PauseManager.h"
#include "DeviceManager.h"
#include "GameMessage.h"
#include "TableManager.h"

#include "Bestellposition.h"
#include "Auftrag.h"
#include "AuftraegeManager.h"

#include "SpielstandManager.h"

using namespace std;
using namespace sf;

int main()
{
    
    //Fenster erstellen-
    RenderWindow window(VideoMode(1920, 1080), "Kitchen Rush");
    window.setFramerateLimit(60);


    //Alles was geladen wird
    
    Font font;
    if (!font.loadFromFile("Texturen & Musik/TDAText.ttf"))
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

	//Auftrag Objekt
    Texture auftragObjektTexture;
    if (!auftragObjektTexture.loadFromFile("Texturen & Musik/Auftrag Objekt.png")) {
        cerr << "Fehler beim Laden der AuftragObjekt-Textur!" << endl;
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

    Texture tasksTexture;
    if (!tasksTexture.loadFromFile("Texturen & Musik/tasks.png")) 
    {
        cerr << "Fehler beim Laden der HintergrundAuftrag!" << endl;
        return -1;
    }


  
    //Game MEssage die man überall aufrüfen kann
    GameMessage::init(font);
    //GameMessage::setText("Nicht genug Zutaten!")  //Um den Text zu setzen der ausgegeben werden soll


    // Spielfeldbegrenzung und Spieler
    FloatRect spielfeldGrenzen(273.f, 243.f, 1312.f, 582.f);
    Spieler spieler1(300.f, 300.f, 50.f, 5.0f, spielfeldGrenzen, &playerLeftTexture);

    //Sound
    mySound* soundManager = new mySound();

    


    // übergebe soundManager an StartScreen
    StartScreen startScreen(soundManager);

    if (!startScreen.run(window))
		return 0; // Starte das Spiel, wenn der Button gedrückt wird

    startScreen.playStartSound(); // -> Spiel beginnt, Sound abspielen


   


    // Spielfeld
    Spielfeld* playField = new Spielfeld();
    DeviceManager* deviceManager = new DeviceManager();

    AuftraegeManager* derAuftraegeManager = new AuftraegeManager(font, &tasksTexture, soundManager, nullptr, &spieler1);
    TableManager* derTableManager = new TableManager(derAuftraegeManager);
    derAuftraegeManager->setTableManager(derTableManager);

    


    Table table1(93, font, &spieler1, 20, derAuftraegeManager);
    table1.setTexture(&auftragObjektTexture);
    derTableManager->addTable(&table1);
    deviceManager->addInventory(table1.getDevInventar());

    Table table2(55, font, &spieler1, 20, derAuftraegeManager);
    table2.setTexture(&auftragObjektTexture);
    derTableManager->addTable(&table2);
	deviceManager->addInventory(table2.getDevInventar());

    Table table3(43, font, &spieler1, 20, derAuftraegeManager);
    table3.setTexture(&auftragObjektTexture);
    derTableManager->addTable(&table3);
	deviceManager->addInventory(table3.getDevInventar());

    Table table4(66, font, &spieler1, 20, derAuftraegeManager);
    table4.setTexture(&auftragObjektTexture);
    derTableManager->addTable(&table4);
	deviceManager->addInventory(table4.getDevInventar());

    Table table5(26, font, &spieler1, 20, derAuftraegeManager);
    table5.setTexture(&auftragObjektTexture);
    derTableManager->addTable(&table5);
	deviceManager->addInventory(table5.getDevInventar());

   
    // Ofen
    Ofen ofen1(32, font, &spieler1, 3);
    ofen1.setTexture(&ofenTexture);     
    deviceManager->addInventory(ofen1.getDevInventar());

	// Lager
    Storage storage1(12, font, &spieler1, 5);
    storage1.setTexture(&lagerTexture);
    deviceManager->addInventory(storage1.getDevInventar());

	// Mixer
    Mixer mixer1(22, font, &spieler1, 3);
    mixer1.setTexture(&mixerTexture);
    deviceManager->addInventory(mixer1.getDevInventar());

    //Ausgabe
    Ausgabe ausgabe1(56, font, &spieler1, 20, derAuftraegeManager);
    ausgabe1.setTexture(&auftragObjektTexture);
    deviceManager->addInventory(ausgabe1.getDevInventar());


   

    



   


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



    // PauseManager mit Musiksteuerung
    PauseManager pauseManager(window.getSize(), soundManager, &spieler1, deviceManager);

    Clock clock;
                                                                                                            
    SpielstandManager ssm(&spieler1);


    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {

                window.close();
            }


            // ESC soll jederzeit die Pause toggeln
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                if (pauseManager.getPauseStatus() == false)
                {
                     pauseManager.togglePause();  // eine Methode, die Pause-Status umschaltet

                }

                continue; // alle weiteren Events ignorieren in diesem Frame
            }

            if (pauseManager.isPaused()) 
            {
                pauseManager.handleInput(event, window);
            }
            else 
            {
                ofen1.handleEvent(event, window);
                storage1.handleEvent(event, window);
                mixer1.handleEvent(event, window);
                ausgabe1.handleEvent(event, window);
                derTableManager->handleEvent(event, window);
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

                spieler1.setTextureManual(&playerLeftTexture);
                spieler1.setLookingLeft(true);
                }
           
            }
            if (Keyboard::isKeyPressed(Keyboard::D)) 
            {
                direction.x += 1.f;
                if (!spieler1.isLookingRight()) {
                    spieler1.setTextureManual(&playerRightTexture);
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
            
            GameMessage::update(deltaTime);
            

            spieler1.draw(window);


            derTableManager->updateAllTables();
            derTableManager->drawAllBots(window);
            derTableManager->drawAllTables(window);
            

            ofen1.update();
            ofen1.draw(window);

            storage1.update();
            storage1.draw(window);

            mixer1.update();
            mixer1.draw(window);

            ausgabe1.update();
            ausgabe1.draw(window);

            derAuftraegeManager->draw(window, deltaTime, pauseManager); 

            

        }


        pauseManager.draw(window);
        GameMessage::draw(window);
        window.display();

    }


    derAuftraegeManager->clearAuftraege();
    return 0;
}
