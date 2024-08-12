#ifndef HW4_FIGHTENTITY_H
#define HW4_FIGHTENTITY_H

#include "unordered_map"
#include "vector"
#include "string"
#include "memory"

#define SNAIL "Snail"
#define SLIME "Slime"
#define BALROG "Balrog"
#define PACK "Pack"

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
    vector<shared_ptr<FightEntity>> members;

public:
    MonsterPack(istringstream &wordStream);

    int getCombatPower() const override;

    int getLoot() const override;

    int getDamage() const override;

    void postFightChanges() override;

    string getEntityTypeMessage() const override;
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
    Snail(istringstream &wordStream);

    string getEntityTypeMessage() const override;
};

class Slime : public Monster {
protected:
    int combatPower = 12;
    int loot = 5;
    int damage = 25;
public:
    Slime(istringstream &wordStream);

    string getEntityTypeMessage() const override;
};

class Balrog : public Monster {
protected:
    int combatPower = 15;
    int loot = 100;
    int damage = 9001;
public:
    Balrog(istringstream &wordStream);

    string getEntityTypeMessage() const override;

    void postFightChanges() override;
};

typedef std::shared_ptr<FightEntity> (*EntitiesFactoryFunction)(istringstream &);

unordered_map<string, EntitiesFactoryFunction> entitiesFactoryMap{
        {SNAIL,  [](istringstream &wordStream) -> shared_ptr<FightEntity> {
            return make_shared<Snail>(wordStream);
        }},
        {SLIME,  [](istringstream &wordStream) -> shared_ptr<FightEntity> {
            return make_shared<Slime>(wordStream);
        }},
        {BALROG, [](istringstream &wordStream) -> shared_ptr<FightEntity> {
            return make_shared<Balrog>(wordStream);
        }},
        {PACK,   [](istringstream &wordStream) -> shared_ptr<FightEntity> {
            return make_shared<MonsterPack>(wordStream);
        }}
};

std::shared_ptr<FightEntity> fightEntityFactory(istringstream &wordStream);

#endif //HW4_FIGHTENTITY_H
