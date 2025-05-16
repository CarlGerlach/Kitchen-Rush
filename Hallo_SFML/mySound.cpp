#include "mySound.h"
#include"PauseManager.h"
using namespace std;
using namespace sf;

mySound::mySound()
{
    if (!buffer.loadFromFile("Texturen & Musik/Button-Click.wav"))
    {
        std::cout << "Fehler beim Laden der Sound-Datei!" << std::endl;
    }

    if (!this->loadGameStartSound("Texturen & Musik/game start.ogg"))
    {
        std::cerr << "Fehler beim Laden von game start.ogg!" << std::endl;
    }

    if (!this->loadGameOverSound("Texturen & Musik/game over.ogg"))
    {
        std::cerr << "Fehler beim Laden von game over.ogg!" << std::endl;
    }

    this->setGameOverVolume(30.f); // 30% Lautstärke

    if (!this->loadAuftragAbgeschlossenSound("Texturen & Musik/auftrag abgeschlossen.ogg"))
    {
        std::cerr << "Fehler beim Laden von auftrag abgeschlossen.ogg!" << std::endl;
    }

    if (this->loadHintergrundMusik("Texturen & Musik/Hintergrund-Musik.ogg"))
    {
        this->setMusicLautstaerke(10.f);
        this->playHintergrundMusik();
    }
    else
    {
        cout << "Fehler beim Laden der Hintergrundmusik!" << endl;
    }


    if (!this->loadFalschSound("Texturen & Musik/falsch.ogg"))
    {
        std::cerr << "Fehler beim Laden von falsch.ogg!" << std::endl;
    }

    meinSound.setBuffer(buffer);
    /*lautstärke = 20.f;*/ // Standardlautstärke


}

sf::Sound& mySound::getMeinSound()
{
    return meinSound;
}

bool mySound::loadHintergrundMusik(const std::string& filePath)
{
    if (!hintergrundMusik.openFromFile(filePath)) // Öffnet die Musikdatei
    {
        cerr << "Fehler beim Laden der Hintergrundmusik-Datei!" << endl;
        return false;
    }
    return true;
}

void mySound::playHintergrundMusik(bool loop)
{
    hintergrundMusik.setLoop(loop); // Endlosschleife aktivieren
    hintergrundMusik.play();
}

void mySound::stopHintergrundMusik()
{
    hintergrundMusik.stop();
}

bool mySound::isMusicPlaying() const
{
    return hintergrundMusik.getStatus() == sf::Music::Playing;
}

void mySound::setMusicLautstaerke(bool volume)
{
    if (volume == 0 && musicVolume > 0)
        musicVolume -= 5.f;
    else if (volume == 1 && musicVolume < 100)
        musicVolume += 5.f;

    hintergrundMusik.setVolume(musicVolume);
}


// Neue Methode zur Verwaltung der Lautstärke der Soundeffekte
float mySound::getEffektLautstaerke() const
{
    return effectVolume;
}

void mySound::setEffektLautstaerke(bool volume)
{
    if (volume == 0 && effectVolume > 0)
        effectVolume -= 5.f;
    else if (volume == 1 && effectVolume < 100)
        effectVolume += 5.f;

    meinSound.setVolume(effectVolume);
    gameStartSound.setVolume(effectVolume);
    gameOverSound.setVolume(effectVolume);
    auftragAbgeschlossenSound.setVolume(effectVolume);
}


bool mySound::loadGameStartSound(const std::string& filePath)
{
    if (!gameStartBuffer.loadFromFile(filePath))
    {
        std::cerr << "Fehler beim Laden von game start.ogg" << std::endl;
        return false;
    }
    gameStartSound.setBuffer(gameStartBuffer);
    return true;
}

void mySound::playGameStartSound()
{
    gameStartSound.play();
}

bool mySound::loadGameOverSound(const std::string& filePath)
{
    if (!gameOverBuffer.loadFromFile(filePath))
    {
        std::cerr << "Fehler beim Laden von game over.ogg!" << std::endl;
        return false;
    }
    gameOverSound.setBuffer(gameOverBuffer);
    return true;
}

void mySound::playGameOverSound()
{
    gameOverSound.play();
}

void mySound::setGameOverVolume(float volume)
{
    gameOverSound.setVolume(volume); // Wertebereich 0–100
}

bool mySound::loadAuftragAbgeschlossenSound(const std::string& filePath)
{
    if (!auftragAbgeschlossenBuffer.loadFromFile(filePath))
    {
        return false; // Falls der Sound nicht geladen werden kann
    }
    auftragAbgeschlossenSound.setBuffer(auftragAbgeschlossenBuffer);
    return true; // Sound erfolgreich geladen
}

void mySound::playAuftragAbgeschlossenSound()
{
    auftragAbgeschlossenSound.setVolume(effectVolume); // Lautstärke setzen
    auftragAbgeschlossenSound.play();
}

void mySound::setVolume(float volume) {
    effectVolume = volume;  // Lautstärke setzen
    hintergrundMusik.setVolume(musicVolume);  // Lautstärke der Hintergrundmusik setzen
    meinSound.setVolume(effectVolume);  // Lautstärke des Standard-Sounds setzen

    // Wenn du weitere Soundobjekte hast, setze auch deren Lautstärke
    gameStartSound.setVolume(effectVolume);
    gameOverSound.setVolume(effectVolume);
    auftragAbgeschlossenSound.setVolume(effectVolume);
}



float mySound::getMusicLautstaerke()
{
    return musicVolume;
}

bool mySound::loadFalschSound(const std::string& filePath)
{
    if (!falschBuffer.loadFromFile(filePath))
        return false;

    falschSound.setBuffer(falschBuffer);
    falschSound.setVolume(effectVolume); // für den Fall, dass sie sich ändert
    return true;
}


void mySound::playFalschSound(bool istGameOver)
{
    if(!istGameOver)
    {
        falschSound.setVolume(std::min(effectVolume * 1.5f, 100.0f)); // Lauter als andere
        falschSound.play();
    }
}
    


