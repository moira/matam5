#ifndef MATAM_HW5_WET_TROLL_H
#define MATAM_HW5_WET_TROLL_H

#include "Player.h"
//troll makes a step of 2 instead of 1
//when makeStep is called, a life is added
//each troll has a predestined maximal life value
class Troll : public Player {
    int maxLife;
//copies troll and returns a Player* pointer to it
    Player* copy() override;
public:
//troll constructor
//throws InvalidParam if maxLife is not positive
    explicit Troll(const string& name, const Weapon& weapon, int maxLife);
//troll copy constructor
    Troll(const Troll&) = default;
//troll assignment operator
    Troll& operator=(const Troll&) = default;
//troll destructor
    ~Troll() throw() override = default;
//life is added upto maximal life is reached
    void addLife() override;
//step of 2 instead of 1, life is added when a step is made
    void makeStep() override;
};

#endif //MATAM_HW5_WET_TROLL_H
