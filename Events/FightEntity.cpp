
#include "FightEntity.h"

void FightEntity::postFightChanges() {}  // the wanted default behavior is no change.

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

int Monster::getCombatPower() const {
    return combatPower;
}

int Monster::getLoot() const {
    return loot;
}

int Monster::getDamage() const {
    return damage;
}

string Snail::getMonsterType() {
    return "Snail";
}

string Slime::getMonsterType() {
    return "Slime";
}

string Balrog::getMonsterType() {
    return "Balrog";
}

void Balrog::postFightChanges() {
    combatPower += 2;
}
