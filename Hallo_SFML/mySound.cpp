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
	if (volume == 0)
	{
		lautst�rke -= 5.f;
	}
	else
	{
		lautst�rke += 5.f;
	}
	hintergrundMusik.setVolume(lautst�rke);
}

