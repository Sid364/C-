//
// Created by vitalii on 29.04.15.
//

#ifndef POKER_PLAYER_H
#define POKER_PLAYER_H

#include "Card.h"
#include "vector"
#include "Rules.h"

typedef unsigned int ui;


class Player {
public:
    friend class Desk;
    Player() {
        money = 100;
    }
    Player(ui money) {
        this->money = money;
    }
    /**
     * Makes a bet, returns the amount of money player put
     * @param previousBet [in] magnitude of previous bet
     * @param rank [in] rank of current hand of player
     * @param pot [in] the amount of money in bank
     */
    virtual ui makeAction(ui previousBet, ui rank, ui pot) = 0;
    /**
     * erases cards that player want to change, return number of removed cards
     * @param rank rank of current hand of the player
     */
    virtual int changeCards(ui rank) = 0;

    //take money from pot
    void takeMoney(ui amount) {
        money += amount;
    }
    // returns the name of the player
    virtual std::string getName()= 0;
    // return the name on const obj of player
    virtual std::string getName() const {
        return name;
    };

    // return 'true' if player has no money left
    bool isBroke() const {
        return money == 0;
    }

    // put equal amount of money into pot before deal begins
    ui ante(ui amount) {
        money -= amount;
        return amount;
    }

    //takes card from the deck and adds them to hand
    virtual void takeCards(std::vector<Card> &cards) {
        for (auto& card : cards)
            this->cards.emplace_back(std::move(card));
    }
    //make all necessary changes at the end of the game
    virtual void endGame() {
        cards.clear();
        isPassed = false;
    }
    virtual ~Player() = default;
    // indicates if player passed current round
    bool isPassed = false;
protected:
    ui money;
    std::string name;
    std::vector<Card> cards;
};


#endif //POKER_PLAYER_H


