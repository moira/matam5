#include "Weapon.h"

using std::string;

Weapon::Weapon(const string& name, Target target, int hitStrength): 
    name(name), target(target), hitStrength(hitStrength) {}

Target Weapon::getTarget() const {
    return target;
}

int Weapon::getHitStrength() const {
    return hitStrength;
}

int Weapon::getValue() const {
    return hitStrength * (target+1);
}

bool operator== (const Weapon& weapon1, const Weapon& weapon2) {
    return weapon1.getValue() == weapon2.getValue();
}

bool operator!= (const Weapon& weapon1, const Weapon& weapon2) {
    return weapon1.getValue() != weapon2.getValue();
}

bool operator> (const Weapon& weapon1, const Weapon& weapon2) {
    return weapon1.getValue() > weapon2.getValue();
}

bool operator< (const Weapon& weapon1, const Weapon& weapon2) {
    return weapon1.getValue() < weapon2.getValue();
}

ostream& operator<<(ostream& os, const Weapon& weapon) {
    return os << "{weapon name: " << weapon.name << ", weapon value:" << 
    weapon.getValue() << "}";
}