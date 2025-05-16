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
			auftragErledigtUndAngekommen = false;

			// Bot zurückschicken
			if (derBot) 
			{
				derBot->setZiel(zielPosition);
			}
			return true;
		}
	}
	else 
	{
		stringstream text;
		text << "Nicht genügend Items im Inventar für Auftrag";
		GameMessage::setText(text.str());
	}
	return false;
}

void Table::updateBot()
{
	if (!botAktiv) {
		derBot = std::make_unique<Bot>(zielPosition);
		derBot->setZiel(this->shape.getPosition());  // Tischposition als Ziel
		botAktiv = true;
		isBotAmTable = false;
	}
	else if (derBot)
	{
		derBot->update();

		// Wenn Bot am Tisch angekommen ist
		if (!isBotAmTable && derBot->amZiel() && derBot->getPosition() == this->shape.getPosition())
		{
			isBotAmTable = true;
			auftragErledigtUndAngekommen = true;  // ⬅️ DAS hat gefehlt!
		}

		// Wenn Bot am Rückgabeort ist
		if (derBot->amZiel() && derBot->getPosition() == zielPosition)
		{
			derBot.reset();
			isBotAmTable = false;
			botAktiv = false;
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

bool Table::darfNeuenAuftragErstellen()
{
	return auftragErledigtUndAngekommen;
}

void Table::resetNeuenAuftragErlaubt()
{
	auftragErledigtUndAngekommen = false;
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
