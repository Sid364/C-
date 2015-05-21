#ifndef _H_CARD_
#define _H_CARD_

#include <memory>
#include <utility>

// Forward declarations
class Stack;
class Player;
class Desk;

/// Playing card representation
class Card {
public:
    /// Possible card value enumeration
    enum Value {
		NONE = 0x00,
        D2 = 0x02,
        D3,
        D4,
        D5,
        D6,
        D7,
        D8,
        D9,
        D10,
        KNAVE,
        QUEEN,
        KING,
        ACE
    };

    /// Possible card suits enumeration
    enum Suit {
        Spades  = 0x100,
        Diamonds = 0x101,
        Clubs     = 0x102,
        Hearts   = 0x103,
        RedFlag = 0x01,
    };

    /// Move card from one place to another
    /**
    *   \param c [in] current card reference
    */
    Card(Card && c);
	/// Move card from one place to another
	/**
	*   \param c [in] current card reference
	*/
	Card & operator =(Card && c);
    /// Look to card for checking value and suit
    /**
    * \param player Player reference to check if actor can see card
    */
    std::pair<Suit, Value> look(std::shared_ptr<Player> const & player) const; //throws InvalidAccess
    /// Open card. This card become visible to all players forever
    void open(std::shared_ptr<Player> const & player);
    void writeCard();
private:
    Card(Suit s, Value v,  std::shared_ptr<Player> owner);
    void setOwner(std::shared_ptr<Player> const &);
    Card(Card const &) = delete;
    Card & operator=(Card const &) = delete;
    Card(Value v, Suit s);
    friend class Stack;
    friend class ComputerPlayer;
    friend class Desk;

    Value value;
    Suit suit;
    std::shared_ptr<Player> owner;
    bool isOpen;
};



#endif //_H_CARD_