#include <algorithm>
#include <set>
#include <iostream>
#include "Rules.h"

namespace{
    unsigned int checkFullHouse(const std::vector<Card> &cards, const std::shared_ptr<Player> &player) {
        size_t values[Card::ACE + 1] = { 0 };
        Card::Value tripleCard = Card::NONE;
        Card::Value pairCard = Card::NONE;
        for (auto & c : cards) {
            if (++values[c.look(player).second - Card::D2] == 3) {
                if (c.look(player).second > tripleCard)
                    tripleCard = c.look(player).second;
            }
        }
        for (auto & c : cards) {
            if (values[c.look(player).second - Card::D2] == 2) {
                if (c.look(player).second > pairCard && c.look(player).second != tripleCard)
                    pairCard = c.look(player).second;
            }
        }
        if (tripleCard > Card::NONE && pairCard > Card::NONE) {
            return Rules::FullHouse | tripleCard << 8 | pairCard;
        } else {
            return 0;
        }
    }
    unsigned int checkPairs(std::vector <Card> const & cards,
		std::shared_ptr<Player> const & player) {
		size_t values[Card::ACE + 1] = { 0 };
		int rank = 0;
		Card::Value highestCard = Card::NONE;
		Card::Value secondCard = Card::NONE;
        Card::Value oneCard = Card::NONE;
		

		for (auto & c : cards) {
			Card::Value curValue = c.look(player).second;
			if (++values[curValue - Card::D2] == 2) {
				if (curValue > highestCard) {
					secondCard = highestCard;
					highestCard = curValue;
				}
				else if (curValue > secondCard)
					secondCard = curValue;
			}
            if (values[curValue - Card::D2] >= 1) {
                if (curValue > oneCard)
                    oneCard = curValue;
            }
		}
		if (secondCard == Card::NONE && highestCard == Card::NONE) return Rules::HighCard | oneCard << 8;
		return (secondCard != Card::NONE ? Rules::TwoPairs : Rules::Pair) | highestCard << 8 | secondCard;
	}
	
	unsigned int checkFlush(std::vector<Card> const & cards, std::shared_ptr<Player> const & player) {
		Card::Value high = Card::NONE;
		Card::Suit  suit = cards.cbegin()->look(player).first;

		for (auto & c : cards) {
			high = std::max(high, c.look(player).second);
			if (c.look(player).first != suit)
				return 0;
		}
		return high | Rules::Flush;
	}

	unsigned int checkStraight(std::vector<Card> const & cards,
		std::shared_ptr<Player> const & player) {
		size_t values[Card::ACE + 1] = { 0 };
		for (auto & c : cards) {
			++values[c.look(player).second - Card::D2];
		}
		
		auto high = Card::NONE;
		auto count = 0;

		for (int i = Card::ACE; i >= Card::D2; --i) {
			if (values[i - Card::D2]) {
				if (high != Card::NONE) {
					++count;
				}
				else {
					high = (Card::Value)i;
					count = 1;
				}
			}
			else {
				high = Card::NONE;
			}
		}

		if (count == 5 || (count == 4 && high == Card::D5 && values[Card::ACE - Card::D2])) {
			return Rules::Straight | high;
		}

		return 0;
	}
}

namespace Rules {
    unsigned int getCombinationRank(std::vector <Card> const & cards,
		std::shared_ptr<Player> const & player) {
		size_t values[Card::ACE + 1] = { 0 };
		int rank = 0;
		Card::Value highestCard = Card::NONE;
	
		if (unsigned flushResult = checkFlush(cards, player))
			if (unsigned int straightResult = checkStraight(cards, player))
				return straightResult & 0x00FFFFFF | Rules::StraightFlush;
			else
				return flushResult;

		if (unsigned int straightResult = checkStraight(cards, player))
			return straightResult;

		if (unsigned int fullHouseResult = checkFullHouse(cards, player))
			return fullHouseResult;

		for (auto & c : cards) {
			Card::Value curValue = c.look(player).second;
			if (++values[curValue - Card::D2] == 3) {
				highestCard = std::max(highestCard, curValue);
			}
		}

		return highestCard == Card::NONE ? checkPairs(cards, player) : Rules::Set | highestCard;
	}

	unsigned int checkFullHouse(const std::vector<Card> &vector, const std::shared_ptr<Player> &shared_ptr) {
		return 0;
}

    void writeCombination(Combinations combination) {
        switch (combination) {
            case Rules::Quads : std::cout << "Quads\n"; break;
            case Rules::Flush : std::cout << "Flush\n"; break;
            case Rules::FullHouse : std::cout << "FullHouse\n";break;
            case Rules::HighCard : std::cout << "High Card\n";break;
            case Rules::Pair : std::cout << "Pair\n";break;
            case Rules::Set : std::cout << "Set\n";break;
            case Rules::TwoPairs : std::cout << "Two Pairs\n";break;
            case Rules::Straight : std::cout << "Straight\n";break;
            case Rules::StraightFlush : std::cout << "Straight Flush\n";break;
            default: std::cout << "Unknown.";break;
        }
    }
}
