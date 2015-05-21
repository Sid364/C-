//
// Created by vitalii on 29.04.15.
//

#ifndef POKER_STACK_HPP
#define POKER_STACK_HPP

#include "../include/Card.h"

class Stack {
public:
    static Card makeCard(Card::Suit suit, Card::Value value) {
        std::shared_ptr<Player> p1;
        //auto p1 = std::make_shared<Player>();
        Card card(value, suit);
        card.setOwner(p1);
        card.open(p1);
        return std::move(card);
    }

    Card makeCard() {
        Card card(Card::D2, Card::Spades);
        return std::move(card);
    }

    Card makeCard(std::shared_ptr <Player> const &player) {
        Card card(Card::D2, Card::Spades);
        card.setOwner(player);
        return std::move(card);
    }
};

#endif //POKER_STACK_HPP
