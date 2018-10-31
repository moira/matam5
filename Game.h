#ifndef CALLOFDUTY_GAME_H
#define CALLOFDUTY_GAME_H

#include <vector>
#include <memory>
#include <algorithm>
#include "mtm_exceptions.h"
#include "Wizard.h"
#include "Troll.h"
#include "Warrior.h"

using std::string;
using std::vector;
using std::unique_ptr;

//Possible errors returned by functions as GameStatus:
//INVALID_PARAM – an invalid parameter was passed to a function,
//NAME_ALREADY_EXISTS – a player already belongs to the game,
//GAME_FULL – the number of the players in the game does not allow to add
//another player,
//FIGHT_FAILED – players cannot fight because they are in different locations
//or their weapon has the same value,
//ILLEGAL_WEAPON – an attempt was made to create a player 
//with an unsuitable weapon (warrior with weapon targeting level or 
//wizard with weapon targeting life),
//SUCCESS – no error*/
enum GameStatus {
    INVALID_PARAM,
    ILLEGAL_WEAPON,
    NAME_ALREADY_EXISTS,
    GAME_FULL,
    NAME_DOES_NOT_EXIST,
    FIGHT_FAILED,
    SUCCESS
};

//Game fields:
//maxPlayer – the maximal number of players in the game,
//numPlayers – the current number of players in the game,
//players – a vector of players currently in game
class Game {
    int maxPlayer;
    int numPlayers;
    vector<unique_ptr<Player>> players;
//Given a player's number, deletes the player
    void deletePlayer(int playerNum);
//Game sorting function
    void insertionSort();
public:
//Initializes a game with a given maximal number of players
    explicit Game(int maxPlayer);
//Initializes a game by copying it from another game
    Game(const Game& game);
//Game assignment operator
    Game& operator=(const Game&);
//Destroys the game and all its contents
    ~Game() = default;
//Adds a player to the game given the player's name and the characteristics of
//their weapon: name, target, strength
//In the new version, creates a non-rider warrior
    GameStatus addPlayer(const string& playerName, const string& weaponName, 
        Target target, int hitStrength);
//Adds wizard (needs an additional range argument)
    void addWizard(const string& playerName, const string& weaponName, 
        Target target, int hitStrength, int range);
//Adds troll (needs an additional maxLife argument)
    void addTroll(const string& playerName, const string& weaponName, 
        Target target, int hitStrength, int maxLife);
//Adds warrior (needs an additional rider argument)
    void addWarrior(const string& playerName, const string& weaponName, 
        Target target, int hitStrength, bool rider);
//Promotes the player with the given name to the next level
    GameStatus nextLevel(const string& playerName);
//Promotes the player with the given name to the next location
    GameStatus makeStep(const string& playerName);
//Adds life to the given player
    GameStatus addLife(const string& playerName);
//Given a player and a strength to add as an integer, adds the strength to
//the player
    GameStatus addStrength(const string& playerName, int strengthToAdd);
//Removes from the game all players whose weapon's strength is less than
//the passed integer; removes true if at least one player was removed and
//false otherwise
    bool removeAllPlayersWithWeakWeapon(int weaponStrength);
//Makes two players fight if they are in the same location, adjusts the game
//according to the outcome
    GameStatus fight(const string& playerName1, const string& playerName2);
//Prints the players in alphabetic order
    friend ostream& operator<<(ostream& os, Game& game);
//Player filter
    template <class FCN>
    bool removePlayersIf(FCN& fcn) {
        players.erase(std::remove_if(players.begin(), players.end(),
            [&fcn](const unique_ptr<Player>& player_ptr) {
            return fcn((const Player&) *player_ptr); }), players.end());
        if ((int) players.size() != numPlayers) {
            numPlayers = (int) players.size();
            return true;
        } else {
            return false;
        }
    }
};

#endif //CALLOFDUTY_GAME_H
