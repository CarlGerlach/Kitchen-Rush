#include "TableManager.h"

TableManager::TableManager(AuftraegeManager* ini_am)
{
    if (ini_am != nullptr)
    {
        am = ini_am;
    }

    if (!normalTexture.loadFromFile("Texturen & Musik/Herd_01.png")) {
        cerr << "Fehler beim Laden der normalTexture!" << endl;   
    }
    if (!isActiveTexture.loadFromFile("Texturen & Musik/temp.png")) {
        cerr << "Fehler beim Laden der Ofen-Textur!" << endl;
    }
}

void TableManager::addTable(Table* ini_Table)
{
    if (ini_Table) 
    {
        allTables.push_back(ini_Table);
    }
}

void TableManager::updateAllTables()
{
    for (auto& table : allTables) 
    {
        table->updateBot();
        cout << table->getIsBotAmTable() << endl;

        if (table->getIsBotAmTable())
        {
            table->setIsActiveTexture(&isActiveTexture);
        }
        else {
           table->setNormalTexture(&normalTexture);
        }
    }
}



    void TableManager::drawAllBots(sf::RenderWindow & window)
    {
        for (auto& table : allTables)
        {
            table->drawBot(window);
        }
    }

    void TableManager::drawAllTables(sf::RenderWindow& window)
{
    for (auto& table : allTables) {
        table->draw(window);
    }
}
