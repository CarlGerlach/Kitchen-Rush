#pragma once  
#include <SFML/Graphics.hpp>  
#include <SFML/Audio.hpp>  
#include <iostream>  
#include <functional>  

#include "mySound.h"  

using namespace std;  
using namespace sf;  

class Button  
{  
private:  
   sf::RectangleShape shape;   // Form des Buttons  
   sf::Text text;              // Text des Buttons  
   sf::Font font;              // Schriftart (f�r den Text)  
   std::function<void()> onClick; // Funktion, die beim Klick ausgef�hrt wird  
   mySound* soundOfButton;  

   sf::Sprite sprite; // Sprite des Buttons  
   sf::Texture* texture; // Zeiger auf eine externe Textur, um Speicherprobleme zu vermeiden  
   bool clicked; // Status, ob der Button geklickt wurde  

public:  
   // Konstruktor  
   Button(float x, float y, float width, float height, const std::string& label, const sf::Font& font, const sf::Color& buttonColor, const sf::Color& textColor, mySound* ini_soundOfButton);  

   // Setter f�r die OnClick-Funktion  
   void setOnClick(std::function<void()> callback);  

   // Zeichne den Button  
   void draw(sf::RenderWindow& window);  

   // �berpr�fe, ob der Button angeklickt wurde  
   void handleEvent(const sf::Event& event, const sf::RenderWindow& window);  

   // Setter f�r die Position  
   void setPosition(float x, float y);  

   // Setter f�r die Textur  
   void setTexture(sf::Texture* newTexture);  

   // Setter f�r den Text  
   string setText(const string& newText);  

   // Setter f�r die Skalierung  
   void setScale(float scale);  

   // �berpr�fen, ob der Button geklickt wurde  
   bool wasClicked() ;  

   void setClicked(bool clicked) 
   { 
	   this->clicked = clicked; 
   } // Setter f�r den Klick-Status
};
