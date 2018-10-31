#include "Warrior.h"

using namespace mtm;

Warrior::Warrior(const string& name, const Weapon& weapon, bool rider): 
            Player(name, weapon) {
    if (weapon.getTarget() == LEVEL) {
        throw IllegalWeapon();
    }
    this->rider = rider;
}

Player* Warrior::copy() {
    return new Warrior(name, weapon, rider);
}

void Warrior::makeStep() {
    if (this->rider) {
        location += 5;
    } else {
        location++;
    }
}