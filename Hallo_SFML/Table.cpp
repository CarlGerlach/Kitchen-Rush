#include "Table.h"
#include "sstream"
#include "GameMessage.h"

int Table::index = 1;

Table::Table(int gridnumber, Font& newFont, Spieler* player, int ini_inventorySize, AuftraegeManager* ini_am)
	: GeraetBase(gridnumber, player, ini_inventorySize), botAktiv(false), isBotAmTable(false)
{
	this->tableID = index++;
	if (ini_am) am = ini_am;
	font = newFont;
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
	//bool botWarImBereich = warImTableBereich;
	//warImTableBereich = this->getCollisionBounds().contains(derBot->getPosition());
	
	if (!botAktiv) {
		derBot = std::make_unique<Bot>(zielPosition);
		
		sf::FloatRect bounds = shape.getGlobalBounds();
		sf::Vector2f center(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
		derBot->setZiel(center);
		
		//derBot->setZiel(this->shape.getPosition());  // Tischposition als Ziel
		botAktiv = true;
		isBotAmTable = false;
		warImTableBereich = false;
	}
	else if (derBot)
	{
		derBot->update();

		sf::FloatRect tableBounds = shape.getGlobalBounds();
		bool istImBereich = tableBounds.contains(derBot->getPosition());

		if (!warImTableBereich && istImBereich) {
			// Bot betritt den Tischbereich
			isBotAmTable = true;
			auftragErledigtUndAngekommen = true;
		}
		else if (warImTableBereich && !istImBereich) {
			// Bot verlässt den Tischbereich
			isBotAmTable = false;
		}

		warImTableBereich = istImBereich;

		if (derBot->amZiel() && derBot->getPosition() == zielPosition) {
			derBot.reset();
			botAktiv = false;
		}
	}
}

void Table::drawBot(RenderWindow& window)
{
	if (derBot && !derBot->getIstAmZiel())
	{
		derBot->draw(window);
	}
}

void Table::drawTableID(RenderWindow& window)
{
	Text text;
	text.setFont(font);
	text.setCharacterSize(18);
	text.setFillColor(sf::Color::Black);
	text.setString(std::to_string(tableID));

	sf::Vector2f shapePos = shape.getPosition();
	sf::Vector2f shapeSize = shape.getSize();
	text.setPosition((shapePos.x + shapeSize.x / 2.f - 10.f) + 2.f, (shapePos.y + shapeSize.y / 2.f - 10.f) + 12);

	window.draw(text);
}

void Table::setZielPosition(Vector2f& pos)
{
	zielPosition = pos;
}

bool Table::getIsBotAmTable()
{
	return isBotAmTable;
}

RectangleShape Table::getCollisionBounds()
{
	return shape;
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
