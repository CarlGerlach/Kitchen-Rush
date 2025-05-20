#pragma once
#include <iostream>
#include <vector>
#include "GeraetBase.h"
#include "DeviceInventar.h"


using namespace std;
using namespace sf;

class DeviceManager
{
private:
	vector<DeviceInventar*> allInventorys;
	vector<sf::FloatRect> cachedBounds;

public:
	DeviceManager();


	void addInventory(DeviceInventar* ini_inventory);
	void addPosition(sf::RectangleShape* shape);

	vector<DeviceInventar*> getAllInventorys();

	bool checkCollision(Spieler* spieler, const sf::Vector2f& direction);
	

	



};

