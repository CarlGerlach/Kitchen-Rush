#include "DeviceManager.h"

DeviceManager::DeviceManager()
{

}



void DeviceManager::addInventory(DeviceInventar* ini_inventory)
{
	allInventorys.push_back(ini_inventory);
}

void DeviceManager::addPosition(sf::RectangleShape* shape)
{
    cachedBounds.push_back(shape->getGlobalBounds()); // Nur EINMAL beim Hinzufügen berechnen
}

vector<DeviceInventar*> DeviceManager::getAllInventorys()
{
	return allInventorys;
}

bool DeviceManager::checkCollision(Spieler* spieler1, const sf::Vector2f& direction) {
    sf::FloatRect bounds = spieler1->getBounds();

    bounds.left += direction.x;
    bounds.top += direction.y;

    const float epsilon = 0.1f;
    bounds.left += epsilon;
    bounds.top += epsilon;
    bounds.width -= 2 * epsilon;
    bounds.height -= 2 * epsilon;

    for (const auto& cachedBound : cachedBounds) {
        if (cachedBound.intersects(bounds)) {
            return true;
        }
    }

    return false;
}





