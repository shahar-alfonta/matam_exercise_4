
#pragma once

#include <iostream>
#include <memory>
#include "Players/Player.h"
#include "Events/Event.h"
#include "vector"

using namespace std;

std::shared_ptr<Player> playerFactory(std::istringstream &wordStream);

class MatamStory {
private:
    vector<shared_ptr<Player>> players;
    vector<shared_ptr<Event>> events;
    unsigned int m_turnIndex;

    /**
     * Playes a single turn for a player
     *
     * @param player - the player to play the turn for
     *
     * @return - void
    */
    void playTurn(Player &player);

    /**
     * Plays a single round of the game
     *
     * @return - void
    */
    void playRound();

    /**
     * Checks if the game is over
     *
     * @return - true if the game is over, false otherwise
    */
    bool isGameOver() const;

    int eventIndex();
public:
    /**
     * Constructor of MatamStory class
     *
     * @param eventsStream - events input stream (file)
     * @param playersStream - players input stream (file)
     *
     * @return - MatamStory object with the given events and players
     *
    */
    MatamStory(std::istream &eventsStream, std::istream &playersStream);

    /**
     * Plays the entire game
     *
     * @return - void
    */
    void play();
};
