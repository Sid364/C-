#include <iostream>
#include "Card.h"
#include "Exceptions.h"

Card::Card(Card && c) : value(c.value), suit(c.suit), isOpen(c.isOpen), owner(c.owner) {
    c.value = (Value)0;
    c.suit = (Suit)0;
}


Card & Card::operator =(Card && c) {
	value = c.value;
	suit = c.suit;
	isOpen = c.isOpen;
	owner = c.owner;
	c.value = (value);
	c.suit = (suit);
	return *this;
}

std::pair<Card::Suit, Card::Value> Card::look(std::shared_ptr<Player> const & player) const {
	//std::cout << "in look" << " " << suit;
	if (isOpen || (owner && player == owner)) {
		return std::make_pair(suit, value);
	}
    throw InvalidAccess();
}

void Card::setOwner(std::shared_ptr<Player> const & player) {
    owner = player;
}

Card::Card(Value v, Suit s) : suit(s), value(v), isOpen(false) {
}
Card::Card(Suit s, Value v, std::shared_ptr<Player> owner) : suit(s), value(v), isOpen(false) {
	setOwner(owner);
}

void Card::open(std::shared_ptr<Player> const & player) {
    isOpen = true;
	setOwner(player);
}

void Card::writeCard() {
    switch (value) {
        case D2: std::cout << "2 "; break;
        case D3: std::cout << "3 "; break;
        case D4: std::cout << "4 "; break;
        case D5: std::cout << "5 "; break;
        case D6: std::cout << "6 "; break;
        case D7: std::cout << "7 "; break;
        case D8: std::cout << "8 "; break;
        case D9: std::cout << "9 "; break;
        case D10: std::cout << "10 "; break;
        case KNAVE: std::cout << "KNAVE "; break;
        case QUEEN: std::cout << "QUEEN "; break;
        case KING: std::cout << "KING "; break;
        case ACE: std::cout << "ACE "; break;
        default: std::cout << "default" ; break;
    }
    switch (suit) {
        case Hearts : std::cout << "of Hearts\n"; break;
        case Spades : std::cout << "of Spades\n"; break;
        case Diamonds : std::cout << "of Diamonds\n"; break;
        case Clubs : std::cout << " of Clubs\n"; break;
        default: break;
    }
}
