//
// Created by vitalii on 29.04.15.
//

#include <ComputerPlayer.h>
#include <iostream>
#include <algorithm>
#include "Desk.h"
#include "HumanPlayer.h"
#include "../test/Stack.hpp"

Player * Desk::playGame() {
    std::cout << "************************\n************************\n";
    std::cout << "Playes of game are : \n";
    for (int i = 0; i < players.size(); i++) {
        std::cout << i + 1 << ": " << players[i]->getName() << "\n";
    }
    for (auto pl : players) {
        pot += pl->ante(1);
    }
    for (auto& p : players)
        giveCards(5, p);
    round();
    changeCards();
    round();
//    std::shared_ptr<Card> c(new Card(Card::D10, Card::Hearts));
//    c->setOwner(players[0]);
//    std::cout << c->look(players[0]).first;
    checkWinner();
    players.erase(std::remove_if(std::begin(players), std::end(players), [](const std::shared_ptr<Player>& player) {
        if (player->isBroke()) {
            std::cout << "Player " << player->getName() << " has quit because of lacking of money\n";
            return true;
        } else {
            return false;
        }
    }), std::end(players));

    if (players.size() == 1) return players[0].get();
    else return NULL;
}

//create 5 AI players without need to bother client
void Desk::setStandardProblems() {
    for (int i = 0; i < 5; i++)
        players.push_back(std::shared_ptr<Player>(new ComputerPlayer()));
}

// create players sitting on Desk
void Desk::setPlayers() {
    unsigned int AIPlayers; // number of AI Players
    unsigned int humanPlayers; // number of Hyman Players
    std::cout << "Enter number of AI players\n";
    std::cin >> AIPlayers;
    std::cout << "Enter the number of noncomputer players\n";
    std::cin >> humanPlayers;
    players.reserve(AIPlayers + humanPlayers);
    for (int i = 0; i < AIPlayers; i++)
        players.push_back(std::shared_ptr<Player>(new ComputerPlayer()));
    for (unsigned int i = 0; i < humanPlayers; i++)
        players.push_back(std::shared_ptr<Player>(new HumanPlayer()));
}

Desk::Desk() {
    for (int i = Card::D2; i <= Card::ACE; i++) {
        for (int j = Card::Suit::Spades; j <= Card::Suit::Hearts; j++) {
            deck.emplace_back(std::move(Stack::makeCard((Card::Suit) j, (Card::Value) i)));
        }
    }
    std::random_shuffle(std::begin(deck), std::end(deck));
    index = 0;
}

void Desk::round() {
    static short int numberOfRound = 0;
    std::cout << numberOfRound + 1 << " round is On\n";
    ui previous = 1;
    for (auto & pl : players) {
        if (pl->isPassed)
            continue;
        previous = pl->makeAction(previous, Rules::getCombinationRank(pl->cards, pl), pot);
        pot += previous;
    }
    numberOfRound ++;
    numberOfRound %= 2;
}

void Desk::checkWinner() {
    unsigned int maxCombinationIndex = 0;
    unsigned int maxCombination = 0;
    for (unsigned int i = 1; i < players.size(); i++) {
        //unsigned int t = players[i]->getCombinationRank();
        if (players[i]->isPassed) {
            players[i]->endGame();
            continue;
        }
        unsigned int t = Rules::getCombinationRank(players[i]->cards, players[i]);
        if (t > maxCombination) {
            maxCombination = t;
            maxCombinationIndex = i;
        }
        players[i]->endGame();
    }
    players[maxCombinationIndex]->takeMoney((ui) pot);
    pot = 0;
    std::cout << players[maxCombinationIndex]->getName() << " wins this game\nHe/She has got :";
    Rules::writeCombination((Rules::Combinations)(maxCombination & 0xFF000000));
}

void Desk::giveCards(int howMany, const std::shared_ptr<Player>& pp) {
    std::vector<Card> giveAway;
    if (howMany + index >= deck.size()) {
        std::random_shuffle(std::begin(deck), std::end(deck));
        index = 0;
    }
    for (int i = 0; i < howMany; i++) {
        Card card(deck[index].value, deck[index].suit);
        card.setOwner(pp);
        giveAway.emplace_back(std::move(card));
        index++;
    }
    pp->takeCards(giveAway);
}

void Desk::changeCards() {
    for (auto &pl : players) {
        if (pl->isPassed)
            continue;
        giveCards(pl->changeCards(Rules::getCombinationRank(pl->cards, pl)), pl);
    }
}
