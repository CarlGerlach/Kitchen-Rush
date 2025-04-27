#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "Knopf.h"
#include "DeviceInventar.h"

using namespace sf;
using namespace std;

class dasFenster 
{
private:
    RectangleShape background;
    vector<Knopf> knoepfe;
    bool visible = false;

protected:
    const int windowWidth = 600;
    const int windowHight = 800;  
    const int buttonDistance = 20;
    int amountOfButtons = 0;


public:
    dasFenster();
    void addKnopf(const string& label, Font& font, function<void()> callback);  // Neue Methode mit Font
    void draw(RenderWindow& window);
    void drawForDevice(RenderWindow& window, RectangleShape(&deviceInventarSlots)[3], DeviceInventar* devInventar);
    void handleEvent(const Event& event, const RenderWindow& window);
    void toggle();
};