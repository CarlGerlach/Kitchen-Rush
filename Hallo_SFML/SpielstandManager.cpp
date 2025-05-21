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
	{ItemID::SALAT, "SALAT"},
	{ItemID::GURKE, "Gurke"},
	{ItemID::SALATKOPF, "Salatkopf"}
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
	case ItemID::GURKE: return "Gurke";
	case ItemID::SALATKOPF: return "Salatkopf";
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
	if (str == "Gurke") return ItemID::GURKE;
	if (str == "Salatkopf") return ItemID::SALATKOPF;
	if (str == "LEER") return ItemID::UNBEKANNT;
	return ItemID::UNBEKANNT; // Falls vorhanden
}

void SpielstandManager::saveGame(Spieler* spieler, DeviceManager* dm)
{
	json saveData;
	saveData["position"]["x"] = spieler->getPosition().x;
	saveData["position"]["y"] = spieler->getPosition().y;
	saveData["points"] = spieler->getPoints();
	saveData["lives"] = spieler->getLeben();

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

	// inv[4] ist Table1
	// inv[5] ist Table2
	// inv[6] ist Table3
	// inv[7] ist Table4
	// inv[8] ist Table5



	// Anzahl der Slots pro Inventar in Reihenfolge: inventories[0] = Ofen, [1] = Theke, etc.
	std::vector<int> inventorySlotCounts = {
		3,   // inventories[0]	  inv[0] ist der Ofen
		5,   // inventories[1]	  inv[1] ist die Theke wo Items spawnen
		3,   // inventories[2]	  inv[2] ist der Mixer
		20,   // inventories[3]	  inv[3] ist der Tresen wo bestellungen abgeschlossen werden
		20,   // inventories[4]	  inv[4] ist Table1
		20,   // inventories[5]	  inv[5] ist Table2
		20,   // inventories[6]	  inv[6] ist Table3
		20,   // inventories[7]	  inv[7] ist Table4
		20    // inventories[8]	  inv[8] ist Table5
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
	int z = j["lives"];

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
	spieler->setLeben(z);



	vector<DeviceInventar*> inventories = dm->getAllInventorys();

	// Anzahl der Slots pro Inventar (Inventar-Indizes: 0 = Ofen, 1 = Theke, ...)
	std::vector<int> inventorySlotCounts = { 3, 5, 3, 20, 20, 20, 20, 20, 20 };

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

	for (int i = 0; i < 5; ++i) {
		std::string itemStr = j["playerInventory"][std::to_string(i)];
		spieler->getPlayerInventar()->removeItem(i); // vorher immer entfernen
		if (itemStr != "LEER" && itemStr != "UNBEKANNT") {
			ItemID id = stringToItemID(itemStr);
			Item* item = new Item(id);
			spieler->getPlayerInventar()->addItemToSlot(item, i);
		}
	}


}
