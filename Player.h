#ifndef CALLOFDUTY_PLAYER_H
#define CALLOFDUTY_PLAYER_H

#include "Weapon.h"

using std::string;

//Player object fields: name – the name of the player, level – the player's
//level, life – the number of player's lives, strength – the player's current
//strength, location – the current location of the player, player_type -
//the player's subclass
class Player {
protected:
    string name;
    Weapon weapon;
    int life;
    int level;
    int strength;
    int location;
//receives another player as argument and checks if the current player
//can attack them
    virtual bool canAttack(const Player& player);
    virtual Player* copy() = 0;
    friend class Game;
    friend class Wizard;
    friend class Warrior;
    friend class Troll;
//player constructor
    Player(const string& name, const Weapon& weapon);
//player copy constructor
    Player(const Player& player) = default;
public:
//player destructor; 
    virtual ~Player() = default;
//Prints the player's name and their weapon's name
    friend ostream& operator<<(ostream& os, const Player& player);
//Assigns a player to a variable pointing to another player
    Player& operator=(const Player& player) = default;
//Promotes the player to the next level
    void nextLevel();
//Checks if the given string is the player's name
    bool isPlayer(const string& playerName) const;
//Moves the player to the next location
    virtual void makeStep();
//Increments the player's number of lives
    virtual void addLife();
//Increments the player's strength by the given integer
    void addStrength(int strengthToAdd);
//Returns true if the player is in game (life, strength, and level are positive) 
//and false otherwise
    bool isAlive() const;
//Returns true is the player's weapon's strength is less then the given integer
    bool weaponIsWeak(int weaponMinStrength) const;
//Compare two players by name lexicographically
    friend bool operator<(const Player& player1, const Player& player2);
    friend bool operator>(const Player& player1, const Player& player2);
//Returns true if the player can fight with the player that is passed as
//argument and false otherwise (if they are in different location or have
//weapon of the same value)
    bool fight(Player& player);
};

#endif //CALLOFDUTY_PLAYER_H
