#include "Troll.h"

using namespace mtm;

Troll::Troll(const string& name, const Weapon& weapon, int maxLife): 
            Player(name, weapon) {
    if (maxLife <= 0) {
        throw InvalidParam();
    }
    this->maxLife=maxLife;
}

Player* Troll::copy() {
    return new Troll(name, weapon, maxLife);
}

void Troll::addLife() {
    if (life < maxLife) {
        life++;
    }
}

void Troll::makeStep() {
    location += 2;
    addLife();
}