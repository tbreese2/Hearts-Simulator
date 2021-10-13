// Project UID 1d9f47bfc76643019cfbf037641defe1

//includes
#include <cassert>
#include "Pack.h"

// EFFECTS: Initializes the Pack to be in the following standard order:
//          the cards of the lowest suit arranged from lowest rank to
//          highest rank, followed by the cards of the next lowest suit
//          in order from lowest to highest rank, and so on.
// NOTE: The standard order is the same as that in pack.in.
// NOTE: Do NOT use pack.in in your implementation of this function
Pack::Pack()
{
    int i = 0;
    for (int s = 0; s < 4; s++) {
        for (int r = 7; r < 13; r++){
            cards[i] = Card(RANK_NAMES_BY_WEIGHT[r], SUIT_NAMES_BY_WEIGHT[s]);
            i++;
        }
    }
    next = 0;
}

// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(std::istream& pack_input)
{
    int i = 0;
    std::string rank, suit;
    while(pack_input >> rank){
        pack_input >> suit;
        pack_input >> suit;
        cards[i] = Card(rank,suit);
        i++;
    }
    next = 0;
}


// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one()
{
    Card return_Card = cards[next];
    next++;
    return return_Card;
}

// EFFECTS: Resets next index to first card in the Pack
void Pack::reset()
{
    next = 0;
}

// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle()
{
    for(int i = 0; i < 7; i++){
        std::array<Card, PACK_SIZE> cardsShuffled = cards;
        int i1 = 0;
        int i2 = 12;
        int index = 0;
        while(i2 < 24) {
            cardsShuffled[index] = cards[i2];
            index++;
            cardsShuffled[index] = cards[i1];
            index++;
            i1++;
            i2++;
        }
        next = 0;
        cards = cardsShuffled;
    }
}

// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const
{
    return next >= PACK_SIZE;
}