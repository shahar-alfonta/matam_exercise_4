
#include "Player.h"

Player::Player(string name, string characterType) : name(name) {
    if (name.size() > 15) {
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
        case RISK_TAKING:
            characterStr = "RiskTaking";
    }

    string description =
            name + ", " + this->getJob() + " with " + characterStr + " character " + "(level " +
            std::to_string(level) + ", force " + std::to_string(force) + ")";
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

int Player::getLevel() const {
    return level;
}

int Player::getForce() const {
    return force;
}

int Player::combatPower() const {
    return level + force;
}

int Player::getHealthPoints() const {
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
    if (hp < maxHP && hp > 0) {
        currentHP = hp;
    }
}

void Player::setForce(int newForce) {
    if (newForce >= 0) {
        force = newForce;
    }
}

int Warrior::combatPower() const {
    return force * 2 + level;
}

void Player::levelUp() {
    level++;
}

string Warrior::getJob() const {
    return "Warrior";
}

string Archer::getJob() const {
    return "Archer";
}

string Magician::getJob() const {
    return "Magician";
}
