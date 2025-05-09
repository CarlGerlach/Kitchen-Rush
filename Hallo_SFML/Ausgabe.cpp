#include "Ausgabe.h"


Ausgabe::Ausgabe(int gridnumber, Font& newFont, Spieler* player, int ini_inventorySize, AuftraegeManager* ini_derAuftraegeManager) : GeraetBase(gridnumber, player, ini_inventorySize)
{
    if (ini_derAuftraegeManager != nullptr)
    {
        derAuftraegeManager = ini_derAuftraegeManager;
    }
    setupButtons(newFont, player);
}

void Ausgabe::setupButtons(Font& newFont, Spieler* player)
{
    dasFenster.addKnopf(
        "Beende Auftrag 1",
        newFont,  // Font �bergeben
        [this, player]()
        {
            if (checkAuftragErf�llbar(0))
            {
                Auftrag* auftrag = derAuftraegeManager->getAuftrag(0);

                if (auftrag != nullptr)
                {
                    // Entferne die Items
                    for (int i = 0; i < auftrag->getAnzahlBestellopsitionen(); ++i)
                    {
                        Bestellposition* bp = auftrag->getBestellposition(i);
                        devInventar->removeItems(bp->getPosition(), bp->getAnzahl());
                    }

                    derAuftraegeManager->removeAuftrag(auftrag);
                }
            }
            else
            {
                std::cout << "Nicht gen�gend Items im Inventar f�r Auftrag 1." << std::endl;
            }
            
        }
    );

    dasFenster.addKnopf(
        "Beende Auftrag 2",
        newFont,  // Font �bergeben
        [this, player]()
        {
            if (checkAuftragErf�llbar(1))
            {

                Auftrag* auftrag = derAuftraegeManager->getAuftrag(1);

                if (auftrag != nullptr)
                {
                    // Entferne die Items
                    for (int i = 0; i < auftrag->getAnzahlBestellopsitionen(); ++i)
                    {
                        Bestellposition* bp = auftrag->getBestellposition(i);
                        devInventar->removeItems(bp->getPosition(), bp->getAnzahl());
                    }

                    derAuftraegeManager->removeAuftrag(auftrag);
                }
            }
            else
            {
                std::cout << "Nicht gen�gend Items im Inventar f�r Auftrag 2." << std::endl;
            }
        }
    );

    dasFenster.addKnopf(
        "Beende Auftrag 3",
        newFont,  // Font �bergeben
        [this, player]()
        {
            if (checkAuftragErf�llbar(2))
            {

                Auftrag* auftrag = derAuftraegeManager->getAuftrag(2);

                if (auftrag != nullptr)
                {
                    // Entferne die Items
                    for (int i = 0; i < auftrag->getAnzahlBestellopsitionen(); ++i)
                    {
                        Bestellposition* bp = auftrag->getBestellposition(i);
                        devInventar->removeItems(bp->getPosition(), bp->getAnzahl());
                    }

                    derAuftraegeManager->removeAuftrag(auftrag);
                }
            }
            else
            {
                std::cout << "Nicht gen�gend Items im Inventar f�r Auftrag 3." << std::endl;
            }
        }
    );

    dasFenster.addKnopf(
        "Beende Auftrag 4",
        newFont,  // Font �bergeben
        [this, player]()
        {
            if (checkAuftragErf�llbar(3))
            {

                Auftrag* auftrag = derAuftraegeManager->getAuftrag(3);

                if (auftrag != nullptr)
                {
                    // Entferne die Items
                    for (int i = 0; i < auftrag->getAnzahlBestellopsitionen(); ++i)
                    {
                        Bestellposition* bp = auftrag->getBestellposition(i);
                        devInventar->removeItems(bp->getPosition(), bp->getAnzahl());
                    }

                    derAuftraegeManager->removeAuftrag(auftrag);
                }
            }
            else
            {
                std::cout << "Nicht gen�gend Items im Inventar f�r Auftrag 4." << std::endl;
            }
        }
    );

    dasFenster.addKnopf(
        "Beende Auftrag 5",
        newFont,  // Font �bergeben
        [this, player]()
        {
            if (checkAuftragErf�llbar(4))
            {

                Auftrag* auftrag = derAuftraegeManager->getAuftrag(4);

                if (auftrag != nullptr)
                {
                    // Entferne die Items
                    for (int i = 0; i < auftrag->getAnzahlBestellopsitionen(); ++i)
                    {
                        Bestellposition* bp = auftrag->getBestellposition(i);
                        devInventar->removeItems(bp->getPosition(), bp->getAnzahl());
                    }

                    derAuftraegeManager->removeAuftrag(auftrag);
                }
                
            }
            else
            {
                std::cout << "Nicht gen�gend Items im Inventar f�r Auftrag 5." << std::endl;
            }
        }
    );

    dasFenster.addKnopf(
        "Schlie�en",
        newFont,  // Font �bergeben
        [this, player]()
        {
            dasFenster.toggle();
        }
    );
}

bool Ausgabe::checkAuftragErf�llbar(int auftragIndex)
{
    if (!derAuftraegeManager || !devInventar)
        return false;

    Auftrag* auftrag = derAuftraegeManager->getAuftrag(auftragIndex);
    if (!auftrag)
        return false;

    for (int i = 0; i < auftrag->getAnzahlBestellopsitionen(); ++i)
    {
        Bestellposition* bp = auftrag->getBestellposition(i);
        if (!bp)
            continue;

        ItemID id = bp->getPosition();
        int benoetigteAnzahl = bp->getAnzahl();
        int vorhandeneAnzahl = devInventar->getItemAnzahl(id);

        if (vorhandeneAnzahl < benoetigteAnzahl)
        {
            return false; // Mindestens ein Item fehlt oder nicht genug vorhanden
        }
    }

    return true; // Alle Bedingungen erf�llt
}