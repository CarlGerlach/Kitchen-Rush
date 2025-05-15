#include "DeviceManager.h"

DeviceManager::DeviceManager()
{

}



void DeviceManager::addInventory(DeviceInventar* ini_inventory)
{
	allInventorys.push_back(ini_inventory);
}

vector<DeviceInventar*> DeviceManager::getAllInventorys()
{
	return allInventorys;
}



