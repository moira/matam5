#ifndef MATAM_HW5_WET_WIZARD_H
#define MATAM_HW5_WET_WIZARD_H

#include "Player.h"
//wizard can only hit a player who is <= range removed from them
//and with whom they are not in the same cell
//wizard can only use weapon not targeting life
class Wizard : public Player {
//the wizard's range
    int range;
//copy wizard and return a Player* pointer to it
    Player* copy() override;
//function checking if the wizard can attack another player
    bool canAttack(const Player& player) override;
public:
//wizard constructor
//throws IllegalWeapon if weapon targets life 
//throws InvalidParam if range is negative
    explicit Wizard(const string& name, const Weapon& weapon, int range);
//wizard copy constructor
    Wizard(const Wizard& wizard) = default;
//wizard assignment operator
    Wizard& operator=(const Wizard&) = default;
//wizard destructor;
    ~Wizard() throw() override = default;
};

#endif //MATAM_HW5_WET_WIZARD_H
