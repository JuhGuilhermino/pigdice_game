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
    char draw_ia_actions(){
        ia_action = rand() % 1;
        return ia_action;
    }
};