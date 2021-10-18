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
        std::string name = argv[5+(2*i)];
        std::string type = argv[6+(2*i)];
        pArray.push_back(Player_factory(name, type));
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
        std::cout << pArray[dealer]->get_name() << " deals";

        //deal cards
        int dealPattern[] = {3,2,3,2,2,3,2,3};
        for (size_t i = 0; i < 2; i++) {

        }

    }

    return 0;
}