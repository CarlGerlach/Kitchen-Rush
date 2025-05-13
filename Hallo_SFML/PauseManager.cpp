#include "PauseManager.h"  
#include "Button.h"  
#include <iostream>  

PauseManager::PauseManager(const sf::Vector2u& windowSize, mySound* soundMgr)  
   : paused(false), soundManager(soundMgr)  
{  
   overlay.setSize(sf::Vector2f(windowSize));  
   overlay.setFillColor(sf::Color(0, 0, 0, 150)); // halbtransparent schwarz  

   font.loadFromFile("Texturen & Musik/arial.ttf"); // Lade Schrift  

   buttonResume = new Button(860, 300, 200, 50, "Fortsetzen", font, sf::Color::Green, sf::Color::White, soundManager);  
   buttonMusicStart = new Button(860, 370, 200, 50, "Musik Start", font, sf::Color::Blue, sf::Color::White, soundManager);  
   buttonMusicStop = new Button(860, 440, 200, 50, "Musik Stop", font, sf::Color::Blue, sf::Color::White, soundManager);  
   buttonVolumeUp = new Button(860, 510, 200, 50, "Lauter", font, sf::Color::Yellow, sf::Color::Black, soundManager);  
   buttonVolumeDown = new Button(860, 580, 200, 50, "Leiser", font, sf::Color::Yellow, sf::Color::Black, soundManager);  
   buttonExit = new Button(860, 650, 200, 50, "Beenden", font, sf::Color::Red, sf::Color::White, soundManager);  
}  

void PauseManager::handleInput(const sf::Event& event, sf::RenderWindow& window)  
{  
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        // Nur pausieren/fortsetzen, wenn das Spiel nicht bereits in der Pause ist
        if (!paused) {
            paused = true;
        }
        else {
            paused = false;
        }
    }
	
    
       buttonResume->handleEvent(event, window);  
       buttonMusicStart->handleEvent(event, window);  
       buttonMusicStop->handleEvent(event, window);  
       buttonVolumeUp->handleEvent(event, window);  
       buttonVolumeDown->handleEvent(event, window);  
       buttonExit->handleEvent(event, window);  

       if (buttonResume->wasClicked())  
       {  
           paused = false;

           if (soundManager) {
               soundManager->playGameStartSound(); // -> Hier wird der Sound abgespielt
           }
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
           std::cout << "Lautstärke: " << vol << "%" << std::endl;  
       }  
       if (buttonVolumeDown->wasClicked())  
       {  
           float vol = soundManager->getMusicLautstaerke();  
            
           soundManager->setMusicLautstaerke(0);  
           std::cout << "Lautstärke: " << vol << "%" << std::endl;  
       }  
       if (buttonExit->wasClicked())  
       {   
           // Musik stoppen
           soundManager->stopHintergrundMusik();

           // Sound spielen
           soundManager->playGameOverSound();

           // Warte kurz, damit der Sound hörbar ist
           sf::sleep(sf::seconds(2.8)); // anpassen je nach Soundlänge


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
   }  
}  

bool PauseManager::isPaused()   
{  
   return paused;  
}
