#include "Player.h"
using std::string;

Player::Player(const string& name, const Weapon& weapon): 
    name(name), weapon(weapon), life(1), level(1), strength(1), location(0) {}

ostream& operator<<(ostream& os, const Player& player) {
    return os << "{player name: " << player.name << ", weapon: " << 
    player.weapon << "}";
}
void Player::nextLevel() {
    level++;
}
bool Player::isPlayer(const string& playerName) const {
    return name == playerName;
}
void Player::makeStep() {
    location++;
}
void Player::addLife() {
    life++;
}
void Player::addStrength(int strengthToAdd) {
    strength += strengthToAdd;
}
bool Player::isAlive() const {
    return (life > 0) && (level > 0) && (strength > 0);
}

bool Player::canAttack(const Player& player) {
//    General case:
//    1. Must be in the same cell
//    2. Weapon must be stronger
    return (location == player.location) && (weapon > player.weapon);
}

bool Player::weaponIsWeak(int weaponMinStrength) const {
    return weapon.getValue() < weaponMinStrength;
}

bool operator<(const Player& player1, const Player& player2) {
    return (player1.name < player2.name);
}

bool operator>(const Player& player1, const Player& player2) {
    return (player1.name > player2.name);
}

bool Player::fight(Player& player) {
    if (!canAttack(player) && !player.canAttack(*this)) {
        return false;
    }
    Player &beater = canAttack(player) ? *this : player;
    Player &beatee = player.canAttack(*this) ? *this : player;
    int hitStrength = beater.weapon.getHitStrength();
    Target target = beater.weapon.getTarget();
    switch (target) {
        case LEVEL:
            beatee.level -= hitStrength;
            if (beatee.level < 0) {
                beatee.level = 0;
            }
            break;
        case STRENGTH:
            beatee.strength -= hitStrength;
            if (beatee.strength < 0) {
                beatee.strength = 0;
            }
            break;
        case LIFE:
            beatee.life -= hitStrength;
            if (beatee.life < 0) {
                beatee.life = 0;
            }
            break;
    }
    return true;
}

//Player& Player::operator=(const Player& player) {
//    if (this != &player) {
//        this->name = player.name;
//        this->weapon = Weapon(player.weapon); // Will make a copy
//        this->life = player.life;
//        this->level = player.level;
//        this->strength = player.strength;
//        this->location = player.location;
//    }
//    return *this;
//}