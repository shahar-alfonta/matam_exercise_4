
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
    this->m_turnIndex = 1;
}

void MatamStory::playTurn(Player& player, Event& event) {
    printTurnDetails(m_turnIndex,player,event);
    event.apply(player);
    printTurnOutcome(event.getOutCome(player));
    m_turnIndex++;
}

void MatamStory::playRound() {

    printRoundStart();

    for (const shared_ptr<Player>& player :players) {
        if(player->getHealthPoints() != 0){
            playTurn(*player,*events[eventIndex()]);
        }
    }

    printRoundEnd();

    printLeaderBoardMessage();

    vector<shared_ptr<Player>> leaderboard = players;
    sort(leaderboard.begin(),leaderboard.end());
    /*===== TODO: Print leaderboard entry for each player using "printLeaderBoardEntry" =====*/

    /*=======================================================================================*/

    printBarrier();
}

bool MatamStory::isGameOver() const {
    for (const shared_ptr<Player>& player :players) {
        if (player->getLevel() == 10){
            return true;
        }
        if(player->getHealthPoints() != 0){
            return false;
        }
    }
    return false;
}

int MatamStory::eventIndex() {
    return m_turnIndex % events.size();
}

void MatamStory::play() {
    printStartMessage();
    for (int i = 0; i < players.size(); ++i) {
        printStartPlayerEntry(i,*players[i]);
    }
    printBarrier();

    while (!isGameOver()) {
        playRound();
    }

    printGameOver();
    vector<shared_ptr<Player>> leaderboard;
    if(leaderboard.front()->getLevel() == 10){
        printWinner(*leaderboard.front());
    }
    else{
        printNoWinners();
    }
}

