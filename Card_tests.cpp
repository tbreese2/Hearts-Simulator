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
TEST(test_get_suit_with_trump_basic)
{
    Card a(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card b(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c(Card::RANK_JACK, Card::SUIT_SPADES);
    Card d(Card::RANK_JACK, Card::SUIT_HEARTS);

    //test normal functionality with jacks
    ASSERT_EQUAL(Card::SUIT_CLUBS, a.get_suit(Card::SUIT_CLUBS));
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, b.get_suit(Card::SUIT_DIAMONDS));
    ASSERT_EQUAL(Card::SUIT_SPADES, c.get_suit(Card::SUIT_SPADES));
    ASSERT_EQUAL(Card::SUIT_HEARTS, d.get_suit(Card::SUIT_HEARTS));

    //test left bower functionality with jacks
    ASSERT_EQUAL(Card::SUIT_SPADES, a.get_suit(Card::SUIT_SPADES));
    ASSERT_EQUAL(Card::SUIT_HEARTS, b.get_suit(Card::SUIT_HEARTS));
    ASSERT_EQUAL(Card::SUIT_CLUBS, c.get_suit(Card::SUIT_CLUBS));
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, d.get_suit(Card::SUIT_DIAMONDS));
}

TEST(test_get_suit_with_trump_edge)
{
    string trumpSuit = Card::SUIT_SPADES;
    for(int s = 0; s < 4; s++)
    {
        for(int r = 0; r < 13; r++)
        {
            Card c(RANK_NAMES_BY_WEIGHT[r],SUIT_NAMES_BY_WEIGHT[s]);
            //check if left bower
            if (c.get_rank() == Card::RANK_JACK && c.is_left_bower(trumpSuit)) 
            {
                ASSERT_EQUAL(c.get_suit(trumpSuit), trumpSuit);
            } else {
                ASSERT_EQUAL(c.get_suit(trumpSuit), SUIT_NAMES_BY_WEIGHT[s]);
            }
        }
    }
}

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
TEST(test_is_trump_basic)
{
    //initiilize
    string trumpSuit = Card::SUIT_SPADES;

    //test if suit is working and bower is working
    Card a(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card b(Card::RANK_KING, Card::SUIT_SPADES);
    Card c(Card::RANK_TWO, Card::SUIT_SPADES);
    Card d(Card::RANK_NINE, Card::SUIT_SPADES);

    //test all cards in trump suit
    ASSERT_EQUAL(true, a.is_trump(trumpSuit));
    ASSERT_EQUAL(true, b.is_trump(trumpSuit));
    ASSERT_EQUAL(true, c.is_trump(trumpSuit));
    ASSERT_EQUAL(true, d.is_trump(trumpSuit));

    //test same cards but change suit
    ASSERT_EQUAL(false, a.is_trump(Card::SUIT_DIAMONDS));
    ASSERT_EQUAL(false, b.is_trump(Card::SUIT_CLUBS));
    ASSERT_EQUAL(false, c.is_trump(Card::SUIT_CLUBS));
    ASSERT_EQUAL(false, d.is_trump(Card::SUIT_CLUBS));

}

//test to make sure rank is working
TEST(test_is_trump_edge)
{
    //loop through every card
    //loop through all suits
    string trumpSuit = Card::SUIT_SPADES;
    for(int s = 0; s < 4; s++)
    {
        for(int r = 0; r < 13; r++)
        {
            Card c(RANK_NAMES_BY_WEIGHT[r],SUIT_NAMES_BY_WEIGHT[s]);
            //check if trump suit
            if (c.get_suit() == trumpSuit || c.is_left_bower(trumpSuit))
            {
                ASSERT_EQUAL(true, c.is_trump(trumpSuit));
            } else {
                ASSERT_EQUAL(false, c.is_trump(trumpSuit));
            }
        }
    }
}

//test overload functions

//overload testing

//test <
//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
TEST(test_less_than_basic)
{
    Card a(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card b(Card::RANK_THREE, Card::SUIT_CLUBS);
    Card c(Card::RANK_THREE, Card::SUIT_SPADES);
    ASSERT_EQUAL(c<a, true);
    ASSERT_EQUAL(a<c, false);
    ASSERT_EQUAL(a<a, false);
    ASSERT_EQUAL(b<c, false);
    ASSERT_EQUAL(c<b, true);
}

TEST(test_less_than_edge)
{
    Card d(Card::RANK_TWO, Card::SUIT_SPADES);
    for(int s = 0; s < 4; s++)
    {
        for(int r = 0; r < 13; r++)
        {
            Card e(RANK_NAMES_BY_WEIGHT[r],SUIT_NAMES_BY_WEIGHT[s]);
            ASSERT_EQUAL(false,e<d);
        }
    }
}

//test <=
//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
TEST(test_less_than_equal_basic)
{
    Card a(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card b(Card::RANK_THREE, Card::SUIT_CLUBS);
    Card c(Card::RANK_THREE, Card::SUIT_SPADES);
    Card d(Card::RANK_THREE, Card::SUIT_CLUBS);
    ASSERT_EQUAL(c<=a, true);
    ASSERT_EQUAL(a<=c, false);
    ASSERT_EQUAL(a<=a, true);
    ASSERT_EQUAL(b<=c, false);
    ASSERT_EQUAL(c<=b, true);
    ASSERT_EQUAL(b<=d, true);
    ASSERT_EQUAL(d<=b, true);
}

TEST(test_less_than_equal_edge)
{
    Card e(Card::RANK_TWO, Card::SUIT_SPADES);
    for(int s = 0; s < 4; s++)
    {
        for(int r = 0; r < 13; r++)
        {
            Card f(RANK_NAMES_BY_WEIGHT[r],SUIT_NAMES_BY_WEIGHT[s]);
            ASSERT_EQUAL(true, e<=f);
        }
    }
}

//test >
//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
TEST(test_greater_than_basic)
{
   Card a(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card b(Card::RANK_THREE, Card::SUIT_CLUBS);
    Card c(Card::RANK_THREE, Card::SUIT_SPADES);
    Card d(Card::RANK_THREE, Card::SUIT_CLUBS);
    ASSERT_EQUAL(c>a, false);
    ASSERT_EQUAL(a>c, true);
    ASSERT_EQUAL(a>a, false);
    ASSERT_EQUAL(b>c, true);
    ASSERT_EQUAL(c>b, false);
    ASSERT_EQUAL(b>d, false);
    ASSERT_EQUAL(d>b, false);
}

TEST(test_greater_than_edge)
{
    Card a(Card::RANK_TWO, Card::SUIT_SPADES);
    for(int s = 0; s < 4; s++)
    {
        for(int r = 0; r < 13; r++)
        {
            Card c(RANK_NAMES_BY_WEIGHT[r],SUIT_NAMES_BY_WEIGHT[s]);
            ASSERT_EQUAL(false,a>c);
        }
    }
}

//test >=
//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
TEST(test_greater_than_equal_basic)
{
   Card a(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card b(Card::RANK_THREE, Card::SUIT_CLUBS);
    Card c(Card::RANK_THREE, Card::SUIT_SPADES);
    Card d(Card::RANK_THREE, Card::SUIT_CLUBS);
    ASSERT_EQUAL(c>=a, false);
    ASSERT_EQUAL(a>=c, true);
    ASSERT_EQUAL(a>=a, true);
    ASSERT_EQUAL(b>=c, true);
    ASSERT_EQUAL(c>=b, false);
    ASSERT_EQUAL(b>=d, true);
    ASSERT_EQUAL(d>=b, true);
}

TEST(test_greater_than_equal_edge)
{
    Card a(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    for(int s = 0; s < 4; s++)
    {
        for(int r = 0; r < 13; r++)
        {
            Card c(RANK_NAMES_BY_WEIGHT[r],SUIT_NAMES_BY_WEIGHT[s]);
            ASSERT_EQUAL(true,a>=c);
        }
    }
}

//test ==
//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.

//test != 
//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.


TEST_MAIN()
