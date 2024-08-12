
#include "Event.h"

#include "../Utilities.h"

Encounter::Encounter(shared_ptr<FightEntity> entity) : entity(entity) {}

string Encounter::getDescription() const {
    return entity->getDescription();
}

void Encounter::apply(Player &player) {
    if (playerWins(player)) {
        player.levelUp();
        player.setCoins(player.getCoins() + entity->getLoot());
        if (player.getFightRange() == CLOSE) {
            player.setHealthPoints(player.getHealthPoints() - 10);
        }
    } else {
        player.setHealthPoints(player.getHealthPoints() - entity->getDamage());
    }
    entity->postFightChanges();
}

bool Encounter::playerWins(Player &player) const {
    return player.combatPower() > entity->getCombatPower();
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
    player.setHealthPoints(player.getHealthPoints() + effect(player));
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

    if (player.getCharacter() == RISK_TAKING) {
        if (player.getHealthPoints() < 50) amountPurchased = 1;
        else amountPurchased = 0;
        player.setHealthPoints(player.getHealthPoints() + amountPurchased);
    } else if (player.getCharacter() == RESPONSIBLE) {
        while (player.getHealthPoints() <= player.getMaxHealthPoints() && player.getCoins() >= 5) {
            amountPurchased += 1;
            player.setCoins(player.getCoins() - 5);
            player.setHealthPoints(player.getHealthPoints() + 1);
        }
    }
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

    if (shared_ptr<FightEntity> entity = fightEntityFactory(wordStream)){
        return make_shared<Encounter>(entity);
    }

    throw Invalid_File("Invalid Events File");
}
