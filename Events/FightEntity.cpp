
#include "FightEntity.h"
#include "Event.h"

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

MonsterPack::MonsterPack(istringstream &wordStream) {
    string sizeStr;
    wordStream >> sizeStr;
    int size = stoi(sizeStr);
    int memberCount = 0;

    while (memberCount < size) {
        members.push_back(fightEntityFactory(wordStream));
        memberCount++;
    }
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
    oss << "Pack of " << members.size() << "members";
    return oss.str();
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

Snail::Snail(istringstream &wordStream) {}

string Snail::getEntityTypeMessage() const {
    return SNAIL;
}

Slime::Slime(istringstream &wordStream) {}

string Slime::getEntityTypeMessage() const {
    return SLIME;
}

Balrog::Balrog(istringstream &wordStream) {}

string Balrog::getEntityTypeMessage() const {
    return BALROG;
}

void Balrog::postFightChanges() {
    combatPower += 2;
}

std::shared_ptr<FightEntity> fightEntityFactory(istringstream &wordStream) {
    string word;
    wordStream >> word;

    auto it = entitiesFactoryMap.find(word);
    if (it != entitiesFactoryMap.end()) {
        return it->second(wordStream);
    }

    return nullptr;
}
