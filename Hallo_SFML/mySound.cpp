#include "mySound.h"
using namespace std;
using namespace sf;

mySound::mySound()
{

    if (!buffer.loadFromFile("Texturen & Musik/Button-Click.wav")) // WAV-Datei statt MP3
    {
        std::cout << "Fehler beim Laden der Sound-Datei!" << std::endl;
    }

    if (!this->loadGameStartSound("Texturen & Musik/game start.ogg")) {
        std::cerr << "Fehler beim Laden von game start.ogg!" << std::endl;
    }

    if (!this->loadGameOverSound("Texturen & Musik/game over.ogg")) {
        std::cerr << "Fehler beim Laden von game over.ogg!" << std::endl;
    }
    this->setGameOverVolume(30.f); // 20 % Lautstärke


    // Lade den Soundmanager und den Auftrag-Abgeschlossen-Sound
    if (!this->loadAuftragAbgeschlossenSound("Texturen & Musik/auftrag abgeschlossen.ogg")) {
        std::cerr << "Fehler beim Laden von auftrag abgeschlossen.ogg!" << std::endl;
    }


    if (this->loadHintergrundMusik("Texturen & Musik/Hintergrund-Musik.ogg")) {
        this->setMusicLautstaerke(10.f);
        this->playHintergrundMusik();
    }
    else {
        cout << "Fehler beim Laden der Hintergrundmusik!" << endl;
    }
    
    meinSound.setBuffer(buffer);

	lautstärke = 20.f; // Standardlautstärke
}

Sound& mySound::getMeinSound()
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
	else if (volume == 1 && lautstärke<100)
	{
		lautstärke += 5.f;
	}
	hintergrundMusik.setVolume(lautstärke);
}


//Neuer Sound game start
bool mySound::loadGameStartSound(const std::string& filePath) {
    if (!gameStartBuffer.loadFromFile(filePath)) {
        std::cerr << "Fehler beim Laden von game start.ogg" << std::endl;
        return false;
    }
    gameStartSound.setBuffer(gameStartBuffer);
    return true;
}

void mySound::playGameStartSound() {
    gameStartSound.play();
}

bool mySound::loadGameOverSound(const std::string& filePath) 
{
    if (!gameOverBuffer.loadFromFile(filePath)) {
        std::cerr << "Fehler beim Laden von game over.ogg!" << std::endl;
        return false;
    }
    gameOverSound.setBuffer(gameOverBuffer);
    return true;
}

void mySound::playGameOverSound() {
    gameOverSound.play();
}

void mySound::setGameOverVolume(float volume) {
    gameOverSound.setVolume(volume); // Wertebereich 0–100
}



// Methode zum Laden des Auftrag-Abgeschlossen-Sounds
bool mySound::loadAuftragAbgeschlossenSound(const std::string& filePath) {
    if (!auftragAbgeschlossenBuffer.loadFromFile(filePath)) {
        return false; // Falls der Sound nicht geladen werden kann
    }
    auftragAbgeschlossenSound.setBuffer(auftragAbgeschlossenBuffer);
    return true; // Sound erfolgreich geladen
}

// Methode zum Abspielen des Auftrag-Abgeschlossen-Sounds
void mySound::playAuftragAbgeschlossenSound() {
    auftragAbgeschlossenSound.setVolume(100.f);  // Lautstärke auf 100% setzen
    auftragAbgeschlossenSound.play();  // Sound abspielen
}

