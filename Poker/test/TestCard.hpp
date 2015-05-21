#include <boost/test/unit_test.hpp>
#include "ComputerPlayer.h"
#include "Card.h"
#include "Exceptions.h"
#include "Stack.hpp"

BOOST_AUTO_TEST_SUITE(TestCard)


BOOST_AUTO_TEST_CASE(CheckLookThrow)
{
    BOOST_CHECK_THROW(Stack().makeCard().look(std::shared_ptr<Player>()), InvalidAccess);
}

BOOST_AUTO_TEST_CASE(CheckLookThrowAnotherPlayer)
{
    std::shared_ptr<Player> p, p1;
    //auto p = std::make_shared<Player>();
    //auto p1 = std::make_shared<Player>();
    BOOST_CHECK_THROW(Stack().makeCard(p).look(p1), InvalidAccess);
}


BOOST_AUTO_TEST_CASE(CheckLookNoThrowAndValid)
{
    std::shared_ptr<Player> pp;
    pp.reset(new ComputerPlayer());
    //auto p = std::make_shared<Player>();
    Card c = std::move(Stack().makeCard(pp));
    BOOST_CHECK_EQUAL(Card::Spades, c.look(pp).first);
    BOOST_CHECK_EQUAL(Card::D2, c.look(pp).second);
}

BOOST_AUTO_TEST_CASE(CheckLookNoThrowAfterOpen)
{
    std::shared_ptr<Player> p, p1;
    //auto p = std::make_shared<Player>();
    //auto p1 = std::make_shared<Player>();
    Card c = std::move(Stack().makeCard(p));
    c.open(p);
    BOOST_CHECK_EQUAL(Card::Spades, c.look(p1).first);
    BOOST_CHECK_EQUAL(Card::D2, c.look(p1).second);
}

BOOST_AUTO_TEST_SUITE_END()