
#include "FightEntity.h"

#include "sstream"

using namespace std;

// the wanted default behavior is no change.
void FightEntity::postFightChanges() {}

string FightEntity::getDescription() const {
    ostringstream oss;
    oss << getEntityType() << " (power " << getCombatPower() << ", loot " << getLoot()
        << ", damage " << getDamage() << ")";
    return oss.str();
}

int MonsterPack::getCombatPower() const {
    int totalPower = 0;
    for (FightEntity *entity: entities) {
        totalPower += entity->getCombatPower();
    }
    return totalPower;
}

int MonsterPack::getLoot() const {
    int totalLoot = 0;
    for (FightEntity *entity: entities) {
        totalLoot += entity->getLoot();
    }
    return totalLoot;
}


int MonsterPack::getDamage() const {
    int totalDamage = 0;
    for (FightEntity *entity: entities) {
        totalDamage += entity->getDamage();
    }
    return totalDamage;
}

void MonsterPack::postFightChanges() {
    for (FightEntity *entity: entities) {
        entity->postFightChanges();
    }
}

string MonsterPack::getEntityType() const {
    ostringstream oss;
    oss << "Pack of " << getMembersAmount();
    return oss.str();
}

int MonsterPack::getMembersAmount() const {
    return (int) entities.size();  // TODO: probably we will iterate over entities and call .amount() on each
}

int Monster::getCombatPower() const {
    return combatPower;
}

int Monster::getLoot() const {
    return loot;
}

int Monster::getDamage() const {
    return damage;
}

string Snail::getEntityType() const {
    return "Snail";
}

string Slime::getEntityType() const {
    return "Slime";
}

string Balrog::getEntityType() const {
    return "Balrog";
}

void Balrog::postFightChanges() {
    combatPower += 2;
}
