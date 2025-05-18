#include "TableManager.h"
#include "AuftraegeManager.h"
#include "Table.h"

TableManager::TableManager(AuftraegeManager* ini_am)
{
    am = ini_am;
    

    cout << "Test 3" << endl;
    normalTexture.loadFromFile("Texturen & Musik/Tisch.png");
    //if (!normalTexture.loadFromFile("Texturen & Musik/Herd_01.png")) {
    //    cerr << "Fehler beim Laden der Herd-Textur!" << endl;
    //    cout << "Test 1 " << endl;
    //}

    isActiveTexture.loadFromFile("Texturen & Musik/Kunde am Tisch.png");
    //if (!isActiveTexture.loadFromFile("Texturen & Musik/temp.png")) {
    //    cerr << "Fehler beim Laden der temp-Textur!" << endl;
    //    cout << "Test 2 " << endl;
    //}
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
            cout << "IstActiveTextur gesetzt" << endl;
            //table->setIsActiveTexture(&isActiveTexture);
            table->setTexture(&isActiveTexture);
        }
        else
        {
            cout << "NormalTextur gesetzt" << endl;
            //table->setNormalTexture(&normalTexture);
            table->setTexture(&normalTexture);
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
    for (auto& table : allTables) 
    {
        table->draw(window);
        table->drawTableID(window);
    }
}

void TableManager::handleEvent(sf::Event& event, sf::RenderWindow& window)
{
    for (auto& table : allTables)
    {
        table->handleEvent(event, window);
    }
}

bool TableManager::sollNeuerAuftragErstelltWerden()
{
    for (auto& table : allTables)
    {
        if (table->darfNeuenAuftragErstellen())
        {
            std::cout << "Neuer Auftrag erlaubt bei Tisch!" << std::endl;
            table->resetNeuenAuftragErlaubt(); // Reset
            return true;
        }
    }
    std::cout << "Kein Tisch erlaubt neuen Auftrag." << std::endl;
    return false;
}

//void TableManager::setAm(AuftraegeManager* ini_am)
//{
//    am = ini_am;
//}
