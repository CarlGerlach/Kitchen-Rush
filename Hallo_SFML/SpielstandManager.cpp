#include "SpielstandManager.h"
#include "Spieler.h"
#include <fstream>
#include "json.hpp"
#include "DeviceManager.h"
#include <vector>
#include "Item.h"

using json = nlohmann::json;

NLOHMANN_JSON_SERIALIZE_ENUM(ItemID, {
	{ItemID::WASSER, "WASSER"},
	{ItemID::MEHL, "MEHL"},
	{ItemID::TEIG, "TEIG"},
	{ItemID::TOMATE, "TOMATE"},
	{ItemID::PIZZA, "PIZZA"},
	{ItemID::COLA, "COLA"},
	{ItemID::SALAT, "SALAT"}
	});

SpielstandManager::SpielstandManager(Spieler* spieler)
{
	this->spieler = spieler;

	// std::cout << "SpielstandManager erstellt!" << std::endl;
}

SpielstandManager::~SpielstandManager()
{
}

std::string itemIDToString(ItemID id) {
	switch (id) {
	case ItemID::WASSER: return "WASSER";
	case ItemID::MEHL: return "MEHL";
	case ItemID::TEIG: return "TEIG";
	case ItemID::TOMATE: return "TOMATE";
	case ItemID::PIZZA: return "PIZZA";
	case ItemID::COLA: return "COLA";
	case ItemID::SALAT: return "SALAT";
	default: return "UNBEKANNT";
	}
}

ItemID stringToItemID(const std::string& str) {
	if (str == "WASSER") return ItemID::WASSER;
	if (str == "MEHL") return ItemID::MEHL;
	if (str == "TEIG") return ItemID::TEIG;
	if (str == "TOMATE") return ItemID::TOMATE;
	if (str == "PIZZA") return ItemID::PIZZA;
	if (str == "COLA") return ItemID::COLA;
	if (str == "SALAT") return ItemID::SALAT;
	if (str == "LEER") return ItemID::UNBEKANNT;
	return ItemID::UNBEKANNT; // Falls vorhanden
}

void SpielstandManager::saveGame(Spieler* spieler, DeviceManager* dm)
{
	json saveData;
	saveData["position"]["x"] = spieler->getPosition().x;
	saveData["position"]["y"] = spieler->getPosition().y;
	saveData["points"] = spieler->getPoints();

	saveData["playerInventory"]["0"] = spieler->getPlayerInventar()->getItem(0) ? itemIDToString(spieler->getPlayerInventar()->getItem(0)->getItemID()) : "LEER";
	saveData["playerInventory"]["1"] = spieler->getPlayerInventar()->getItem(1) ? itemIDToString(spieler->getPlayerInventar()->getItem(1)->getItemID()) : "LEER";
	saveData["playerInventory"]["2"] = spieler->getPlayerInventar()->getItem(2) ? itemIDToString(spieler->getPlayerInventar()->getItem(2)->getItemID()) : "LEER";
	saveData["playerInventory"]["3"] = spieler->getPlayerInventar()->getItem(3) ? itemIDToString(spieler->getPlayerInventar()->getItem(3)->getItemID()) : "LEER";
	saveData["playerInventory"]["4"] = spieler->getPlayerInventar()->getItem(4) ? itemIDToString(spieler->getPlayerInventar()->getItem(4)->getItemID()) : "LEER";

	vector<DeviceInventar*> inventories = dm->getAllInventorys();

	// das cout hier ist ein test zum ausgeben der items bitte nicht löschen wird später wichtig zum debuggen
	//cout << itemIDToString(inventories[0]->getItem(0)->getItemID()) << endl;



	// inv[0] ist der Ofen
	// inv[1] ist die Theke wo Items spawnen
	// inv[2] ist der Mixer
	// inv[3] ist der Tresen wo bestellungen abgeschlossen werden



	// Anzahl der Slots pro Inventar in Reihenfolge: inventories[0] = Ofen, [1] = Theke, etc.
	std::vector<int> inventorySlotCounts = {
		3,   // inventories[0]
		5,   // inventories[1]
		3,   // inventories[2]
		20   // inventories[3]
	};

	for (size_t invIndex = 0; invIndex < inventorySlotCounts.size(); ++invIndex) {
		int slotCount = inventorySlotCounts[invIndex];
		for (int slot = 0; slot < slotCount; ++slot) {
			Item* item = inventories[invIndex]->getItem(slot);
			std::string slotKey = (slot < 10 ? "0" : "") + std::to_string(slot);
			saveData["inventories"][std::to_string(invIndex)][slotKey] =
				item ? itemIDToString(item->getItemID()) : "LEER";
		}
	}

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

void SpielstandManager::loadGame(Spieler* spieler, DeviceManager* dm)
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

	// Spielerinventar laden
	spieler->getPlayerInventar()->removeItem(0);
	spieler->getPlayerInventar()->removeItem(1);
	spieler->getPlayerInventar()->removeItem(2);
	spieler->getPlayerInventar()->removeItem(3);
	spieler->getPlayerInventar()->removeItem(4);
	spieler->getPlayerInventar()->addItemToSlot(new Item(stringToItemID(j["playerInventory"]["0"])), 0);
	spieler->getPlayerInventar()->addItemToSlot(new Item(stringToItemID(j["playerInventory"]["1"])), 1);
	spieler->getPlayerInventar()->addItemToSlot(new Item(stringToItemID(j["playerInventory"]["2"])), 2);
	spieler->getPlayerInventar()->addItemToSlot(new Item(stringToItemID(j["playerInventory"]["3"])), 3);
	spieler->getPlayerInventar()->addItemToSlot(new Item(stringToItemID(j["playerInventory"]["4"])), 4);

	// Zurück in den Spieler schreiben
	spieler->setPoints(punkte);
	spieler->setPosition(x, y);



	vector<DeviceInventar*> inventories = dm->getAllInventorys();

	// Anzahl der Slots pro Inventar (Inventar-Indizes: 0 = Ofen, 1 = Theke, ...)
	std::vector<int> inventorySlotCounts = { 3, 5, 3, 20 };

	// Alle Inventare zurücksetzen und laden
	for (size_t invIndex = 0; invIndex < inventorySlotCounts.size(); ++invIndex) {
		int slotCount = inventorySlotCounts[invIndex];
		std::string invKey = std::to_string(invIndex);

		for (int slot = 0; slot < slotCount; ++slot) {
			std::string slotKey = (slot < 10 ? "0" : "") + std::to_string(slot);
			std::string itemStr = j["inventories"][invKey][slotKey];

			// Inventarslot zurücksetzen (z.B. auf nullptr oder leer)
			inventories[invIndex]->removeItem(slot);

			if (itemStr != "LEER" && itemStr != "UNBEKANNT") {
				// String → ItemID konvertieren
				ItemID id = stringToItemID(itemStr);

				// Item erzeugen (du brauchst eine Item-Fabrik oder ähnliches)
				Item* item = new Item(id);

				// Item ins Inventar setzen
				inventories[invIndex]->addItemToSlot(item, slot); // Beispiel: Item in den ersten Slot des Ofens setzen
			}
		}
	}

}
