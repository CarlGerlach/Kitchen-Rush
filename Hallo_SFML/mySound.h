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
	sf::SoundBuffer buffer; //Speichert sounds, dass diese Sp�ter nicht neu geladen werden m�ssen
	sf::Music hintergrundMusik; // F�r Hintergrundmusik

public:
	mySound();
	Sound& getMeinSound();

	bool loadHintergrundMusik(const string& filePath); // L�dt Hintergrundmusik
	void playHintergrundMusik(bool loop = true); // Spielt die Hintergrundmusik
	void stopHintergrundMusik(); // Stoppt die Hintergrundmusik
	bool isMusicPlaying() const; // Checkt den Status ob die Musik schon spielt

	void setMusicLautstaerke(float volume); // Lautst�rke der Hintergrundmusik setzen




};

