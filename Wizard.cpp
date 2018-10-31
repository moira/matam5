#include "Wizard.h"

using namespace mtm;

Wizard::Wizard(const string &name, const Weapon &weapon, int range): 
            Player(name, weapon) {
    if (range < 0) {
        throw InvalidParam();
    }
    if (weapon.getTarget() == LIFE) {
        throw IllegalWeapon();
    }
    this->range=range;
}

Player* Wizard::copy() {
    return new Wizard(name, weapon, range);
}

bool Wizard::canAttack(const Player& player) {
    int distance = abs(location - player.location);
    if (distance == 0 || distance > range) {
        return false;
    }
    return (weapon > player.weapon);
}
