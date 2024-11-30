#include "mySound.h"
using namespace std;
using namespace sf;

mySound::mySound()
{
    if (!buffer.loadFromFile("Button-Click.wav")) // WAV-Datei statt MP3
    {
        std::cout << "Fehler beim Laden der Sound-Datei!" << std::endl;
    }
    
    meinSound.setBuffer(buffer);
}

Sound& mySound::getMeinSound()
{
    return meinSound;
}
