// Project UID 1d9f47bfc76643019cfbf037641defe1

//include
#include <iostream>
#include <fstream>
#include "Player.h"
#include "Pack.h"
#include "Card.h"

int main(int argc, char *argv[])
{
    //check arguments for errrors
    if (argc !=12) {
        std::cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << std::endl;
        return 1;
    }
    if (atoi(argv[3]) > 100 || atoi(argv[3]) < 1) {
        std::cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << std::endl;
        return 1;
    }
    if (strcmp(argv[2],"shuffle") != 0 && strcmp(argv[2],"noshuffle") != 0) {
        std::cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << std::endl;
        return 1;
    }
    if (strcmp(argv[5],"Human") != 0 && strcmp(argv[5],"Simple") != 0) {
        std::cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << std::endl;
        return 1;
    }
    if (strcmp(argv[7],"Human") != 0 && strcmp(argv[7],"Simple") != 0) {
        std::cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << std::endl;
        return 1;
    }
    if (strcmp(argv[9],"Human") != 0 && strcmp(argv[9],"Simple") != 0) {
        std::cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << std::endl;
        return 1;
    }
    if (strcmp(argv[11],"Human") != 0 && strcmp(argv[11],"Simple") != 0) {
        std::cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << std::endl;
        return 1;
    }

    //open file
    std::ifstream fin;
    fin.open(argv[1]);
    if (!fin.is_open()) {
        std::cout << "Error opening " << argv[1] << std::endl;
        return 1;
    }

    //create pack
    Pack p(fin);

    //create players
    std::vector<Player *> pArray;
    for (size_t i = 0; i < 4; i++) {
        pArray.push_back(Player_factory(argv[4+(2*i)], argv[5+(2*i)]));
    }

    //print first line
    for (int i = 0; i < argc; i++) {
        std::cout << argv[i] << " ";
    }
    std::cout << std::endl;


    //start main game loop
    int score = 0;
    int hand = 0;
    while (score < atoi(argv[3])) {

        //shuffle pack
        if (strcmp(argv[2],"shuffle") == 0) {
            p.shuffle();
        }
        p.reset();

        //print out hand number
        std::cout << "Hand " << hand << std::endl;
        hand++;

        //find dealer and announce
        int dealer = hand % 4;
        std::cout << pArray[dealer]->get_name() << " deals" << std::endl;

        //set variables to deal cards
        int dealPattern[] = {3,2,3,2,2,3,2,3};
        int dealPatternI = 0;

        //loop through players starting with player to the left of dealer
        for (size_t i = dealer+1; i < dealer+9; i++) {

            //get player number
            int playerNum = i % 4;

            //deal specific number of cards based on the deal pattern
            for (int c = 0; c < dealPattern[dealPatternI]; c++) {
                pArray[playerNum]->add_card(p.deal_one());
            }

            //increment deal pattern
            dealPatternI++;
        }

        //deal upcard
        Card up_card = p.deal_one();

        //print upcard
        std::cout << up_card.get_rank() << " of " << up_card.get_suit() << " turned up" << std::endl;
        
        //loop through players to establish trump
        int count = 0;
        bool trump_ordered = false;
        std::string order_up_suit = " ";
        int order_up_player = 0;

        //loop through players starting with player to the left of dealer
        for (size_t i = dealer+1; i < dealer+9; i++) {
            //get player number
            int playerNum = i % 4;

            //offer players chance to make upcard during first round
            if (count < 4) {
                trump_ordered = pArray[playerNum]->make_trump(up_card,playerNum==dealer,1,order_up_suit);
                if (trump_ordered) {
                    pArray[dealer]->add_and_discard(up_card);
                    order_up_player = playerNum;
                    break;
                }
            }  else if (count < 8) {
                trump_ordered = pArray[playerNum]->make_trump(up_card,playerNum==dealer,1,order_up_suit);
                if (trump_ordered) {
                    order_up_player = playerNum;
                    break;
                }
            }
            count ++;
        }
        
        //initialize trick variables
        int currentLeader = (dealer+1) % 4;

        //play 5 tricks
        for (int i = 0; i < 5; i++) {
            //initialize vector to hold trick
            std::vector<Card> trick;

            //start by lead player playing
            trick.push_back(pArray[currentLeader]->lead_card(order_up_suit));

            //find other three players
            int player2 = (currentLeader+1) % 4;
            int player3 = (currentLeader+2) % 4;
            int player4 = (currentLeader+3) % 4;

            //have other three players play
            pArray[player2]->play_card(trick[0], order_up_suit);
            pArray[player3]->play_card(trick[0], order_up_suit);
            pArray[player4]->play_card(trick[0], order_up_suit);

            //now find highest card in trick
            Card c = trick[0];
            int playerWHighestCard = currentLeader;
            int playerCount = 0;

            //loop through all cards in trick
            for (size_t ti = 0; ti < 4; ti++) {

                //if card is greator than current highest card,
                //replace c with current card and take note of player
                //with that card
                if (Card_less(c,trick[ti],trick[0],order_up_suit)) {
                    c = trick[ti];
                    playerWHighestCard = currentLeader + playerCount;
                    playerWHighestCard = playerWHighestCard % 4;
                }

                //increment player count
                playerCount++;
            }
        }


    }

    return 0;
}