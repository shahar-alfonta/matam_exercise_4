
#include "MatamStory.h"
#include <fstream>
#include <iostream>
#include <string>
#include "Utilities.h"

using namespace std;

std::shared_ptr<Player> playerFactory (string line){
    string name, job, character;
    std::istringstream newLine(line);
    newLine >> name;
    newLine >> job;
    newLine >> character;
    if(job == "Warrior"){
        return make_shared<Warrior>(name,character);
    }
    if(job == "Magician"){
        return make_shared<Magician>(name,character);
    }
    if(job == "Archer"){
        return make_shared<Archer>(name,character);
    }
    throw Invalid_File("Invalid Players File");
}

MatamStory::MatamStory(std::istream& eventsStream, std::istream& playersStream) {
    string line, word;
    while(!eventsStream.eof()){
        getline(eventsStream,line);
        events.push_back(eventFactory(line));
    }

    while(!playersStream.eof()){
        getline(playersStream,line);
        players.push_back(playerFactory(line));
    }

    printStartMessage();
    for (int i = 0; i < players.size(); ++i) {
        printStartPlayerEntry(i,*players[i]);
    }
    printBarrier();
    this->m_turnIndex = 1;
}

void MatamStory::playTurn(Player& player, Event& event) {
    printTurnDetails(m_turnIndex,player,event);
    event.apply(player);
    printTurnOutcome(event.getOutCome(player));
    /**
     * Steps to implement (there may be more, depending on your design):
     * 1. Get the next event from the events list
     * 2. Print the turn details with "printTurnDetails"
     * 3. Play the event
     * 4. Print the turn outcome with "printTurnOutcome"
    */

    m_turnIndex++;
}

void MatamStory::playRound() {

    printRoundStart();

    for (const shared_ptr<Player>& player :players) {
        playTurn(*player,*events[eventIndex()]);
    }

    printRoundEnd();

    printLeaderBoardMessage();


    /*===== TODO: Print leaderboard entry for each player using "printLeaderBoardEntry" =====*/

    /*=======================================================================================*/

    printBarrier();
}

bool MatamStory::isGameOver() const {
    bool gameOver = true;
    for (const shared_ptr<Player>& player :players) {
        if(player->getLevel() != 10 || player->getHealthPoints() != 0){
            gameOver = false;
        }
    }
    return gameOver;
}

int MatamStory::eventIndex() {
    return m_turnIndex % events.size();
}

void MatamStory::play() {
    printStartMessage();
    /*===== TODO: Print start message entry for each player using "printStartPlayerEntry" =====*/

    /*=========================================================================================*/
    printBarrier();

    while (!isGameOver()) {
        playRound();
    }

    printGameOver();
    /*===== TODO: Print either a "winner" message or "no winner" message =====*/

    /*========================================================================*/
}

