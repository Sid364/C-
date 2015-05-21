#include <boost/test/unit_test.hpp>
#include "Rules.h"
#include "Exceptions.h"
#include "Stack.hpp"


//TODO: Check test, probably add others
BOOST_AUTO_TEST_SUITE(TestRules)

BOOST_AUTO_TEST_CASE(TestHighCard) {
	std::vector<Card> cards, cards2;
	cards.emplace_back(std::move(Stack::makeCard(Card::Hearts, Card::D7)));
	cards.emplace_back(std::move(Stack::makeCard(Card::Diamonds, Card::KNAVE)));
	cards2.emplace_back(std::move(Stack::makeCard(Card::Diamonds, Card::KNAVE)));
	cards2.emplace_back(std::move(Stack::makeCard(Card::Hearts, Card::ACE)));
	BOOST_CHECK_EQUAL(Rules::HighCard, Rules::getCombinationRank(cards) & 0xFF000000);
    BOOST_CHECK_GT(Rules::getCombinationRank(cards2), Rules::getCombinationRank(cards));
}

BOOST_AUTO_TEST_CASE(TestOnePair)
{
	std::vector<Card> cards, cards2;
	cards.emplace_back(std::move(Stack::makeCard(Card::Hearts, Card::D2)));
	cards.emplace_back(std::move(Stack::makeCard(Card::Clubs, Card::D2)));
	cards2.emplace_back(std::move(Stack::makeCard(Card::Clubs, Card::D5)));
	cards2.emplace_back(std::move(Stack::makeCard(Card::Clubs, Card::D5)));
	BOOST_CHECK_EQUAL(Rules::Pair, Rules::getCombinationRank(cards) & 0xFF000000);
    BOOST_CHECK_GT(Rules::getCombinationRank(cards2), Rules::getCombinationRank(cards));
}

BOOST_AUTO_TEST_CASE(TestTwoPair)
{
	std::vector<Card> cards;
	cards.emplace_back(std::move(Stack::makeCard(Card::Hearts, Card::D2)));
	cards.emplace_back(std::move(Stack::makeCard(Card::Clubs, Card::D2)));
	cards.emplace_back(std::move(Stack::makeCard(Card::Hearts, Card::D3)));
	cards.emplace_back(std::move(Stack::makeCard(Card::Clubs, Card::D3)));
	BOOST_CHECK_EQUAL(Rules::TwoPairs, Rules::getCombinationRank(cards) & 0xFF000000);
}

BOOST_AUTO_TEST_CASE(TestSet)
{
	std::vector<Card> cards;
	cards.emplace_back(std::move(Stack::makeCard(Card::Hearts, Card::D2)));
	cards.emplace_back(std::move(Stack::makeCard(Card::Clubs, Card::D2)));
	cards.emplace_back(std::move(Stack::makeCard(Card::Diamonds, Card::D2)));
	BOOST_CHECK_EQUAL(Rules::Set, Rules::getCombinationRank(cards) & 0xFF000000);
}

BOOST_AUTO_TEST_CASE(TestStraight)
{
	std::vector<Card> cards;
	cards.emplace_back(std::move(Stack::makeCard(Card::Hearts, Card::D2)));
	cards.emplace_back(std::move(Stack::makeCard(Card::Clubs, Card::D3)));
	cards.emplace_back(std::move(Stack::makeCard(Card::Diamonds, Card::D4)));
	cards.emplace_back(std::move(Stack::makeCard(Card::Hearts, Card::D5)));
	cards.emplace_back(std::move(Stack::makeCard(Card::Diamonds, Card::D6)));
	BOOST_CHECK_EQUAL(Rules::Straight, Rules::getCombinationRank(cards) & 0xFF000000);
}


BOOST_AUTO_TEST_CASE(TestLowestStraight)
{
	std::vector<Card> cards;
	cards.emplace_back(std::move(Stack::makeCard(Card::Hearts, Card::D2)));
	cards.emplace_back(std::move(Stack::makeCard(Card::Clubs, Card::D3)));
	cards.emplace_back(std::move(Stack::makeCard(Card::Diamonds, Card::D4)));
	cards.emplace_back(std::move(Stack::makeCard(Card::Hearts, Card::D5)));
	cards.emplace_back(std::move(Stack::makeCard(Card::Diamonds, Card::ACE)));
	BOOST_CHECK_EQUAL(Rules::Straight, Rules::getCombinationRank(cards) & 0xFF000000);
}

BOOST_AUTO_TEST_CASE(TestHighestStraight)
{
	std::vector<Card> cards;
	cards.emplace_back(std::move(Stack::makeCard(Card::Hearts, Card::ACE)));
	cards.emplace_back(std::move(Stack::makeCard(Card::Clubs, Card::KING)));
	cards.emplace_back(std::move(Stack::makeCard(Card::Diamonds, Card::QUEEN)));
	cards.emplace_back(std::move(Stack::makeCard(Card::Hearts, Card::KNAVE)));
	cards.emplace_back(std::move(Stack::makeCard(Card::Diamonds, Card::D10)));
	BOOST_CHECK_EQUAL(Rules::Straight, Rules::getCombinationRank(cards) & 0xFF000000);
}

BOOST_AUTO_TEST_CASE(TestFlush)
{
	std::vector<Card> cards;
	cards.emplace_back(std::move(Stack::makeCard(Card::Hearts, Card::ACE)));
	cards.emplace_back(std::move(Stack::makeCard(Card::Hearts, Card::KING)));
	cards.emplace_back(std::move(Stack::makeCard(Card::Hearts, Card::QUEEN)));
	cards.emplace_back(std::move(Stack::makeCard(Card::Hearts, Card::KNAVE)));
	cards.emplace_back(std::move(Stack::makeCard(Card::Hearts, Card::D2)));
	BOOST_CHECK_EQUAL(Rules::Flush, Rules::getCombinationRank(cards) & 0xFF000000);
}

BOOST_AUTO_TEST_CASE(TestStraightFlush)
{
	std::vector<Card> cards;
	cards.emplace_back(std::move(Stack::makeCard(Card::Hearts, Card::ACE)));
	cards.emplace_back(std::move(Stack::makeCard(Card::Hearts, Card::KING)));
	cards.emplace_back(std::move(Stack::makeCard(Card::Hearts, Card::QUEEN)));
	cards.emplace_back(std::move(Stack::makeCard(Card::Hearts, Card::KNAVE)));
	cards.emplace_back(std::move(Stack::makeCard(Card::Hearts, Card::D10)));
	BOOST_CHECK_EQUAL(Rules::StraightFlush, Rules::getCombinationRank(cards) & 0xFF000000);
}

BOOST_AUTO_TEST_CASE(TestFullHouse) {
	std::vector<Card> cards;
	cards.emplace_back(std::move(Stack::makeCard(Card::Hearts, Card::ACE)));
	cards.emplace_back(std::move(Stack::makeCard(Card::Hearts, Card::ACE)));
	cards.emplace_back(std::move(Stack::makeCard(Card::Diamonds, Card::QUEEN)));
	cards.emplace_back(std::move(Stack::makeCard(Card::Diamonds, Card::QUEEN)));
	cards.emplace_back(std::move(Stack::makeCard(Card::Hearts, Card::QUEEN)));
	BOOST_CHECK_EQUAL(Rules::FullHouse, Rules::getCombinationRank(cards)  & 0xFF000000);
}

BOOST_AUTO_TEST_SUITE_END()
