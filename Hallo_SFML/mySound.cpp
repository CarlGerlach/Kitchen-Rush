#include "mySound.h"
using namespace std;
using namespace sf;

mySound::mySound()
{
    if (!buffer.loadFromFile("Texturen & Musik/Button-Click.wav")) // WAV-Datei statt MP3
    {
        std::cout << "Fehler beim Laden der Sound-Datei!" << std::endl;
    }
    
    meinSound.setBuffer(buffer);

	lautst�rke = 10.f; // Standardlautst�rke
}

Sound& mySound::getMeinSound()
{
    return meinSound;
}

bool mySound::loadHintergrundMusik(const std::string& filePath)
{
    if (!hintergrundMusik.openFromFile(filePath)) // �ffnet die Musikdatei
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
	if (volume == 0 && lautst�rke > 0)
	{
		lautst�rke -= 5.f;
	}
	else if (volume == 1 && lautst�rke<100)
	{
		lautst�rke += 5.f;
	}
	hintergrundMusik.setVolume(lautst�rke);
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
    gameOverSound.setVolume(volume); // Wertebereich 0�100
}





