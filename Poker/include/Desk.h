//
// Created by vitalii on 29.04.15.
//

#ifndef POKER_DESK_H
#define POKER_DESK_H


#include <vector>
#include "Player.hpp"

class Desk {
public:
    unsigned long long pot = 0;
    /**
     * plays one game. setPlayers() or setStandardPlayers() must be called before.
     * Returns pointer to player if there is only one left and hence is a winner,
     * otherwise returns NULL
     */
    Player * playGame();
    Desk();
    /**
     * Asks player how many players they want to put in game and sets them
     */
    void setPlayers();
    /**
     * sets five AI players
     */
    void setStandardProblems();
private:
    std::vector< std::shared_ptr<Player> > players;
    void round();
    void checkWinner();
    std::vector<Card> deck;
    ui index;
    void changeCards();
    void giveCards(int howMany, const std::shared_ptr<Player> &pp);
};


#endif //POKER_DESK_H
