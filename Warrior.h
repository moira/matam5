#ifndef MATAM_HW5_WET_WARRIOR_H
#define MATAM_HW5_WET_WARRIOR_H

#include "Player.h"
//warrior can be a rider or a regular warrior
//rider makes a step of 5 instead of 1
//warrior's weapon cannot target level
class Warrior : public Player {
    bool rider;
//copy a warrior and return a Player* pointer to it
    Player* copy() override;
public:
//warrior constuctor
//throws IllegalWeapon if weapon targets level
    explicit Warrior(const string& name, const Weapon& weapon, bool rider);
//warrior copy constructor
    Warrior(const Warrior&) = default;
//warrior assignment operator
    Warrior& operator=(const Warrior&) = default;
//warrior destructor
    ~Warrior() throw() override = default;
//change location (add 1 for regular warrior, 5 for rider)
    void makeStep() override;
};

#endif //MATAM_HW5_WET_WARRIOR_H
