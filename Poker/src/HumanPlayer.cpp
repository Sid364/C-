//
// Created by vitalii on 09.05.15.
//

#include <iostream>
#include <algorithm>
#include "HumanPlayer.h"

HumanPlayer::HumanPlayer() = default;

ui HumanPlayer::makeAction(ui previousBet, ui rank, ui pot) {
    std::cout << "Your cards are: \n";
    for (auto& c : cards)
        c.writeCard();
    std::cout << "Your combination :";
    Rules::writeCombination((Rules::Combinations)(rank & 0xFF000000));
    std::cout << "You've got " << money << " and pot is :" << pot << "\n" ;
    std::cout << "Previous bet is " << previousBet << ". What do you wanna do ?\n1.Call\n2.Raise\n3.Fold\n";
    int choice;
    std::cin >> choice;
    switch (choice) {
        case 1:
            std::cout << getName() << " is calling " << previousBet << "\n";
            money -= previousBet;
            return previousBet;
        case 2:
            std::cout << getName() << " is raising " << previousBet * 2 << "\n";
            money -= previousBet * 2;
            return previousBet * 2;
        case 3:
            std::cout << getName() << " is folding\n";
            isPassed = true;
            return 0;
        default:
            return 0;
    }
}

void HumanPlayer::takeMoney(ui amount) {
    Player::takeMoney(amount);
}

std::string HumanPlayer::getName() {
    if (name == "") {
        std::cout << "\nEnter your Name:\n";
        std::cin >> name;
    }
    return name;
}

void HumanPlayer::takeCards(std::vector<Card> &cards) {
    Player::takeCards(cards);
//    std::cout << "Your new cards :\n";
//    for (int i = 0; i < 5; i++) {
//        std::cout << i + 1 << ". ";
//        this->cards[i].writeCard();
//    }
}

int HumanPlayer::changeCards(ui rank) {
    std::cout << "Your Cards :\n";
    for (int i = 0; i < 5; i++) {
        std::cout << i + 1 << ". ";
        cards[i].writeCard();
    }
    std::cout << "Your combinaion is :\n";
    Rules::writeCombination((Rules::Combinations) (rank & 0xFF000000));
    std::cout << "How much cards do you wanna change ?\n";
    int n;
    std::cin >> n;
    std::cout << "Which cards ?\n";
    std::vector<int> which;
    for (int i = 0; i < n; i++) {
        int temp;
        std::cin >> temp;
        which.push_back(temp - 1);
    }
    std::sort(std::begin(which), std::begin(which));
    for (int i = (int) (which.size() - 1); i >= 0; i--) {
        cards.erase(cards.begin() + which[i]);
    }
    return n;
}
