
#include "Player.h"

int Player::combatPower() const {
    return level + force;
}

unsigned int Player::getCoins() const {
    return coins;
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

int Player::getHealthPoints() const {
    return currentHP;
}

void Player::levelUp() {
    level++;
}

int Player::getForce() const {
    return force;
}

int Player::getLevel() const {
    return level;
}

string Player::getName() const {
    return name;
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

Character Player::getCharacter() const {
    return character;
}


FightRange Player::getFightRange() const {
    return fightRange;
}

bool Player::getIsMagic() const {
    return isMagic;
}

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

void Player::setCoins(unsigned int newCoins) {
    coins = newCoins;
}

unsigned int Player::getMaxHealthPoints() const {
    return maxHP;
}

int Warrior::combatPower() const {
    return force * 2 + level;
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
