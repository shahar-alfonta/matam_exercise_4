
#include "MatamStory.h"
#include <iostream>
#include <string>
#include "Utilities.h"
#include "Events/Event.h"

using namespace std;

bool comp(shared_ptr<Player> &player1, shared_ptr<Player> &player2) {
    if (player1->getLevel() > player2->getLevel()) {
        return true;
    } else if (player1->getLevel() == player2->getLevel()) {
        if (player1->getCoins() > player2->getCoins()) {
            return true;
        } else if (player1->getCoins() == player2->getCoins()) {
            if (player1->getName() > player2->getName()) {
                return true;
            }
        }
    }
    return false;
}

std::shared_ptr<Player> playerFactory(std::istringstream &wordStream) {
    string name, job, character;
    wordStream >> name;
    wordStream >> job;
    wordStream >> character;
    if (job == "Warrior") {
        return make_shared<Warrior>(name, character);
    }
    if (job == "Magician") {
        return make_shared<Magician>(name, character);
    }
    if (job == "Archer") {
        return make_shared<Archer>(name, character);
    }
    throw Invalid_File("Invalid Players File");
}

MatamStory::MatamStory(std::istream &eventsStream, std::istream &playersStream) {
    string line, word;
    while (!eventsStream.eof()) {
        getline(eventsStream, line);
        std::istringstream wordStream(line);
        events.push_back(eventFactory(wordStream));
    }

    while (!playersStream.eof()) {
        getline(playersStream, line);
        std::istringstream wordStream(line);
        players.push_back(playerFactory(wordStream));
    }
    this->m_turnIndex = 1;
}

void MatamStory::playTurn(Player &player, Event &event) {
    printTurnDetails(m_turnIndex, player, event);
    event.apply(player);
    printTurnOutcome(event.getOutCome(player));
    m_turnIndex++;
}

void MatamStory::playRound() {

    printRoundStart();

    for (const shared_ptr<Player> &player: players) {
        if (player->getHealthPoints() != 0) {
            playTurn(*player, *events[eventIndex()]);
        }
    }

    printRoundEnd();

    printLeaderBoardMessage();

    vector<shared_ptr<Player>> leaderboard = players;
    sort(leaderboard.begin(), leaderboard.end(), comp);
    for (unsigned int i = 0; i < leaderboard.size(); ++i) {
        printLeaderBoardEntry(i, *leaderboard[i]);
    }

    printBarrier();
}

bool MatamStory::isGameOver() const {
    for (const shared_ptr<Player> &player: players) {
        if (player->getLevel() == 10) {
            return true;
        }
        if (player->getHealthPoints() != 0) {
            return false;
        }
    }
    return false;
}

unsigned int MatamStory::eventIndex() {
    return m_turnIndex % (unsigned int) events.size();
}

void MatamStory::play() {
    printStartMessage();
    for (unsigned int i = 0; i < players.size(); ++i) {
        printStartPlayerEntry(i, *players[i]);
    }
    printBarrier();

    while (!isGameOver()) {
        playRound();
    }

    printGameOver();
    vector<shared_ptr<Player>> leaderboard;
    sort(leaderboard.begin(), leaderboard.end(), comp);
    if (leaderboard.front()->getLevel() == 10) {
        printWinner(*leaderboard.front());
    } else {
        printNoWinners();
    }
}

