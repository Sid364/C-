//
// Created by vitalii on 09.05.15.
//

#ifndef POKER_HUMANPLAYER_H
#define POKER_HUMANPLAYER_H

#include "Player.hpp"

class HumanPlayer : public Player{

public:
    virtual ui makeAction(ui previousBet, ui rank, ui pot) override;

    virtual void takeMoney(ui amount) override;

    virtual int changeCards(ui rank) override;

    virtual std::string getName() override;

    HumanPlayer();

    virtual void takeCards(std::vector<Card> &cards) override;
};


#endif //POKER_HUMANPLAYER_H
