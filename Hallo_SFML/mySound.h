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


public:
	mySound();
	Sound& getMeinSound();



};

