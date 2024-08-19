
#pragma once

#include "../Players/Player.h"
#include <sstream>
#include <string>
#include "memory"
#include "FightEntity.h"
#include "unordered_map"

#define SOLAR_ECLIPSE "SolarEclipse"
#define POTIONS_MERCHANT "PotionsMerchant"
#define HEALTH_POTIONS_HP 10
#define HEALTH_POTIONS_PRICE 5

class Event {
public:
    /**
     * Gets the description of the event
     *
     * @return - the description of the event
    */
    virtual string getDescription() const = 0;

    virtual string getOutCome(Player &player) const = 0;

    virtual void apply(Player &player) = 0;
};

class Encounter : public Event {
private:
    std::shared_ptr<FightEntity> entity;
public:
    Encounter(std::shared_ptr<FightEntity> entity);

    string getDescription() const override;

    string getOutCome(Player &player) const override;

    void apply(Player &player) override;

    bool playerWins(Player &player) const;
};


class SolarEclipse : public Event {
public:
    SolarEclipse() = default;

    string getDescription() const override;

    string getOutCome(Player &player) const override;

    void apply(Player &player) override;

    int effect(Player &player) const;
};

class PotionsMerchant : public Event {
private:
    unsigned int amountPurchased = 0;
public:
    PotionsMerchant() = default;

    string getDescription() const override;

    string getOutCome(Player &player) const override;

    void apply(Player &player) override;

    void buyPotion(Player& player);

    void resetAmountPurchased();
};

std::shared_ptr<Event> eventFactory(std::istringstream &wordStream);

std::shared_ptr<FightEntity> fightEntityFactory(std::istringstream &wordStream);

typedef std::shared_ptr<Event> (*SpecialEventsFactoryFunction)();

extern std::unordered_map<string, SpecialEventsFactoryFunction> specialEventsFactoryMap;