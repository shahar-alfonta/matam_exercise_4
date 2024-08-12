
#pragma once

#include "../Players/Player.h"
#include "FightEntity.h"

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
    FightEntity* entity;
public:
    string getDescription() const override;

    string getOutCome(Player &player) const override;

    void apply(Player &player) override;

    bool playerWins(Player &player) const;
};


class SolarEclipse : public Event {
    string getDescription() const override;

    string getOutCome(Player &player) const override;

    void apply(Player &player) override;

    int effect(Player &player) const;
};

class PotionsMerchant : public Event {
private:
    int amountPurchased;

public:
    string getDescription() const override;

    string getOutCome(Player &player) const override;

    void apply(Player &player) override;

    void resetAmountPurchased();
};
