// Project UID 1d9f47bfc76643019cfbf037641defe1

//include
#include <cassert>
#include <iostream>
#include <string>
#include <array>
#include "Player.h"

//object declarations
//two types of players: a human, and a computer
//first we will instansiate the human class
class Simple : public Player
{
public:
  //REQUIRES string is valid
  //EFFECTS sets players name
  Simple(std::string name_in);

  //EFFECTS returns player's name
  const std::string & get_name() const;

  //REQUIRES player has less than MAX_HAND_SIZE cards
  //EFFECTS  adds Card c to Player's hand
  void add_card(const Card &c);

  //REQUIRES round is 1 or 2
  //MODIFIES order_up_suit
  //EFFECTS If Player wishes to order up a trump suit then return true and
  //  change order_up_suit to desired suit.  If Player wishes to pass, then do
  //  not modify order_up_suit and return false.
  bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const;

  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
  void add_and_discard(const Card &upcard);

  //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  Card lead_card(const std::string &trump);

  //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
  Card play_card(const Card &led_card, const std::string &trump);

  // Maximum number of cards in a player's hand
  static const int MAX_HAND_SIZE = 5;
private:
  std::string name;
  std::array<Card, MAX_HAND_SIZE> cards;
  int lastCard;
};

class Human : public Player
{
public:
 //EFFECTS returns player's name
  const std::string & get_name() const;

  //REQUIRES player has less than MAX_HAND_SIZE cards
  //EFFECTS  adds Card c to Player's hand
  void add_card(const Card &c);

  //REQUIRES round is 1 or 2
  //MODIFIES order_up_suit
  //EFFECTS If Player wishes to order up a trump suit then return true and
  //  change order_up_suit to desired suit.  If Player wishes to pass, then do
  //  not modify order_up_suit and return false.
  bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const;

  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
  void add_and_discard(const Card &upcard);

  //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  Card lead_card(const std::string &trump);

  //REQUIRES Player has at least one card, trump is a valid suit
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
  virtual Card play_card(const Card &led_card, const std::string &trump);

  // Maximum number of cards in a player's hand
  static const int MAX_HAND_SIZE = 5;
private:
  std::string name;
  std::array<Card, MAX_HAND_SIZE> cards;
  int lastCard;
};

//next we will define functions for each type of player

//first, simple player functions
//REQUIRES string is valid
//EFFECTS sets players name
Simple::Simple(std::string name_in)
    : name(name_in), lastCard(0)
{
}

//EFFECTS returns player's name
const std::string & Simple::get_name() const
{
  return name;
}


//REQUIRES player has less than MAX_HAND_SIZE cards
//EFFECTS  adds Card c to Player's hand
void Simple::add_card(const Card &c)
{
  cards[lastCard] = c;
  lastCard++;
}

//REQUIRES round is 1 or 2
//MODIFIES order_up_suit
//EFFECTS If Player wishes to order up a trump suit then return true and
//  change order_up_suit to desired suit.  If Player wishes to pass, then do
//  not modify order_up_suit and return false.
bool Simple::make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const
{
  assert(false);
  return 0;
}

//REQUIRES Player has at least one card
//EFFECTS  Player adds one card to hand and removes one card from hand.
void Simple::add_and_discard(const Card &upcard)
{
  assert(false);
}

//REQUIRES Player has at least one card, trump is a valid suit
//EFFECTS  Leads one Card from Player's hand according to their strategy
//  "Lead" means to play the first Card in a trick.  The card
//  is removed the player's hand.
Card Simple::lead_card(const std::string &trump)
{
  assert(false);
}

//REQUIRES Player has at least one card, trump is a valid suit
//EFFECTS  Plays one Card from Player's hand according to their strategy.
//  The card is removed from the player's hand.
Card Simple::play_card(const Card &led_card, const std::string &trump)
{
  assert(false);
}

//nest the human functions





//functions
//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over
Player * Player_factory(const std::string &name, const std::string &strategy) {
  if (strategy == "Human") {
    //return new Human(name);
  }
   return new Simple(name);
}

std::ostream & operator<<(std::ostream &os, const Player &p) {
  assert(false);
}