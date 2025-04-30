#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include <iostream>

using namespace std;
using namespace sf;



class mySound
{
private:
	sf::Sound meinSound;
	sf::SoundBuffer buffer; //Speichert sounds, dass diese Später nicht neu geladen werden müssen
	sf::Music hintergrundMusik; // Für Hintergrundmusik
	mySound *soundManager;
	bool volume; // 0= weniger 1= mehr

	float lautstärke;
public:
	mySound();
	Sound& getMeinSound();

	bool loadHintergrundMusik(const string& filePath); // Lädt Hintergrundmusik
	void playHintergrundMusik(bool loop = true); // Spielt die Hintergrundmusik
	void stopHintergrundMusik(); // Stoppt die Hintergrundmusik
	bool isMusicPlaying() const; // Checkt den Status ob die Musik schon spielt

	void setMusicLautstaerke(bool volume); // Lautstärke der Hintergrundmusik setzen

	float getMusicLautstaerke() const // Gibt die Lautstärke der Hintergrundmusik zurück
	{
		return lautstärke;
	}


};

