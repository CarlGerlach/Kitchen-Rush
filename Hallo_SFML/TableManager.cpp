#include "TableManager.h"

TableManager::TableManager()
{
}

void TableManager::addTable(Table* ini_Table)
{
    if (ini_Table) {
        allTables.push_back(ini_Table);
    }
}

void TableManager::updateAllTables()
{
    for (auto& table : allTables) {
        table->updateBot();

        //if (table->isBotAmTable()) {
        //    table->setAktivVisual();
        //}
        //else {
        //    table->setNormalVisual();
        //}
    }
}

void TableManager::drawAllBots(sf::RenderWindow& window)
{
    for (auto& table : allTables) {
        table->drawBot(window);
    }
}

void TableManager::drawAllTables(sf::RenderWindow& window)
{
    for (auto& table : allTables) {
        table->draw(window);
    }
}
