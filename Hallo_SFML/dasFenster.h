#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "Knopf.h"
#include "DeviceInventar.h"
#include "Spieler.h"

using namespace sf;
using namespace std;

class dasFenster 
{
private:
    RectangleShape background;
    vector<Knopf> knoepfe;
    DeviceInventar* connectedDeviceInventar = nullptr;
    Spieler* connectedPlayer = nullptr;
    vector<RectangleShape> connectedDeviceSlots;
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
    void drawForDevice(RenderWindow& window, vector<RectangleShape>& deviceInventorySlots, DeviceInventar* devInventar);
    void handleEvent(const Event& event, const RenderWindow& window);
    void toggle();

    void connectDeviceInventar(DeviceInventar* inventar);
    void connectPlayer(Spieler* player);
    void connectDeviceSlots(vector<RectangleShape> ini_connectedDeviceSlots);

    Spieler* getConnectedPlayer();
    bool getIsVisible();
};