
#include "Player.h"
#include "Card.h"
#include "unit_test_framework.h"
#include <sstream>
using namespace std;

TEST(test_human_make_trump) {
    Player * alice = Player_factory("Alice", "Human");
    std::string trump = " ";
    std::string suit = "";
    Card up = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card a(Card::RANK_TWO,Card::SUIT_CLUBS);
    Card b(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c(Card::RANK_TWO,Card::SUIT_HEARTS);
    Card d(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card e(Card::RANK_TWO,Card::SUIT_HEARTS);
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);
    alice->add_card(e);
    alice->make_trump(up,1,1,suit);
    alice->add_and_discard(up);
    alice->lead_card(trump);
}



TEST_MAIN()