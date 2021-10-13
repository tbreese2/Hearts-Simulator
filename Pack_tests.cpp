// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "unit_test_framework.h"

#include <iostream>
#include <fstream>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_NINE, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, first.get_suit());
}

// Add more tests here

//test defualt ctor
TEST(test_pack_default_ctor_edge) {
    Pack p;
    for(int s =0; s < 4; s++) {
        for(int r = 7; r < 13; r++) {
            ASSERT_EQUAL(p.deal_one(), Card(RANK_NAMES_BY_WEIGHT[r],SUIT_NAMES_BY_WEIGHT[s]));
        }
    }
}

//test input ctor
TEST(test_pack_input_ctor_basic) {
    std::ifstream fin;
    fin.open("pack.in");
    Pack p(fin);
    for(int s =0; s < 4; s++) {
        for(int r = 7; r < 13; r++) {
            ASSERT_EQUAL(p.deal_one(), Card(RANK_NAMES_BY_WEIGHT[r],SUIT_NAMES_BY_WEIGHT[s]));
        }
    }
    fin.close();
}

TEST(test_pack_input_ctor_edge) {
    std::istringstream fin;
    fin.str("Jack of Clubs\nAce of Spades");
    Pack p(fin);
    ASSERT_EQUAL(p.deal_one(), Card(Card::RANK_JACK,Card::SUIT_CLUBS));
    ASSERT_EQUAL(p.deal_one(), Card(Card::RANK_ACE,Card::SUIT_SPADES));
}

//deal one
//don't need to test this since eirlier functions already test it

//reset
//i don't think I need to test this, but I will
TEST(test_reset_basic) {
std::istringstream fin;
    fin.str("Jack of Clubs\nAce of Spades");
    Pack p(fin);
    ASSERT_EQUAL(p.deal_one(), Card(Card::RANK_JACK,Card::SUIT_CLUBS));
    ASSERT_EQUAL(p.deal_one(), Card(Card::RANK_ACE,Card::SUIT_SPADES));
    p.reset();
    ASSERT_EQUAL(p.deal_one(), Card(Card::RANK_JACK,Card::SUIT_CLUBS));
}
TEST_MAIN()
