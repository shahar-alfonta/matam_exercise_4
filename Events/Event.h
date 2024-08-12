
#pragma once

#include "../Players/Player.h"
#include <sstream>
#include <string>
#include "memory"

class Event {
public:
    /**
     * Gets the description of the event
     *
     * @return - the description of the event
    */
    string getDescription() const;
};

std::shared_ptr<Event> eventFactory (string line){
    string word;
    std::istringstream newLine(line);
    newLine >> word;
    if(word == "Snail"){}
    if(word == "Balrog"){}
    if(word == "Slime"){}
    if(word == "SolarEclipse"){}
    if(word == "PotionsMerchant"){}
    if(word == "Pack"){}
    throw Invalid_File("Invalid Players File");
}
