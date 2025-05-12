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
        newFont,  // Font übergeben
        [this, player]()
        {
            cout << "Klickt auf Auftrag1" << endl;
            versucheAuftragZuErfüllen(1);
            
            
            //if (checkAuftragErfüllbar(0))
            //{
            //    Auftrag* auftrag = derAuftraegeManager->getAuftrag(0);
            //
            //    if (auftrag != nullptr)
            //    {
            //        // Entferne die Items
            //        for (int i = 0; i < auftrag->getAnzahlBestellopsitionen(); ++i)
            //        {
            //            Bestellposition* bp = auftrag->getBestellposition(i);
            //            devInventar->removeItems(bp->getPosition(), bp->getAnzahl());
            //        }
            //
            //        derAuftraegeManager->removeAuftrag(auftrag);
            //    }
            //}
            //else
            //{
            //    std::cout << "Nicht genügend Items im Inventar für Auftrag 1." << std::endl;
            //}
            
        }
    );

    dasFenster.addKnopf(
        "Beende Auftrag 2",
        newFont,  // Font übergeben
        [this, player]()
        {
            cout << "Klickt auf Auftrag2" << endl;
            versucheAuftragZuErfüllen(2);


            //if (checkAuftragErfüllbar(1))
            //{

            //    Auftrag* auftrag = derAuftraegeManager->getAuftrag(1);

            //    if (auftrag != nullptr)
            //    {
            //        // Entferne die Items
            //        for (int i = 0; i < auftrag->getAnzahlBestellopsitionen(); ++i)
            //        {
            //            Bestellposition* bp = auftrag->getBestellposition(i);
            //            devInventar->removeItems(bp->getPosition(), bp->getAnzahl());
            //        }

            //        derAuftraegeManager->removeAuftrag(auftrag);
            //    }
            //}
            //else
            //{
            //    std::cout << "Nicht genügend Items im Inventar für Auftrag 2." << std::endl;
            //}
        }
    );

    dasFenster.addKnopf(
        "Beende Auftrag 3",
        newFont,  // Font übergeben
        [this, player]()
        {
            cout << "Klickt auf Auftrag3" << endl;
            versucheAuftragZuErfüllen(3);



            //if (checkAuftragErfüllbar(2))
            //{

            //    Auftrag* auftrag = derAuftraegeManager->getAuftrag(2);

            //    if (auftrag != nullptr)
            //    {
            //        // Entferne die Items
            //        for (int i = 0; i < auftrag->getAnzahlBestellopsitionen(); ++i)
            //        {
            //            Bestellposition* bp = auftrag->getBestellposition(i);
            //            devInventar->removeItems(bp->getPosition(), bp->getAnzahl());
            //        }

            //        derAuftraegeManager->removeAuftrag(auftrag);
            //    }
            //}
            //else
            //{
            //    std::cout << "Nicht genügend Items im Inventar für Auftrag 3." << std::endl;
            //}
        }
    );

    dasFenster.addKnopf(
        "Beende Auftrag 4",
        newFont,  // Font übergeben
        [this, player]()
        {
            cout << "Klickt auf Auftrag4" << endl;
            versucheAuftragZuErfüllen(4);



            //if (checkAuftragErfüllbar(3))
            //{

            //    Auftrag* auftrag = derAuftraegeManager->getAuftrag(3);

            //    if (auftrag != nullptr)
            //    {
            //        // Entferne die Items
            //        for (int i = 0; i < auftrag->getAnzahlBestellopsitionen(); ++i)
            //        {
            //            Bestellposition* bp = auftrag->getBestellposition(i);
            //            devInventar->removeItems(bp->getPosition(), bp->getAnzahl());
            //        }

            //        derAuftraegeManager->removeAuftrag(auftrag);
            //    }
            //}
            //else
            //{
            //    std::cout << "Nicht genügend Items im Inventar für Auftrag 4." << std::endl;
            //}
        }
    );

    dasFenster.addKnopf(
        "Beende Auftrag 5",
        newFont,  // Font übergeben
        [this, player]()
        {
            cout << "Klickt auf Auftrag5" << endl;
            versucheAuftragZuErfüllen(5);



            //if (checkAuftragErfüllbar(4))
            //{

            //    Auftrag* auftrag = derAuftraegeManager->getAuftrag(4);

            //    if (auftrag != nullptr)
            //    {
            //        // Entferne die Items
            //        for (int i = 0; i < auftrag->getAnzahlBestellopsitionen(); ++i)
            //        {
            //            Bestellposition* bp = auftrag->getBestellposition(i);
            //            devInventar->removeItems(bp->getPosition(), bp->getAnzahl());
            //        }

            //        derAuftraegeManager->removeAuftrag(auftrag);
            //    }
            //    
            //}
            //else
            //{
            //    std::cout << "Nicht genügend Items im Inventar für Auftrag 5." << std::endl;
            //}
        }
    );

    dasFenster.addKnopf(
        "Schließen",
        newFont,  // Font übergeben
        [this, player]()
        {
            dasFenster.toggle();
        }
    );
}

bool Ausgabe::checkAuftragErfüllbar(int gesuchteID)
{
    if (!derAuftraegeManager || !devInventar)
        return false;

    Auftrag* auftrag = derAuftraegeManager->getAuftragMitID(gesuchteID);
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

    return true; // Alle Bedingungen erfüllt
}


bool Ausgabe::versucheAuftragZuErfüllen(int auftragIndex)
{
    if (checkAuftragErfüllbar(auftragIndex))
    {
        Auftrag* auftrag = derAuftraegeManager->getAuftragMitID(auftragIndex);
        if (auftrag != nullptr)
        {
            // Items aus dem Inventar entfernen
            for (int i = 0; i < auftrag->getAnzahlBestellopsitionen(); ++i)
            {
                Bestellposition* bp = auftrag->getBestellposition(i);
                devInventar->removeItems(bp->getPosition(), bp->getAnzahl());
            }

            // Auftrag entfernen
            derAuftraegeManager->removeAuftrag(auftrag);

            std::cout << "Auftrag " << auftragIndex << " erfolgreich erfüllt und entfernt." << std::endl;
            return true;
        }
        else
        {
            std::cout << "Auftrag mit Index " << auftragIndex << " nicht gefunden." << std::endl;
        }
    }
    else
    {
        std::cout << "Nicht genügend Items im Inventar für Auftrag " << auftragIndex << "." << std::endl;
    }

    return false;
}