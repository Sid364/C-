#ifndef _H_HAND_
#define _H_HAND_

#include <memory>
#include <vector>
#include "Card.h"

// Forward declarations
class Player;

/// Payer hand representation
class Hand {
public:
    //TODO: сделать что-нибудь с этим
    Hand(std::shared_ptr<Player> const & player);

private:

};

#endif //_H_HAND_
