#include "Table.h"
#include "sstream"
#include "GameMessage.h"

int Table::index = 1;

Table::Table(int gridnumber, Font& newFont, Spieler* player, int ini_inventorySize, AuftraegeManager* ini_am)
	: GeraetBase(gridnumber, player, ini_inventorySize), botAktiv(false), isBotAmTable(false)
{
	this->tableID = index++;
	if (ini_am) am = ini_am;
	setupButtons(newFont, player);

}

bool Table::checkAuftragErfüllbar()
{
	if (!am || !devInventar) return false;
	Auftrag* auftrag = am->getAuftragMitID(tableID);
	if (!auftrag) return false;

	for (int i = 0; i < auftrag->getAnzahlBestellopsitionen(); ++i) {
		Bestellposition* bp = auftrag->getBestellposition(i);
		if (!bp) continue;

		if (devInventar->getItemAnzahl(bp->getPosition()) < bp->getAnzahl())
			return false;
	}

	return true;
}

bool Table::versucheAuftragZuErfüllen()
{
	if (!derBot) return false; // Bot muss da sein

	if (checkAuftragErfüllbar()) {
		Auftrag* auftrag = am->getAuftragMitID(tableID);
		if (auftrag) {
			for (int i = 0; i < auftrag->getAnzahlBestellopsitionen(); ++i) {
				Bestellposition* bp = auftrag->getBestellposition(i);
				int punkte = bp->getPointsForItem(bp->getPosition()) * bp->getAnzahl();
				player->addPoints(punkte);
				devInventar->removeItems(bp->getPosition(), bp->getAnzahl());
			}

			am->finishAuftrag(auftrag);

			// Bot zurückschicken
			if (derBot) 
			{
				derBot->setZiel(zielPosition);
			}
			return true;
		}
	}
	else {
		stringstream text;
		text << "Nicht genügend Items im Inventar für Auftrag";
		GameMessage::setText(text.str());
	}
	return false;
}

void Table::updateBot()
{
	if (!botAktiv) {
		// Starte neuen Bot zum Table
		derBot = std::make_unique<Bot>(zielPosition);
		derBot->setZiel(this->shape.getPosition());
		cout << "Test 1 Table::updateBot" << endl;
		botAktiv = true;
	}
	else if (derBot) 
	{
		derBot->update();

		if (derBot->amZiel()) 
		{
			//shape.setFillColor(sf::Color::Black);
			
			// Ziel erreicht?
			if (derBot->getPosition() == zielPosition) 
			{
				// Bot ist am Rückgabeort → entfernen
				cout << "Test 3 Table::update" << endl;
				derBot.reset();
				isBotAmTable = true;
				botAktiv = false;
			}
		}
	}
}

void Table::drawBot(RenderWindow& window)
{
	if (derBot) derBot->draw(window);
}

void Table::setZielPosition(Vector2f& pos)
{
	zielPosition = pos;
}

bool Table::getIsBotAmTable()
{
	return isBotAmTable;
}

void Table::setNormalTexture(Texture* tex)
{
	this->shape.setTexture(tex);
}

void Table::setIsActiveTexture(Texture* tex)
{
	this->shape.setTexture(tex);
}

void Table::setupButtons(Font& newFont, Spieler* player)
{
	dasFenster.addKnopf(
		"Beende Auftrag",
		newFont,
		[this, player]()
		{
			versucheAuftragZuErfüllen();
		}
	);
}
