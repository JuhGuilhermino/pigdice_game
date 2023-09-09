/**
 * @file main.cpp
 *
 * @description
 * This program implements an interactive Pig Dicegame.
 *
 * @author	Júlia Maria A Guilhermino, <juh.guilhermino03@gmail.com>
 * @author  Ludmilla Rodrigues, <ludmillarodr178@gmail.com>
 * @date	September, 2023
 * ====================================================================
 * 
 * This file contains the "Dice" class responsible for all random actions in the game:
 * * Choose the player who will start the game
 * * Roll the dice
 * * Choose the action of the machine
 */

#include <iostream>
#include <string>
#include <vector>
#include <random>
using namespace std;

class Dice {
private:
    int player;
    int dice;
    int ia_action;

public:
    //Choose the player who will start
    int choose_player(int numbers_players) {
        player = rand() % numbers_players;
        return player;
    }

    //Draw a number from 1 to 6
    int roll_dice() {
        dice = rand() % 6 + 1;
        return dice;
    }

    //Draw IA actions: ROOL or HOLD
    // 0 =  HOLD
    // 1 = ROOL
    int draw_ia_actions(){
        ia_action = rand() % 1;
        return ia_action;
    }
};