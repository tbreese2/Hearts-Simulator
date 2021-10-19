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

//MODIFIES each teams tricks taken
//EFFECTS prints out each players discision and the
//number of tricks they take
void play_trick(int &team_one_tricks, int &team_two_tricks, int &currentLeader, std::vector<Player *> &pArray, std::string &order_up_suit) {
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
}

//MODIFIES player array by playing each card in their hands
//EFFECTS prints plays all tricks delt and returns the tricks each player took
std::vector<int> play_tricks(int dealer, std::vector<Player *> &pArray, std::string &order_up_suit) {

    //intialize return vector
    std::vector<int> return_vec;

    //initialize trick variables
    int currentLeader = (dealer+1) % 4;
    int team_one_tricks = 0;
    int team_two_tricks = 0;

    for (int i = 0; i < 5; i++) {
        //call play trick function
        play_trick(team_one_tricks,team_two_tricks,currentLeader,pArray,order_up_suit);

        std::cout << std::endl;
    }

    //capture return values
    return_vec.push_back(team_one_tricks);
    return_vec.push_back(team_two_tricks);
    return return_vec;
}

//REQUIRES team one and two scores point to each teams score
//MODIFIES adds to team scores based on tricks taken
//EFFECTS runs main game loop and returns scores of each player
void score_hand(int &team_one_score, int &team_two_score, std::vector<Player *> &pArray, int team_one_tricks, int team_two_tricks, int order_up_player) {
    //assign trick value to apropriate team
    if (team_one_tricks > team_two_tricks) {
        std::cout << pArray[0]->get_name() << " and " << pArray[2]->get_name() << " win the hand" << std::endl;
        if (order_up_player == 1 || order_up_player == 3) {
            std::cout << "euchred!" << std::endl;
            team_one_score += 2;
        } else {
            if (team_one_tricks == 5){ team_one_score += 2; std::cout << "march!" << std::endl; }
            else team_one_score += 1;
        }
    } else if (team_one_tricks < team_two_tricks) {
        std::cout << pArray[1]->get_name() << " and " << pArray[3]->get_name() << " win the hand" << std::endl;
        if (order_up_player == 0 || order_up_player == 2) {
            std::cout << "euchred!" << std::endl;
            team_two_score += 2;
        } else {
            if (team_two_tricks == 5){team_two_score += 2; std::cout << "march!" << std::endl;}
            else team_two_score += 1;
        }
    }
}

//REQUIRES p is a valid pack and team scores point to scores
//MODIFIES team scores
//EFFECTS runs until the team scores are greater than max points
void play_hand(int &team_one_score, int &team_two_score, int argc, char *argv[], Pack &p, int hand) {
    
    //play hand until
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
                Card a = p.deal_one();
                pArray[playerNum]->add_card(a);
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
                    std::cout << pArray[playerNum]->get_name() << " orders up " << order_up_suit << std::endl;
                    pArray[dealer]->add_and_discard(up_card);
                    order_up_player = playerNum;
                    break;
                } else {
                    std::cout << pArray[playerNum]->get_name() << " passes" << std::endl;
                }
            }  else if (count < 8) {
                trump_ordered = pArray[playerNum]->make_trump(up_card,playerNum==dealer,2,order_up_suit);
                if (trump_ordered) {
                    std::cout << pArray[playerNum]->get_name() << " orders up " << order_up_suit << std::endl;
                    order_up_player = playerNum;
                    break;
                }  else {
                    std::cout << pArray[playerNum]->get_name() << " passes" << std::endl;
                }
            }
            count ++;
        }

        std::cout << std::endl;

        //play 5 tricks
        std::vector<int> team_tricks = play_tricks(dealer,pArray,order_up_suit);

        //score hand
        score_hand(team_one_score,team_two_score,pArray,team_tricks[0],team_tricks[1],order_up_player);

        //print out points for each team
        std::cout << pArray[0]->get_name() << " and " << pArray[2]->get_name() << " have " << team_one_score << " points" << std::endl;
        std::cout << pArray[1]->get_name() << " and " << pArray[3]->get_name() << " have " << team_two_score << " points" << std::endl;

        //delete p array
        for (int i = 0; i < int(pArray.size()); ++i) {
            delete pArray[i];
        }

        std::cout << std::endl;
    }
}


//REQUIRES argc and argv are valid command line arguments from main
//and fin is a file stream of valid pack input file
//EFFECTS runs main game loop and returns scores of each player
std::vector<int> play_game(std::ifstream &fin, int argc, char *argv[]) {
    //create return vector
    std::vector<int> return_vec;

    //create pack
    Pack p(fin);

    //print first line
    print_first_line(argc, argv);

    //initialize variables for main game loop
    int team_one_score = 0;
    int team_two_score = 0;
    int hand = 0;

    //play game
    play_hand(team_one_score,team_two_score,argc,argv,p,hand);
    
    //return team scores
    return_vec.push_back(team_one_score);
    return_vec.push_back(team_two_score);
    return return_vec;
}

//REQUIRES team scores is an array with the score of each team
//so it only has two elements, also requires that argv and
//argc are valid command line arguments
//EFFECTS prints out team that won
void print_winning_team(std::vector<int> &team_scores, int argc, char *argv[]) {
    std::vector<Player *> pArray;
    for (size_t i = 0; i < 4; i++) {
        pArray.push_back(Player_factory(argv[4+(2*i)], argv[5+(2*i)]));
    }

    if (team_scores[0] > team_scores[1]) {
        std::cout << pArray[0]->get_name() << " and " << pArray[2]->get_name() << " win!" << std::endl;
    } else if (team_scores[1] > team_scores[0]) {
        std::cout << pArray[1]->get_name() << " and " << pArray[3]->get_name() << " win!" << std::endl;
    }

    //delete p array
    for (int i = 0; i < int(pArray.size()); ++i) {
        delete pArray[i];
    }
}

int main(int argc, char *argv[]) {
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

    //call main game loop
    std::vector<int> team_scores = play_game(fin,argc,argv);
    
    //decide winner
    print_winning_team(team_scores,argc,argv);

    return 0;
}