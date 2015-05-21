//
// Created by vitalii on 08.05.15.
//

#include <iostream>
#include "ComputerPlayer.h"


void ComputerPlayer::endGame() {
    Player::endGame();
    isBluff = false;
}

int ComputerPlayer::changeCards(ui rank) {
   // ui rank = Rules::getCombinationRank(cards);
    std::vector<int> del;
    ui values[Card::ACE + 1] = { 0 };
    switch (rank & 0xFF000000) {
        case Rules::HighCard:
            del.push_back(0);
            del.push_back(1);
            del.push_back(2);
            del.push_back(3);
            break;
        case Rules::Pair:
            for (int i = 0; i < 5; i++) {
                if (++values[cards[i].value] == 2) {
                    for (int j = 0; j < 5; j++)
                        if (cards[j].value != cards[i].value)
                            del.push_back(j);
                }
            }
            break;
        case Rules::TwoPairs:
        case Rules::Quads:
            for (int i = 0; i < 5; i++) {
                ++values[cards[i].value];
            }
            for (int i = 0; i < 5; i++)
                if (values[cards[i].value] == 1)
                    del.push_back(i);
            break;
        default:break;
    }
    for (int i = (int) (del.size() - 1); i >= 0; i--)
        cards.erase(std::begin(cards) + del[i]);
    return (int) del.size();
}

ui ComputerPlayer::raise(ui previous) {
    if (money < 2 * previous)
        return call(previous);
    money -= 2 * previous;
    std::cout << getName() << " is raising\n";
    return 2 * previous;
}
ui ComputerPlayer::call(ui previous) {
    if (money < previous)
        return fold();
    money -= previous;
    std::cout << getName() << " is calling\n";
    return previous;
}
ui ComputerPlayer::fold() {
    std::cout << getName() << " is folding\n";
    isPassed = true;
    return 0;
}

ui ComputerPlayer::makeAction(ui previousBet, ui rank, ui pot) {
    if (!isBluff) {
        isBluff = rand() % 5 > 3;
    }
    switch (rank & 0xFF000000) {
        case Rules::HighCard:
        case Rules::Pair:
        case Rules::TwoPairs:
            if (isBluff) return raise(previousBet);
            else return call(previousBet);
        default:
            return raise(previousBet);
    }
}

std::string ComputerPlayer::getName() {
    if (name == "")
        name = makeUpName();
    return name;
}

std::string ComputerPlayer::makeUpName() {
    return playerNames[rand() % 12];
}


