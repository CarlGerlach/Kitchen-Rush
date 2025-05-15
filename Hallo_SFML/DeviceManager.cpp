#include "DeviceManager.h"

DeviceManager::DeviceManager()
{

}

void DeviceManager::addDevice(GeraetBase* ini_Device)
{	
	allDevices.push_back(ini_Device);
}

