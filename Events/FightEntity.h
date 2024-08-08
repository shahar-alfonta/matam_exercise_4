#ifndef HW4_FIGHTENTITY_H
#define HW4_FIGHTENTITY_H

#include "vector"
#include "string"
#include "memory"

using namespace std;

class FightEntity {
public:
    virtual int getCombatPower() const = 0;

    virtual int getLoot() const = 0;

    virtual int getDamage() const = 0;

    virtual void postFightChanges();

    virtual string getEntityTypeMessage() const = 0;

    string getDescription() const;
};


class MonsterPack : public FightEntity {
private:
    int membersAmount;
    unique_ptr<unique_ptr<FightEntity>[]> members;

public:
    MonsterPack(int membersAmount);

    int getCombatPower() const override;

    int getLoot() const override;

    int getDamage() const override;

    void postFightChanges() override;

    string getEntityTypeMessage() const override;

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
    string getEntityTypeMessage() const override;
};

class Slime : public Monster {
protected:
    int combatPower = 12;
    int loot = 5;
    int damage = 25;
public:
    string getEntityTypeMessage() const override;
};

class Balrog : public Monster {
protected:
    int combatPower = 15;
    int loot = 100;
    int damage = 9001;
public:
    string getEntityTypeMessage() const override;

    void postFightChanges() override;
};

#endif //HW4_FIGHTENTITY_H
