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


public:
	mySound();
	Sound& getMeinSound();



};

