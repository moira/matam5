#ifndef CALLOFDUTY_WEAPON_H
#define CALLOFDUTY_WEAPON_H

#include <iostream>
#include <string>

#include "mtm_exceptions.h"

using std::ostream;
using std::string;

//Possible weapon targets
enum Target {
    LEVEL,
    STRENGTH,
    LIFE
};

//Weapon class fields: target (level, strength, or life, as above),
//hit strength as integer (diminishes one of the above when used),
//the name of the weapon.
class Weapon {
    string name;
    Target target;
    int hitStrength;
public:
//Constructor receives the name as a string, the target, and the hit strength
//(see above)
    explicit Weapon(const string& name, Target target, int hitStrength);
//Assigns a weapon to a variable
    Weapon(const Weapon&) = default;
//Deletes a weapon and all the memory that was allocated to it
    ~Weapon() = default;
//Returns the target of the weapon
    Target getTarget() const;
//Returns the hit strength of the weapon
    int getHitStrength() const;
//Returns the value of the weapon: (target + 1)* hit strength
    int getValue() const;
//Prints the name and the value of the weapon
    friend ostream& operator<<(ostream& os, const Weapon& weapon);
//Weapon copy constructor
    Weapon& operator=(const Weapon&) = default;
};

//Compares two weapons by value using getValue()
bool operator==(const Weapon& weapon1, const Weapon& weapon2);
bool operator!=(const Weapon& weapon1, const Weapon& weapon2);
bool operator>(const Weapon& weapon1, const Weapon& weapon2);
bool operator<(const Weapon& weapon1, const Weapon& weapon2);

#endif //CALLOFDUTY_WEAPON_H
