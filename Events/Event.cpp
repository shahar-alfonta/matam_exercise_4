
#include "Event.h"
#include <iostream>
#include "../Utilities.h"
#include "iostream"

#define CLOSE_RANGE_DEFAULT_DAMAGE 10

using namespace std;

Encounter::Encounter(shared_ptr<FightEntity> entity) : entity(entity) {}

string Encounter::getDescription() const {
    return entity->getDescription();
}

void Encounter::apply(Player &player) {
    if (playerWins(player)) {
        player.levelUp();
        player.setCoins(player.getCoins() + entity->getLoot());
        if (player.getFightRange() == CLOSE) {
            player.setHealthPoints((int) player.getHealthPoints() - CLOSE_RANGE_DEFAULT_DAMAGE);
        }
    } else {
        player.setHealthPoints((int) player.getHealthPoints() - entity->getDamage());
    }
    entity->postFightChanges();
}

bool Encounter::playerWins(Player &player) const {
    return (int) player.combatPower() > entity->getCombatPower();
}

string Encounter::getOutCome(Player &player) const {
    if (playerWins(player)) {
        return getEncounterWonMessage(player, entity->getLoot());
    } else {
        return getEncounterLostMessage(player, entity->getDamage());
    }
}

string SolarEclipse::getDescription() const {
    return SOLAR_ECLIPSE;
}

string SolarEclipse::getOutCome(Player &player) const {
    return getSolarEclipseMessage(player, effect(player));
}

void SolarEclipse::apply(Player &player) {
    player.setForce((int) player.getForce() + effect(player));
}

int SolarEclipse::effect(Player &player) const {
    if (player.getIsMagic()) {
        return 1;
    } else {
        return -1;
    }
}

string PotionsMerchant::getDescription() const {
    return POTIONS_MERCHANT;
}

string PotionsMerchant::getOutCome(Player &player) const {
    return getPotionsPurchaseMessage(player, amountPurchased);
}

void PotionsMerchant::apply(Player &player) {
    resetAmountPurchased();
    switch (player.getCharacter()) {
        case RISK_TAKING:
            if (player.getHealthPoints() < 50 && player.getCoins() >= HEALTH_POTIONS_PRICE) {
                buyPotion(player);
            }
        case RESPONSIBLE:
            while (player.getHealthPoints() <= player.getMaxHealthPoints() &&
                   player.getCoins() >= HEALTH_POTIONS_PRICE) {
                buyPotion(player);
            }
    }
}

void PotionsMerchant::buyPotion(Player &player) {
    amountPurchased += 1;
    player.setCoins(player.getCoins() - HEALTH_POTIONS_PRICE);
    player.setHealthPoints((int) player.getHealthPoints() + HEALTH_POTIONS_HP);
}

void PotionsMerchant::resetAmountPurchased() {
    amountPurchased = 0;
}

std::shared_ptr<Event> eventFactory(std::istringstream &wordStream) {
    string word;
    wordStream >> word;
    auto it = specialEventsFactoryMap.find(word);
    if (it != specialEventsFactoryMap.end()) {
        return it->second();
    }

    if (shared_ptr<FightEntity> entity = fightEntityFactory(wordStream, word)) {
        return make_shared<Encounter>(entity);
    }
    std::cout <<"here" <<endl;

    throw Invalid_File("Invalid Events File");
}

std::unordered_map<string, SpecialEventsFactoryFunction> specialEventsFactoryMap{
        {SOLAR_ECLIPSE,    []() -> std::shared_ptr<Event> { return std::make_shared<SolarEclipse>(); }},
        {POTIONS_MERCHANT, []() -> std::shared_ptr<Event> { return std::make_shared<PotionsMerchant>(); }}
};