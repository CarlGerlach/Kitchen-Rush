#include "PauseManager.h"
#include "gamemessage.h"
#include <iostream>
#include <sstream>

PauseManager::PauseManager(const sf::Vector2u& windowSize, mySound* soundMgr)
    : paused(false), soundManager(soundMgr)
{
    overlay.setSize(sf::Vector2f(windowSize));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));  // halbtransparent schwarz

    font.loadFromFile("Texturen & Musik/TDAText.ttf"); // Lade Schrift

    buttonResume = new Button(860, 300, 200, 50, "Fortsetzen", font, sf::Color::Green, sf::Color::White, soundManager);
    buttonMusicStart = new Button(860, 370, 200, 50, "Musik Start", font, sf::Color::Blue, sf::Color::White, soundManager);
    buttonMusicStop = new Button(860, 440, 200, 50, "Musik Stop", font, sf::Color::Blue, sf::Color::White, soundManager);
    buttonVolumeUp = new Button(860, 510, 200, 50, "Lauter", font, sf::Color::Yellow, sf::Color::Black, soundManager);
    buttonVolumeDown = new Button(860, 580, 200, 50, "Leiser", font, sf::Color::Yellow, sf::Color::Black, soundManager);
    buttonExit = new Button(860, 650, 200, 50, "Beenden", font, sf::Color::Red, sf::Color::White, soundManager);

    buttonFXUp = new Button(860, 720, 200, 50, "Effekte +", font, sf::Color::Cyan, sf::Color::Black, soundManager);
    buttonFXDown = new Button(860, 790, 200, 50, "Effekte -", font, sf::Color::Cyan, sf::Color::Black, soundManager);
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

    if (buttonResume->wasClicked())
    {
        paused = false;
        if (soundManager)
        {
            soundManager->playGameStartSound();
        }
    }

    if (buttonFXUp->wasClicked())
    {
        soundManager->setEffektLautstaerke(1);
        float vol = soundManager->getEffektLautstaerke();
        std::stringstream text;
        text << "Effektlautstärke: " << vol << "%";
        GameMessage::setText(text.str());
    }

    if (buttonFXDown->wasClicked())
    {
        soundManager->setEffektLautstaerke(0);
        float vol = soundManager->getEffektLautstaerke();
        std::stringstream text;
        text << "Effektlautstärke: " << vol << "%";
        GameMessage::setText(text.str());
    }

    if (buttonExit->wasClicked())
    {
        soundManager->stopHintergrundMusik();
        soundManager->playGameOverSound();
        window.close();
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
void PauseManager::togglePause() {
    paused = !paused;  // Wechsel zwischen Pause und Fortsetzung
}
