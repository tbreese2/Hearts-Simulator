
//include
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
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
  Human(std::string name_in);
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

  //helper functions
  Card play_card_human() {
    std::vector<Card> temp = cards;
    std::sort(temp.begin(), temp.end());
    for (size_t i = 0; i < temp.size(); i++) {
      std::cout << "Human player " << name << 
      "'s hand: [" << i << "] " << temp[i].get_rank() 
      << " of " << temp[i].get_suit() << std::endl;
    }
    std::cout << "Human player " << name <<", please select a card:" << std::endl;
    std::string input;
    std::cin >> input;
    Card temp1 = temp[stoi(input)];
    temp.erase(temp.begin()+stoi(input));
    cards = temp;
    return temp1;
  }
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
    if (!Card_less(c,cards[i],upcard.get_suit())) {
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
  Card c;
  for (size_t i = 0; i < cards.size(); i++) {
    if (led_card.get_suit(trump) == cards[i].get_suit(trump)) {
      if (lowestIndex == -1) {
        c = cards[i];
        lowestIndex = i;
      } else if (!Card_less(cards[i],c,trump)) {
        c = cards[i];
        lowestIndex = i;
      }
    }
  }
  if (lowestIndex != -1) { cards.erase(cards.begin()+lowestIndex); return c; }
  c = cards[0];
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
//REQUIRES string is valid
//EFFECTS sets players name
Human::Human(std::string name_in)
    : name(name_in)
{
}

//EFFECTS returns player's name
const std::string & Human::get_name() const
{
  return name;
}


//REQUIRES player has less than MAX_HAND_SIZE cards
//EFFECTS  adds Card c to Player's hand
void Human::add_card(const Card &c)
{
  cards.push_back(c);
}

//REQUIRES round is 1 or 2
//MODIFIES order_up_suit
//EFFECTS If Player wishes to order up a trump suit then return true and
//  change order_up_suit to desired suit.  If Player wishes to pass, then do
//  not modify order_up_suit and return false.
bool Human::make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const
{
  std::vector<Card> temp = cards;
  std::sort(temp.begin(), temp.end());
  for (size_t i = 0; i < temp.size(); i++) {
    std::cout << "Human player " << name << "'s hand: [" 
    << i << "] " << temp[i].get_rank() << " of " 
    << temp[i].get_suit() << std::endl;
  }
  std::cout << "Human player " << name 
  << ", please enter a suit, or \"pass\":" << std::endl;
  std::string input;
  std::cin >> input;
  if (input == "pass") {
    return false;
  }
  order_up_suit = input;
  return true;
}

//REQUIRES Player has at least one card
//EFFECTS  Player adds one card to hand and removes one card from hand.
void Human::add_and_discard(const Card &upcard)
{
  std::vector<Card> temp = cards;
  std::sort(temp.begin(), temp.end());
  for (size_t i = 0; i < temp.size(); i++) {
    std::cout << "Human player " << 
    name << "'s hand: [" << i << "] " 
    << temp[i].get_rank() << " of " << 
    temp[i].get_suit() << std::endl;
  }
  std::cout << "Discard upcard: [-1]" << std::endl;
  std::cout << "Human player " << name 
  <<", please select a card to discard:" << std::endl;
  std::string input;
  std::cin >> input;
  if (stoi(input) == -1) {
    cards = temp;
  } else {
    temp.push_back(upcard);
    temp.erase(temp.begin()+stoi(input));
    cards = temp;
  }
}

//REQUIRES Player has at least one card, trump is a valid suit
//EFFECTS  Leads one Card from Player's hand according to their strategy
//  "Lead" means to play the first Card in a trick.  The card
//  is removed the player's hand.
Card Human::lead_card(const std::string &trump)
{
  return play_card_human();
}

//REQUIRES Player has at least one card, trump is a valid suit
//EFFECTS  Plays one Card from Player's hand according to their strategy.
//  The card is removed from the player's hand.
Card Human::play_card(const Card &led_card, const std::string &trump) {
  return lead_card(trump);
}




//functions
//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over
Player * Player_factory(const std::string &name, const std::string &strategy) {
  if (strategy == "Human") {
    return new Human(name);
  } else if (strategy == "Simple") {
   return new Simple(name);
  }
  // Invalid strategy if we get here
  assert(false);
  return nullptr;
}

std::ostream & operator<<(std::ostream &os, const Player &p) {
  os << p.get_name();
  return os;
}