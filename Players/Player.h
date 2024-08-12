
#pragma once

#include <string>

#include "exception.h"

using std::string;


enum Character {
    RESPONSIBLE, RISK_TAKING
};

class Player {
    string name;
    Character chracter;

protected:
    unsigned int level = 1;
    unsigned int force = 5;
    unsigned int currentHP = 100;
    unsigned int maxHP = 100;
    unsigned int coins = 10;

public:
    Player(string name, string characterType);
    /**
     * Gets the description of the player
     *
     * @return - description of the player
    */
    string getDescription() const;

    /**
     * Gets the name of the player
     *
     * @return - name of the player
    */
    string getName() const;

    string getCharacter() const;

    /**
     * Gets the current level of the player
     *
     * @return - level of the player
    */
    int getLevel() const;

    /**
     * Gets the of force the player has
     *
     * @return - force points of the player
    */
    int getForce() const;

    /**
     * Gets the amount of health points the player currently has
     *
     * @return - health points of the player
    */
    int getHealthPoints() const;

    /**
     * Gets the amount of coins the player has
     *
     * @return - coins of the player
    */
    int getCoins() const;

    void setCoins(int newCoins);

    void setForce(int force);

    void setHp(int hp);

     virtual int combatPower() const;

     void levelUp();

    virtual string getJob() const = 0;
};

class Warrior : public Player {
    int maxHP = 150;

public:
    Warrior(string name, string characterType);
    int combatPower() const override;

    string getJob() const override;
};

class Archer : public Player {
    int coins = 20;

public:
    Archer(string name, string characterType);
    string getJob() const override;

};

class Magician : public Player {
public:
    Magician(string name, string characterType);
    string getJob() const override;
};