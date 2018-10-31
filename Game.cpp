#include <utility>
#include <algorithm>

#include "Game.h"
#include "mtm_exceptions.h"
#include "Warrior.h"
#include "Wizard.h"
#include "Troll.h"

using namespace mtm;
using std::swap;

Game::Game(int maxPlayer) : maxPlayer(maxPlayer), numPlayers(0) {
    players.reserve((unsigned long)maxPlayer);
}

Game::Game(const Game& game) : maxPlayer(game.maxPlayer), 
                numPlayers(game.numPlayers) {
    players.reserve((unsigned long)game.maxPlayer);
    for (auto it = game.players.begin(); it != game.players.end(); it++) {
        players.emplace_back((*it)->copy());
    }
}

Game& Game::operator=(const Game& game) {
    if (this == &game) {
        return *this;
    }
    players.empty();
//    Copy-create new players of a needed type
    for (auto it = game.players.begin(); it != game.players.end(); it++) {
        players.emplace_back((*it)->copy());
    }
    numPlayers = game.numPlayers;
    maxPlayer = game.maxPlayer;
    return *this;
}

GameStatus Game::addPlayer(const string& playerName, const string& weaponName,
                           Target target, int hitStrength) {
    for (int i = 0; i < numPlayers; i++) {
        if (players[i]->isPlayer(playerName)) {
            return NAME_ALREADY_EXISTS;
        }
    }
    if (numPlayers == maxPlayer) {
        return GAME_FULL;
    }
    try {
        addWarrior(playerName, weaponName, target, hitStrength, false);
    } catch(const IllegalWeapon& exception) {
        return ILLEGAL_WEAPON;
    }
    return SUCCESS;
}

void Game::insertionSort() {
    int i = numPlayers;
    while (i > 0) {
        if ((*players[i]) < (*players[i-1])) {
            swap(players[i], players[i-1]);
        }
        i--;
    }
    numPlayers++;
}

void Game::addWarrior(const string& playerName, const string& weaponName,
                      Target target, int hitStrength, bool rider) {
    for (auto it = players.begin(); it != players.end(); it++) {
        if ((*it)->isPlayer(playerName)) {
            throw NameAlreadyExists();
        }
    }
    if (numPlayers == maxPlayer) {
        throw GameFull();
    }
    players.emplace_back(new Warrior(playerName, Weapon(weaponName, target, 
        hitStrength), rider));
    insertionSort();
}

void Game::addWizard(const string& playerName, const string& weaponName,
        Target target, int hitStrength, int range) {
    for (auto it = players.begin(); it != players.end(); it++) {
        if ((*it)->isPlayer(playerName)) {
            throw NameAlreadyExists();
        }
    }
    if (numPlayers == maxPlayer) {
        throw GameFull();
    }
    players.emplace_back(new Wizard(playerName, Weapon(weaponName, target, 
        hitStrength), range));
    insertionSort();
}

void Game::addTroll(const string& playerName, const string& weaponName, 
    Target target, int hitStrength, int maxLife) {
    for (auto it = players.begin(); it != players.end(); it++) {
        if ((*it)->isPlayer(playerName)) {
            throw NameAlreadyExists();
        }
    }
    if (maxLife <= 0) {
        throw InvalidParam();
    }
    if (numPlayers == maxPlayer) {
        throw GameFull();
    }
    players.emplace_back(new Troll(playerName, Weapon(weaponName, target, 
        hitStrength), maxLife));
    insertionSort();
}

GameStatus Game::nextLevel(const string& playerName) {
    for (int i = 0; i < numPlayers; i++) {
        if (players[i]->isPlayer(playerName)) {
            players[i]->nextLevel();
            return SUCCESS;
        }
    }
    return NAME_DOES_NOT_EXIST;
}

GameStatus Game::makeStep(const string& playerName) {
    for (int i = 0; i < numPlayers; i++) {
        if (players[i]->isPlayer(playerName)) {
            players[i]->makeStep();
            return SUCCESS;
        }
    }
    return NAME_DOES_NOT_EXIST;
}

GameStatus Game::addLife(const string& playerName) {
    for (int i = 0; i < numPlayers; i++) {
        if (players[i]->isPlayer(playerName)) {
            players[i]->addLife();
            return SUCCESS;
        }
    }
    return NAME_DOES_NOT_EXIST;
}

GameStatus Game::addStrength(const string& playerName, int strengthToAdd) {
    if (strengthToAdd < 0) {
        return INVALID_PARAM;
    }
    for (int i = 0; i < numPlayers; i++) {
        if (players[i]->isPlayer(playerName)) {
            players[i]->addStrength(strengthToAdd);
            return SUCCESS;
        }
    }
    return NAME_DOES_NOT_EXIST;
}

void Game::deletePlayer(int playerNum) {
    players.erase(players.begin() + playerNum);
    numPlayers--;
}

GameStatus Game::fight(const string& playerName1, const string& playerName2) {
    int playerCount = 0;
    int playerIndices[2];
    for (int i = 0; i < numPlayers; i++) {
        if (players[i]->isPlayer(playerName1) &&
            players[i]->isPlayer(playerName2)) {
            return FIGHT_FAILED; // Players cannot fight themselves,
                                 // but the name is there.
        } else if (players[i]->isPlayer(playerName1) ||
                   players[i]->isPlayer(playerName2)) {
            playerIndices[playerCount++] = i;
        }
    }
    if (playerCount != 2) {
        throw NameDoesNotExist();
    }
    if (!players[playerIndices[0]]->fight(*(players[playerIndices[1]]))) {
        return FIGHT_FAILED;
    }
    for (int i = 0; i < 2; i++) {
        if (!players[playerIndices[i]]->isAlive()) {
            deletePlayer(playerIndices[i]);
            break; // Players cannot kill each other in this game.
            // Checking the second player after the death of the 1st
            // can lead to a segfault if she was the last in the list.
        }
    }
    return SUCCESS;
}

std::ostream& operator<<(std::ostream& os, Game& game) {
    int j = 0;
    std::for_each(game.players.begin(), game.players.end(), [&os, &j]
        (const unique_ptr<Player>& player_ptr) {
        os << "player " << j++ << ": " << *player_ptr << "," << std::endl;
    });
    return os;
}

class DetectWeakWeapon {
    int weaponStrength;
public:
    explicit DetectWeakWeapon(int weaponStrength): 
    weaponStrength(weaponStrength) {}
    bool operator()(const Player& player) const {
        return player.weaponIsWeak(weaponStrength);
    }
};

bool Game::removeAllPlayersWithWeakWeapon(int weaponStrength) {
    DetectWeakWeapon detector = DetectWeakWeapon(weaponStrength);
    return removePlayersIf(detector);
}
