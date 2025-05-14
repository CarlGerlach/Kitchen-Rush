#pragma once

#include <SFML/Audio.hpp>
#include <iostream>

class mySound
{
private:
    sf::SoundBuffer buffer;
    sf::Sound meinSound;

    sf::Music hintergrundMusik;

    float musicVolume = 10.f;
    float effectVolume = 20.f;  


    sf::SoundBuffer gameStartBuffer;
    sf::Sound gameStartSound;

    sf::SoundBuffer gameOverBuffer;
    sf::Sound gameOverSound;

    sf::SoundBuffer auftragAbgeschlossenBuffer;
    sf::Sound auftragAbgeschlossenSound;

public:
    mySound();

    sf::Sound& getMeinSound();

    bool loadHintergrundMusik(const std::string& filePath);
    void playHintergrundMusik(bool loop = true);
    void stopHintergrundMusik();
    bool isMusicPlaying() const;

    void setMusicLautstaerke(bool volume);
    float getEffektLautstaerke() const;
    void setEffektLautstaerke(bool volume);  // Neue Methode f�r Effektlautst�rke

    bool loadGameStartSound(const std::string& filePath);
    void playGameStartSound();
    bool loadGameOverSound(const std::string& filePath);
    void playGameOverSound();
    void setGameOverVolume(float volume);

    bool loadAuftragAbgeschlossenSound(const std::string& filePath);
    void playAuftragAbgeschlossenSound();

    // Neue Methode zum Setzen der Lautst�rke
    void setVolume(float volume);  // Methode zum Setzen der Lautst�rke f�r alle Sounds

    float getMusicLautstaerke();
};
