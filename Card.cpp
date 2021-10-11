// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below
//card class helper functions
void Card::check_invariants() const
{
    bool validSuit = false;
    bool validRank = false;

    //check if valid suit
    for(int s = 0; s < 4; s++)
    {
      if (SUIT_NAMES_BY_WEIGHT[s] == suit)
      {
        validSuit = true;
      }
    }
    
    for(int r = 0; r < 13; r++)
    {
      if (RANK_NAMES_BY_WEIGHT[r])
      {
        validRank = true;
      }
    }
    assert(validSuit);
    assert(validRank);
}

//REQUIRES valid suit as input
//EFFECTS returns next suit
std::string Card::return_same_color_suit(const std::string &trump) const
{
    if (trump == Card::SUIT_CLUBS)
    {
        return Card::SUIT_SPADES;
    } 
    else if (trump == Card::SUIT_DIAMONDS) 
    {
        return Card::SUIT_HEARTS;
    } 
    else if (trump == Card::SUIT_SPADES) 
    {
        return Card::SUIT_CLUBS;
    } 
    else 
    {
        return Card::SUIT_DIAMONDS;
    }
}

//card class functions

//EFFECTS Initializes Card to the Two of Spades
Card::Card()
    : rank(RANK_TWO), suit(SUIT_SPADES)
{
    check_invariants();
}

//REQUIRES rank is one of "Two", "Three", "Four", "Five", "Six", "Seven",
//  "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
//  suit is one of "Spades", "Hearts", "Clubs", "Diamonds"
//EFFECTS Initializes Card to specified rank and suit
Card::Card(const std::string &rank_in, const std::string &suit_in)
    : rank(rank_in), suit(suit_in)
{
    check_invariants();
}

//EFFECTS Returns the rank
std::string Card::get_rank() const
{
    return rank;
}

//EFFECTS Returns the suit.  Does not consider trump.
std::string Card::get_suit() const
{
    return suit;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns the suit
//HINT: the left bower is the trump suit!
std::string Card::get_suit(const std::string &trump) const
{
    assert(false);
}

//EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
bool Card::is_face() const
{
    return rank == RANK_JACK || rank == RANK_QUEEN || rank == RANK_KING || rank == RANK_ACE;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the trump suit
 bool Card::is_right_bower(const std::string &trump) const
{
    if (suit == trump && rank == Card::RANK_JACK) {
        return true;
    }
    return false;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the next suit
bool Card::is_left_bower(const std::string &trump) const
{
    std::string next_suit = return_same_color_suit(trump);
    if (suit == next_suit && rank == Card::RANK_JACK) {
        return true;
    }
    return false;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if the card is a trump card.  All cards of the trump
// suit are trump cards.  The left bower is also a trump card.
bool Card::is_trump(const std::string &trump) const
{
    assert(false);
}

//outside class functions

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs)
{
    assert(false);
}

//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card &lhs, const Card &rhs)
{
    assert(false);
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs)
{
    assert(false);
}

//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card &lhs, const Card &rhs)
{
    assert(false);
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs)
{
    assert(false);
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs)
{
    assert(false);
}

//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
std::string Suit_next(const std::string &suit)
{
    assert(false);
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card)
{
    assert(false);
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const std::string &trump)
{
    assert(false);
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump)
{
    assert(false);
}   


// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec (see the appendices) before implementing
// the following operator overload functions:
//   operator<<
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=
