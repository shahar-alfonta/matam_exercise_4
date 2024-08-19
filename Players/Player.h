
#pragma once

#include <string>

#include "exception.h"

using std::string;


enum Character {
    RESPONSIBLE, RISK_TAKING
};

enum FightRange {
    CLOSE, FAR
};

class Player {
protected:
    string name;
    Character character;
    FightRange fightRange;
    bool isMagic;
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

    Character getCharacter() const;

    FightRange getFightRange() const;

    bool getIsMagic() const;

    /**
     * Gets the current level of the player
     *
     * @return - level of the player
    */
    unsigned int getLevel() const;

    /**
     * Gets the of force the player has
     *
     * @return - force points of the player
    */
    unsigned int getForce() const;

    /**
     * Gets the amount of health points the player currently has
     *
     * @return - health points of the player
    */
    unsigned int getHealthPoints() const;

    /**
     * Gets the amount of coins the player has
     *
     * @return - coins of the player
    */
    unsigned int getCoins() const;

    unsigned int getMaxHealthPoints() const;

    void setCoins(unsigned int newCoins);

    void setHealthPoints(int hp);

    void setForce(int force);

    virtual unsigned int combatPower() const;

    void levelUp();

    virtual string getJob() const = 0;
};

class Warrior : public Player {
    unsigned int maxHP = 150;

public:
    Warrior(string name, string characterType);

    unsigned int combatPower() const override;

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