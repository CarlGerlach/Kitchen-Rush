#include "PauseManager.h"
#include "gamemessage.h"
#include <iostream>
#include <sstream>
#include "GameMessage.h"
#include "Spieler.h"
#include "SpielstandManager.h"
#include "DeviceManager.h"

PauseManager::PauseManager(const sf::Vector2u& windowSize, mySound* soundMgr, Spieler* spieler, DeviceManager* dm)
    : paused(false), soundManager(soundMgr)
{
    overlay.setSize(sf::Vector2f(windowSize));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));  // halbtransparent schwarz

    font.loadFromFile("Texturen & Musik/TDAText.ttf"); // Lade Schrift

	this->spieler = spieler; // Speichert die Referenz auf den Spieler zum Speichern
    this->devicemanager = dm; // Speichert die Referenz auf den DeviceManager


    buttonResume = new Button(860, 300, 200, 50, "Fortsetzen", font, sf::Color::Green, sf::Color::White, soundManager);
    buttonMusicStart = new Button(860, 370, 200, 50, "Musik Start", font, sf::Color::Blue, sf::Color::White, soundManager);
    buttonMusicStop = new Button(860, 440, 200, 50, "Musik Stop", font, sf::Color::Blue, sf::Color::White, soundManager);
    buttonVolumeUp = new Button(860, 510, 200, 50, "Lauter", font, sf::Color::Yellow, sf::Color::Black, soundManager);
    buttonVolumeDown = new Button(860, 580, 200, 50, "Leiser", font, sf::Color::Yellow, sf::Color::Black, soundManager);
    buttonExit = new Button(860, 650, 200, 50, "Beenden", font, sf::Color::Red, sf::Color::White, soundManager);

    buttonFXUp = new Button(860, 720, 200, 50, "Effekte +", font, sf::Color::Cyan, sf::Color::Black, soundManager);
    buttonFXDown = new Button(860, 790, 200, 50, "Effekte -", font, sf::Color::Cyan, sf::Color::Black, soundManager);

	buttonSaveGame = new Button(860, 860, 200, 50, "Spiel speichern", font, sf::Color::Magenta, sf::Color::White, soundManager);
	buttonLoadGame = new Button(860, 930, 200, 50, "Spiel laden", font, sf::Color::Magenta, sf::Color::White, soundManager);

}

void PauseManager::handleInput(const sf::Event& event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    {
        paused = !paused;
    }

    buttonResume->handleEvent(event, window);
    buttonMusicStart->handleEvent(event, window);
    buttonMusicStop->handleEvent(event, window);
    buttonVolumeUp->handleEvent(event, window);
    buttonVolumeDown->handleEvent(event, window);
    buttonExit->handleEvent(event, window);

    // Neue Soundeffekt-Lautstärke-Steuerung
    buttonFXUp->handleEvent(event, window);
    buttonFXDown->handleEvent(event, window);

	buttonSaveGame->handleEvent(event, window);
	buttonLoadGame->handleEvent(event, window);

    if (buttonResume->wasClicked())
    {
        if (!gameOver)
        {
            paused = false;
            if (soundManager)
            {
                soundManager->playGameStartSound();
            }
        }
        else
        {
            GameMessage::setText("Spielende - Auftrag abgelaufen");
        }
    }

    if (buttonFXUp->wasClicked())
    {
        soundManager->setEffektLautstaerke(1);
        float vol = soundManager->getEffektLautstaerke();
        //std::cout << "Effektlautstärke nach +: " << vol << "%" << std::endl; // Logging
        std::stringstream text;
        text << "Effektlautstärke: " << vol << "%";
        GameMessage::setText(text.str());
    }

    if (buttonFXDown->wasClicked())
    {
        soundManager->setEffektLautstaerke(0);
        float vol = soundManager->getEffektLautstaerke();
        //std::cout << "Effektlautstärke nach -: " << vol << "%" << std::endl; // Logging
        std::stringstream text;
        text << "Effektlautstärke: " << vol << "%";
        GameMessage::setText(text.str());
    }


    if (buttonExit->wasClicked()) {
        soundManager->stopHintergrundMusik(); // Musik stoppen
        soundManager->playGameOverSound();  // Game Over Sound abspielen
        sf::sleep(sf::seconds(2.8));         // Warte, damit der Sound hörbar ist
        window.close(); // Fenster schließen
    }

    if (buttonMusicStart->wasClicked())
    {
        if (!soundManager->isMusicPlaying())
            soundManager->playHintergrundMusik();
    }
    if (buttonMusicStop->wasClicked())
    {
        soundManager->stopHintergrundMusik();
    }
    if (buttonVolumeUp->wasClicked())
    {
        float vol = soundManager->getMusicLautstaerke();

        soundManager->setMusicLautstaerke(1);
        stringstream text;
        text << "Lautstärke: " << vol << "%";
        GameMessage::setText(text.str());
    }
    if (buttonVolumeDown->wasClicked())
    {
        float vol = soundManager->getMusicLautstaerke();

        soundManager->setMusicLautstaerke(0);

        stringstream text;
        text << "Lautstärke: " << vol << "%";
        GameMessage::setText(text.str());
    }
	if (buttonSaveGame->wasClicked())
    {
        SpielstandManager::saveGame(spieler, devicemanager); // Spielstand speichern

		// Hier den Spielstand speichern
		GameMessage::setText("Spielstand gespeichert!");
		//std::cout << "Spielstand gespeichert!" << std::endl;
	}
	if (buttonLoadGame->wasClicked())
    {
        try {
            SpielstandManager::loadGame(spieler, devicemanager); // Spielstand laden
            GameMessage::setText("Spielstand geladen!");
			std::cout << "Spielstand geladen!" << std::endl;
		}
        catch (const std::exception& e) {
			GameMessage::setText("Fehler beim Laden des Spielstands!");
			std::cerr << "Fehler: " << e.what() << std::endl;
		}
	}
}

void PauseManager::draw(sf::RenderWindow& window)
{
    if (paused)
    {
        window.draw(overlay);
        buttonResume->draw(window);
        buttonMusicStart->draw(window);
        buttonMusicStop->draw(window);
        buttonVolumeUp->draw(window);
        buttonVolumeDown->draw(window);
        buttonExit->draw(window);

        buttonFXUp->draw(window);
        buttonFXDown->draw(window);

		buttonSaveGame->draw(window);
		buttonLoadGame->draw(window);

        
        spieler->getPoints();

        Text text;
        text.setFont(font);
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::White);

        stringstream idStream;
        idStream << "Score " << spieler->getPoints();
        text.setString(idStream.str());



        Text text2;
        text2.setFont(font);
        text2.setCharacterSize(30);
        text2.setFillColor(sf::Color::White);

        stringstream id2Stream;
        id2Stream << "Highscore " << spieler->getHighscore();
        text2.setString(id2Stream.str());

        

        float fensterBreite = window.getSize().x;

        // Text in die Mitte (X) und auf Y=200 setzen
        text.setPosition(fensterBreite / 2.0f - 80.f, 200.f);
        text2.setPosition(fensterBreite / 2.0f - 110.f, 250.f);

        window.draw(text);
        window.draw(text2);
    }
}




bool PauseManager::isPaused()
{
    return paused;
}

void PauseManager::setGameOver(bool value)
{
    gameOver = value;
}

bool PauseManager::getGameOver()
{
    return gameOver;
}
bool PauseManager::getPauseStatus()
{
    return paused;
}
void PauseManager::togglePause() {
    if (gameOver == true)
    {
        GameMessage::setText("Spielende - Auftrag abgelaufen");
    }

    paused = !paused;  // Wechsel zwischen Pause und Fortsetzung
}
