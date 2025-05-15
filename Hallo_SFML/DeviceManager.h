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

public:
	DeviceManager();


	void addInventory(DeviceInventar* ini_inventory);
	vector<DeviceInventar*> getAllInventorys();

	

	



};

