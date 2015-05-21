#ifndef _H_RULES_
#define _H_RULES_

#include <memory>
#include <vector>
#include "Card.h"

/// Useful functions to implement poker rules
namespace Rules {
	/// Mask for getCombinationRank result indicating best found cobbination.
	/// LSB used to rank diffirent combinations of same type
	enum Combinations {
		StraightFlush	= 0x09000000,
		Quads		= 0x08000000,
		FullHouse		= 0x07000000,
		Flush			= 0x06000000,
		Straight		= 0x05000000,
		Set			= 0x04000000,
		TwoPairs		= 0x03000000,
		Pair			= 0x02000000,
		HighCard		= 0x01000000
	};

	/// \param cards Cards
	/// \param player If looking for combinations in hand, Player object passed to card
	/// Get rank of best combination in given cards.
	unsigned int getCombinationRank(std::vector<Card> const & cards, std::shared_ptr<Player> const & player = std::shared_ptr<Player>());
	//writes combination to standard output
	void writeCombination(Combinations combination);
}


#endif //_H_RULES_

