// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_simple_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

// Add more tests here
//simple tests
//test simple ctor
TEST(test_simple_get_name_basic) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

//test simple get name
TEST(test_simple_get_name_basic2) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

//test simple add card
TEST(test_simple_add_card_basic) {
    Player * alice = Player_factory("Alice", "Simple");
    Card c(Card::RANK_JACK,Card::SUIT_HEARTS);
    alice->add_card(c);
    ASSERT_EQUAL(alice->play_card(c,Card::SUIT_CLUBS), c);

    delete alice;
}

TEST(test_simple_add_card_edge) {
    Player * alice = Player_factory("Alice", "Simple");
    Card c(Card::RANK_JACK,Card::SUIT_HEARTS);
    Card d(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    alice->add_card(c);
    alice->add_and_discard(d);
    ASSERT_EQUAL(alice->play_card(c,Card::SUIT_CLUBS), d);
    alice->add_card(c);
    ASSERT_NOT_EQUAL(alice->play_card(c,Card::SUIT_CLUBS), d);

    delete alice;
}

TEST(test_simple_add_card_edge2) {
    Player * alice = Player_factory("Alice", "Simple");
    Card a(Card::RANK_NINE,Card::SUIT_DIAMONDS);
    Card b(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card c(Card::RANK_JACK,Card::SUIT_DIAMONDS);
    Card d(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card e(Card::RANK_KING,Card::SUIT_DIAMONDS);
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);
    alice->add_card(e);
    ASSERT_EQUAL(alice->play_card(c,Card::SUIT_DIAMONDS), c);
    ASSERT_EQUAL(alice->play_card(c,Card::SUIT_DIAMONDS), e);
    ASSERT_EQUAL(alice->play_card(c,Card::SUIT_DIAMONDS), d);
    ASSERT_EQUAL(alice->play_card(c,Card::SUIT_DIAMONDS), b);
    ASSERT_EQUAL(alice->play_card(c,Card::SUIT_DIAMONDS), a);
    delete alice;
}



//test make trump
TEST(test_simple_make_trump_basic) {
    Player * alice = Player_factory("Alice", "Simple");
    std::string trump = " ";
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
    ASSERT_EQUAL(alice->make_trump(up,true,1,trump),true);
    ASSERT_EQUAL(trump,Card::SUIT_DIAMONDS);

    delete alice;
}

TEST(test_simple_make_trump_basic2) {
    Player * alice = Player_factory("Alice", "Simple");
    std::string trump = " ";
    Card up = Card(Card::RANK_QUEEN, Card::SUIT_CLUBS);
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
    ASSERT_EQUAL(alice->make_trump(up,false,1,trump),false)

    delete alice;
}

TEST(test_simple_make_trump_basic3) {
    Player * alice = Player_factory("Alice", "Simple");
    std::string trump = "";
    Card up = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card a(Card::RANK_TWO,Card::SUIT_CLUBS);
    Card b(Card::RANK_THREE, Card::SUIT_DIAMONDS);
    Card c(Card::RANK_TWO,Card::SUIT_HEARTS);
    Card d(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card e(Card::RANK_TWO,Card::SUIT_HEARTS);
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);
    alice->add_card(e);
    bool orderup = alice->make_trump(
        up,
        false,
        2,
        trump
    );
    ASSERT_FALSE(orderup);

    delete alice;
}

TEST(test_simple_make_trump_basic4) {
    Player * alice = Player_factory("Alice", "Simple");
    std::string trump = "";
    Card up = Card(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card a(Card::RANK_TWO,Card::SUIT_CLUBS);
    Card b(Card::RANK_THREE, Card::SUIT_DIAMONDS);
    Card c(Card::RANK_TWO,Card::SUIT_HEARTS);
    Card d(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card e(Card::RANK_TWO,Card::SUIT_HEARTS);
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);
    alice->add_card(e);
    bool orderup = alice->make_trump(
        up,
        false,
        2,
        trump
    );
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump,Card::SUIT_DIAMONDS);
    delete alice;
}

TEST(test_simple_make_trump_basic5) {
    Player * alice = Player_factory("Alice", "Simple");
    std::string trump = "";
    Card up = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card a(Card::RANK_TWO,Card::SUIT_CLUBS);
    Card b(Card::RANK_THREE, Card::SUIT_DIAMONDS);
    Card c(Card::RANK_TWO,Card::SUIT_HEARTS);
    Card d(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card e(Card::RANK_TWO,Card::SUIT_HEARTS);
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);
    alice->add_card(e);
    bool orderup = alice->make_trump(
        up,
        true,
        2,
        trump
    );
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump,Card::SUIT_CLUBS);
    delete alice;
}

//test add discard card
TEST(test_simple_add_discard_basic) {
    Player * alice = Player_factory("Alice", "Simple");
    std::string trump = "";
    Card up = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card a(Card::RANK_TWO,Card::SUIT_CLUBS);
    Card b(Card::RANK_THREE, Card::SUIT_DIAMONDS);
    Card c(Card::RANK_TWO,Card::SUIT_HEARTS);
    Card d(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card e(Card::RANK_TWO,Card::SUIT_HEARTS);
     alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);
    alice->add_card(e);
    alice->add_and_discard(up);
    ASSERT_EQUAL(alice->play_card(b,Card::SUIT_DIAMONDS), d);
    ASSERT_EQUAL(alice->play_card(b,Card::SUIT_DIAMONDS), b);
    ASSERT_EQUAL(alice->play_card(b,Card::SUIT_DIAMONDS), c);
    ASSERT_EQUAL(alice->play_card(b,Card::SUIT_DIAMONDS), a);
    ASSERT_EQUAL(alice->play_card(b,Card::SUIT_DIAMONDS), up);
    delete alice;
}

TEST(test_simple_add_discard_edge) {
    Player * alice = Player_factory("Alice", "Simple");
    std::string trump = "";
    Card up = Card(Card::RANK_TWO, Card::SUIT_DIAMONDS);
    Card a(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card b(Card::RANK_FOUR, Card::SUIT_DIAMONDS);
    Card c(Card::RANK_THREE,Card::SUIT_DIAMONDS);
    Card d(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card e(Card::RANK_NINE,Card::SUIT_DIAMONDS);
     alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);
    alice->add_card(e);
    alice->add_and_discard(up);
    ASSERT_EQUAL(alice->play_card(b,Card::SUIT_DIAMONDS), d);
    ASSERT_EQUAL(alice->play_card(b,Card::SUIT_DIAMONDS), a);
    ASSERT_EQUAL(alice->play_card(b,Card::SUIT_DIAMONDS), e);
    ASSERT_EQUAL(alice->play_card(b,Card::SUIT_DIAMONDS), b);
    ASSERT_EQUAL(alice->play_card(b,Card::SUIT_DIAMONDS), c);
    delete alice;
}

TEST(test_simple_add_discard_edge2) {
    Player * alice = Player_factory("Alice", "Simple");
    std::string trump = "";
    Card up = Card(Card::RANK_TWO, Card::SUIT_DIAMONDS);
    Card a(Card::RANK_TEN, Card::SUIT_SPADES);
    Card b(Card::RANK_FOUR, Card::SUIT_SPADES);
    Card c(Card::RANK_THREE,Card::SUIT_SPADES);
    Card d(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card e(Card::RANK_NINE,Card::SUIT_SPADES);
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);
    alice->add_card(e);
    alice->add_and_discard(up);
    ASSERT_EQUAL(alice->play_card(up,Card::SUIT_DIAMONDS), up);
    ASSERT_EQUAL(alice->play_card(up,Card::SUIT_DIAMONDS), b);
    ASSERT_EQUAL(alice->play_card(up,Card::SUIT_DIAMONDS), e);
    ASSERT_EQUAL(alice->play_card(up,Card::SUIT_DIAMONDS), a);
    ASSERT_EQUAL(alice->play_card(up,Card::SUIT_DIAMONDS), d);
    delete alice;
}

//test lead card
TEST(test_simple_card_basic) {
    Player * alice = Player_factory("Alice", "Simple");
    std::string trump = Card::SUIT_DIAMONDS;
    Card a(Card::RANK_TWO,Card::SUIT_CLUBS);
    Card b(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c(Card::RANK_TWO,Card::SUIT_HEARTS);
    Card d(Card::RANK_FOUR, Card::SUIT_DIAMONDS);
    Card e(Card::RANK_TWO,Card::SUIT_HEARTS);
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);
    alice->add_card(e);
    ASSERT_EQUAL(alice->lead_card(trump),a);

    delete alice;
}

TEST(test_simple_card_basic2) {
    Player * alice = Player_factory("Alice", "Simple");
    std::string trump = Card::SUIT_DIAMONDS;
    Card a(Card::RANK_TWO,Card::SUIT_DIAMONDS);
    Card b(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card c(Card::RANK_TWO,Card::SUIT_DIAMONDS);
    Card d(Card::RANK_FOUR, Card::SUIT_DIAMONDS);
    Card e(Card::RANK_JACK,Card::SUIT_HEARTS);
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);
    alice->add_card(e);
    ASSERT_EQUAL(alice->lead_card(trump),e);

    delete alice;
}

TEST(test_simple_card_edge) {
    Player * alice = Player_factory("Alice", "Simple");
    std::string trump = Card::SUIT_DIAMONDS;
    Card a(Card::RANK_TWO,Card::SUIT_DIAMONDS);
    Card b(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c(Card::RANK_TWO,Card::SUIT_DIAMONDS);
    Card d(Card::RANK_FOUR, Card::SUIT_DIAMONDS);
    Card e(Card::RANK_ACE,Card::SUIT_DIAMONDS);
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);
    alice->add_card(e);
    ASSERT_EQUAL(alice->lead_card(trump),b);

    delete alice;
}

TEST(test_simple_card_edge2) {
    Player * alice = Player_factory("Alice", "Simple");
    std::string trump = Card::SUIT_CLUBS;
    Card a(Card::RANK_TWO,Card::SUIT_DIAMONDS);
    Card b(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c(Card::RANK_TWO,Card::SUIT_DIAMONDS);
    Card d(Card::RANK_FOUR, Card::SUIT_DIAMONDS);
    Card e(Card::RANK_ACE,Card::SUIT_DIAMONDS);
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);
    alice->add_card(e);
    ASSERT_EQUAL(alice->lead_card(trump),e);

    delete alice;
}

//test play card
TEST(test_simple_card_basic12) {
    Player * alice = Player_factory("Alice", "Simple");
    std::string trump = Card::SUIT_DIAMONDS;
    Card led = Card(Card::RANK_EIGHT, Card::SUIT_SPADES);
    Card a(Card::RANK_TWO,Card::SUIT_CLUBS);
    Card b(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c(Card::RANK_TWO,Card::SUIT_HEARTS);
    Card d(Card::RANK_FOUR, Card::SUIT_DIAMONDS);
    Card e(Card::RANK_TWO,Card::SUIT_HEARTS);
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);
    alice->add_card(e);
    ASSERT_EQUAL(alice->play_card(led,trump), c);

    delete alice;
}

TEST(test_simple_card_basic22) {
    Player * alice = Player_factory("Alice", "Simple");
    std::string trump = Card::SUIT_DIAMONDS;
    Card led = Card(Card::RANK_EIGHT, Card::SUIT_CLUBS);
    Card a(Card::RANK_TWO,Card::SUIT_CLUBS);
    Card b(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c(Card::RANK_TWO,Card::SUIT_HEARTS);
    Card d(Card::RANK_FOUR, Card::SUIT_DIAMONDS);
    Card e(Card::RANK_TWO,Card::SUIT_HEARTS);
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);
    alice->add_card(e);
    ASSERT_EQUAL(alice->play_card(led,trump), a);

    delete alice;
}

TEST(test_simple_card_basic23) {
    Player * alice = Player_factory("Alice", "Simple");
    std::string trump = Card::SUIT_HEARTS;
    Card led = Card(Card::RANK_KING, Card::SUIT_SPADES);
    Card a(Card::RANK_NINE,Card::SUIT_SPADES);
    Card b(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card c(Card::RANK_QUEEN,Card::SUIT_SPADES);
    Card d(Card::RANK_ACE, Card::SUIT_HEARTS);
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);
    ASSERT_EQUAL(alice->play_card(led,trump), c);

    delete alice;
}


TEST(test_simple_card_basic33) {
    Player * alice = Player_factory("Alice", "Simple");
    std::string trump = Card::SUIT_SPADES;
    Card led = Card(Card::RANK_EIGHT, Card::SUIT_CLUBS);
    Card a(Card::RANK_TWO,Card::SUIT_CLUBS);
    Card b(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card c(Card::RANK_TWO,Card::SUIT_HEARTS);
    Card d(Card::RANK_FOUR, Card::SUIT_DIAMONDS);
    Card e(Card::RANK_TWO,Card::SUIT_HEARTS);
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);
    alice->add_card(e);
    ASSERT_EQUAL(alice->play_card(led,trump), a);

    delete alice;
}

TEST(test_simple_card_basic4) {
  Player * alice = Player_factory("Alice", "Simple");
    std::string trump = Card::SUIT_SPADES;
    Card led = Card(Card::RANK_EIGHT, Card::SUIT_CLUBS);
    Card a(Card::RANK_TWO,Card::SUIT_DIAMONDS);
    Card b(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card c(Card::RANK_TWO,Card::SUIT_HEARTS);
    Card d(Card::RANK_FOUR, Card::SUIT_DIAMONDS);
    Card e(Card::RANK_TWO,Card::SUIT_HEARTS);
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);
    alice->add_card(e);
    ASSERT_EQUAL(alice->play_card(led,trump), c);

    delete alice;
}

TEST(test_simple_cedard_basic5) {
  Player * alice = Player_factory("Alice", "Simple");
    std::string trump = Card::SUIT_SPADES;
    Card led = Card(Card::RANK_EIGHT, Card::SUIT_SPADES);
    Card a(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card b(Card::RANK_TWO,Card::SUIT_DIAMONDS);
    Card c(Card::RANK_TWO,Card::SUIT_HEARTS);
    Card d(Card::RANK_FOUR, Card::SUIT_DIAMONDS);
    Card e(Card::RANK_TWO,Card::SUIT_HEARTS);
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);
    alice->add_card(e);
    ASSERT_EQUAL(alice->play_card(led,trump), a);

    delete alice;
}

TEST(test_simple_card_basic6) {
  Player * alice = Player_factory("Alice", "Simple");
    std::string trump = Card::SUIT_SPADES;
    Card led = Card(Card::RANK_EIGHT, Card::SUIT_SPADES);
    Card a(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card b(Card::RANK_JACK,Card::SUIT_SPADES);
    Card c(Card::RANK_TWO,Card::SUIT_HEARTS);
    Card d(Card::RANK_FOUR, Card::SUIT_DIAMONDS);
    Card e(Card::RANK_TWO,Card::SUIT_HEARTS);
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);
    alice->add_card(e);
    ASSERT_EQUAL(alice->play_card(led,trump), b);

    delete alice;
}

TEST(test_simple_card_basic7) {
  Player * alice = Player_factory("Alice", "Simple");
    std::string trump = Card::SUIT_SPADES;
    Card led = Card(Card::RANK_EIGHT, Card::SUIT_DIAMONDS);
    Card a(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card b(Card::RANK_JACK,Card::SUIT_SPADES);
    Card c(Card::RANK_TWO,Card::SUIT_SPADES);
    Card d(Card::RANK_FOUR, Card::SUIT_HEARTS);
    Card e(Card::RANK_TWO,Card::SUIT_HEARTS);
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);
    alice->add_card(e);
    ASSERT_EQUAL(alice->play_card(led,trump), e);

    delete alice;
}

TEST(test_simple_card_basic8) {
  Player * alice = Player_factory("Alice", "Simple");
    std::string trump = Card::SUIT_SPADES;
    Card led = Card(Card::RANK_EIGHT, Card::SUIT_SPADES);
    Card a(Card::RANK_TWO,Card::SUIT_HEARTS);
    Card b(Card::RANK_JACK,Card::SUIT_DIAMONDS);
    Card c(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card d(Card::RANK_FOUR, Card::SUIT_HEARTS);
    Card e(Card::RANK_TWO,Card::SUIT_DIAMONDS);
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);
    alice->add_card(e);
    ASSERT_EQUAL(alice->play_card(led,trump), a);

    delete alice;
}

TEST(test_simple_card_basic9) {
  Player * alice = Player_factory("Alice", "Simple");
    std::string trump = Card::SUIT_SPADES;
    Card led = Card(Card::RANK_EIGHT, Card::SUIT_CLUBS);
    Card a(Card::RANK_NINE,Card::SUIT_SPADES);
    Card b(Card::RANK_NINE,Card::SUIT_HEARTS);
    Card c(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card d(Card::RANK_KING, Card::SUIT_HEARTS);
    Card e(Card::RANK_ACE,Card::SUIT_CLUBS);
    alice->add_card(a);
    alice->add_card(b);
    alice->add_card(c);
    alice->add_card(d);
    alice->add_card(e);
    ASSERT_EQUAL(alice->play_card(led,trump), e);

    delete alice;
}

TEST(test_simple_card_basic10) {
  Player * alice = Player_factory("Alice", "Simple");
    std::string trump = Card::SUIT_DIAMONDS;
    Card led = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card a(Card::RANK_NINE,Card::SUIT_DIAMONDS);
    Card b(Card::RANK_TEN,Card::SUIT_SPADES);
    alice->add_card(a);
    alice->add_card(b);
    ASSERT_EQUAL(alice->play_card(led,trump), a);

    delete alice;
}

//test human functions
//test simple ctor
TEST(test_human_ctor_basic) {
    Player * alice = Player_factory("Alice", "Human");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

//test simple get name
TEST(test_human_get_name_basic) {
    Player * alice = Player_factory("Alice", "Human");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

//test outside functions
//test <<
TEST(test_player_print) {
    // Create a Human player
  Player * human = Player_factory("NotRobot", "Human");

  // Print the player using the stream insertion operator
  ostringstream oss1;
  oss1 << * human;

  // Verify that the output is the player's name
  ASSERT_EQUAL(oss1.str(), "NotRobot");

  // Create a Simple player
  Player * alice = Player_factory("Alice", "Simple");

  // Print the player using the stream insertion operator
  ostringstream oss2;
  oss2 << *alice;
  ASSERT_EQUAL(oss2.str(), "Alice");

  // Clean up players that were created using Player_factory()
  delete human;
  delete alice;
}



TEST_MAIN()
