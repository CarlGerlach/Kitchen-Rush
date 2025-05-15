#include "SpielstandManager.h"
#include "Spieler.h"
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

SpielstandManager::SpielstandManager(Spieler* spieler)
{
	this->spieler = spieler;

	// std::cout << "SpielstandManager erstellt!" << std::endl;
}

SpielstandManager::~SpielstandManager()
{
}

void SpielstandManager::saveGame(Spieler* spieler)
{
	json saveData;
	saveData["position"]["x"] = spieler->getPosition().x;
	saveData["position"]["y"] = spieler->getPosition().y;
	saveData["points"] = spieler->getPoints();

	// Hier können weitere Spielstände hinzugefügt werden

	std::ofstream file("savegame.json");
	if (file.is_open())
	{
		file << saveData.dump(4); // 4 ist die Einrückung für die Lesbarkeit
		file.close();
		std::cout << "Spielstand gespeichert!" << std::endl;
	}
	else
	{
		std::cerr << "Fehler beim Speichern des Spielstands!" << std::endl;
	}
}

void SpielstandManager::loadGame(Spieler* spieler)
{
	std::ifstream file("savegame.json");
	if (!file.is_open()) {
		throw std::runtime_error("Datei konnte nicht geöffnet werden");
	}

	json j;
	file >> j;

	// Werte auslesen
	int punkte = j["points"];
	int x = j["position"]["x"];
	int y = j["position"]["y"];

	// Zurück in den Spieler schreiben
	spieler->setPoints(punkte);
	spieler->setPosition(x, y);
}
