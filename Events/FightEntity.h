#ifndef HW4_FIGHTENTITY_H
#define HW4_FIGHTENTITY_H

#include "vector"
#include "string"

using namespace std;

class FightEntity {
public:
    virtual int getCombatPower() const = 0;

    virtual int getLoot() const = 0;

    virtual int getDamage() const = 0;

    virtual void postFightChanges();

    virtual string getEntityType() const = 0;

    string getDescription() const;
};


class MonsterPack : public FightEntity {
private:
    std::vector<FightEntity *> entities;  // TODO: probably a dynamically created array

public:

    int getCombatPower() const override;

    int getLoot() const override;

    int getDamage() const override;

    void postFightChanges() override;

    string getEntityType() const override;

    int getMembersAmount() const;
};


class Monster : public FightEntity {
protected:
    int combatPower;
    int loot;
    int damage;
public:
    int getCombatPower() const override;

    int getLoot() const override;

    int getDamage() const override;
};


class Snail : public Monster {
protected:
    int combatPower = 5;
    int loot = 2;
    int damage = 10;
public:
    string getEntityType() const override;
};

class Slime : public Monster {
protected:
    int combatPower = 12;
    int loot = 5;
    int damage = 25;
public:
    string getEntityType() const override;
};

class Balrog : public Monster {
protected:
    int combatPower = 15;
    int loot = 100;
    int damage = 9001;
public:
    string getEntityType() const override;

    void postFightChanges() override;
};

#endif //HW4_FIGHTENTITY_H
