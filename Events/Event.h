
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

    virtual void apply(Player &player) = 0;
};


class SolarEclipse : public Event {
};


class PotionsMerchant : public Event {
};


class Encounter : public Event {
private:
    FightEntity* entity;
public:
    string getDescription() const;

    void apply(Player &player) override;
};
