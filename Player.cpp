// Project UID 1d9f47bfc76643019cfbf037641defe1

//include
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include "Player.h"

//helper funciton
std::string lowest_possible_rank(std::string led)
{
  for (int i = 0; i < 4; i++) {
    if (SUIT_NAMES_BY_WEIGHT[i] != led) {
      return SUIT_NAMES_BY_WEIGHT[i];
    }
  }
  std::string s;
  return s;
}

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
  std::vector<Card> cards;
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
  std::vector<Card> cards;
};

//next we will define functions for each type of player

//first, simple player functions
//REQUIRES string is valid
//EFFECTS sets players name
Simple::Simple(std::string name_in)
    : name(name_in)
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
  cards.push_back(c);
}

//REQUIRES round is 1 or 2
//MODIFIES order_up_suit
//EFFECTS If Player wishes to order up a trump suit then return true and
//  change order_up_suit to desired suit.  If Player wishes to pass, then do
//  not modify order_up_suit and return false.
bool Simple::make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const
{
  int trumpCardsInHand = 0;
  for (size_t i = 0; i < cards.size(); i++) {
    if (cards[i].is_trump(upcard.get_suit()) && cards[i].is_face()) {
      trumpCardsInHand++;
    }
  }
  if (round == 1)
  {
    if (trumpCardsInHand > 1) {
      order_up_suit = upcard.get_suit();
      return true;
    }
    return false;
  }
  trumpCardsInHand = 0;
  for (size_t i = 0; i < cards.size(); i++) {
    if (cards[i].is_trump(Suit_next(upcard.get_suit())) && cards[i].is_face()) {
      trumpCardsInHand++;
    }
  }
  if (is_dealer) {
    order_up_suit = Suit_next(upcard.get_suit());
    return true;
  }
  if (trumpCardsInHand > 0){
    order_up_suit = Suit_next(upcard.get_suit());
    return true;
  }
  return false;
}

//REQUIRES Player has at least one card
//EFFECTS  Player adds one card to hand and removes one card from hand.
void Simple::add_and_discard(const Card &upcard)
{
  cards.push_back(upcard);
  int lowestIndex = 0;
  Card c = cards[lowestIndex];
  for (size_t i = 0; i < cards.size(); i++) {
    if (cards[i]<=c) {
      c = cards[i];
      lowestIndex = i;
    }
  }
  cards.erase(cards.begin()+lowestIndex);
}

//REQUIRES Player has at least one card, trump is a valid suit
//EFFECTS  Leads one Card from Player's hand according to their strategy
//  "Lead" means to play the first Card in a trick.  The card
//  is removed the player's hand.
Card Simple::lead_card(const std::string &trump)
{
  Card c = Card(Card::RANK_TWO,lowest_possible_rank(trump));
  int cardIndex = -1;
  for (size_t i = 0; i < cards.size(); i++) {
    if (!cards[i].is_trump(trump) && cards[i]>=c)
    {
      c = cards[i]; 
      cardIndex = i;
    }
  }
  if (cardIndex == -1) {
    c = Card(Card::RANK_TWO,trump);
    for (size_t i = 0; i < cards.size(); i++) {
      if (!Card_less(cards[i],c,trump))
      {
        c = cards[i]; 
        cardIndex = i;
      }
    }
    cards.erase(cards.begin()+cardIndex);
    return c;
  }
  cards.erase(cards.begin()+cardIndex);
  return c;
}

//REQUIRES Player has at least one card, trump is a valid suit
//EFFECTS  Plays one Card from Player's hand according to their strategy.
//  The card is removed from the player's hand.
Card Simple::play_card(const Card &led_card, const std::string &trump) {
  int lowestIndex = -1;
  Card c = Card(Card::RANK_TWO,led_card.get_suit());
  for (size_t i = 0; i < cards.size(); i++) {
    if (led_card.get_suit() == trump) {
      if (!Card_less(cards[i],c,trump) && (cards[i].get_suit() == led_card.get_suit() || cards[i].is_left_bower(trump))) {
        c = cards[i];
        lowestIndex = i;
      }
    } else if (Suit_next(led_card.get_suit()) == trump && cards[i].get_suit() == led_card.get_suit()) {
      if (cards[i]>=c && !cards[i].is_left_bower(trump)) { c = cards[i]; lowestIndex = i; }
    } else if (cards[i].get_suit() == led_card.get_suit()){
      if (cards[i]>=c) { c = cards[i]; lowestIndex = i;}
    }
  }
  if (lowestIndex != -1) { cards.erase(cards.begin()+lowestIndex); return c; }
  else if (c.get_suit() == led_card.get_suit() && lowestIndex != -1) { 
    cards.erase(cards.begin()+lowestIndex); 
    return c; 
  }
  c = Card(Card::RANK_ACE,Card::SUIT_DIAMONDS);
  lowestIndex = 0;
  for (size_t i = 0; i < cards.size(); i++) {
    if (!Card_less(c,cards[i],trump)) {
      c = cards[i];
      lowestIndex = i;
    }
  }
  cards.erase(cards.begin()+lowestIndex);
  return c;
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