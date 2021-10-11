// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

// Add more test cases here

//test defualt card ctor
TEST(test_defualt_card_ctor_basic)
{
    Card c;
    ASSERT_EQUAL(Card::RANK_TWO, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, c.get_suit());
}

TEST(test_defualt_card_ctor_edge)
{
    Card c;
    ASSERT_EQUAL(Card::SUIT_SPADES, c.get_suit());
    ASSERT_EQUAL(Card::RANK_TWO, c.get_rank());
}

//test card init ctor
TEST(test_card_ctor_edge) {
    Card c(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(Card::RANK_JACK, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, c.get_suit());
}

//test get rank
TEST(test_card_get_rank_basic)
{
    Card c;
    ASSERT_EQUAL(Card::RANK_TWO, c.get_rank());
}

TEST(test_card_get_rank_edge)
{
    Card c(Card::RANK_KING, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_KING, c.get_rank());
}

//test get suit without trump suit
TEST(test_card_get_suit_without_trump_basic)
{
    Card c;
    ASSERT_EQUAL(Card::SUIT_SPADES, c.get_suit());
}

TEST(test_card_get_suit_without_trump_edge)
{
    Card c(Card::RANK_KING, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

//test get suit with trump suit

//test is face
TEST(test_is_face_basic)
{
    Card c(Card::RANK_KING, Card::SUIT_HEARTS);
    Card d(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(true, c.is_face());
    ASSERT_EQUAL(false, d.is_face());
}

TEST(test_is_face_edge)
{
    Card a(Card::RANK_TWO, Card::SUIT_HEARTS);
    Card b(Card::RANK_THREE, Card::SUIT_DIAMONDS);
    Card c(Card::RANK_FOUR, Card::SUIT_HEARTS);
    Card d(Card::RANK_FIVE, Card::SUIT_DIAMONDS);
    Card e(Card::RANK_SIX, Card::SUIT_HEARTS);
    Card f(Card::RANK_SEVEN, Card::SUIT_DIAMONDS);
    Card g(Card::RANK_EIGHT, Card::SUIT_HEARTS);
    Card h(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card i(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card j(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card k(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card l(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(false, a.is_face());
    ASSERT_EQUAL(false, b.is_face());
    ASSERT_EQUAL(false, c.is_face());
    ASSERT_EQUAL(false, d.is_face());
    ASSERT_EQUAL(false, e.is_face());
    ASSERT_EQUAL(false, f.is_face());
    ASSERT_EQUAL(false, g.is_face());
    ASSERT_EQUAL(false, h.is_face());
    ASSERT_EQUAL(true, i.is_face());
    ASSERT_EQUAL(true, j.is_face());
    ASSERT_EQUAL(true, k.is_face());
    ASSERT_EQUAL(true, l.is_face());
}

//test is right bower
TEST(test_is_right_bower_basic)
{
    Card a(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card b(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c(Card::RANK_JACK, Card::SUIT_SPADES);
    Card d(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(true, a.is_right_bower(Card::SUIT_CLUBS));
    ASSERT_EQUAL(true, b.is_right_bower(Card::SUIT_DIAMONDS));
    ASSERT_EQUAL(true, c.is_right_bower(Card::SUIT_SPADES));
    ASSERT_EQUAL(true, d.is_right_bower(Card::SUIT_HEARTS));
    ASSERT_EQUAL(false, a.is_right_bower(Card::SUIT_HEARTS));
    ASSERT_EQUAL(false, b.is_right_bower(Card::SUIT_CLUBS));
    ASSERT_EQUAL(false, c.is_right_bower(Card::SUIT_DIAMONDS));
    ASSERT_EQUAL(false, d.is_right_bower(Card::SUIT_SPADES));
}

TEST(test_is_right_bower_edge)
{
    //loop through every card
    //loop through all suits
    string trumpSuit = Card::SUIT_SPADES;
    for(int s = 0; s < 4; s++)
    {
        for(int r = 0; r < 13; r++)
        {
            Card c(RANK_NAMES_BY_WEIGHT[r],SUIT_NAMES_BY_WEIGHT[s]);
            if (c.get_rank() == Card::RANK_JACK && c.get_suit() == trumpSuit)
            {
                ASSERT_EQUAL(true, c.is_right_bower(trumpSuit));
            } else {
                ASSERT_EQUAL(false, c.is_right_bower(trumpSuit));
            }
        }
    }
}

//test is left bower
TEST(test_is_left_bower_basic)
{
    Card a(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card b(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c(Card::RANK_JACK, Card::SUIT_SPADES);
    Card d(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(true, a.is_left_bower(Card::SUIT_SPADES));
    ASSERT_EQUAL(true, b.is_left_bower(Card::SUIT_HEARTS));
    ASSERT_EQUAL(true, c.is_left_bower(Card::SUIT_CLUBS));
    ASSERT_EQUAL(true, d.is_left_bower(Card::SUIT_DIAMONDS));
    ASSERT_EQUAL(false, a.is_left_bower(Card::SUIT_CLUBS));
    ASSERT_EQUAL(false, b.is_left_bower(Card::SUIT_DIAMONDS));
    ASSERT_EQUAL(false, c.is_left_bower(Card::SUIT_SPADES));
    ASSERT_EQUAL(false, d.is_left_bower(Card::SUIT_HEARTS));
}

TEST(test_is_left_bower_edge)
{
    //loop through every card
    //loop through all suits
    string trumpSuit = Card::SUIT_SPADES;
    for(int s = 0; s < 4; s++)
    {
        for(int r = 0; r < 13; r++)
        {
            Card c(RANK_NAMES_BY_WEIGHT[r],SUIT_NAMES_BY_WEIGHT[s]);
            if (c.get_rank() == Card::RANK_JACK && c.get_suit() == Card::SUIT_CLUBS)
            {
                ASSERT_EQUAL(true, c.is_left_bower(trumpSuit));
            } else {
                ASSERT_EQUAL(false, c.is_left_bower(trumpSuit));
            }
        }
    }
}

//test is trump

TEST_MAIN()
