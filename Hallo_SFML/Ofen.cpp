#include "Ofen.h"

Ofen::Ofen(float x, float y) : GeraetBase(x, y, 50, 50) {
    setupButtons(); // Buttons setzen nach Konstruktion
}

void Ofen::setupButtons() {
    dasFenster.addKnopf(Knopf(shape.getPosition().x + 10, shape.getPosition().y + 10, 80, 30, "Start", [this]() {
        cout << "Ofen startet!" << endl;
        }));

    dasFenster.addKnopf(Knopf(shape.getPosition().x + 10, shape.getPosition().y + 50, 80, 30, "Stop", [this]() {
        cout << "Ofen stoppt!" << endl;
        }));
}
