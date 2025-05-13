#include "mySound.h"
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

    meinSound.setBuffer(buffer);
    lautstärke = 20.f; // Standardlautstärke
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
    if (volume == 0 && lautstärke > 0)
    {
        lautstärke -= 5.f;
    }
    else if (volume == 1 && lautstärke < 100)
    {
        lautstärke += 5.f;
    }
    hintergrundMusik.setVolume(lautstärke);
}

// Neue Methode zur Verwaltung der Lautstärke der Soundeffekte
float mySound::getEffektLautstaerke() const
{
    return lautstärke;
}

void mySound::setEffektLautstaerke(bool volume)
{
    if (volume == 0 && lautstärke > 0)
    {
        lautstärke -= 5.f;
    }
    else if (volume == 1 && lautstärke < 100)
    {
        lautstärke += 5.f;
    }

    meinSound.setVolume(lautstärke);
    gameStartSound.setVolume(lautstärke);
    gameOverSound.setVolume(lautstärke);
    auftragAbgeschlossenSound.setVolume(lautstärke);
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
    auftragAbgeschlossenSound.setVolume(100.f);  // Lautstärke auf 100% setzen
    auftragAbgeschlossenSound.play();  // Sound abspielen
}

void mySound::setVolume(float volume) {
    lautstärke = volume;  // Lautstärke setzen
    hintergrundMusik.setVolume(lautstärke);  // Lautstärke der Hintergrundmusik setzen
    meinSound.setVolume(lautstärke);  // Lautstärke des Standard-Sounds setzen

    // Wenn du weitere Soundobjekte hast, setze auch deren Lautstärke
    gameStartSound.setVolume(lautstärke);
    gameOverSound.setVolume(lautstärke);
    auftragAbgeschlossenSound.setVolume(lautstärke);
}

// In der mySound-Klasse
float mySound::getMusicLautstaerke() {
    return lautstärke;
}
