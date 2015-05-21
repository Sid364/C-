//
// Created by vitalii on 08.05.15.
//

#ifndef POKER_COMPUTERPLAYER_H
#define POKER_COMPUTERPLAYER_H

#include "Player.hpp"

// Array of possible names for players
static std::string playerNames[] = {"Michael", "Kim", "Vladimir", "Vitaly", "Sam", "Jack",
                       "Anna", "Ira", "Lily", "Robin", "Taylor", "Raobin"};


class ComputerPlayer : public Player {
public:

    ComputerPlayer() = default;

    ComputerPlayer(ui money) : Player(money) {}

    virtual std::string getName() override;

    virtual ui makeAction(ui previousBet, ui rank, ui pot) override;

    virtual int changeCards(ui rank) override;

private:
    bool isBluff = false;

    std::string makeUpName();

    ui raise(ui previous);

    ui call(ui previous);

    ui fold();

public:
    virtual void endGame() override;
};


#endif //POKER_COMPUTERPLAYER_H
