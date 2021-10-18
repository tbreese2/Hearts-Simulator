// Project UID 1d9f47bfc76643019cfbf037641defe1

//include
#include <iostream>
#include <fstream>
#include "Player.h"
#include "Pack.h"
#include "Card.h"

//helper functions
int strcmp1 (const char *p1, const char *p2)
{ 
    const unsigned char *s1 = (const unsigned char *) p1;
	const unsigned char *s2 = (const unsigned char *) p2;
	unsigned char c1, c2;
	
	do
	{
	    c1 = (unsigned char) *s1++;
	    c2 = (unsigned char) *s2++;
        if (c1 == '\0')
	        return c1 - c2;
	    }
	    while (c1 == c2);
	
	    return c1 - c2;
}

//EFFECTS returns false if arguments are not valid
bool args_not_valid(int argc, char *argv[]) {
    //check arguments for errrors
    if (argc !=12) {
        return 1;
    }
    if (atoi(argv[3]) > 100 || atoi(argv[3]) < 1) {
        return 1;
    }
    if (strcmp1(argv[2],"shuffle") != 0 && strcmp1(argv[2],"noshuffle") != 0) {
        return 1;
    }
    if (strcmp1(argv[5],"Human") != 0 && strcmp1(argv[5],"Simple") != 0) {
        return 1;
    }
    if (strcmp1(argv[7],"Human") != 0 && strcmp1(argv[7],"Simple") != 0) {
        return 1;
    }
    if (strcmp1(argv[9],"Human") != 0 && strcmp1(argv[9],"Simple") != 0) {
        return 1;
    }
    if (strcmp1(argv[11],"Human") != 0 && strcmp1(argv[11],"Simple") != 0) {
        return 1;
    }
    return false;
}

//EFFECTS prints out args to command line
void print_first_line(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        std::cout << argv[i] << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[])
{
    if (args_not_valid(argc,argv)) {
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

    //print first line
    print_first_line(argc, argv);


    //start main game loop
    int team_one_score = 0;
    int team_two_score = 0;
    int hand = 0;

    //create arrays for teams
    int team_one[] = {0,2};
    int team_two[] = {1,3};
    while (team_one_score < atoi(argv[3]) && team_two_score < atoi(argv[3])) {
        //create players
        std::vector<Player *> pArray;
        for (size_t i = 0; i < 4; i++) {
            pArray.push_back(Player_factory(argv[4+(2*i)], argv[5+(2*i)]));
        }

        //shuffle pack
        if (strcmp1(argv[2],"shuffle") == 0) {
            p.shuffle();
        } else {
            p.reset();
        }

        //print out hand number
        std::cout << "Hand " << hand << std::endl;

        //find dealer and announce
        int dealer = hand % 4;
        hand++;
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
                    std::cout << pArray[order_up_player]->get_name() << " orders up " << order_up_suit << std::endl;
                    pArray[dealer]->add_and_discard(up_card);
                    order_up_player = playerNum;
                    break;
                } else {
                    std::cout << pArray[playerNum]->get_name() << " passes" << std::endl;
                }
            }  else if (count < 8) {
                trump_ordered = pArray[playerNum]->make_trump(up_card,playerNum==dealer,2,order_up_suit);
                if (trump_ordered) {
                    std::cout << pArray[order_up_player]->get_name() << " orders up " << order_up_suit << std::endl;
                    order_up_player = playerNum;
                    break;
                }
            }
            count ++;
        }

        std::cout << std::endl;
        
        //initialize trick variables
        int currentLeader = (dealer+1) % 4;
        int team_one_tricks = 0;
        int team_two_tricks = 0;

        //play 5 tricks
        for (int i = 0; i < 5; i++) {
            //initialize vector to hold trick
            std::vector<Card> trick;

            //start by lead player playing
            trick.push_back(pArray[currentLeader]->lead_card(order_up_suit));
            std::cout << trick[0].get_rank() << " of " << trick[0].get_suit() << " led by " << pArray[currentLeader]->get_name() << std::endl;

            //find other three players
            int player2 = (currentLeader+1) % 4;
            int player3 = (currentLeader+2) % 4;
            int player4 = (currentLeader+3) % 4;

            //have other three players play and print what play
            trick.push_back(pArray[player2]->play_card(trick[0], order_up_suit));
            std::cout << trick[1].get_rank() << " of " << trick[1].get_suit() << " played by " << pArray[player2]->get_name() << std::endl;
            trick.push_back(pArray[player3]->play_card(trick[0], order_up_suit));
            std::cout << trick[2].get_rank() << " of " << trick[2].get_suit() << " played by " << pArray[player3]->get_name() << std::endl;
            trick.push_back(pArray[player4]->play_card(trick[0], order_up_suit));
            std::cout << trick[3].get_rank() << " of " << trick[3].get_suit() << " played by " << pArray[player4]->get_name() << std::endl;

            //now find highest card in trick
            Card c = trick[0];
            int playerWHighestCard = currentLeader;
            int playerCount = 0;

            //loop through all cards in trick
            for (size_t ti = 0; ti < 4; ti++) {

                //if card is greator than current highest card,
                //replace c with current card and take note of player
                //with that card
                if (!Card_less(trick[ti],c,trick[0],order_up_suit)) {
                    c = trick[ti];
                    playerWHighestCard = currentLeader + playerCount;
                    playerWHighestCard = playerWHighestCard % 4;
                }

                //increment player count
                playerCount++;
            }

            //print who won the trick
            std::cout << pArray[playerWHighestCard]->get_name() << " takes the trick" << std::endl;

            //assign trick value to apropriate team
            if (playerWHighestCard == 0 || playerWHighestCard == 2) {
                team_one_tricks++;
            } else if (playerWHighestCard == 1 || playerWHighestCard == 3) {
                team_two_tricks++;
            }

            //set leader for next trick
            currentLeader = playerWHighestCard;
            std::cout << std::endl;
        }

        //assign trick value to apropriate team
        if (team_one_tricks > team_two_tricks) {
            std::cout << pArray[team_one[0]]->get_name() << " and " << pArray[team_one[1]]->get_name() << " win the hand" << std::endl;
            if (order_up_player == team_two[0] || order_up_player == team_two[1]) {
                std::cout << "euchred!" << std::endl;
                team_one_score += 2;
            } else {
                if (team_one_tricks == 5) team_one_score += 2;
                else team_one_score += 1;
            }
        } else if (team_one_tricks < team_two_tricks) {
            std::cout << pArray[team_two[0]]->get_name() << " and " << pArray[team_two[1]]->get_name() << " win the hand" << std::endl;
            if (order_up_player == team_one[0] || order_up_player == team_one[1]) {
                std::cout << "euchred!" << std::endl;
                team_two_score += 2;
            } else {
                if (team_two_tricks == 5) team_two_score += 2;
                else team_two_score += 1;
            }
        }

        //print out points for each team
        std::cout << pArray[team_one[0]]->get_name() << " and " << pArray[team_one[1]]->get_name() << " have " << team_one_score << " points" << std::endl;
        std::cout << pArray[team_two[0]]->get_name() << " and " << pArray[team_two[1]]->get_name() << " have " << team_two_score << " points" << std::endl;

        //delete p array
        for (int i = 0; i < int(pArray.size()); ++i) {
            delete pArray[i];
        }
    }

    std::cout << std::endl;
    
    std::vector<Player *> pArray;
    for (size_t i = 0; i < 4; i++) {
        pArray.push_back(Player_factory(argv[4+(2*i)], argv[5+(2*i)]));
    }

    if (team_one_score > team_two_score) {
        std::cout << pArray[team_one[0]]->get_name() << " and " << pArray[team_one[1]]->get_name() << " win!" << std::endl;
    } else if (team_two_score < team_one_score) {
        std::cout << pArray[team_two[0]]->get_name() << " and " << pArray[team_two[1]]->get_name() << " win!" << std::endl;
    }

    //delete p array
    for (int i = 0; i < int(pArray.size()); ++i) {
        delete pArray[i];
    }

    return 0;
}