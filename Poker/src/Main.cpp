//
// Created by vitalii on 05.05.15.
//
#define BOOST_TEST_MODULE Module2
#include <iostream>
#include <Desk.h>
//#include <Desk.h>
//#include "ComputerPlayer.h"

int main() {
    std::cout << "Welcome to Poker by Bushaev Vitalii" << std::endl;
    Desk desk;
    desk.setPlayers();
    // play till we got a winner
//    while (desk.playGame() == NULL);
    while (true) {
        std::cout << "You wanna play one more game ?\n";
        std::string answer;
        std::cin >> answer;
        if (answer == "no")
            break;
        else
            desk.playGame();
    }
    return 0;
}