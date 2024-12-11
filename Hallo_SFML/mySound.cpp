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

void mySound::setMusicLautstaerke(float volume)
{
    hintergrundMusik.setVolume(volume);
}

