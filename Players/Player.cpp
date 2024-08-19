
#include "Player.h"

Player::Player(string name, string characterType) : name(name) {
    if (name.size() > 15 || name.size() < 3) {
        throw Invalid_File("Invalid Players File");
    }
    if (characterType == "Responsible") {
        character = RESPONSIBLE;
    } else if (characterType == "RiskTaking") {
        character = RISK_TAKING;
    } else {
        throw Invalid_File("Invalid Players File");
    }
}

string Player::getDescription() const {
    string characterStr;
    switch (getCharacter()) {
        case RESPONSIBLE:
            characterStr = "Responsible";
            break;
        case RISK_TAKING:
            characterStr = "RiskTaking";
            break;
    }

    string description =
            name + ", " + this->getJob() + " with " + characterStr + " character " + "(level " +
            std::to_string(level) + ", force " + std::to_string(force) + ")";

    return description;
}

string Player::getName() const {
    return name;
}

Character Player::getCharacter() const {
    return character;
}

FightRange Player::getFightRange() const {
    return fightRange;
}

bool Player::getIsMagic() const {
    return isMagic;
}

unsigned int Player::getLevel() const {
    return level;
}

unsigned int Player::getForce() const {
    return force;
}

unsigned int Player::combatPower() const {
    return level + force;
}

unsigned int Player::getHealthPoints() const {
    return currentHP;
}

unsigned int Player::getCoins() const {
    return coins;
}

unsigned int Player::getMaxHealthPoints() const {
    return maxHP;
}

void Player::setCoins(unsigned int newCoins) {
    coins = newCoins;
}

void Player::setHealthPoints(int hp) {
    if (hp < 0) {
        currentHP = 0;
    } else if (hp < maxHP) {
        currentHP = hp;
    } else {
        currentHP = maxHP;
    }
}

void Player::setForce(int newForce) {
    if (newForce >= 0) {
        force = newForce;
    } else {
        force = 0;
    }
}

unsigned int Warrior::combatPower() const {
    return force * 2 + level;
}

void Player::levelUp() {
    level++;
}

Warrior::Warrior(string name, string characterType) : Player(name, characterType) {
    this->maxHP = 150;
    this->currentHP = 150;
}

string Warrior::getJob() const {
    return "Warrior";
}

Archer::Archer(string name, string characterType) : Player(name, characterType) {
    coins = 20;
}

string Archer::getJob() const {
    return "Archer";
}

Magician::Magician(string name, string characterType) : Player(name, characterType) {}


string Magician::getJob() const {
    return "Magician";
}
