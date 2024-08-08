
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
    for (int i = 0; i < membersAmount; i++) {
        totalPower += members[i]->getCombatPower();
    }
    return totalPower;
}

int MonsterPack::getLoot() const {
    int totalLoot = 0;
    for (int i = 0; i < membersAmount; i++) {
        totalLoot += members[i]->getLoot();
    }
    return totalLoot;
}


int MonsterPack::getDamage() const {
    int totalDamage = 0;
    for (int i = 0; i < membersAmount; i++) {
        totalDamage += members[i]->getDamage();
    }
    return totalDamage;
}

void MonsterPack::postFightChanges() {
    for (int i = 0; i < membersAmount; i++) {
        members[i]->postFightChanges();
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

MonsterPack::MonsterPack(int membersAmount) :
        membersAmount(membersAmount),
        members(make_unique<unique_ptr<FightEntity>[]>(membersAmount)) {}

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
