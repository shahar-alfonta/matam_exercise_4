#ifndef HW4_FIGHTENTITY_H
#define HW4_FIGHTENTITY_H

#pragma once

#include "unordered_map"
#include "vector"
#include "string"
#include "memory"

#define SNAIL "Snail"
#define SLIME "Slime"
#define BALROG "Balrog"
#define PACK "Pack"

class FightEntity {
public:
    virtual int getCombatPower() const = 0;

    virtual int getLoot() const = 0;

    virtual int getDamage() const = 0;

    virtual void postFightChanges();

    virtual std::string getEntityTypeMessage() const = 0;

    std::string getDescription() const;
};


class MonsterPack : public FightEntity {
private:
    std::vector<std::shared_ptr<FightEntity>> members;

public:
    MonsterPack(std::istringstream &wordStream);

    int getCombatPower() const override;

    int getLoot() const override;

    int getDamage() const override;

    void postFightChanges() override;

    std::string getEntityTypeMessage() const override;
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
public:
    Snail(std::istringstream &wordStream);

    std::string getEntityTypeMessage() const override;
};

class Slime : public Monster {
public:
    Slime(std::istringstream &wordStream);

    std::string getEntityTypeMessage() const override;
};

class Balrog : public Monster {
public:
    Balrog(std::istringstream &wordStream);

    std::string getEntityTypeMessage() const override;

    void postFightChanges() override;
};

std::shared_ptr<FightEntity> fightEntityFactory(std::istringstream &wordStream, std::string &firstWord);

typedef std::shared_ptr<FightEntity> (*EntitiesFactoryFunction)(std::istringstream &);

extern std::unordered_map<std::string, EntitiesFactoryFunction> entitiesFactoryMap;


#endif //HW4_FIGHTENTITY_H
