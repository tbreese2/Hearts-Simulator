// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

// Add more tests here
//simple tests
//test simple ctor
TEST(test_player_get_name_basic) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

//test simple get name
TEST(test_simple_get_name_basic) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

//test simple add card
TEST(test_simple_add_card_basic) {
    Player * alice = Player_factory("Alice", "Simple");
    Card c(Card::RANK_JACK,Card::SUIT_HEARTS);
    alice->add_card(c);
}

TEST_MAIN()
