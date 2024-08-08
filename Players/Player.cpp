
#include "Player.h"

int Player::combatPower() const{
    return level + force;
}

int Player::getCoins() const {
    return coins;
}

void Player::setHp(int hp) {
    if(hp < maxHP && hp > 0){
        currentHP = hp;
    }
}

void Player::setForce(int newForce) {
    if (newForce >= 0){
        force = newForce;
    }
}

int Player::getHealthPoints() const {
    return currentHP;
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

    string description = name + "," + this->getJob() + "with" + this->getCharacter() + "character" + "(level" + std::to_string(level) + ", force" + std::to_string(force) + ")";
}

string Player::getCharacter() const {
    switch (chracter) {
        case RESPONSIBLE: return "Responsible";
        case RISK_TAKING: return "RiskTaking";
    }
}

Player::Player(string name, string characterType){
    if(name.size() > 15){
        throw Invalid_File("Invalid Players File");
    }
    name = name;
    if (characterType == "Responsible"){
        chracter = RESPONSIBLE;
    } else if(characterType == "RiskTaking"){
        chracter = RISK_TAKING;
    }else{
        throw Invalid_File("Invalid Players File");
    }
}

void Player::setCoins(int newCoins) {
    if (newCoins > 0){
        coins = newCoins;
    }
}

int Warrior::combatPower() const {
    return force*2 + level;
}

string Warrior::getJob() const {
    return "Warrior";
}


string Archer::getJob() const{
    return "Archer";
}

string Magician::getJob() const {
    return "Magician";
}
