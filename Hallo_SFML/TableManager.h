#pragma once

#include <vector>
#include "Table.h"
#include "AuftraegeManager.h"
#include <SFML/Graphics.hpp>

class TableManager
{
private:
    std::vector<Table*> allTables;
    AuftraegeManager* am;
    Texture normalTexture;
    Texture isActiveTexture;

    

public:
    TableManager(AuftraegeManager* ini_am);

    
    
    void addTable(Table* ini_Table);

    // Aktualisiert Bots und Visualisierung
    void updateAllTables();

    // Zeichnet Bots separat
    void drawAllBots(sf::RenderWindow& window);

    // Zeichnet alle Tische
    void drawAllTables(sf::RenderWindow& window);
};
