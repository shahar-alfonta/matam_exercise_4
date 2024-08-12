
#include "FightEntity.h"

#include "sstream"
#include "memory"

using namespace std;

// the wanted default behavior is no change.
void FightEntity::postFightChanges() {}

string FightEntity::getDescription() const {
    ostringstream oss;
    oss << getEntityTypeMessage() << " (power " << getCombatPower() << ", loot " << getLoot()
        << ", damage " << getDamage() << ")";
    return oss.str();
}

int MonsterPack::getCombatPower() const {
    int totalPower = 0;
    for (const shared_ptr<FightEntity>& member: members) {
        totalPower += member->getCombatPower();
    }
    return totalPower;
}

int MonsterPack::getLoot() const {
    int totalLoot = 0;
    for (const shared_ptr<FightEntity>& member: members) {
        totalLoot += member->getLoot();
    }
    return totalLoot;
}


int MonsterPack::getDamage() const {
    int totalDamage = 0;
    for (const shared_ptr<FightEntity>& member: members) {
        totalDamage += member->getDamage();
    }
    return totalDamage;
}

void MonsterPack::postFightChanges() {
    for (shared_ptr<FightEntity>& member: members) {
        member->postFightChanges();
    }
}

string MonsterPack::getEntityTypeMessage() const {
    ostringstream oss;
    oss << "Pack of " << getMembersAmount() << "members";
    return oss.str();
}

int MonsterPack::getMembersAmount() const {
    return membersAmount;
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

string Snail::getEntityTypeMessage() const {
    return "Snail";
}

string Slime::getEntityTypeMessage() const {
    return "Slime";
}

string Balrog::getEntityTypeMessage() const {
    return "Balrog";
}

void Balrog::postFightChanges() {
    combatPower += 2;
}
