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
	vector<GeraetBase*> allDevices;

public:
	DeviceManager();

	void addDevice(GeraetBase* ini_Device);

	

	



};

